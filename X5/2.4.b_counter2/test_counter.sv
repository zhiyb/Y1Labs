module test_counter();
  logic clk, n_reset, up, down;
  logic [3:0] volume;
  counter c(.*);
  
  always
    begin
      clk = 0;
      #10ns clk = 1;
      #10ns clk = 0;
    end
    
  initial
    begin
      n_reset = 0;
      up = 1;
      down = 0;
      #50ns n_reset = 1;
      #50ns up = 0;
      #50ns down = 1;
      #50ns up = 1;
    end
endmodule
