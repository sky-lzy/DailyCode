`timescale 1ns/1ps

module IF_ID_Reg (reset, clk, Control, PC_in, Instruction_in, PC_out, Instruction_out);
    //Input Clock Signals
    input reset;
    input clk;
    input [1:0] Control;
    //Input Data
    input [31:0] PC_in;
    input [31:0] Instruction_in;
    //Output Data
    output reg [31:0] PC_out;
    output reg [31:0] Instruction_out;

    always @(posedge reset or posedge clk)
    begin
        if (reset)
        begin
            PC_out <= 32'h00000000;
            Instruction_out <= 32'h00000000;
        end
        else 
        begin
            case (Control)
                2'b00: begin PC_out <= PC_in; Instruction_out <= Instruction_in; end
                2'b01: begin PC_out <= PC_out; Instruction_out <= Instruction_out; end
                default: begin PC_out <= 32'h00000000; Instruction_out <= 32'h00000000; end
            endcase
        end
    end

endmodule