module volume_asm(
  input logic up, down, n_reset, clk,
  output logic increment, decrement
);
  enum {none, uppress, uppressed, downpress, downpressed} state, next;

  always_ff @ (posedge clk)
  if (~n_reset)
    state = none;
  else
    state = next;

  always_comb
    case (state)
    uppress:
      begin
      increment = '1;
      next = uppressed;
      end
    uppressed:
      begin
      increment = '0;
      if (up)
        next = uppressed;
      else
        next = none;
      end
    downpress:
      begin
      decrement = '1;
      next = downpressed;
      end
    downpressed:
      begin
      decrement = '0;
      if (down)
        next = downpressed;
      else
        next = none;
      end
    default:
      begin
      increment = '0;
      decrement = '0;
      if (up)
        next = uppress;
      else if (down)
        next = downpress;
      else
        next = none;
      end
    endcase
endmodule
