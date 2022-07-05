`timescale 1ns/1ps

module Hazard (PCSource1, IsBranch2, Rs1, Rt1, Rs2, Rt2, MemRead2, RegWr2, RegWrAddr2, PCWrite, Conf1, Conf2);
    input [1:0] PCSource1;
    input IsBranch2;
    input [4:0] Rs1;
    input [4:0] Rt1;
    input [4:0] Rs2;
    input [4:0] Rt2;
    input MemRead2;
    input RegWr2;
    input [4:0] RegWrAddr2;
    output PCWrite;
    output [1:0] Conf1;
    output [1:0] Conf2;

    assign LOAD_USE = MemRead2 && (Rt2 == Rs1 || Rt2 == Rt1);
    assign BRANCH = IsBranch2;
    // assign JUMP = (PCSource1 == 2'b01) || (PCSource1 == 2'b10 && (!RegWr2 || (RegWrAddr2 != Rs1)));
    assign JUMP = 0;
    assign JUMP_HAZARD = PCSource1 == 2'b10 && RegWr2 && RegWrAddr2 == Rs1;

    assign PCWrite = (LOAD_USE || JUMP_HAZARD) ? 1'b0 : 1'b1;
    assign Conf1 = (BRANCH || JUMP) ? 2'b10 : (LOAD_USE || JUMP_HAZARD ? 2'b01 : 2'b00);
    assign Conf2 = (LOAD_USE || BRANCH || JUMP_HAZARD) ? 2'b10 : 2'b00;
    
endmodule