module clock (sysclk, clk);
    input sysclk;
    output clk;

    reg clk_temp;
    reg [13:0] counter;
    assign clk = clk_temp;

    always @(posedge sysclk)
    begin
        if (counter >= 14'b10_0111_0001_0000)
        begin
            counter <= 14'b0;
            clk_temp <= 1'b1;
        end
        else
        begin
            counter <= counter + 1'b1;
            clk_temp <= 1'b0;
        end
    end

endmodule