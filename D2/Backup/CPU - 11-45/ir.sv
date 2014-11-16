/////////////////////////////////////////////////////////////////////
// Design unit: IR
//            :
// File name  : ir.sv
//            :
// Description: Instruction register for basic processor
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

module IR  #(parameter WORD_W = 8, OP_W = 3)
             (input logic clock, n_reset, Addr_bus, load_IR,
              inout wire [WORD_W-1:0] sysbus,
              output logic [OP_W-1:0] op);
	      
logic  [WORD_W-1:0] instr_reg;

assign sysbus = Addr_bus ?
{{OP_W{1'b0}},instr_reg[WORD_W-OP_W-1:0]} :
{WORD_W{1'bZ}};

assign op = instr_reg[WORD_W-1:WORD_W-OP_W];

always_ff @(posedge clock, negedge n_reset)
  begin
  if (~n_reset)
    instr_reg <= 0;
  else
    if (load_IR)
      instr_reg <= sysbus;
  end
endmodule