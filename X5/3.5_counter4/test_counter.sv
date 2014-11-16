module test_counter();
  logic clk, n_reset, up, down, mode;
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
      mode = 0;
      #50ns n_reset = 1;
      #500ns up = 0;
      #500ns down = 1;
      #500ns up = 1;
      #500ns mode = 1;
      #500ns up = 0;
      #500ns down = 1;
      #500ns up = 1;
    end
endmodule
