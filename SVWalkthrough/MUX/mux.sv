//-----------------------------------------------------
// Simple 2-to-1 mux
// File Name  - mux.sv
// Last revised - 10 Feb 2009
// Author - tjk
//-----------------------------------------------------
module  mux(
input  logic[1:0]  din  , // Mux data input
input  logic  sel       , // Select input
output logic  dout        // Mux data output
);
//------------- mux behaviour ---------
always_comb // infers combinational logic
  if (sel == 1'b0)
      dout = din[0];
  else 
      dout = din[1] ;

endmodule //End Of Module mux

