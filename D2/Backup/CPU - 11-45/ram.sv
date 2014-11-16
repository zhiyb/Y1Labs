/////////////////////////////////////////////////////////////////////
// Design unit: RAM
//            :
// File name  : ram.sv
//            :
// Description: Synchronous RAM for basic processor
//            : including loading of simple program at reset
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

module RAM #(parameter WORD_W = 8, OP_W = 3)
               (input logic clock, n_reset, load_MAR,
					 inout wire [WORD_W - 1:0] sysbus,
					 output logic [WORD_W - OP_W - 1:0] addrbus);
					 
logic [WORD_W - OP_W - 1:0] mar;

assign addrbus = mar;

always_ff @(posedge clock, negedge n_reset)
	if (~n_reset)
		mar <= 0;
	else if (load_MAR)
		mar <= sysbus[WORD_W - OP_W - 1:0];

endmodule
