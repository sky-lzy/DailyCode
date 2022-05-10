`timescale 1ns/1ps
`define SYS_PERIOD 10
`define CLK_PERIOD 100

module top_tb ();
    reg sysclk;
    reg key;
    reg res;
    wire [3:0] an;
    wire [7:0] leds;
    wire state;

    top my_top(sysclk, key, res, an, leds, state);

    initial
    begin
        forever
        # (`SYS_PERIOD / 2) sysclk = ~sysclk;
    end

    initial
    begin
        sysclk = 1'b0;
        key = 1'b0;
        res = 1'b0;

        # (`CLK_PERIOD * 15000) key = 1'b1;
        # (`CLK_PERIOD * 10) key = 1'b0;
        # (`CLK_PERIOD * 5000) res = 1'b1;
        # (`CLK_PERIOD * 10) res = 1'b0;
        # (`CLK_PERIOD * 1000);
        
        $finish;
    end
endmodule