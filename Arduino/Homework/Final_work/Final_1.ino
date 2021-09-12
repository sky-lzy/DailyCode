/******************************************
 * 开发环境：Arduino UNO
 * 模块：电机、LD3320语音识别（连线情况见代码）
 * 功能：语音识别功能、小车移动
 * 编号：1
 * **************************************** */

#include "ld3320.h"
#include <IRremote.h>

//引脚接口声明
//语音需要引脚: MI D12; MO D11; SCK D13; CS D4; RST; D9; IRQ D2; WR GND
#define ENA_1 3
#define ENA_2 5
#define STBY_1 6
#define STBY_2 7
#define IN1_1 A0
#define IN2_1 A1
#define IN1_2 A2
#define IN2_2 A3

//运动模式
#define LEFT 1
#define RIGHT 2
#define FORWARD 3
#define BACK 4
#define STOP 0

//对象实例化
VoiceRecognition Voice; //声明一个语音识别对象

//全局变量定义
int mode = STOP;	   //运动模式

//语音识别函数
void LD3320_work()
{
	int temp = Voice.read();
	if (temp != -1) //判断是否成功接受信息
		mode = temp;
}

//运动状态：左转
void turn_left()
{
	digitalWrite(IN1_1, HIGH);
	digitalWrite(IN2_1, LOW);
	digitalWrite(IN1_2, HIGH);
	digitalWrite(IN2_2, LOW);

	analogWrite(ENA_1, 25);
	analogWrite(ENA_2, 100);
	delay(25);
}

//运动状态：右转
void turn_right()
{
	digitalWrite(IN1_1, HIGH);
	digitalWrite(IN2_1, LOW);
	digitalWrite(IN1_2, HIGH);
	digitalWrite(IN2_2, LOW);

	analogWrite(ENA_1, 100);
	analogWrite(ENA_2, 25);
	delay(25);
}

//运动状态：前进
void move_forward()
{
	digitalWrite(IN1_1, HIGH);
	digitalWrite(IN2_1, LOW);
	digitalWrite(IN1_2, HIGH);
	digitalWrite(IN2_2, LOW);

	analogWrite(ENA_1, 50);
	analogWrite(ENA_2, 50);
	delay(50);
}

//运动状态: 后退
void move_back()
{
	digitalWrite(IN1_1, LOW);
	digitalWrite(IN2_1, HIGH);
	digitalWrite(IN1_2, LOW);
	digitalWrite(IN2_2, HIGH);

	analogWrite(ENA_1, 50);
	analogWrite(ENA_2, 50);
	delay(50);
}

//初始化函数
void setup()
{
	//串口波特率设置
	Serial.begin(9600);

	//初始化VoiceRecognition模块
	Voice.init();
	Voice.addCommand("zuo", LEFT);	   //添加左转指令
	Voice.addCommand("you", RIGHT);	   //添加右转指令
	Voice.addCommand("qian", FORWARD); //添加前进指令
	Voice.addCommand("dao", BACK);	   //添加后退指令
	Voice.addCommand("yi", STOP);	   //添加停止指令
	Voice.start();					   //开始识别

	//初始化引脚
	pinMode(STBY_1, OUTPUT);
	pinMode(STBY_2, OUTPUT);
	pinMode(IN1_1, OUTPUT);
	pinMode(IN1_2, OUTPUT);
	pinMode(IN2_1, OUTPUT);
	pinMode(IN2_2, OUTPUT);
	pinMode(ENA_1, OUTPUT);
	pinMode(ENA_2, OUTPUT);
	digitalWrite(STBY_1, HIGH);
	digitalWrite(STBY_2, HIGH);
	digitalWrite(IN1_1, HIGH);
	digitalWrite(IN2_1, LOW);
	digitalWrite(IN1_2, HIGH);
	digitalWrite(IN2_2, LOW);
}

void loop()
{
	LD3320_work();

	switch (mode)
	{
	case LEFT:
		turn_left();
		// Serial.print("Turn Left!");
		break;

	case RIGHT:
		turn_right();
		// Serial.print("Turn Right!");
		break;

	case FORWARD:
		move_forward();
		// Serial.print("Forward!\n");
		break;

	case BACK:
		move_back();
		break;

	case STOP:
		analogWrite(ENA_1, 0);
		analogWrite(ENA_2, 0);
		delay(50);
		// Serial.print("Stop!\n");
		break;
	default:
		break;
	}

	//延时保持稳定
	// delay(25);
}
