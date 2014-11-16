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
               (input logic clock, n_reset, MDR_bus, load_MDR, load_MAR, CS, R_NW,
                inout wire [WORD_W-1:0] sysbus);

`include "opcodes.h"
		
logic [WORD_W-1:0] mdr;
logic [WORD_W-OP_W-1:0] mar;
logic [WORD_W-1:0] mem [0:(1<<(WORD_W-OP_W))-1];
int i;

assign sysbus = MDR_bus ? mdr : {WORD_W{1'bZ}};

always_ff @(posedge clock, negedge n_reset)
  begin
  if (~n_reset)
    begin 
    mdr <= 0;
    mar <= 0;
    mem[0] <= {`LOAD, {(WORD_W-OP_W-3){1'b0}},3'd4};
    mem[1] <= {`ADD, {(WORD_W-OP_W-3){1'b0}},3'd5};
    mem[2] <= {`STORE,{(WORD_W-OP_W-3){1'b0}},3'd6};
    mem[3] <= {`BNE, {(WORD_W-OP_W-3){1'b0}},3'd7};
    mem[4] <= 2;
    mem[5] <= 2;
    mem[6] <= 0;
    mem[7] <= 0;
    for (i = 8; i < (1<<(WORD_W-OP_W));  i+=1)
      mem[i] <= 0;
    end
  else
    if (load_MAR)
      mar <= sysbus[WORD_W-OP_W-1:0];
    else if (load_MDR)
      mdr <= sysbus;
    else if (CS)
      if (R_NW)
        mdr <= mem[mar];
      else
        mem[mar] <= mdr;
  end
endmodule