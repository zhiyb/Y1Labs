// simple counter for X6
module counter(
  input logic clk, n_reset, up, down,
  output logic [3:0] volume);
  
  always_ff @ (posedge clk, negedge n_reset)
  if (~n_reset)
    volume <= 0;
  else if (up)
    begin
    if (volume != 15)
      volume <= volume + 1;
    end
  else if (down)
    begin
    if (volume != 0)
      volume <= volume - 1;
    end

endmodule
