// testbench for bit pattern recogniser ------------------------
// File name: bitpatternsm_test.sv
// Last modified: 16/02/09
// Author: tjk
// ------------------------------
module bitpatternsm_test();

// declare signals for fsm ports
logic inp, clock, nreset, outp;

bitpatternsm  sm (.*); // create fsm instance
always // clock process
begin
clock = 0;
#50ns clock = 1;
#50ns clock = 0;
end

initial // test the machine
begin
    inp= 0;
    nreset = 0; // assert reset

    #100ns nreset = 1; // remove reset
    #100ns inp = 1; // first bit
    #100ns inp = 0; // 2nd bit
    #100ns inp = 1; // 3rd bit
    #100ns inp = 0; //
end
endmodule // End of module bitpatternsm_test