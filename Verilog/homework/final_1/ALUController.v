module ALUController (OpCode, Funct, ALUCtrl, Sign);
    input  [5 : 0] OpCode;
    input  [5 : 0] Funct;
    output [4 : 0] ALUCtrl;
    output Sign;

    reg Sign;
    reg [4 : 0] ALUCtrl;

    parameter ADD = 5'b00000;
    parameter SUB = 5'b00001;
    parameter AND = 5'b00010;
    parameter OR  = 5'b00011;
    parameter XOR = 5'b00100;
    parameter NOR = 5'b00101;
    parameter SLT = 5'b00110;
    parameter SLL = 5'b10000;
    parameter SRL = 5'b10001;
    parameter SRA = 5'b10010;
    parameter NULL = 5'b11111;

    always @(*)
    begin
        case (OpCode)
            6'b0: 
            begin
                case (Funct)
                    6'h20: begin ALUCtrl <= ADD; Sign <= 1; end
                    6'h21: begin ALUCtrl <= ADD; Sign <= 0; end
                    6'h22: begin ALUCtrl <= SUB; Sign <= 1; end
                    6'h23: begin ALUCtrl <= SUB; Sign <= 0; end
                    6'h24: begin ALUCtrl <= AND; Sign <= 1; end
                    6'h25: begin ALUCtrl <=  OR; Sign <= 1; end
                    6'h26: begin ALUCtrl <= XOR; Sign <= 1; end
                    6'h27: begin ALUCtrl <= NOR; Sign <= 1; end
                    6'h00: begin ALUCtrl <= SLL; Sign <= 1; end
                    6'h02: begin ALUCtrl <= SRL; Sign <= 1; end
                    6'h03: begin ALUCtrl <= SRA; Sign <= 1; end
                    6'h2a: begin ALUCtrl <= SLT; Sign <= 1; end
                    6'h2b: begin ALUCtrl <= SLT; Sign <= 0; end
                    default: begin ALUCtrl <= NULL; Sign <= 0; end
                endcase
            end
            6'h08: begin ALUCtrl <= ADD; Sign <= 1; end
            6'h09: begin ALUCtrl <= ADD; Sign <= 0; end
            6'h0c: begin ALUCtrl <= AND; Sign <= 1; end
            6'h0a: begin ALUCtrl <= SLT; Sign <= 1; end
            6'h0b: begin ALUCtrl <= SLT; Sign <= 0; end
            default: begin ALUCtrl <= NULL; Sign <= 0; end
        endcase
    end

endmodule