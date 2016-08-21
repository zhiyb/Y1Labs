/////////////////////////////////////////////////////////////////////
// Design unit: 
//            :
// File name  : opcodes.h
//            :
// Description: include file with opcode definition for basic processor
//            :
// Limitations: None
//            : 
// System     : SystemVerilog IEEE 1800-2005
//            :
// Author     : Mark Zwolinski
//            : School of Electronics and Computer Science
//            : University of Southampton
//            : Southampton SO17 1BJ, UK
//            : mz@ecs.soton.ac.uk
//
// Revision   : Version 1.0 05/08/08
//            : Version 1.1 17/12/13
/////////////////////////////////////////////////////////////////////

`define LOAD	3'b000
`define STORE	3'b001
`define ADD		3'b010
`define SUB		3'b011
`define BNE		3'b100
`define LSHIFT	3'b101
`define RSHIFT	3'b110
`define EXTRA	3'b111

// Extra op codes
`define LED		3'b000
`define MOD2	3'b001
