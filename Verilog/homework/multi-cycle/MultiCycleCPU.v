`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Class: Fundamentals of Digital Logic and Processor
// Designer: Shulin Zeng
// 
// Create Date: 2021/04/30
// Design Name: MultiCycleCPU
// Module Name: MultiCycleCPU
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

module MultiCycleCPU (sysclk, reset, clk, RegShow, ENs, LEDs, BCDs);
    //Input Clock Signals
    input sysclk;
    input reset;
    input clk;
    input [1:0] RegShow;
    output [3:0] ENs;
    output [7:0] LEDs;
    output [6:0] BCDs;
    
    //--------------Your code below-----------------------
    
    wire [31:0] Address;
    wire [31:0] PCMux;
    wire [4:0] Write_register;
    wire [31:0] ALUIn1;
    wire [31:0] ALUIn2;
    wire [31:0] Write_data;
    wire PCWriteControl;

    wire [5:0] OpCode;
    wire [4:0] rs;
    wire [4:0] rt;
    wire [4:0] rd;
    wire [4:0] Shamt;
    wire [5:0] Funct;

    wire PCWrite;
    wire PCWriteCond;
    wire IorD;
    wire MemWrite;
    wire MemRead;
    wire IRWrite;
    wire [1:0] MemtoReg;
    wire [1:0] RegDst;
    wire RegWrite;
    wire ExtOp;
    wire LuiOp;
    wire [1:0] ALUSrcA;
    wire [1:0] ALUSrcB;
    wire [3:0] ALUOp;
    wire [1:0] PCSource;

    wire [31:0] PCOut;
    wire [31:0] Mem_data;
    wire [31:0] Read_data1;
    wire [31:0] Read_data2;
    wire [31:0] Reg_data1;
    wire [31:0] Reg_data2;
    wire [31:0] Reg_ALUResult;
    wire [31:0] Reg_MemData;
    wire [31:0] ImmExtOut;
    wire [31:0] ImmExtShift;
    wire [4:0] ALUConf;
    wire Sign;
    wire [31:0] Result;
    wire Zero;

    assign PCMux = PCSource[1] ? {PCOut[31:28], rs, rt, rd, Shamt, Funct, 2'b00} : (PCSource[0] ? Reg_ALUResult : Result);
    assign Write_register = RegDst[1] ? 5'd31 : (RegDst[0] ? rd : rt);
    assign ALUIn1 = ALUSrcA[1] ? {27'b0, Shamt} : (ALUSrcA[0] ? Reg_data1 : PCOut);
    assign ALUIn2 = ALUSrcB[1] ? (ALUSrcB[0] ? ImmExtShift : ImmExtOut) : (ALUSrcB[0] ? 32'd4 : Reg_data2);
    assign Write_data = MemtoReg[1] ? PCOut : (MemtoReg[0] ? Reg_ALUResult : Reg_MemData);
    assign Address = IorD ? Reg_ALUResult : PCOut;
    assign PCWriteControl = PCWrite | (PCWriteCond & Zero);

    //debounce
    debounce my_debounce(sysclk, clk, clk_o);

    // InstAndDataMemory my_Memory(reset, clk_o, Address, Read_data2, MemRead, MemWrite, Mem_data);
    InstAndDataMemory2 my_Memory2(reset, clk_o, Address, Read_data2, MemRead, MemWrite, Mem_data);
    Controller my_Controller(reset, clk_o, OpCode, Funct, PCWrite, PCWriteCond, IorD, MemWrite, MemRead, IRWrite, MemtoReg, RegDst, RegWrite, ExtOp, LuiOp, ALUSrcA, ALUSrcB, ALUOp, PCSource);
    ALUControl my_ALUControl(ALUOp, Funct, ALUConf, Sign);
    InstReg my_InstReg(reset, clk_o, IRWrite, Mem_data, OpCode, rs, rt, rd, Shamt, Funct);
    ImmProcess my_ImmProcess(ExtOp, LuiOp, {rd, Shamt, Funct}, ImmExtOut, ImmExtShift);
    PC my_PC(reset, clk_o, PCWriteControl, PCMux, PCOut);
    ALU my_ALU(ALUConf, Sign, ALUIn1, ALUIn2, Zero, Result);
    // RegisterFile my_RegisterFile(reset, clk_o, RegWrite, rs, rt, Write_register, Write_data, Read_data1, Read_data2);
    RegisterFile my_RegisterFile(reset, clk_o, RegShow, RegWrite, rs, rt, Write_register, Write_data, Read_data1, Read_data2, RegShowData);
    RegTemp my_RegReadData1(reset, clk_o, Read_data1, Reg_data1);
    RegTemp my_RegReadData2(reset, clk_o, Read_data2, Reg_data2);
    RegTemp my_RegALUOut(reset, clk_o, Result, Reg_ALUResult);
    RegTemp my_RegMDR(reset, clk_o, Mem_data, Reg_MemData);

    //--------------------visual--------------------------
    wire [7:0] LEDs;
    wire [6:0] BCDs;
    wire [3:0] ENs;
    wire [31:0] RegShowData;
    reg [1:0] BCD_state;
    reg [13:0] sysclk_count;

    assign LEDs[7:0] = PCOut[7:0];
    DataToBCD my_DataToBCD(RegShowData[15:0], BCD_state, ENs, BCDs);
    
    always @(posedge sysclk)
    begin
        if (sysclk_count >= 14'd10000)
        begin
            BCD_state <= BCD_state + 1'b1;
            sysclk_count <= 14'b0;
        end
        else sysclk_count <= sysclk_count + 1'b1;
    end

    initial
    begin
        BCD_state = 2'b0;
        sysclk_count = 14'b0;
    end
    //--------------Your code above-----------------------

endmodule