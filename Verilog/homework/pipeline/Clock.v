`timescale 1ns/1ps

module Clock (sysclk, reset, clk);
    input sysclk;
    input reset;
    output clk;

    assign clk = sysclk;
    // output reg clk;

    // always @(posedge reset or posedge sysclk) 
    // begin
    //     if (reset)
    //         clk <= 1'b0;
    //     else
    //         clk <= ~clk;
    // end

    // initial 
    // begin
    //     clk = 1'b0;
    // end
endmodule