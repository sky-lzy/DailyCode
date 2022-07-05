`timescale 1ns/1ps

module MEM_WB_Reg (
    reset, clk, 
    Data_in, RegWrAddr_in, RegWrite_in, 
    Data_out, RegWrAddr_out, RegWrite_out
    );
    
    //Input Signals
    input reset;
    input clk;
    //Input Data
    input [31:0] Data_in;
    input [4:0] RegWrAddr_in;
    input RegWrite_in;
    //Output Data
    output reg [31:0] Data_out;
    output reg [4:0] RegWrAddr_out;
    output reg RegWrite_out; 

    always @(posedge reset or posedge clk) 
    begin
        if (reset)
        begin
            Data_out <= 32'h00000000;
            RegWrAddr_out <= 5'h00;
            RegWrite_out <= 1'b0;
        end
        else
        begin
            Data_out <= Data_in;
            RegWrAddr_out <= RegWrAddr_in;
            RegWrite_out <= RegWrite_in;
        end
    end

endmodule