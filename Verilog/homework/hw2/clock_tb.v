`timescale 1ns/1ps
`define PERIOD 10

module clock_tb ();
    reg sysclk;
    wire clk;

    initial begin
        sysclk = 1'b0;
        forever
        # (`PERIOD / 2) sysclk = ~sysclk;
    end

    clock my_clock(sysclk, clk);
endmodule