// simple counter for X6
module counter(
  input logic clk, n_reset,
  output logic [3:0] volume);
  
  always_ff @ (posedge clk, negedge n_reset)
  if (~n_reset)
    volume <= 0;
  else
    volume <= volume + 1;

endmodule
