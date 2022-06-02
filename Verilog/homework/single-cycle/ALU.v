
module ALU(in1, in2, ALUCtrl, Sign, out, zero);
	input [31:0] in1, in2;
	input [4:0] ALUCtrl;
	input Sign;
	output reg [31:0] out;
	output zero;
	
	// Your code below
	parameter ADD  = 5'b00000;
    parameter SUB  = 5'b00001;
    parameter AND  = 5'b00010;
    parameter OR   = 5'b00011;
    parameter XOR  = 5'b00100;
    parameter NOR  = 5'b00101;
    parameter SLT  = 5'b00110;
    parameter SLL  = 5'b10000;
    parameter SRL  = 5'b10001;
    parameter SRA  = 5'b10010;
    parameter NULL = 5'b11111;

    assign zero = ~|out;

    always @(*)
    begin
        case (ALUCtrl)
            ADD: out <= in1 + in2;
            SUB: out <= in1 - in2;
            AND: out <= in1 & in2;
            OR:  out <= in1 | in2;
            XOR: out <= in1 ^ in2;
            NOR: out <= ~(in1 | in2);
            SLT: begin if (Sign) out <= (in1[31] & ~in2[31]) | ((~in1[31] & ~in2[31]) & (in1 < in2)) | ((in1[31] & in2[31]) & (in1 > in2));
                       else out <= in1 < in2; end
            SLL: out <= in2 << in1;
            SRL: out <= in2 >> in1;
            SRA: out <= $signed(in2) >>> in1;
            default: out <= 32'b0;
        endcase
    end

    initial
    begin
        out = 32'b0;
    end
	// Your code above
	
endmodule