/////////////////////////////////////////////////////////////////////
// Design unit: ALU
//            :
// File name  : alu.sv
//            :
// Description: ALU for basic processor
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

module ALU #(parameter WORD_W = 8, OP_W = 3)
                   (input logic clock, n_reset, ACC_bus, load_ACC, ALU_ACC,
										  ALU_add, ALU_sub, ALU_lshift, ALU_rshift, ALU_mod2,
                    inout wire [WORD_W-1:0] sysbus,
                    output logic z_flag);
		    
logic [WORD_W-1:0] acc;

assign sysbus = ACC_bus ? acc : {WORD_W{1'bZ}};
assign z_flag = acc == 0 ? 1'b1 :1'b0;

always_ff @(posedge clock, negedge n_reset)
  begin
  if (~n_reset)
    acc <= 0;
  else
    if (load_ACC)
		begin
		if (ALU_mod2)
			acc <= {{(WORD_W - 1){1'b0}},acc[0:0]};
      else if (ALU_ACC)
        begin
        if (ALU_add)
          acc <= acc + sysbus;
        else if (ALU_sub)
          acc <= acc - 1;//acc - sysbus;
		  else if (ALU_lshift)
			 acc <<= 1;//sysbus;
		  else if (ALU_rshift)
			 acc >>= 1;//sysbus;
		  end
      else
        acc <= sysbus;
		end
  end
endmodule