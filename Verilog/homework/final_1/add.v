module add (I, M, m, Y);
    input  [31: 0] I;
    input  [2 : 0] M;
    input  [2 : 0] m;
    output [6 : 0] Y;

    wire [7 : 0] conf;
    wire [31: 0] out_1;
    wire [19: 0] out_2;
    wire [11: 0] out_3;
    wire [6 : 0] Y;

    assign conf[0] = ((3'b000 >= m) & (3'b000 <= M)) | ((3'b000 >= M) & (3'b000 <= m));
    assign conf[1] = ((3'b001 >= m) & (3'b001 <= M)) | ((3'b001 >= M) & (3'b001 <= m));
    assign conf[2] = ((3'b010 >= m) & (3'b010 <= M)) | ((3'b010 >= M) & (3'b010 <= m));
    assign conf[3] = ((3'b011 >= m) & (3'b011 <= M)) | ((3'b011 >= M) & (3'b011 <= m));
    assign conf[4] = ((3'b100 >= m) & (3'b100 <= M)) | ((3'b100 >= M) & (3'b100 <= m));
    assign conf[5] = ((3'b101 >= m) & (3'b101 <= M)) | ((3'b101 >= M) & (3'b101 <= m));
    assign conf[6] = ((3'b110 >= m) & (3'b110 <= M)) | ((3'b110 >= M) & (3'b110 <= m));
    assign conf[7] = ((3'b111 >= m) & (3'b111 <= M)) | ((3'b111 >= M) & (3'b111 <= m));

    assign out_1[3 : 0] = conf[0]?I[3 : 0]:4'b0;
    assign out_1[7 : 4] = conf[1]?I[7 : 4]:4'b0;
    assign out_1[11: 8] = conf[2]?I[11: 8]:4'b0;
    assign out_1[15:12] = conf[3]?I[15:12]:4'b0;
    assign out_1[19:16] = conf[4]?I[19:16]:4'b0;
    assign out_1[23:20] = conf[5]?I[23:20]:4'b0;
    assign out_1[27:24] = conf[6]?I[27:24]:4'b0;
    assign out_1[31:28] = conf[7]?I[31:28]:4'b0;

    assign out_2[4 : 0] = out_1[3 : 0] + out_1[7 : 4];
    assign out_2[9 : 5] = out_1[11: 8] + out_1[15:12];
    assign out_2[14:10] = out_1[19:16] + out_1[23:20];
    assign out_2[19:15] = out_1[27:24] + out_1[31:28];

    assign out_3[5 : 0] = out_2[4 : 0] + out_2[9 : 5];
    assign out_3[11: 6] = out_2[14:10] + out_2[19:15];

    assign Y[6 : 0] = out_3[5 : 0] + out_3[11: 6];
    
endmodule