/*************************************************
 * 开发环境：Arduino UNO
 * 模块：红外接收模块、LED、舵机
 * 功能：实现红外信号传输、机械臂控制、LED工作状态显示
 * 编号：3
 * *********************************************** */

#include <IRremote.h>
#include <Servo.h>

#define RECV_PIN 13 //定义红外接收器的引脚为13
#define RED_1 2
#define GREEN_1 3
#define BLUE_1 4
#define RED_2 5
#define GREEN_2 6
#define BLUE_2 7
#define Servo_1 8
#define Servo_2 9

//全局对象的定义
IRrecv irrecv(RECV_PIN);
decode_results results; //解码结果放在 decode results结构的 result中
Servo servo_1;
Servo servo_2;

bool mode_1 = 0;
bool mode_2 = 0;
bool mode_3 = 0;
bool mode_4 = 0;
bool mode_5 = 0;
bool mode_6 = 0;

//熄灭所有灯
void LED_setoff()
{
	digitalWrite(RED_1, LOW);
	digitalWrite(GREEN_1, LOW);
	digitalWrite(BLUE_1, LOW);
	digitalWrite(RED_2, LOW);
	digitalWrite(GREEN_2, LOW);
	digitalWrite(BLUE_2, LOW);
}

//舵机一：向上移动
void moveup()
{
	LED_setoff();
	digitalWrite(RED_1, HIGH);
	digitalWrite(GREEN_2, HIGH);
	servo_1.writeMicroseconds(1400);
	bool flag = true;
	while (flag)
	{
		if (irrecv.decode(&results))
		{
			if (results.value == 0xFF38C7)
				flag = false;
			irrecv.resume();
		}
		delay(50);
	}
	servo_1.writeMicroseconds(1500);
	digitalWrite(RED_1, LOW);
	digitalWrite(GREEN_1, HIGH);
}

//舵机一：向下移动
void movedown()
{
	LED_setoff();
	digitalWrite(BLUE_1, HIGH);
	digitalWrite(GREEN_2, HIGH);
	servo_1.writeMicroseconds(1600);
	bool flag = true;
	while (flag)
	{
		if (irrecv.decode(&results))
		{
			if (results.value == 0xFF38C7)
				flag = false;
			irrecv.resume();
		}
		delay(50);
	}
	servo_1.writeMicroseconds(1500);
	digitalWrite(BLUE_1, LOW);
	digitalWrite(GREEN_1, HIGH);
}

//舵机二：开口打开
void moveleft()
{
	LED_setoff();
	digitalWrite(RED_2, HIGH);
	digitalWrite(GREEN_1, HIGH);
	bool flag = true;
	while (flag)
	{
		servo_2.writeMicroseconds(1400);
		delay(50);
		if (irrecv.decode(&results))
		{
			if (results.value == 0xFF38C7)
				flag = false;
			irrecv.resume();
		}
	}
	servo_2.writeMicroseconds(1500);
	digitalWrite(RED_2, LOW);
	digitalWrite(GREEN_2, HIGH);
}

//舵机二：开口闭合
void moveright()
{
	LED_setoff();
	digitalWrite(BLUE_2, HIGH);
	digitalWrite(GREEN_1, HIGH);
	bool flag = true;
	while (flag)
	{
		servo_2.writeMicroseconds(1600);
		delay(50);
		if (irrecv.decode(&results))
		{
			if (results.value == 0xFF38C7)
				flag = false;
			irrecv.resume();
		}
	}
	servo_2.writeMicroseconds(1500);
	digitalWrite(BLUE_2, LOW);
	digitalWrite(GREEN_2, HIGH);
}

void setup()
{
	Serial.begin(9600);

	//启动接收器
	irrecv.enableIRIn();

	//初始化舵机
	servo_1.attach(Servo_1);
	servo_2.attach(Servo_2);
	// servo_1.write(pos_1);
	// servo_2.write(pos_2);

	//初始化引脚
	pinMode(RED_1, OUTPUT);
	pinMode(GREEN_1, OUTPUT);
	pinMode(BLUE_1, OUTPUT);
	pinMode(RED_2, OUTPUT);
	pinMode(GREEN_2, OUTPUT);
	pinMode(BLUE_2, OUTPUT);
	LED_setoff();
	digitalWrite(GREEN_1, HIGH);
	digitalWrite(GREEN_2, HIGH);
}

void loop()
{
	if (irrecv.decode(&results)) //解码成功，收到一组红外讯号
	{
		switch (results.value)
		{
		case 0xFFA25D:// 1
			mode_1 = !mode_1;
			digitalWrite(RED_1, mode_1);
			break;

		case 0xFF629D:// 2
			mode_2 = !mode_2;
			digitalWrite(GREEN_1, mode_2);
			break;

		case 0xFFE21D:// 3
			mode_3 = !mode_3;
			digitalWrite(BLUE_1, mode_3);
			break;

		case 0xFF22DD:// 4
			mode_4 = !mode_4;
			digitalWrite(RED_2, mode_4);
			break;

		case 0xFF02FD:// 5
			mode_5 = !mode_5;
			digitalWrite(GREEN_2, mode_5);
			break;

		case 0xFFC23D:// 6
			mode_6 = !mode_6;
			digitalWrite(BLUE_2, mode_6);
			break;

		case 0xFF38C7:// OK
			break;

		case 0xFF18E7:// 上(机械臂: 上)
			digitalWrite(RED_2, HIGH);
			moveup();
			break;

		case 0xFF4AB5:// 下(机械臂: 下)
			digitalWrite(RED_2, HIGH);
			movedown();
			break;

		case 0xFF10EF:// 左(机械臂: 开)
			digitalWrite(RED_2, HIGH);
			moveleft();
			break;

		case 0xFF5AA5:// 右(机械臂: 关)
			digitalWrite(RED_2, HIGH);
			moveright();
			break;

		default:
			break;
		}
		irrecv.resume(); // 接收下一个值
	}
	delay(100);
}
