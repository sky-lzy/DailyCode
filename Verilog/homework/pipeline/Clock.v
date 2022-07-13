`timescale 1ns/1ps

module Clock (sysclk, reset, clk);
    input sysclk;
    input reset;
    output reg clk;

    reg [1:0] count;

    always @(posedge reset or posedge sysclk) 
    begin
        if (reset)
        begin
            clk <= 1'b0;
            count <= 2'b0;
        end
        else if (count >= 2'b11)
        begin
            clk <= ~clk;
            count <= 2'b0;
        end
        else count <= count + 1'b1;
    end

    initial 
    begin
        clk = 1'b0;
        count = 2'b0;
    end
endmodule