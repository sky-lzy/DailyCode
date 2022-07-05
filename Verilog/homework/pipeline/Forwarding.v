`timescale 1ns/1ps

module Forwarding (Rs1, Rs2, Rt2, RegWr3, RegWrAddr3, RegWr4, RegWrAddr4, ALUSrcA, ALUSrcB, JumpConf);
    input [4:0] Rs1;
    input [4:0] Rs2;
    input [4:0] Rt2;
    input [4:0] RegWrAddr3;
    input [4:0] RegWrAddr4;
    input RegWr3;
    input RegWr4;
    output [1:0] ALUSrcA;
    output [1:0] ALUSrcB;
    output JumpConf;

    assign ALUSrcA = (RegWr3 && (RegWrAddr3 != 5'b0) && (RegWrAddr3 == Rs2)) ? 2'b01 : ((RegWr4 && (RegWrAddr4 != 5'b0) && (RegWrAddr4 == Rs2)) ? 2'b10 : 2'b00);
    assign ALUSrcB = (RegWr3 && (RegWrAddr3 != 5'b0) && (RegWrAddr3 == Rt2)) ? 2'b01 : ((RegWr4 && (RegWrAddr4 != 5'b0) && (RegWrAddr4 == Rt2)) ? 2'b10 : 2'b00);
    assign JumpConf = (RegWr3 && (RegWrAddr3 != 5'b0) && (RegWrAddr3 == Rs1)) ? 1'b1 : 1'b0;

endmodule