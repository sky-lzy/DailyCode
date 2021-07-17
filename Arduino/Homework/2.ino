#include <U8glib.h>
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "String.h"

//初始化信息
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);
SoftwareSerial softserial(2, 3);

//设置全局变量
String passward("");       //蓝牙传递的信息
char passward_str[7] = ""; //需打印的验证码
int32_t time_count = 0;    //记录时间
int flag = 0;              //判定状态

//绘制函数，打印 passward_str
void draw()
{
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(40, 20, passward_str);
}

//生成验证码函数
void send()
{
    //生成六位随机验证码
    for (int i = 0; i < 6; i++)
    {
        passward_str[i] = random(9) + '0';
    }
    passward = passward_str;

    //在OLED上显示验证码
    u8g.firstPage();
    do
    {
        draw();
    } while (u8g.nextPage());
    softserial.print("the code has been sent");
    time_count = millis(); //开始计时
    flag = 1;              //进入第一等待过程
}

//初始化函数
void setup()
{
    softserial.begin(9600);
    randomSeed(analogRead(5)); //设置随机数种子
}

//循环函数
void loop()
{
    if (flag == 0) //初始状态
    {
        //非工作状态输出"000000"
        for (int i = 0; i < 6; i++)
            passward_str[i] = '0';
        u8g.firstPage();
        do
        {
            draw();
        } while (u8g.nextPage());

        //接受信息
        if (softserial.available())
        {
            String input = softserial.readString();
            if (input == "request")
            {
                send();
            }
            else
                softserial.print("error");
        }
        else
            delay(25);
    }
    else if (flag == 1) //第一等待状态
    {
        if (softserial.available())
        {
            String input = softserial.readString();
            if (input == "request") //请求过于频繁
            {
                softserial.print("request later please");
            }
            else if (input == passward)
            {
                softserial.print("pass");
                flag = 0;
            }
            else
                softserial.print("fail");
        }
        if (millis() - time_count >= 10000) //超时进入第二等待状态
            flag = 2;
    }
    else //第二等待状态
    {
        if (softserial.available())
        {
            String input = softserial.readString();
            if (input == "request")
                send();
            else if (input == passward)
            {
                softserial.print("pass");
                flag = 0;
            }
            else
                softserial.print("fail");
        }
        if (millis() - time_count >= 25000) //超时验证码过期
        {
            flag = 0;
            softserial.print("the code is overdue");
        }
    }
}