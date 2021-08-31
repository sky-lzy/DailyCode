/******************************
 * 开发环境：Arduino UNO
 * 模块：电机（连线情况见代码）
 * 功能：实现PID控制电机、板间通信
 * 编号：2
 * **************************** */

#include "SoftwareSerial.h"

//引脚接口声明
#define STBY 4
#define ENA 6
#define IN1 10
#define IN2 11
#define ENC_A 2
#define ENC_B 3

//运动模式
#define LEFT 1
#define RIGHT 2
#define FORWARD 3
#define STOP 4

//PID参数
#define Kp 0.003
#define Ki 0.6
#define Kd 1.3

//对象实例化
SoftwareSerial serial(0, 1);

//全局变量定义
int count = 0;															//计数
unsigned long curtime, oldtime;											//计时
const int goal_rspeed = 200;											//目标转速
double rpm;																//当前转速
int input_rspeed, output_rspeed, output_pwm, pre_err = 0, fore_err = 0; //保存数据
int mode = 0;

//发送消息
void GetMessage(SoftwareSerial &serial, int &mode)
{
	// Serial.print("Get! serial.available() = " + String(serial.available()) + "\n");
	if (serial.available() > 0)
		// mode = serial.readString()[0] - '0';
		Serial.print("Success! Mode = " + serial.readString());
}

//中断计数函数
void Code()
{
	if (digitalRead(ENC_B) == LOW)
	{
		if (digitalRead(ENC_A) == LOW) //正转
			count += 1;
		if (digitalRead(ENC_A) == HIGH) //反转
			count -= 1;
	}
}

//微分形式 PID函数
double dPID(double in, double goal)
{
	double err = goal - in;
	double d_PID = Kp * (err - pre_err) + Ki * err + Kd * ((err - pre_err) - (pre_err - fore_err));
	fore_err = pre_err;
	pre_err = err;
	return d_PID;
}

//运动状态：左转
void turn_left()
{
}

//运动状态：右转
void turn_right()
{
}

//运动状态：前进
void move_forward()
{
	//定时器测速
	curtime = millis();
	int dt = abs(curtime - oldtime);
	if (dt > 50)
	{
		rpm = (double)count * 20 * 60 / 260;
		count = 0;
		oldtime = millis();
		input_rspeed = rpm;
		output_rspeed += dPID(input_rspeed, goal_rspeed);
		output_rspeed = constrain(output_rspeed, 90, 450);
		output_pwm = 0.3 * output_rspeed;
	}

	analogWrite(ENA, output_pwm);
}

//初始化函数
void setup()
{
	//串口波特率设置
	Serial.begin(9600);
	serial.begin(9600);

	//初始化引脚
	pinMode(STBY, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(ENA, OUTPUT);
	digitalWrite(STBY, HIGH);
	digitalWrite(IN1, HIGH);
	digitalWrite(IN2, LOW);
	pinMode(ENC_A, INPUT);
	pinMode(ENC_B, INPUT);

	//初始化中断函数
	attachInterrupt(0, Code, FALLING);
}

void loop()
{
	GetMessage(serial, mode);

	switch (mode)
	{
	case LEFT:
		turn_left();
		break;

	case RIGHT:
		turn_right();
		break;

	case FORWARD:
		move_forward();
		break;

	case STOP:
		analogWrite(ENA, 0);
		break;
	default:
		break;
	}
	//延时保持稳定
	delay(25);
}
