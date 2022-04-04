module detect (sys_clk, clk, res, in, dict, out);
    input  sys_clk;
    input  clk;
    input  res;
    input  in;
    output [5:0] dict;
    output out;

    reg [5:0] dict;
    wire out;
    wire clk_o;

    debounce xdebounce(sys_clk, clk, clk_o);

    always @(negedge res or posedge clk_o)
    begin
        if (res)
            dict <= 6'b0;
        else
            dict <= {dict[4:0], in};
    end

    assign out = (dict == 6'b101011);
endmodule