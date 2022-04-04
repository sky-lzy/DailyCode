module top (sys_clk, clk, res, en, leds);
    input  sys_clk;
    input  clk;
    input  res;
    output en;
    output [6:0] leds;

    wire [6:0] leds;
    assign en = 1'b1;
    reg [3:0] counter;
    wire clk_o;

    debounce xdebounce(sys_clk, clk, clk_o);

    always @(negedge res or posedge clk_o)
    begin
        if(res)
            counter <= 4'b0;
        else
            if (counter == 4'b1001)
                counter <= 4'b0;
            else
                counter <= counter + 1;
    end

    BCD7 bcd27seg (counter, leds);

endmodule