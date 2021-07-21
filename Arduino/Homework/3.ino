#include <LiquidCrystal.h>
#include <TimerOne.h>
#include <String.h>
#include <HardwareSerial.h>
#include <Arduino.h>

//全局变量的定义
const int rs = 13, en = 12, d7 = 11, d6 = 10, d5 = 9, d4 = 8; //LCD引脚
const int R = 5, G = 4, B = 3;                                //OLED引脚
const int Rx = A0, Ry = A1, SW = 2;                           //摇杆引脚
const long interval = 10000;                                  //10ms刷新一次
unsigned long spend_time = 0;                                 //记录反应时间
unsigned long set_time = 0;                                   //记录设定时间
int flag = 0;                                                 //当前状态
int color = G;                                                //亮灯的颜色

//全局对象的构建
LiquidCrystal LCD(rs, en, d4, d5, d6, d7); //LCD对象

//初始化函数
void setup()
{
    Serial.begin(9600);
    randomSeed(analogRead(5));

    //OLED的初始化
    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);

    //LCD的初始化
    LCD.begin(16, 2);

    //摇杆初始化
    pinMode(SW, INPUT_PULLUP);

    //中断程序的初始化
    Timer1.initialize(interval);
    attachInterrupt(0, Isr2, FALLING);

    set_time = random(3000, 5000);
}

void loop()
{
    if (flag == 0) //复位状态
    {
    again:
        flag = 0;
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("Start!");

        set_time = random(3000, 5000);
        digitalWrite(color, LOW);
        color = random(3, 5);
        for (int i = 0; i < set_time / 10; i++)
        {
            delay(10);
            vertify();
            if (flag)
                goto again;
        }

        flag = 1;
        digitalWrite(color, HIGH);
        spend_time = 0;
        Timer1.attachInterrupt(Isr1);
    }
    else if (flag == 1) //游戏进行状态
    {
    }
    else if (flag == 2) //游戏停止状态
    {
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print(String(spend_time) + "ms");
        for (int i = 0; i < 500 && flag == 2; i++)
            delay(10);

        flag = 0;
    }

    vertify();
}

//定时中断程序
void Isr1()
{
    spend_time += 10;
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print(String(spend_time) + "ms");
}

//外界触发中断程序
void Isr2()
{
    Timer1.detachInterrupt();
    flag = 0;
}

//发送信息
void send_message(int meg)
{
    switch (meg)
    {
    case 1:
        Serial.print("Your action time is " + String(spend_time) + " ms!" + "\n");
        break;
    case 2:
        Serial.print("You moved the rocker in a wrong direction!\n");
        break;
    case 3:
        Serial.print("LED hasn't been lighted!\n");
        break;
    default:
        Serial.print("error!\n");
        break;
    }
}

void vertify()
{
    int x = analogRead(Rx);
    int y = analogRead(Ry);
    if ((x > 800 || x < 200 || y > 800 || y < 200) && flag != 2) //摇杆被推动
    {
        digitalWrite(color, LOW); //指示灯熄灭
        digitalWrite(R, HIGH);    //立刻亮红灯
        Timer1.detachInterrupt();

        if (flag == 0) //未亮灯之前已结束游戏
            send_message(3);
        else if (flag == 1) //结束游戏
        {
            if (color == G && y > 800 || color == B && x > 800) //正确推动
                send_message(1);
            else //错误推动
                send_message(2);
        }

        flag = 2;
        delay(500);
        digitalWrite(R, LOW);
    }
}