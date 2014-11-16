module test_starter ;

// This file is the testbench for starter.sv

/*  Provides stimulus for inspection of starter functionality
    Also includes simplistic stimulus for all PlayBus functions
    Absolutely NO checks for CORRECT functionality anywhere. */

// Last edit TMF 2009 May 14
//corrected MZ 2012 Nov 16

logic CK2HZ , GO , n_CLR ;
logic [3:0] ADD ;
logic [2:0] FUNC ;

logic n_ROMO , n_RAMO , n_RAMW , n_SWBEN , LEDLTCH, DUMMY ;
logic [1:0] St ;

initial
   begin
   CK2HZ = '0 ;
   forever #250ns CK2HZ = ~CK2HZ ;  // perpetual 2Hz clock
   /*   modelled as a 2MHz clock for simulation,
        to keep simulation length within bounds */
   end

initial
   begin
   n_CLR = '1 ;
   #1ns n_CLR = '0 ;                // Power-on reset
   #10ns n_CLR = '1 ;
   end

initial
   begin
   GO = '0 ;
   ADD = 0 ;
   FUNC = 0 ;
   #1.1us FUNC = 5 ;   // NOT co-incident with clock edge
   /*   All subsequent stimulus changes are at intervals of
        multiples of clock period, therefore are also
        not coincident with clock edges. */
   #1us GO = '1 ;
   #3us GO = '0 ;
   #1us FUNC = 0 ;
   #500ns GO = '1 ;   // Check that GO is ignored
   #500ns GO = '0 ;
   #1us FUNC = 1 ;
   #500ns GO = '1 ;   // Check that GO is ignored
   #500ns GO = '0 ;
   #1us FUNC = 2 ;
   #500ns GO = '1 ;   // Check that GO is ignored
   #500ns GO = '0 ;
   #500ns FUNC = 3 ;
   #500ns GO = '1 ;   // Should initiate new function
   #3us GO = '0 ;
   #500ns FUNC = 4 ;
   #500ns GO = '1 ;   // Should initiate new function
   #3us GO = '0 ;
   #500ns FUNC = 5 ;
   #500ns GO = '1 ;   // Should initiate new function
   #3us GO = '0 ;
   #500ns FUNC = 6 ;
   #500ns GO = '1 ;   // Should initiate new function
   #3us GO = '0 ;
   #500ns FUNC = 7 ;
   #500ns GO = '1 ;   // Should initiate new function
   #3us GO = '0 ;
   #500ns FUNC = 0 ;
   #500ns ADD = 1 ;
   #500ns ADD = 2 ;
   #500ns ADD = 3 ;
   #500ns ADD = 4 ;
   #500ns ADD = 5 ;
   #500ns ADD = 6 ;
   #500ns ADD = 7 ;
   #500ns ADD = 8 ;
   #500ns ADD = 9 ;
   #500ns ADD = 10 ;
   #500ns ADD = 11 ;
   #500ns ADD = 12 ;
   #500ns ADD = 13 ;
   #500ns ADD = 14 ;
   #500ns ADD = 15 ;
   #500ns ADD = 0 ;
   end
    
starter d0 (.*) ;   // magic incantation

endmodule