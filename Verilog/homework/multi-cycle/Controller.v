`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Class: Fundamentals of Digital Logic and Processor
// Designer: Shulin Zeng, Shang Yang
// 
// Create Date: 2021/04/30
// Design Name: MultiCycleCPU
// Module Name: Controller
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


module Controller(reset, clk, OpCode, Funct, 
                PCWrite, PCWriteCond, IorD, MemWrite, MemRead,
                IRWrite, MemtoReg, RegDst, RegWrite, ExtOp, LuiOp,
                ALUSrcA, ALUSrcB, ALUOp, PCSource);
    //Input Clock Signals
    input reset;
    input clk;
    //Input Signals
    input  [5:0] OpCode;
    input  [5:0] Funct;
    //Output Control Signals
    output reg PCWrite;
    output reg PCWriteCond;
    output reg IorD;
    output reg MemWrite;
    output reg MemRead;
    output reg IRWrite;
    output reg [1:0] MemtoReg;
    output reg [1:0] RegDst;
    output reg RegWrite;
    output reg ExtOp;
    output reg LuiOp;
    output reg [1:0] ALUSrcA;
    output reg [1:0] ALUSrcB;
    output reg [3:0] ALUOp;
    output reg [1:0] PCSource;
      
    reg [2:0] state; //current state
    reg [2:0] next_state; //next_state
    parameter sIF = 3'b0 ,sID = 3'b1; 
     
    //--------------Your code below-----------------------

    always @(posedge reset or posedge clk) 
    begin
        if (reset) 
            begin
                state <= 3'b0;
                next_state <=3'b0;
                PCWrite <= 1'b0;
                PCWriteCond <= 1'b0;
                IorD <= 1'b0;
                MemWrite <= 1'b0;
                MemRead <= 1'b0;
                IRWrite <= 1'b0;
                MemtoReg <= 2'b00;
                RegDst <= 2'b0;
                RegWrite <= 1'b0;
                ExtOp <= 1'b0;
                LuiOp <= 1'b0;
                ALUSrcA <= 2'b0;
                ALUSrcB <= 2'b0;
                PCSource <=2'b0;
            end
        else
        begin
            if (next_state == sIF) 
                begin
                    
                    state <= next_state;
                    next_state <= next_state + 3'b1;
                    
                    MemRead <= 1'b1;
                    IRWrite <= 1'b1;
                    PCWrite <= 1'b1;
                    PCSource <= 2'b00;
                    ALUSrcA <= 2'b00;
                    IorD <= 1'b0;
                    ALUSrcB <= 2'b01;
        
                    PCWriteCond <= 1'b0;
                    MemWrite <= 1'b0;
                    MemtoReg <= 2'b00;
                    RegDst <= 2'b0;
                    RegWrite <= 1'b0;
                    ExtOp <= 1'b0;
                    LuiOp <= 1'b0;
                end
                
            else if (next_state == sID) 
                begin
                    state <= next_state;
                    next_state <= next_state + 3'b1;
                    ALUSrcA <= 2'b00;
                    ALUSrcB <= 2'b11;    
                    ExtOp <= 1'b1;
                    
                    PCWrite <= 1'b0;
                    PCWriteCond <= 1'b0;
                    IorD <= 1'b0;
                    MemWrite <= 1'b0;
                    MemRead <= 1'b0;
                    IRWrite <= 1'b0;
                    MemtoReg <= 2'b00;
                    RegDst <= 2'b0;
                    RegWrite <= 1'b0;
                    LuiOp <= 1'b0;
                    PCSource <=2'b0;
                end
            else if (next_state == 3'd2) 
                begin
                    state <= next_state;
                    case(OpCode)
                        6'h00: 
                            begin
                                ALUSrcA <= (Funct==6'h00 || Funct==6'h02 || Funct==6'h03 ) ? 2'b10 : 2'b01; 
                                ALUSrcB <= 2'b00;                       
                                case(Funct)
                                    6'h08:      
                                        begin
                                            PCSource <= 2'b00;
                                            PCWrite  <= 1'b1;
                                            next_state <= sIF;
                                        end
                                    6'h09:        
                                        begin
                                            PCSource <= 2'b00;
                                            PCWrite  <= 1'b1;
                                            next_state <= sIF;
                                            
                                            RegDst <= 2'b01;   
                                            MemtoReg <= 2'b10;
                                            RegWrite <= 1'b1;
                                        end
                                    default:
                                        begin
                                            next_state <= next_state + 3'b1;
                                        end
                                endcase
                            end
                        6'h23,6'h2b,6'h0f,6'h08,6'h09,6'h0c,6'h0b,6'h0a:      
                            begin
                                ALUSrcA <= 2'b01;   
                                ALUSrcB <= 2'b10;   
                                ExtOp <=((OpCode==6'h0c)? 0 : 1);      
                                LuiOp <=((OpCode==6'h0f)? 1 : 0);      
                                next_state <= next_state +3'b1;
                            end
                        6'h04: 
                            begin
                                PCWriteCond <= 1'b1;
                                ALUSrcA <= 2'b01;
                                ALUSrcB <= 2'b00;
                                PCSource <= 2'b01;
                                next_state <= sIF;
                            end
                        6'h02: 
                            begin
                                PCWrite <= 1'b1;
                                PCSource <= 2'b10;
                                next_state <= sIF;
                            end
                        6'h03: 
                            begin
                                PCWrite <= 1'b1;
                                PCSource <= 2'b10;
                                                               
                                RegDst <=  2'b10;   
                                MemtoReg <= 2'b10;
                                RegWrite <= 1'b1;
                                
                                next_state <= sIF;
                            end 
                        default: 
                            begin
                                next_state <= sIF;
                            end
                    endcase
                end
            else if (next_state == 3'd3) 
                begin
                    state<=next_state;
                    case(OpCode)
                        6'h00: 
                            begin
                                RegWrite <= 1'b1;
                                RegDst <= 2'b01;
                                MemtoReg <= 2'b01;
                                next_state <= sIF;
                            end
                        6'h2b:      
                            begin
                                MemWrite<=1'b1;
                                IorD <=1'b1;
                                next_state <= sIF;
                            end
                        6'h08,6'h09,6'h0c,6'h0b,6'h0a,6'h0f:      
                            begin
                                RegWrite <= 1'b1;
                                RegDst <= 2'b00;
                                MemtoReg <= 2'b01;
                                next_state <= sIF;
                            end
                        6'h23:      
                            begin
                                MemRead <= 1'b1;
                                IorD <= 1'b1;
                                IRWrite <=1'b0;
                                next_state <= next_state +3'b001;
                            end
                        default: 
                            begin
                                next_state <= sIF;
                            end
                    endcase
        
                end
            else if (next_state == 3'd4) 
                begin
                    state<=next_state;
                    case(OpCode)
                        6'h23: 
                            begin
                                RegWrite <= 1'b1;
                                RegDst <= 2'b00;
                                MemtoReg <= 2'b00;
                                next_state <= sIF;
                            end
                        default: 
                            begin
                                next_state <= sIF;
                            end
                    endcase
                end
        end
    end
    
    
    //--------------Your code below-----------------------
    //ALUOp
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

    always @(posedge reset or posedge clk)
    begin
        if (reset) ALUOp = 4'b0;
        else
        begin
            if (next_state == sIF) ALUOp <= ALU_IF;
            else if (next_state == sID) ALUOp <= ALU_ID;
            else if (next_state == 3'd2)
            begin
                case (OpCode)
                    6'h00: ALUOp <= ALU_EX_R;
                    6'h23, 6'h2b, 6'h08: ALUOp <= ALU_ADD;
                    6'h09: ALUOp <= ALU_ADDU;
                    6'h0c: ALUOp <= ALU_AND;
                    6'h0a: ALUOp <= ALU_SLT;
                    6'h0b: ALUOp <= ALU_SLTU;
                    6'h04: ALUOp <= ALU_BEQ;
                    default: ALUOp <= ALU_NULL;
                endcase
            end
        end
    end

    initial
    begin
        state = 3'b0;
        next_state =3'b0;
        PCWrite = 1'b0;
        PCWriteCond = 1'b0;
        IorD = 1'b0;
        MemWrite = 1'b0;
        MemRead = 1'b0;
        IRWrite = 1'b0;
        MemtoReg = 2'b00;
        RegDst = 2'b0;
        RegWrite = 1'b0;
        ExtOp = 1'b0;
        LuiOp = 1'b0;
        ALUSrcA = 2'b0;
        ALUSrcB = 2'b0;
        PCSource =2'b0;
        ALUOp = 4'b0;
    end
    //--------------Your code above-----------------------

endmodule