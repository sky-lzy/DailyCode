`timescale 1ns/1ps

module Controller (OpCode, Funct, PCSource, Branch, RegWrite, RegDst, MemRead, MemWrite, MemtoReg, ALUSrc1, ALUSrc2, ExtOp, LuiOp, LbuOp, ALUCtrl, Sign);
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
    output reg [4:0] ALUCtrl;
    output Sign;

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

    //ALU parameters
    parameter ADD  = 5'b00000;
    parameter SUB  = 5'b00001;
    parameter AND  = 5'b00010;
    parameter OR   = 5'b00011;
    parameter XOR  = 5'b00100;
    parameter NOR  = 5'b00101;
    parameter SLT  = 5'b00110;
    parameter SLL  = 5'b01000;
    parameter SRL  = 5'b01001;
    parameter SRA  = 5'b01010;
    parameter BEQ  = 5'b10000;
    parameter BNE  = 5'b10001;
    parameter BLEZ = 5'b10010;
    parameter BGTZ = 5'b10011;
    parameter BLTZ = 5'b10100;
    parameter NULL = 5'b11111;

    always @(*) 
    begin
        case (OpCode)
            6'h00: 
            begin
                case (Funct)
                    6'h20:   ALUCtrl <= ADD; 
                    6'h21:   ALUCtrl <= ADD; 
                    6'h22:   ALUCtrl <= SUB; 
                    6'h23:   ALUCtrl <= SUB; 
                    6'h24:   ALUCtrl <= AND; 
                    6'h25:   ALUCtrl <=  OR; 
                    6'h26:   ALUCtrl <= XOR; 
                    6'h27:   ALUCtrl <= NOR; 
                    6'h00:   ALUCtrl <= SLL; 
                    6'h02:   ALUCtrl <= SRL; 
                    6'h03:   ALUCtrl <= SRA; 
                    6'h2a:   ALUCtrl <= SLT; 
                    6'h2b:   ALUCtrl <= SLT; 
                    default: ALUCtrl <= NULL;
                endcase
            end
            6'h23:   ALUCtrl <= ADD; 
            6'h2b:   ALUCtrl <= ADD; 
            6'h0f:   ALUCtrl <= ADD; 
            6'h08:   ALUCtrl <= ADD; 
            6'h09:   ALUCtrl <= ADD; 
            6'h0c:   ALUCtrl <= AND; 
            6'h0a:   ALUCtrl <= SLT; 
            6'h0b:   ALUCtrl <= SLT; 
            6'h04:   ALUCtrl <= BEQ;
            6'h05:   ALUCtrl <= BNE;
            6'h06:   ALUCtrl <= BLEZ;
            6'h07:   ALUCtrl <= BGTZ;
            6'h01:   ALUCtrl <= BLTZ;
            default: ALUCtrl <= NULL;
        endcase

    end
    assign Sign = (OpCode == 6'h09 || OpCode == 6'h0b || (OpCode == 6'h0 && (Funct == 6'h21 || Funct == 6'h23 || Funct ==6'h2b))) ? 1'b0 : 1'b1;

endmodule