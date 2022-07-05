`timescale 1ns / 1ps

module PipelineCPU (reset, clk);
    //Input Clock Signals
    input reset;
    input clk;

    //Wires
    wire IsBranch;
    wire [31:0] PCMux;
    wire [31:0] JumpMux;
    wire [31:0] ALUMuxA;
    wire [31:0] ALUMuxB;
    wire [31:0] ALUData1;
    wire [31:0] ALUData2;
    wire [4:0] RegWrAddr;
    wire [31:0] MemDataMux;

    wire [31:0] PCNext;
    wire [31:0] BranchAddr;

    wire [5:0] OpCode;
    wire [4:0] Rs;
    wire [4:0] Rt;
    wire [4:0] Rd;
    wire [4:0] Shamt;
    wire [5:0] Funct;

    wire [31:0] PC_IFID;
    wire [31:0] Instruction_IFID;
    wire [31:0] Data1_IDEX;
    wire [31:0] Data2_IDEX;
    wire [31:0] PC_IDEX;
    wire [31:0] Imm32_IDEX;
    wire [4:0] Rs_IDEX;
    wire [4:0] Rt_IDEX;
    wire [4:0] Rd_IDEX;
    wire [4:0] Shamt_IDEX;
    wire Branch_IDEX;
    wire RegWrite_IDEX;
    wire [1:0] RegDst_IDEX;
    wire MemRead_IDEX;
    wire MemWrite_IDEX;
    wire [1:0] MemtoReg_IDEX;
    wire ALUSrc1_IDEX;
    wire ALUSrc2_IDEX;
    wire [4:0] ALUCtrl;
    wire Sign;
    wire [31:0] ALUResult_EXMEM;
    wire [31:0] Data_EXMEM;
    wire [31:0] PC_EXMEM;
    wire [4:0] RegWrAddr_EXMEM;
    wire RegWrite_EXMEM;
    wire MemRead_EXMEM;
    wire [1:0] MemtoReg_EXMEM;
    wire [31:0] Data_MEMWB;
    wire [4:0] RegWrAddr_MEMWB;
    wire RegWrite_MEMWB;

    wire [31:0] PCAddress;
    wire [31:0] Instruction;
    wire [31:0] Read_data1;
    wire [31:0] Read_data2;
    wire [1:0] PCSource;
    wire Branch;
    wire RegWrite;
    wire [1:0] RegDst;
    wire MemRead;
    wire MemWrite;
    wire [1:0] MemtoReg;
    wire ALUSrc1;
    wire ALUSrc2;
    wire ExtOp;
    wire LuiOp;
    wire [31:0] Imm32;
    wire Zero;
    wire [31:0] ALUResult;
    wire [31:0] DataFromMemory;

    wire [1:0] ALUSrcA;
    wire [1:0] ALUSrcB;
    wire JumpConf;

    wire PCWrite;
    wire [1:0] IFIDCtrl;
    wire [1:0] IDEXCtrl;

    //Logic
    assign IsBranch = Branch_IDEX & Zero;

    //Mux
    assign PCMux = IsBranch ? BranchAddr : (PCSource[1] ? JumpMux : (PCSource[0] ? {PC_IFID[31:28], Instruction_IFID[25:0], 2'b00} : PCNext));
    assign JumpMux = JumpConf ? ALUResult_EXMEM : Read_data1;
    assign ALUMuxA = ALUSrcA[1] ? Data_MEMWB : (ALUSrcA[0] ? ALUResult_EXMEM : Data1_IDEX);
    assign ALUMuxB = ALUSrcB[1] ? Data_MEMWB : (ALUSrcB[0] ? ALUResult_EXMEM : Data2_IDEX);
    assign ALUData1 = ALUSrc1_IDEX ? Shamt_IDEX : ALUMuxA;
    assign ALUData2 = ALUSrc2_IDEX ? Imm32_IDEX : ALUMuxB;
    assign RegWrAddr = RegDst_IDEX[1] ? 5'd31 : (RegDst_IDEX[0] ? Rd_IDEX : Rt_IDEX);
    assign MemDataMux = MemtoReg_EXMEM[1] ? PC_EXMEM : (MemtoReg_EXMEM[0] ? ALUResult_EXMEM : DataFromMemory);

    //Adds
    assign PCNext = PCAddress + 3'd4;
    assign BranchAddr = PC_IDEX + (Imm32_IDEX << 2);

    //Instruction
    assign OpCode = Instruction_IFID[31:26];
    assign Rs = Instruction_IFID[25:21];
    assign Rt = Instruction_IFID[20:16];
    assign Rd = Instruction_IFID[15:11];
    assign Shamt = Instruction_IFID[10:6];
    assign Funct = Instruction_IFID[5:0];

    //Registers
    IF_ID_Reg my_IFIDReg(reset, clk, IFIDCtrl, PCNext, Instruction, PC_IFID, Instruction_IFID);
    ID_EX_Reg my_IDEXReg(reset, clk, IDEXCtrl, Read_data1, Read_data2, PC_IFID, Imm32, OpCode, Funct, Rs, Rt, Rd, Shamt, Branch, RegWrite, RegDst, MemRead, MemWrite, MemtoReg, ALUSrc1, ALUSrc2, Data1_IDEX, Data2_IDEX, PC_IDEX, Imm32_IDEX, Rs_IDEX, Rt_IDEX, Rd_IDEX, Shamt_IDEX, Branch_IDEX, RegWrite_IDEX, RegDst_IDEX, MemRead_IDEX, MemWrite_IDEX, MemtoReg_IDEX, ALUSrc1_IDEX, ALUSrc2_IDEX, ALUCtrl, Sign);
    EX_MEM_Reg my_EXMEMReg(reset, clk, ALUResult, Data2_IDEX, PC_IDEX, RegWrAddr, RegWrite_IDEX, MemRead_IDEX, MemWrite_IDEX, MemtoReg_IDEX, ALUResult_EXMEM, Data_EXMEM, PC_EXMEM, RegWrAddr_EXMEM, RegWrite_EXMEM, MemRead_EXMEM, MemWrite_EXMEM, MemtoReg_EXMEM);
    MEM_WB_Reg my_MEMWBReg(reset, clk , MemDataMux, RegWrAddr_EXMEM, RegWrite_EXMEM, Data_MEMWB, RegWrAddr_MEMWB, RegWrite_MEMWB);

    //Modules
    PC my_PC(reset, clk, PCWrite, PCMux, PCAddress);
    InstructionMemory my_InstructionMemory(PCAddress, Instruction);
    RegisterFile my_Register(reset, clk, RegWrite_MEMWB, Rs, Rt, RegWrAddr_MEMWB, Data_MEMWB, Read_data1, Read_data2);
    Controller my_Controller(OpCode, Funct, PCSource, Branch, RegWrite, RegDst, MemRead, MemWrite, MemtoReg, ALUSrc1, ALUSrc2, ExtOp, LuiOp);
    ImmProcess my_ImmProcess(ExtOp, LuiOp, {Rd, Shamt, Funct}, Imm32);
    ALU my_ALU(ALUCtrl, Sign, ALUData1, ALUData2, Zero, ALUResult);
    DataMemory my_DataMemory(reset, clk, ALUResult_EXMEM, Data_EXMEM, DataFromMemory, MemRead_EXMEM, MemWrite_EXMEM);

    //Forwarding
    Forwarding my_Forwarding(Rs, Rs_IDEX, Rt_IDEX, RegWrite_EXMEM, RegWrAddr_EXMEM, RegWrite_MEMWB, RegWrAddr_MEMWB, ALUSrcA, ALUSrcB, JumpConf);

    //Hazard
    Hazard my_Hazard(PCSource, IsBranch, Rs, Rt, Rs_IDEX, Rt_IDEX, MemRead_IDEX, RegWrite_IDEX, RegWrAddr, PCWrite, IFIDCtrl, IDEXCtrl);

endmodule