
module CPU(sysclk, reset, clk, RegShow, ENs, LEDs, BCDs);
	input sysclk, reset, clk;
    input [1:0] RegShow;
    output [3:0] ENs;
    output [7:0] LEDs;
    output [6:0] BCDs;

    //--------------Your code below-----------------------
    reg [31:0] InstructionAddress;
    wire [31:0] DataAddress;
    wire [31:0] Instruction;
    wire [5:0] OpCode;
    wire [5:0] Funct;
    wire [4:0] ALUCtrl;
    wire [4:0] Read_register1;
    wire [4:0] Read_register2;
    wire [4:0] Write_register;
    wire [31:0] Write_data_Mem;
    wire [31:0] Write_data_Reg;
    wire [31:0] Read_data_Mem;
    wire [31:0] Read_data1;
    wire [31:0] Read_data2;
    wire [31:0] in1;
    wire [31:0] in2;
    wire [31:0] ALUout;
    wire [31:0] Imm32;
    wire [1:0] PCSrc;
    wire Branch;
    wire RegWrite;
    wire [1:0] RegDst;
    wire MemRead;
    wire MemWrite;
    wire [1:0] MemtoReg;
    wire ALUSrc1;
    wire ALUSrc2;
    wire ExtOp;
    wire LuOp;
    wire Sign;
    wire zero;
    wire sysclk;
    wire clk_o;
    wire [31:0] RegShowData;
    
    assign OpCode = Instruction[31:26];
    assign Funct = Instruction[5:0];
    assign Read_register1 = PCSrc[1] ? 5'd31 : Instruction[25:21];
    assign Read_register2 = Instruction[20:16];
    assign Write_register = RegDst[1] ? 5'd31 : (RegDst[0] ? Instruction[15:11] : Instruction[20:16]);
    assign in1 = ALUSrc1 ? {27'b0, Instruction[10:6]} : Read_data1;
    assign Imm32 = LuOp ? {Instruction[15:0], 16'b0} : ((ExtOp && Instruction[15]) ? {16'hffff, Instruction[15:0]} : {16'h0, Instruction[15:0]});
    assign in2 = ALUSrc2 ? Imm32 : Read_data2;
    assign Write_data_Reg = MemtoReg[1] ? InstructionAddress + 32'd4 : (MemtoReg[0] ? Read_data_Mem : ALUout);
    assign Write_data_Mem = Read_data2;
    assign DataAddress = ALUout;

    // debounce
    debounce my_debounce(sysclk, clk, clk_o);
    // assign clk_o = clk;

    // InstructionMemory my_InstructionMemory(InstructionAddress, Instruction);
    InstructionMemory2 my_InstructionMemory(InstructionAddress, Instruction);
    DataMemory my_DataMemory(reset, clk_o, DataAddress, Write_data_Mem, Read_data_Mem, MemRead, MemWrite);
    // RegisterFile my_RegisterFile(reset, clk_o, RegWrite, Read_register1, Read_register2, Write_register, Write_data_Reg, Read_data1, Read_data2);
    RegisterFile my_RegisterFile(reset, clk_o, RegShow, RegWrite, Read_register1, Read_register2, Write_register, Write_data_Reg, Read_data1, Read_data2, RegShowData);
    Control my_Control(OpCode, Funct, PCSrc, Branch, RegWrite, RegDst, MemRead, MemWrite, MemtoReg, ALUSrc1, ALUSrc2, ExtOp, LuOp);
    ALUControl my_ALUControl(OpCode, Funct, ALUCtrl, Sign);
    ALU my_ALU(in1, in2, ALUCtrl, Sign, ALUout, zero);

    always @(posedge reset or posedge clk_o)
    begin
        if (reset)
            InstructionAddress <= 32'b0;
        else
        begin
            case (PCSrc)
                2'b00: InstructionAddress <= InstructionAddress + 32'd4 + ((Branch && zero) ? {Imm32[29:0], 2'b00} : 32'b0);
                2'b01: InstructionAddress <= {InstructionAddress[31:28], Instruction[25:0], 2'b00};
                2'b10: InstructionAddress <= Read_data1;
            endcase
        end
    end
    
    //------------------initial---------------------------
    initial
    begin
        InstructionAddress = 32'b0;
        BCD_state = 2'b0;
        sysclk_count = 14'b0;
    end

    //------------------visual----------------------------
    wire [7:0] LEDs;
    wire [6:0] BCDs;
    wire [3:0] ENs;
    reg [1:0] BCD_state;
    reg [13:0] sysclk_count;

    assign LEDs[7:0] = InstructionAddress[7:0];
    DataToBCD my_DataToBCD(RegShowData[15:0], BCD_state, ENs, BCDs);
    
    always @(posedge sysclk)
    begin
        if (sysclk_count >= 14'd10000)
        // if (sysclk_count >= 14'd0)
        begin
            BCD_state <= BCD_state + 1'b1;
            sysclk_count <= 14'b0;
        end
        else sysclk_count <= sysclk_count + 1'b1;
    end

    //--------------Your code above-----------------------

endmodule
	