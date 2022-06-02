
module ALUControl(OpCode, Funct, ALUCtrl, Sign);
	input [5:0] OpCode;
	input [5:0] Funct;
	output reg [4:0] ALUCtrl;
	output Sign;
	
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

    always @(*)
    begin
        case (OpCode)
            6'b0: 
            begin
                case (Funct)
                    6'h20:   ALUCtrl <= ADD; 
                    6'h21:   ALUCtrl <= ADD; 
                    6'h22:   ALUCtrl <= SUB; 
                    6'h23:   ALUCtrl <= SUB; 
                    6'h24:   ALUCtrl <= AND; 
                    6'h25:   ALUCtrl <=  OR; 
                    6'h26:   ALUCtrl <= XOR; 
                    6'h27:   ALUCtrl <= NOR; 
                    6'h00:   ALUCtrl <= SLL; 
                    6'h02:   ALUCtrl <= SRL; 
                    6'h03:   ALUCtrl <= SRA; 
                    6'h2a:   ALUCtrl <= SLT; 
                    6'h2b:   ALUCtrl <= SLT; 
                    default: ALUCtrl <= NULL;
                endcase
            end
            6'h23:   ALUCtrl <= ADD; 
            6'h2b:   ALUCtrl <= ADD; 
            6'h0f:   ALUCtrl <= ADD; 
            6'h08:   ALUCtrl <= ADD; 
            6'h09:   ALUCtrl <= ADD; 
            6'h0c:   ALUCtrl <= AND; 
            6'h0a:   ALUCtrl <= SLT; 
            6'h0b:   ALUCtrl <= SLT; 
            6'h04:   ALUCtrl <= SUB; 
            default: ALUCtrl <= NULL;
        endcase
    end

    assign Sign = (OpCode == 6'h09 || OpCode == 6'h0b || (OpCode == 6'h0 && (Funct == 6'h21 || Funct == 6'h23 || Funct ==6'h2b))) ? 1'b0 : 1'b1;

    initial
    begin
        ALUCtrl = 5'b0;
    end
	// Your code above

endmodule
