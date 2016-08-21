module starter (input logic CK2HZ ,  GO , n_CLR ,
	input logic [3:0] ADD ,
	input logic [2:0] FUNC ,
    output logic n_ROMO , n_RAMO , n_RAMW , n_SWBEN , LEDLTCH , DUMMY ,
	output logic [1:0] St ) ;


// This file is starter.sv
/* It provides guaranteed correct operation for PlayBus
   functions 0 (read ROM) and 5 (copy switches to LEDs).
   It can also be used as a template for developing full
   PlayBus functionality. */

// Author Tim Forcer

// Last edit 2012 November 27

/* Note that the state machine used here has explicitly-designated
   state values and explicitly-designated state registers, with the
   latter providing system outputs.  This is NOT standard practice,
   but is applied so as to allow the state machine to be monitored
   at all times using the PlayBus fixed connections */

logic RAMW ;    
/*  This avoids synthesis problems whereby Synplify generates an
    EDIF file which specifies an asynchronous PREset for n_RAMW,
    which has been optimised to use a NON-inverting macrocell output,
    whereas what is required is asynchronous RESET of an
    INVerting macrocell output. */
    
logic next_RAMW, next_LEDLTCH ;
logic [1:0] next_St ;

parameter idle_static = 0 , start_source = 1 , do_write = 2 , end_dynamic = 3 ;
// Descriptive state names 

always_ff

@ (posedge CK2HZ, negedge n_CLR)

    begin: SEQ

    if (~n_CLR)
     begin
   	  St <= 0 ;       // will also clear all other registered outputs
		  RAMW <= 0 ;     // but this needs to be stated explicitly
		  LEDLTCH <= 0 ;  // for the other registered outputs
	   end

    else
      begin
        St <= next_St ;
        RAMW <= next_RAMW ;
        LEDLTCH <= next_LEDLTCH ;
      end
  end

always_comb

    begin: COM

    // default assignments
    n_RAMO = 1 ;
    n_ROMO = 1 ;
    n_SWBEN = 1 ;
    
    next_St = idle_static ;
    next_RAMW = 0 ;
    next_LEDLTCH = 0 ;
    
	  DUMMY = (ADD == 2) ;    // Stops address bus being optimised away to nothing

    n_RAMW = ~RAMW ;        // To achieve correct pin function
    // DO NOT MAKE ANY OTHER ASSIGNMENT TO n_RAMW!
    
    case (St)
        idle_static: // static functions and, for dynamic functions, wait for GO
            begin
                if (FUNC == 0) n_ROMO = 0;
                else if (FUNC == 1) n_RAMO = 0;
                else if (FUNC == 2) n_SWBEN = 0;
                else if ((FUNC == 5) & (GO == 1)) next_St = start_source ;
            end

        start_source:  /* Enable data source for dynamic functions,
                       prepare data sinks to take data from bus.
                       Assignments to RAMW and LEDLTCH defined here
                       occur on the first clock edge AFTER entering
                       this state, when their next_X values are transferred
                       to the latched outputs */
            begin
                if (FUNC == 5)
                  begin
                    n_SWBEN = 0 ;
                    next_LEDLTCH = 1 ;
                    next_St = do_write ;
                  end 
            end

        do_write:   /* Keep data source enabled while sink writes data,
                    set up for data sink to stop taking data from bus.
                    Assignments to RAMW and LEDLTCH defined here
                    occur on the first clock edge AFTER entering
                    this state.
                    In this state, the RAM and LED latch data sinks will
                    have the values set by their next_X values in the
                    previous state */
            begin
                if (FUNC == 5)
                  begin
                    n_SWBEN = 0 ;
                    next_St = end_dynamic ;
                  end
            end

        end_dynamic: /* Keep data source enabled in case data needs
                     a hold time after end of write to sink.
                    Assignments to RAMW and LEDLTCH defined here
                    occur on the first clock edge AFTER entering
                    this state.
                    In this state, the RAM and LED latch data sinks will
                    have the values set by their next_X values in the
                    previous state
                    Wait for GO to be inactive before returning to idle,
                    so that a second write sequence isn't inadvertently
                    initiated. */
                     
            begin 
                if ((FUNC == 5) & (GO == 1) )
                  begin
                    n_SWBEN = 0 ;
                    next_St = end_dynamic ;
                  end
                else 
                  begin
                    next_St = idle_static ;
                    if (FUNC == 5) n_SWBEN = 0 ;
                  end
            end
    endcase
end
endmodule
