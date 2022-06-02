`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Class: Fundamentals of Digital Logic and Processor
// Designer: Shulin Zeng
// 
// Create Date: 2021/04/30
// Design Name: MultiCycleCPU
// Module Name: ALUControl
// Project Name: Multi-cycle-cpu
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module ALUControl(ALUOp, Funct, ALUConf, Sign);
	//Control Signals
	input [3:0] ALUOp;
	//Inst. Signals
	input [5:0] Funct;
	//Output Control Signals
	output reg [4:0] ALUConf;
	output Sign;

    //--------------Your code below-----------------------
	parameter ALU_IF = 4'b0001;
    parameter ALU_ID = 4'b0010;
    parameter ALU_EX_R = 4'b0011;
    parameter ALU_ADD = 4'b0100;
    parameter ALU_ADDU = 4'b0101;
    parameter ALU_AND = 4'b0110;
    parameter ALU_LUI = 4'b0111;
    parameter ALU_SLT = 4'b1000;
    parameter ALU_SLTU = 4'b1001;
    parameter ALU_BEQ = 4'b1010;
    parameter ALU_NULL = 4'b1111;

	parameter ADD  = 5'b00000;
    parameter SUB  = 5'b00001;
    parameter AND  = 5'b00010;
    parameter OR   = 5'b00011;
    parameter XOR  = 5'b00100;
    parameter NOR  = 5'b00101;
    parameter SLT  = 5'b00110;
    parameter SLL  = 5'b10000;
    parameter SRL  = 5'b10001;
    parameter SRA  = 5'b10010;
    parameter NULL = 5'b11111;

	always @(*)
	begin
		case (ALUOp)
			ALU_EX_R: 
			begin
				case (Funct)
					6'h20:   ALUConf <= ADD; 
                    6'h21:   ALUConf <= ADD; 
                    6'h22:   ALUConf <= SUB; 
                    6'h23:   ALUConf <= SUB; 
                    6'h24:   ALUConf <= AND; 
                    6'h25:   ALUConf <=  OR; 
                    6'h26:   ALUConf <= XOR; 
                    6'h27:   ALUConf <= NOR; 
                    6'h00:   ALUConf <= SLL; 
                    6'h02:   ALUConf <= SRL; 
                    6'h03:   ALUConf <= SRA; 
                    6'h2a:   ALUConf <= SLT; 
                    6'h2b:   ALUConf <= SLT; 
                    6'h08:   ALUConf <= ADD;
                    6'h09:   ALUConf <= ADD;
                    default: ALUConf <= NULL;
				endcase
			end
			ALU_IF, ALU_ID, ALU_ADD, ALU_ADDU, ALU_LUI: ALUConf <= ADD;
			ALU_AND: ALUConf <= AND;
			ALU_SLT, ALU_SLTU: ALUConf <= SLT;
			ALU_BEQ: ALUConf <= SUB;
			default: ALUConf <= NULL;
		endcase
	end

	assign Sign = (ALUOp == ALU_ADDU || ALUOp == ALU_SLTU || (ALUOp == ALU_EX_R && (Funct == 6'h21 || Funct == 6'h23 || Funct == 6'h2b))) ? 1'b0 : 1'b1;

	initial
	begin
		ALUConf = 5'b0;
	end
    //--------------Your code above-----------------------

endmodule
