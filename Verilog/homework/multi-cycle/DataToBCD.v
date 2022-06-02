module DataToBCD(Data, BCD_state, ENs, BCDs);
input [15:0] Data;
input [1:0] BCD_state;
output [3:0] ENs;
output [6:0] BCDs;

wire [3:0] DataOut;
assign DataOut = (BCD_state==2'b00)? Data[3:0]:
                 (BCD_state==2'b01)? Data[7:4]:
                 (BCD_state==2'b10)? Data[11:8]:
                 (BCD_state==2'b11)? Data[15:12]:
                 2'b0;

assign ENs = (BCD_state==3'b000)? 4'b0001:
             (BCD_state==3'b001)? 4'b0010:
             (BCD_state==3'b010)? 4'b0100:
             (BCD_state==3'b011)? 4'b1000:
             4'b0;

assign  BCDs=(DataOut==4'h0)?7'b0111111:
             (DataOut==4'h1)?7'b0000110:
             (DataOut==4'h2)?7'b1011011:
             (DataOut==4'h3)?7'b1001111:
             (DataOut==4'h4)?7'b1100110:
             (DataOut==4'h5)?7'b1101101:
             (DataOut==4'h6)?7'b1111101:
             (DataOut==4'h7)?7'b0000111:
             (DataOut==4'h8)?7'b1111111:
             (DataOut==4'h9)?7'b1101111:
             (DataOut==4'ha)?7'b1110111:
             (DataOut==4'hb)?7'b1111100:
             (DataOut==4'hc)?7'b0111001:
             (DataOut==4'hd)?7'b1011110:
             (DataOut==4'he)?7'b1111001:
             (DataOut==4'hf)?7'b1110001:
             7'b0;

endmodule
