module ALU (ALUCtrl, Sign, in1, in2, out, zero);
    input  [4 : 0] ALUCtrl;
    input  Sign;
    input  [31: 0] in1;
    input  [31: 0] in2;
    output [31: 0] out;
    output zero;
    
endmodule