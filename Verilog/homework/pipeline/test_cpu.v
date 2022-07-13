`timescale 1ns / 1ps

module test_cpu();
    
    reg reset;
    reg clk;
    wire [7:0] LEDs;
    wire [11:0] ENs;
    
    PipelineCPU PipelineCPU_1(reset, clk, LEDs, ENs);
    
    initial begin
        reset = 1;
        clk = 1;
        #100 reset = 0;
        #1000000 $finish;
    end
    
    always #50 clk = ~clk;
    
endmodule
