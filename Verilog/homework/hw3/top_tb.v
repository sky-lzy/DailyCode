`timescale 1ns/1ps
`define SYS_PERIOD 10
`define CLKS_PER_BIT 16'd868
// `define CLKS_PER_BIT 16'd10417

module top_tb ();
    reg clk;
    reg rst;
    reg mem2uart;
    reg Rx_Serial;

    wire recv_done;
    wire send_done;
    wire Tx_Serial;

    reg [7:0] Data [4096:1];

    UART_MEM my_UART_MEM
    (
        .clk(clk),
        .rst(rst),
        .mem2uart(mem2uart),
        .recv_done(recv_done),
        .send_done(send_done),
        .Rx_Serial(Rx_Serial),
        .Tx_Serial(Tx_Serial)
    );

    initial
    begin
        clk = 1'b0;
        rst = 1'b0;
        mem2uart = 1'b0;
        Rx_Serial = 1'b1;
        $readmemh("D:/Code/Verilog/homework/hw3/send.txt", Data);
        forever
        # (`SYS_PERIOD / 2) clk = ~clk;
    end

    integer i;
    integer j;
    initial
    begin
        # (`SYS_PERIOD * `CLKS_PER_BIT * 10)
        for (i = 1; i <= 4096; i = i + 1)
        begin
            # (`SYS_PERIOD * `CLKS_PER_BIT) Rx_Serial = 1'b0;
            for (j = 0; j < 8; j = j + 1)
            begin
                # (`SYS_PERIOD * `CLKS_PER_BIT) Rx_Serial = Data[i][j];
            end
            # (`SYS_PERIOD * `CLKS_PER_BIT) Rx_Serial = 1'b1;
        end

        # (`SYS_PERIOD * `CLKS_PER_BIT * 100) mem2uart = 1;
        # (`SYS_PERIOD * `CLKS_PER_BIT * 50000) mem2uart = 0; rst = 1;
        # (`SYS_PERIOD * `CLKS_PER_BIT) rst = 0;
        # (`SYS_PERIOD * `CLKS_PER_BIT * 100);

        $finish;
    end

endmodule