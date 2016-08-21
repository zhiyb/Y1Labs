// state machine to recognise bit pattern 101
// Mealy version
// File name: bitpatternsm.sv
// Last modified: 16/02/09
// Author: tjk

module bitpatternsm(
input logic inp, clock, nreset,
output logic outp
);

// ----------- local declarations -------
typedef enum logic[1:0] {start, cycle1, cycle2, unused} states;

states state,next; // local signals for present and next state

// fsm behaviour consists of two processes,
// one for the memory and one for combinational logic

// always_ff process implements the flip-flops
// the process is sensitive to pve clock edge and async reset
always_ff@(posedge clock or negedge nreset)
    if (~nreset) // active low asynchronous reset
        state <= start;
    else 
        state <= next; 

// combinational logic process, implements both next state and output
always_comb
    case(state)
    start: //behaviour in state start 
	    begin
        outp <= '0;
        if(inp) 
	        next <= cycle1; // first bit is 1
        else 
	        next <= start;
    end

	cycle1:  // behaviour in state cycle1
	    begin
        outp <= '0;
        if(inp) 
	        next <= cycle1; // first bit, stay in cycle1
        else 
	        next <= cycle2; // second bit = 0
    end
	
	cycle2:  // behaviour in state cycle2
	    begin
        outp <= inp;    // assert output if inp==1 (third bit)
	                    // nb. this is Mealy behaviour; why?
        next <= start;  // start over again
     end

	unused: // unused state, proceed to start
        begin
            outp <= '0;
            next <= start;
    end
  endcase	  
	  
endmodule // End of Module bitpatternsm
