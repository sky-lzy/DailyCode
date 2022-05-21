module add2 (sysclk, key, I, M, m, Y);
    input  sysclk;
    input  key;
    input  [31: 0] I;
    input  [2 : 0] M;
    input  [2 : 0] m;
    output [6 : 0] Y;

    reg work;
    reg [2 : 0] state;
    reg [6 : 0] Y;
    
    reg clk;
    reg [5 : 0] count;

    always @(posedge sysclk)
    begin
        if (count < 6'b11_0010)
            count <= count + 1'b1;
        else
        begin
            count <= 6'b0;
            clk <= ~clk;
        end
    end

    // always @(posedge clk or posedge key)
    always @(posedge sysclk or posedge key)
    begin
        if (key)
        begin
            work <= 1'b1;
            Y <= 7'b0;
            state <= 3'b0;
        end
        else
        begin
            if (work)
            begin
                case (state)
                    3'b000: begin if (((3'b000 >= m) & (3'b000 <= M)) | ((3'b000 >= M) & (3'b000 <= m))) Y <= Y + I[3 : 0]; state <= 3'b001; end
                    3'b001: begin if (((3'b001 >= m) & (3'b001 <= M)) | ((3'b001 >= M) & (3'b001 <= m))) Y <= Y + I[7 : 4]; state <= 3'b010; end
                    3'b010: begin if (((3'b010 >= m) & (3'b010 <= M)) | ((3'b010 >= M) & (3'b010 <= m))) Y <= Y + I[11: 8]; state <= 3'b011; end
                    3'b011: begin if (((3'b011 >= m) & (3'b011 <= M)) | ((3'b011 >= M) & (3'b011 <= m))) Y <= Y + I[15:12]; state <= 3'b100; end
                    3'b100: begin if (((3'b100 >= m) & (3'b100 <= M)) | ((3'b100 >= M) & (3'b100 <= m))) Y <= Y + I[19:16]; state <= 3'b101; end
                    3'b101: begin if (((3'b101 >= m) & (3'b101 <= M)) | ((3'b101 >= M) & (3'b101 <= m))) Y <= Y + I[23:20]; state <= 3'b110; end
                    3'b110: begin if (((3'b110 >= m) & (3'b110 <= M)) | ((3'b110 >= M) & (3'b110 <= m))) Y <= Y + I[27:24]; state <= 3'b111; end
                    3'b111: begin if (((3'b111 >= m) & (3'b111 <= M)) | ((3'b111 >= M) & (3'b111 <= m))) Y <= Y + I[31:28]; state <= 3'b000; work <= 1'b0; end
                endcase
            end
        end
    end

    initial
    begin
        work = 0;
        clk = 0;
        state = 3'b0;
        Y = 7'b0;
        count = 6'b0;
    end

endmodule