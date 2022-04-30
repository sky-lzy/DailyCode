module top (sysclk, key, res, an, leds, state);
    input sysclk;
    input key;
    input res;
    output [3:0] an;
    output [7:0] leds;
    output state;

    reg [3:0] an;
    wire [7:0] leds;

    wire clk;
    reg [13:0] count;
    reg [15:0] bcd;
    reg [1:0] an_temp;
    reg [3:0] temp_led;
    reg [2:0] temp_state;

    assign state = temp_state[0];

    clock newclock(sysclk, clk);

    always @(posedge res or posedge clk)
    begin
        if (res)
        begin
            temp_state <= 2'b0;
            count <= 10'b0;
            an <= 4'b0;
        end
        else
            if(temp_state == 2'b0)
                if(count < 14'b10_0111_0001_0000)
                    count <= count + 1'b1;
                else
                begin
                    temp_state <= 2'b01;
                    count <= 10'b0;
                    bcd <= 16'b0;
                end
            else if(temp_state == 2'b01)
                if (key == 1'b0)
                begin
                    if (bcd[3:0] == 4'b1001)
                    begin
                        bcd[3:0] <= 4'b0;
                        if (bcd[7:4] == 4'b1001)
                        begin
                            bcd[7:4] <= 4'b0;
                            if (bcd[11:8] == 4'b1001)
                            begin
                                bcd[11:8] <= 4'b0;
                                if (bcd[15:12] == 4'b1001)
                                    begin
                                        temp_state <= 2'b10;
                                        bcd <= 16'b1001_1001_1001_1001;
                                    end
                                else bcd[15:12] <= bcd[15:12] + 1'b1;
                            end
                            else bcd[11:8] <= bcd[11:8] + 1'b1;
                        end
                        else bcd[7:4] <= bcd[7:4] + 1'b1;
                    end
                    else bcd[3:0] <= bcd[3:0] + 1'b1;
                    an_temp <= an_temp + 1'b1;
                    an <= (4'b0001 << an_temp);
                    case (an_temp)
                        2'b00: temp_led <= bcd[3:0];
                        2'b01: temp_led <= bcd[7:4];
                        2'b10: temp_led <= bcd[11:8];
                        2'b11: temp_led <= bcd[15:12];
                        default: temp_led <= 4'b0;
                    endcase
                end
                else
                begin
                temp_state <= 2'b10;
                count <= 10'b0;
                end
            else
            begin
                an_temp <= an_temp + 1'b1;
                an <= (4'b0001 << an_temp);
                case (an_temp)
                    2'b00: temp_led <= bcd[3:0];
                    2'b01: temp_led <= bcd[7:4];
                    2'b10: temp_led <= bcd[11:8];
                    2'b11: temp_led <= bcd[15:12];
                    default: temp_led <= 4'b0;
                endcase
            end
    end

    LED7 led7(temp_led, leds[6:0]);
    assign leds[7] = an[1];

endmodule