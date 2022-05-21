`timescale 1ns/1ps
`define SYS_PERIOD 10
// `define CLK_PERIOD 1000
`define CLK_PERIOD 10

module add2_tb ();
    reg  sysclk;
    reg  key;
    reg  [31: 0] I;
    reg  [2 : 0] M;
    reg  [2 : 0] m;
    wire [6 : 0] Y;

    add2 my_add2(sysclk, key, I, M, m, Y);

    initial
    begin
        sysclk = 1'b0;
        key = 1'b0;
        I = 31'b0;
        M = 3'b0;
        m = 3'b0;
        forever
        # (`SYS_PERIOD / 2) sysclk = ~sysclk;
    end

    initial
    begin
        # (`CLK_PERIOD)
        I[31: 0] = 32'b1111_1101_1011_1001_1000_0110_0100_0001;

        // M2M1M0 = m2m1m0
        # (`CLK_PERIOD)
        M[2 : 0] = 3'b000;
        m[2 : 0] = 3'b000;
        # (`SYS_PERIOD)
        key = 1'b1;
        # (`SYS_PERIOD)
        key = 1'b0;
        # (`CLK_PERIOD * 15)

        # (`CLK_PERIOD)
        M[2 : 0] = 3'b100;
        m[2 : 0] = 3'b100;
        # (`SYS_PERIOD)
        key = 1'b1;
        # (`SYS_PERIOD)
        key = 1'b0;
        # (`CLK_PERIOD * 15)

        # (`CLK_PERIOD)
        M[2 : 0] = 3'b110;
        m[2 : 0] = 3'b110;
        # (`SYS_PERIOD)
        key = 1'b1;
        # (`SYS_PERIOD)
        key = 1'b0;
        # (`CLK_PERIOD * 15)

        // M2M1M0 > m2m1m0
        # (`CLK_PERIOD)
        M[2 : 0] = 3'b111;
        m[2 : 0] = 3'b000;
        # (`SYS_PERIOD)
        key = 1'b1;
        # (`SYS_PERIOD)
        key = 1'b0;
        # (`CLK_PERIOD * 15)

        # (`CLK_PERIOD)
        M[2 : 0] = 3'b101;
        m[2 : 0] = 3'b010;
        # (`SYS_PERIOD)
        key = 1'b1;
        # (`SYS_PERIOD)
        key = 1'b0;
        # (`CLK_PERIOD * 15)

        # (`CLK_PERIOD)
        M[2 : 0] = 3'b010;
        m[2 : 0] = 3'b001;
        # (`SYS_PERIOD)
        key = 1'b1;
        # (`SYS_PERIOD)
        key = 1'b0;
        # (`CLK_PERIOD * 15)

        // M2M1M0 < m2m1m0
        # (`CLK_PERIOD)
        M[2 : 0] = 3'b000;
        m[2 : 0] = 3'b111;
        # (`SYS_PERIOD)
        key = 1'b1;
        # (`SYS_PERIOD)
        key = 1'b0;
        # (`CLK_PERIOD * 15)

        # (`CLK_PERIOD)
        M[2 : 0] = 3'b011;
        m[2 : 0] = 3'b110;
        # (`SYS_PERIOD)
        key = 1'b1;
        # (`SYS_PERIOD)
        key = 1'b0;
        # (`CLK_PERIOD * 15)

        # (`CLK_PERIOD)
        M[2 : 0] = 3'b001;
        m[2 : 0] = 3'b011;
        # (`SYS_PERIOD)
        key = 1'b1;
        # (`SYS_PERIOD)
        key = 1'b0;
        # (`CLK_PERIOD * 15)

        # (`CLK_PERIOD * 15)
        $finish;
    end

endmodule