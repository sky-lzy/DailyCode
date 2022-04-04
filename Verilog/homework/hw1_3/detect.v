module detect (sys_clk, clk, res, state, in, out);
    input  sys_clk;
    input  clk;
    input  res;
    input  in;
    output [2:0] state;
    output out;

    parameter s0 = 3'b000;
    parameter s1 = 3'b001;
    parameter s2 = 3'b010;
    parameter s3 = 3'b011;
    parameter s4 = 3'b100;
    parameter s5 = 3'b101;

    reg  out;
    reg  [2:0] state;
    wire clk_o;

    debounce xdebounce(sys_clk, clk, clk_o);
    always @(negedge res or posedge clk_o)
    begin
        if (res)
        begin
            state <= s0;
            out <= 1'b0;
        end
        else
        begin
            case (state)
                s0: begin out <= 1'b0; if (in) state <= s1; else state <= s0; end
                s1: begin out <= 1'b0; if (in) state <= s1; else state <= s2; end
                s2: begin out <= 1'b0; if (in) state <= s3; else state <= s0; end
                s3: begin out <= 1'b0; if (in) state <= s1; else state <= s4; end
                s4: begin out <= 1'b0; if (in) state <= s5; else state <= s0; end
                s5: begin if (in) begin state <= s0; out <= 1'b1; end  else begin state <= s4; out <= 1'b0; end end
                default: begin state <= s0; out <= 1'b0; end
            endcase
        end
    end

endmodule