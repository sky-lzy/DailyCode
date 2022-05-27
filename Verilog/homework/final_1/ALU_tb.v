`timescale 1ns/1ps
`define CLOCK 10
`define PERIOD 100

module ALU_tb ();
    reg          sysclk;
    reg  [5 : 0] OpCode;
    reg  [5 : 0] Funct;
    wire [4 : 0] ALUCtrl;
    wire         Sign;
    reg  [31: 0] in1;
    reg  [31: 0] in2;
    wire [31: 0] out;
    wire         zero;

    ALUController my_ALUController(OpCode, Funct, ALUCtrl, Sign);
    ALU my_ALU(ALUCtrl, Sign, in1, in2, out, zero);

    initial
    begin
        sysclk = 1'b0;
        OpCode = 6'b0;
        Funct  = 6'b0;
        in1    = 32'b0;
        in2    = 32'b0;
        forever
        # (`CLOCK / 2) sysclk <= ~sysclk;
    end

    initial
    begin
        # (`PERIOD)
        # (`PERIOD) OpCode = 6'h23; in1 = 32'hABCD0000; in2 = 32'h0000007F; // lw
        # (`PERIOD) OpCode = 6'h2b; in1 = 32'h12340000; in2 = 32'h00000044; // sw
        # (`PERIOD) OpCode = 6'h0f; in1 = 32'h0;        in2 = 32'hABCD1234; // lui
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h20; in1 = 32'hABCD1234; in2 = 32'h4321DCBA; // add
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h21; in1 = 32'h1234ABCD; in2 = 32'hDCBA4321; // addu
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h22; in1 = 32'hABCD1234; in2 = 32'h4321DCBA; // sub
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h23; in1 = 32'hDCBA4321; in2 = 32'h1234ABCD; // subu
        # (`PERIOD) OpCode = 6'h08; in1 = 32'hABCD0000; in2 = 32'h0000007F; // addi
        # (`PERIOD) OpCode = 6'h09; in1 = 32'h12340000; in2 = 32'h00000044; // addiu
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h24; in1 = 32'hABCD1234; in2 = 32'h4321DCBA; // and
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h25; in1 = 32'h1234ABCD; in2 = 32'hDCBA4321; // or
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h26; in1 = 32'hABCD1234; in2 = 32'h4321DCBA; // xor
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h27; in1 = 32'h1234ABCD; in2 = 32'hDCBA4321; // nor
        # (`PERIOD) OpCode = 6'h0c; in1 = 32'hABCD0000; in2 = 32'h0000007F; // andi
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h0;  in1 = 32'hABCD1234; in2 = 32'h00000004; // sll
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h02; in1 = 32'hABCD1234; in2 = 32'h00000004; // srl
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h03; in1 = 32'hABCD1234; in2 = 32'h00000004; // sra
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h2a; in1 = 32'hABCD1234; in2 = 32'h00000004; // slt
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h2b; in1 = 32'hABCD1234; in2 = 32'h00000004; // sltu
        # (`PERIOD) OpCode = 6'h0a; in1 = 32'hABCD1234; in2 = 32'h00000004; // slti
        # (`PERIOD) OpCode = 6'h0b; in1 = 32'hABCD1234; in2 = 32'h00000004; // sltui
        # (`PERIOD) OpCode = 6'h04; in1 = 32'hABCD1111; in2 = 32'hABCD1112; // beq
        # (`PERIOD) OpCode = 6'h02; // j
        # (`PERIOD) OpCode = 6'h03; // jal
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h08; // jr
        # (`PERIOD) OpCode = 6'h0;  Funct = 6'h09; // jalr
        # (`PERIOD)
        $finish;
    end

endmodule