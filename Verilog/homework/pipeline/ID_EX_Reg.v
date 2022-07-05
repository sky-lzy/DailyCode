`timescale 1ns/1ps

module ID_EX_Reg (
    reset, clk, Control, 
    Data1_in, Data2_in, PC_in, 
    Imm32_in, OpCode_in, Funct_in, Rs_in, Rt_in, Rd_in, Shamt_in, 
    Branch_in, RegWrite_in, RegDst_in, MemRead_in, MemWrite_in, MemtoReg_in, ALUSrc1_in, ALUSrc2_in, LbuOp_in, 
    Data1_out, Data2_out, PC_out, 
    Imm32_out, Rs_out, Rt_out, Rd_out, Shamt_out, 
    Branch_out, RegWrite_out, RegDst_out, MemRead_out, MemWrite_out, MemtoReg_out, ALUSrc1_out, ALUSrc2_out, LbuOp_out, 
    ALUCtrl, Sign
    );
    //Input Signals
    input reset;
    input clk;
    input [1:0] Control;
    //Input Data
    input [31:0] Data1_in;
    input [31:0] Data2_in;
    input [31:0] PC_in;
    input [31:0] Imm32_in;
    input [5:0] OpCode_in;
    input [5:0] Funct_in;
    input [4:0] Rs_in;
    input [4:0] Rt_in;
    input [4:0] Rd_in;
    input [4:0] Shamt_in;
    input Branch_in;
    input RegWrite_in;
    input [1:0] RegDst_in;
    input MemRead_in;
    input MemWrite_in;
    input [1:0] MemtoReg_in;
    input ALUSrc1_in;
    input ALUSrc2_in;
    input LbuOp_in;
    //Output Data
    output reg [31:0] Data1_out;
    output reg [31:0] Data2_out;
    output reg [31:0] PC_out;
    output reg [31:0] Imm32_out;
    output reg [4:0] Rs_out;
    output reg [4:0] Rt_out;
    output reg [4:0] Rd_out;
    output reg [4:0] Shamt_out;
    output reg Branch_out;
    output reg RegWrite_out;
    output reg [1:0] RegDst_out;
    output reg MemRead_out;
    output reg MemWrite_out;
    output reg [1:0] MemtoReg_out;
    output reg ALUSrc1_out;
    output reg ALUSrc2_out;
    output reg LbuOp_out;
    output reg [4:0] ALUCtrl;
    output reg Sign;

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

    always @(posedge reset or posedge clk)
    begin
        if (reset)
        begin
            Data1_out <= 32'h00000000;
            Data2_out <= 32'h00000000;
            PC_out <= 32'h00000000;
            Imm32_out <= 32'h00000000;
            Rs_out <= 5'h00;
            Rt_out <= 5'h00;
            Rd_out <= 5'h00;
            Shamt_out <= 5'h00;
            Branch_out <= 1'b0;
            RegWrite_out <= 1'b0;
            RegDst_out <= 2'b00;
            MemRead_out <= 1'b0;
            MemWrite_out <= 1'b0;
            MemtoReg_out <= 2'b00;
            ALUSrc1_out <= 1'b0;
            ALUSrc2_out <= 1'b0;
            LbuOp_out <= 1'b0;
            ALUCtrl <= 5'b11111;
            Sign <= 1'b0;
        end
        else 
        begin
            case (Control)
                2'b00: 
                begin
                    Data1_out <= Data1_in;
                    Data2_out <= Data2_in;
                    PC_out <= PC_in;
                    Imm32_out <= Imm32_in;
                    Rs_out <= Rs_in;
                    Rt_out <= Rt_in;
                    Rd_out <= Rd_in;
                    Shamt_out <= Shamt_in;
                    Branch_out <= Branch_in;
                    RegWrite_out <= RegWrite_in;
                    RegDst_out <= RegDst_in;
                    MemRead_out <= MemRead_in;
                    MemWrite_out <= MemWrite_in;
                    MemtoReg_out <= MemtoReg_in;
                    ALUSrc1_out <= ALUSrc1_in;
                    ALUSrc2_out <= ALUSrc2_in;
                    LbuOp_out <= LbuOp_in;

                    case (OpCode_in)
                        6'b0: 
                        begin
                            case (Funct_in)
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

                    Sign <= (OpCode_in == 6'h09 || OpCode_in == 6'h0b || (OpCode_in == 6'h0 && (Funct_in == 6'h21 || Funct_in == 6'h23 || Funct_in ==6'h2b))) ? 1'b0 : 1'b1;
                end
                2'b01:
                begin
                    Data1_out <= Data1_out;
                    Data2_out <= Data2_out;
                    PC_out <= PC_out;
                    Imm32_out <= Imm32_out;
                    Rs_out <= Rs_out;
                    Rt_out <= Rt_out;
                    Rd_out <= Rd_out;
                    Shamt_out <= Shamt_out;
                    Branch_out <= Branch_out;
                    RegWrite_out <= RegWrite_out;
                    RegDst_out <= RegDst_out;
                    MemRead_out <= MemRead_out;
                    MemWrite_out <= MemWrite_out;
                    MemtoReg_out <= MemtoReg_out;
                    ALUSrc1_out <= ALUSrc1_out;
                    ALUSrc2_out <= ALUSrc2_out;
                    LbuOp_out <= LbuOp_out;
                    ALUCtrl <= ALUCtrl;
                    Sign <= Sign;
                end
                default: 
                begin
                    Data1_out <= 32'h00000000;
                    Data2_out <= 32'h00000000;
                    PC_out <= 32'h00000000;
                    Imm32_out <= 32'h00000000;
                    Rs_out <= 5'h00;
                    Rt_out <= 5'h00;
                    Rd_out <= 5'h00;
                    Shamt_out <= 5'h00;
                    Branch_out <= 1'b0;
                    RegWrite_out <= 1'b0;
                    RegDst_out <= 2'b00;
                    MemRead_out <= 1'b0;
                    MemWrite_out <= 1'b0;
                    MemtoReg_out <= 2'b00;
                    ALUSrc1_out <= 1'b0;
                    ALUSrc2_out <= 1'b0;
                    LbuOp_out <= 1'b0;
                    ALUCtrl <= 5'b11111;
                    Sign <= 1'b0;
                end
            endcase
        end
    end

endmodule