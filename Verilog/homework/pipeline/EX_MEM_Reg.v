`timescale 1ns/1ps

module EX_MEM_Reg (
    reset, clk, 
    ALU_in, Data_in, PC_in, RegWrAddr_in, 
    RegWrite_in, MemRead_in, MemWrite_in, MemtoReg_in, 
    ALU_out, Data_out, PC_out, RegWrAddr_out, 
    RegWrite_out, MemRead_out, MemWrite_out, MemtoReg_out
    );
    //Input Signals
    input reset;
    input clk;
    //Input Data
    input [31:0] ALU_in;
    input [31:0] Data_in;
    input [31:0] PC_in;
    input [4:0] RegWrAddr_in;
    input RegWrite_in;
    input MemRead_in;
    input MemWrite_in;
    input [1:0] MemtoReg_in;
    //Output Data
    output reg [31:0] ALU_out;
    output reg [31:0] Data_out;
    output reg [31:0] PC_out;
    output reg [4:0] RegWrAddr_out;
    output reg RegWrite_out;
    output reg MemRead_out;
    output reg MemWrite_out;
    output reg [1:0] MemtoReg_out;

    always @(posedge reset or posedge clk) 
    begin
        if (reset)
        begin
            ALU_out <= 32'h00000000;
            Data_out <= 32'h00000000;
            PC_out <= 32'h00000000;
            RegWrAddr_out <= 5'h00;
            RegWrite_out <= 1'b0;
            MemRead_out <= 1'b0;
            MemWrite_out <= 1'b0;
            MemtoReg_out <= 2'b00;
        end
        else 
        begin
            ALU_out <= ALU_in;
            Data_out <= Data_in;
            PC_out <= PC_in;
            RegWrAddr_out <= RegWrAddr_in;
            RegWrite_out <= RegWrite_in;
            MemRead_out <= MemRead_in;
            MemWrite_out <= MemWrite_in;
            MemtoReg_out <= MemtoReg_in;
        end
    end
    
endmodule