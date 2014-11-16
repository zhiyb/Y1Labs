/////////////////////////////////////////////////////////////////////
// Design unit: sequencer
//            :
// File name  : sequencer.sv
//            :
// Description: Sequencer for basic processor
//            :
// Limitations: None
//            : 
// System     : SystemVerilog IEEE 1800-2005
//            :
// Author     : Mark Zwolinski
//            : School of Electronics and Computer Science
//            : University of Southampton
//            : Southampton SO17 1BJ, UK
//            : mz@ecs.soton.ac.uk
//
// Revision   : Version 1.0 05/08/08
//            : Version 1.1 17/12/13
/////////////////////////////////////////////////////////////////////

module sequencer #(parameter WORD_W = 8, OP_W = 3)
                          (input logic clock, n_reset, z_flag, SW,
                           input logic [OP_W-1:0] op,
                           output logic ACC_bus, load_ACC, PC_bus, load_PC,
                                        load_IR, load_MAR, Addr_bus,
                                        ALU_ACC, ALU_add, ALU_sub, INC_PC,
                                        RAM_NCE, RAM_NOE, RAM_NWE, LED/*,
													 ALU_lshift*//*, ALU_rshift*/);
	
`include "opcodes.h"	

typedef enum {s0, s1, s3, s5, s6} state_type;
(* syn_encoding="sequential" *)
state_type Present_State, Next_State;

always_ff @(posedge clock, negedge n_reset)
  begin: seq
    if (~n_reset)
      Present_State <= s0;
    else
      Present_State <= Next_State;
    end

always_comb
  begin: com
  // reset all the control signals to default
  ACC_bus = 1'b0;
  load_ACC = 1'b0;
  PC_bus = 1'b0;
  load_PC = 1'b0;
  load_IR = 1'b0;
  load_MAR = 1'b0;
  ALU_ACC = 1'b0;
  ALU_add = 1'b0;
  ALU_sub = 1'b0;
  INC_PC = 1'b0;
  Addr_bus = 1'b0;
  RAM_NCE = 1'b1;
  RAM_NOE = 1'b1;
  RAM_NWE = 1'b1;
  //ALU_lshift = 1'b0;
  //ALU_rshift = 1'b0;
  LED = 1'b0;
  Next_State = Present_State;
  case (Present_State)
    s0: begin	// Read next instruction
         PC_bus = 1'b1;
         load_MAR = 1'b1;
         INC_PC = 1'b1;
         load_PC = 1'b1;
         Next_State = s1;
         end
    s1: begin	// Read
         RAM_NCE = 1'b0;
			RAM_NOE = 1'b0;
         load_IR = 1'b1;
         Next_State = s3;
         end
    s3: begin
         Addr_bus = 1'b1;
         load_MAR = 1'b1;
         if (op == `STORE)
				Next_State = s5;
			else if (op == `LED)
				begin
				LED = SW;
				Next_State = s3;
				end
         else
           Next_State = s6;
         end
    s5: begin	// Store
			ACC_bus = 1'b1;
			RAM_NOE = 1'b1;
			RAM_NCE = 1'b0;
			RAM_NWE = 1'b0;
         Next_State = s0;
         end
    s6:	begin
			RAM_NOE = 1'b0;
			RAM_NCE = 1'b0;
			RAM_NWE = 1'b1;
			Next_State = s0;
			if (op == `BNE)
				begin
				if (z_flag == 1'b0)
					load_PC = 1'b1;
				end
			else
				begin
				load_ACC = 1'b1;
				if (op != `LOAD)
					begin
					ALU_ACC = 1'b1;
					if (op == `ADD)
						ALU_add = 1'b1;
					else if (op == `SUB)
						ALU_sub = 1'b1;
					//else if (op == `LSHIFT)
						//ALU_lshift = 1'b1;
					//else if (op == `RSHIFT)
						//ALU_rshift = 1'b1;
					end
				end
			end
  endcase
  end

endmodule