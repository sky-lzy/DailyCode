`timescale 1ns/1ps

module Controller (OpCode, Funct, PCSource, Branch, RegWrite, RegDst, MemRead, MemWrite, MemtoReg, ALUSrc1, ALUSrc2, ExtOp, LuiOp, LbuOp);
    //Input Signals
    input  [5:0] OpCode;
    input  [5:0] Funct;
    //Output Signals
    output [1:0] PCSource;
    output Branch;
    output RegWrite;
    output [1:0] RegDst;
    output MemRead;
    output MemWrite;
    output [1:0] MemtoReg;
    output ALUSrc1;
    output ALUSrc2;
    output ExtOp;
    output LuiOp;
    output LbuOp;

	assign PCSource[0] = (OpCode == 6'h02 || OpCode == 6'h03) ? 1'b1 : 1'b0;
	assign PCSource[1] = (OpCode == 6'h0 && (Funct == 6'h08 || Funct == 6'h09)) ? 1'b1 : 1'b0;
	assign Branch = (OpCode == 6'h01 || OpCode == 6'h04 || OpCode == 6'h05 || OpCode == 6'h06 || OpCode == 6'h07) ? 1'b1 : 1'b0;
	assign RegWrite = (OpCode == 6'h2b || OpCode == 6'h02 || (OpCode == 6'h0 && Funct == 6'h08) || Branch) ? 1'b0 : 1'b1;
	assign RegDst[0] = (OpCode == 6'h023 || OpCode == 6'h024 || OpCode == 6'h0f || OpCode == 6'h08 || OpCode == 6'h09 || OpCode == 6'h0c || OpCode == 6'h0a || OpCode == 6'h0b || OpCode == 6'h03) ? 1'b0 : 1'b1;
	assign RegDst[1] = (OpCode == 6'h03) ? 1'b1 : 1'b0;
	assign MemRead = (OpCode == 6'h23 || OpCode == 6'h24) ? 1'b1 : 1'b0;
	assign MemWrite = (OpCode == 6'h2b) ? 1'b1 : 1'b0;
	assign MemtoReg[0] = ~MemRead;
	assign MemtoReg[1] = (OpCode == 6'h03 || (OpCode == 6'h0 && Funct == 6'h09)) ? 1'b1 : 1'b0;
	assign ALUSrc1 = (OpCode == 6'h0 && (Funct == 6'h0 || Funct == 6'h02 || Funct == 6'h03)) ? 1'b1 : 1'b0;
	assign ALUSrc2 = (OpCode == 6'h23 || OpCode == 6'h24 || OpCode == 6'h2b || OpCode == 6'h0f || OpCode == 6'h08 || OpCode == 6'h09 || OpCode == 6'h0c || OpCode == 6'h0a || OpCode == 6'h0b) ? 1'b1 : 1'b0;
	assign ExtOp = (OpCode == 6'h0c) ? 1'b0 : 1'b1;
	assign LuiOp = (OpCode == 6'h0f) ? 1'b1 : 1'b0;
    assign LbuOp = (OpCode == 6'h24) ? 1'b1 : 1'b0;

endmodule