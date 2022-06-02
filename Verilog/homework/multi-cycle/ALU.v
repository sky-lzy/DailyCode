`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Class: Fundamentals of Digital Logic and Processor
// Designer: Shulin Zeng
// 
// Create Date: 2021/04/30
// Design Name: MultiCycleCPU
// Module Name: ALU
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


module ALU(ALUConf, Sign, In1, In2, Zero, Result);
    // Control Signals
    input [4:0] ALUConf;
    input Sign;
    // Input Data Signals
    input [31:0] In1;
    input [31:0] In2;
    // Output 
    output Zero;
    output reg [31:0] Result;

    //--------------Your code below-----------------------
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

    assign Zero = ~|Result;

    always @(*)
    begin
        case (ALUConf)
            ADD: Result <= In1 + In2;
            SUB: Result <= In1 - In2;
            AND: Result <= In1 & In2;
            OR:  Result <= In1 | In2;
            XOR: Result <= In1 ^ In2;
            NOR: Result <= ~(In1 | In2);
            SLT: begin if (Sign) Result <= (In1[31] & ~In2[31]) | ((~In1[31] & ~In2[31]) & (In1 < In2)) | ((In1[31] & In2[31]) & (In1 > In2));
                       else Result <= In1 < In2; end
            SLL: Result <= In2 << In1;
            SRL: Result <= In2 >> In1;
            SRA: Result <= $signed(In2) >>> In1;
            default: Result <= 32'b0;
        endcase
    end

    initial
    begin
        Result = 32'b0;
    end
    //--------------Your code above-----------------------

endmodule
