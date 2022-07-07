`timescale 1ns/1ps

module Clock (sysclk, reset, clk);
    input sysclk;
    input reset;
    output reg clk;

    // parameter number = 2'b10;

    always @(posedge reset or posedge sysclk) 
    begin
        if (reset)
            clk <= 1'b0;
        else 
            clk <= ~clk;
    end

    initial 
    begin
        clk = 1'b0;
    end
endmodule