module state(input logic clock, A, output logic Y);
  enum {S1, S2} states;
  
  always_ff @(posedge clock)
    if (A == 1)
      states = S1;
    else
      states = S2;
    
  always_comb
    case (states)
    S1:
      Y = '0;
    S2:
      Y = '1;
    default:
      Y = 'x;
    endcase
endmodule
