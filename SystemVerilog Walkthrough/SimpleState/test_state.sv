module test_state();
  logic clock, A, Y;
  state s(.*);
  always
    begin
      clock = '0;
      #25ns clock = '1;
      #25ns clock = '0;
    end
  initial
    begin
      A = '0;
      #100ns A = '1;
      #100ns A = '0;
      #100ns A = '1;
    end
endmodule
