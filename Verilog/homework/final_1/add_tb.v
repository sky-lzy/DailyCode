`timescale 1ns/1ps
`define SYS_PERIOD 10
`define PERIOD 1000

module add_tb ();
    reg  [31: 0] I;
    reg  [2 : 0] M;
    reg  [2 : 0] m;
    wire [6 : 0] Y;

    add my_add(I, M, m, Y);

    initial
    begin
        I[31: 0] = 32'b0;
        M[2 : 0] = 3'b0;
        m[2 : 0] = 3'b0;

        # (`PERIOD)
        I[31: 0] = 32'b1111_1101_1011_1001_1000_0110_0100_0001;
        
        // M2M1M0 = m2m1m0
        # (`PERIOD)
        M[2 : 0] = 3'b000;
        m[2 : 0] = 3'b000;
        # (`PERIOD)
        M[2 : 0] = 3'b100;
        m[2 : 0] = 3'b100;
        # (`PERIOD)
        M[2 : 0] = 3'b110;
        m[2 : 0] = 3'b110;

        // M2M1M0 > m2m1m0
        # (`PERIOD)
        M[2 : 0] = 3'b111;
        m[2 : 0] = 3'b000;
        # (`PERIOD)
        M[2 : 0] = 3'b101;
        m[2 : 0] = 3'b010;
        # (`PERIOD)
        M[2 : 0] = 3'b010;
        m[2 : 0] = 3'b001;

        // M2M1M0 < m2m1m0
        # (`PERIOD)
        M[2 : 0] = 3'b000;
        m[2 : 0] = 3'b111;
        # (`PERIOD)
        M[2 : 0] = 3'b011;
        m[2 : 0] = 3'b110;
        # (`PERIOD)
        M[2 : 0] = 3'b001;
        m[2 : 0] = 3'b011;

        # (`PERIOD)
        $finish;
    end
endmodule