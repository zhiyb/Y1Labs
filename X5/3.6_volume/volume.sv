module volume(
  input logic clk, n_reset, up, down, mode,
  output logic [3:0] volume);

  logic inc, dec;

  volume_asm fsm(up, down, n_reset, clk, inc, dec);
  counter c(clk, n_reset, inc, dec, mode, volume);
endmodule