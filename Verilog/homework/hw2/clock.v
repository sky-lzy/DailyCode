module clock (sysclk, clk);
    input sysclk;
    output clk;

    reg clk_temp;
    reg [12:0] counter;
    // reg [2:0] counter;
    assign clk = clk_temp;

    always @(posedge sysclk)
    begin
        if (counter >= 13'b1_0011_1000_1000)
        // if (counter >= 3'b100)
        begin
            counter <= 13'b0;
            // counter <= 3'b0;
            clk_temp <= ~clk_temp;
        end
        else
            counter <= counter + 1'b1;
    end

    initial
    begin
        clk_temp = 1'b0;
        counter = 13'b0;
        // counter = 3'b0;
    end

endmodule