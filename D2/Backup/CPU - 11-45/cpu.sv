/////////////////////////////////////////////////////////////////////
// Design unit: CPU
//            :
// File name  : cpu.sv
//            :
// Description: Top level of basic processor
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

module CPU #(parameter WORD_W = 8, OP_W = 3)
                  (input logic clock, n_reset, SW,
						 output logic RAM_NOE, RAM_NCE, RAM_NWE, LED,
                   inout wire [WORD_W-1:0] sysbus,
						 output logic [WORD_W - OP_W - 1:0] addrbus);
		   
logic ACC_bus, load_ACC, PC_bus, load_PC, load_IR, ALU_ACC, ALU_add, ALU_sub, INC_PC,
Addr_bus, z_flag, load_MAR/*, ALU_lshift*//*, ALU_rshift*/;

logic [OP_W-1:0] op;

sequencer #(.WORD_W(WORD_W), .OP_W(OP_W)) s1  (.*);

IR #(.WORD_W(WORD_W), .OP_W(OP_W)) i1  (.*);

PC #(.WORD_W(WORD_W), .OP_W(OP_W)) p1 (.*);

ALU #(.WORD_W(WORD_W), .OP_W(OP_W)) a1 (.*);

RAM #(.WORD_W(WORD_W), .OP_W(OP_W)) r1 (.*);

endmodule