`timescale 1ns / 1ps

module ALU(ALUConf, Sign, In1, In2, Zero, Result);
    // Control Signals
    input [4:0] ALUConf;
    input Sign;
    // Input Data Signals
    input [31:0] In1;
    input [31:0] In2;
    // Output 
    output reg Zero;
    output reg [31:0] Result;

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

    //ALU Operators
    always @(*)
    begin
        case (ALUConf)
            ADD: Result <= In1 + In2;
            SUB: Result <= In1 - In2;
            AND: Result <= In1 & In2;
            OR : Result <= In1 | In2;
            XOR: Result <= In1 ^ In2;
            NOR: Result <= ~(In1 | In2);
            SLT: begin if (Sign) Result <= (In1[31] & ~In2[31]) | ((~In1[31] & ~In2[31]) & (In1 < In2)) | ((In1[31] & In2[31]) & (In1 > In2)); else Result <= In1 < In2; end
            SLL: Result <= In2 << In1;
            SRL: Result <= In2 >> In1;
            SRA: Result <= $signed(In2) >>> In1;
            BEQ: Result <= In1 - In2;
            BNE: Result <= In1 - In2;
            default: Result <= In1;
        endcase
    end
    
    assign tempZero = ~|Result;
    always @(*)
    begin
        case (ALUConf)
            BEQ: Zero <= tempZero;
            BNE: Zero <= ~tempZero;
            BLEZ: Zero <= Result[31] || tempZero;
            BGTZ: Zero <= ~Result[31] && ~tempZero;
            BLTZ: Zero <= Result[31];
            default: Zero <= 0;
        endcase
    end

endmodule
