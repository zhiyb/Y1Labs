module test();
  logic clk, n_reset, up, down, mode;
  logic [3:0] volume;
  volume v(.*);
  
  always
    begin
      clk = 0;
      #10ns clk = 1;
      #10ns clk = 0;
    end
    
  initial
    begin
      n_reset = 0;
      up = 0;
      down = 0;
      mode = 1;
      #40ns n_reset = 1;
      #40ns up = 1;
      #40ns up = 0;
      #40ns up = 1;
      #40ns up = 0;
      #40ns down = 1;
      #40ns down = 0;
      #40ns down = 1;
      #40ns down = 0;
      #40ns down = 1;
      #40ns down = 0;
      forever
      begin
        #40ns up = 1;
        #40ns up = 0;
      end
    end
endmodule
