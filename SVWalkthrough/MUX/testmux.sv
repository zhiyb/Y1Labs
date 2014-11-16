// 2-1 mux testbench ----------------------------------
// File name - testmux.sv
// Last revised - 16 Feb 2009
// Author - tjk
//-----------------------------------------------------

module testmux;
    logic[1:0] din;
    logic sel, dout;
    // invoke an instance of the mux
    mux m (.*); // .* syntax for port mapping works
                // if testbench and mux use the same signal names

    initial
    begin
        din <= 2'b01;
        sel <= 1'b0;
        #25ns sel <= '1;
        #25ns din <= 2'b11;
        #25ns din <= 2'b10;
        #50ns sel <= '0;
        
    end
endmodule   // End of Module testmux ----------------