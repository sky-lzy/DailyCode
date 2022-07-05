`timescale 1ns / 1ps

module test_cpu();
    
    reg reset;
    reg clk;
    
    PipelineCPU PipelineCPU_1(reset, clk);
    
    initial begin
        reset = 1;
        clk = 1;
        #100 reset = 0;
        #90000 $finish;
    end
    
    always #50 clk = ~clk;
    
endmodule
