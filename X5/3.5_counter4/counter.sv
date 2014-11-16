// simple counter for X6
module counter(
  input logic clk, n_reset, up, down, mode,
  output logic [3:0] volume);
  
  always_ff @ (posedge clk, negedge n_reset)
  begin
  if (~n_reset)
    volume <= 0;
  else
    begin
    if (mode)
      case (volume)
      10: volume <= 9;
      11: volume <= 9;
      12: volume <= 9;
      13: volume <= 9;
      14: volume <= 9;
      15: volume <= 9;
      endcase
    if (up)
      begin
      if (mode)
        begin
        if (volume != 9)
          volume <= volume + 1;
        end
      else if (volume != 15)
        volume <= volume + 1;
      end
    else if (down)
      begin
      if (volume != 0)
        volume <= volume - 1;
      end
    end
  end

endmodule
