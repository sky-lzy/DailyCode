#include <TimerOne.h>

//引脚定义
#define ENC_A 2
#define ENC_B 3
#define STBY 4
#define ENA 6
#define IN1 10
#define IN2 11

//PID参数设置
#define Kp 1.0
#define Ki 0.3
#define Kd 0.5

//定义全局变量
const unsigned long time_period = 50000; //计时周期
const int goal_rate = 200;               //目标转速
const int output_min = -100;             //最小反馈
const int output_max = 100;              //最大反馈

int output_pwm = 0; //输出转速
int count = 0;      //计数
int rpm = 0;        //转速 转每分
double pwm = 100;   //控制误差
double d_pwm = 0;   //微分误差控制

double err = 0.0;    //误差
double p1_err = 0.0; //前一次误差
double p2_err = 0.0; //前两次误差

//计数函数
void Count()
{
    if (digitalRead(ENC_A) == LOW)
    {
        if (digitalRead(ENC_B) == LOW)
            count += 1;
        else if (digitalRead(ENC_B) == HIGH)
            count -= 1;
    }
}

//定时器中断
void TimerIsr()
{
    //计数
    rpm = count / (time_period / 1000000.0) * 60.0 / 260.0;
    count = 0;

    //PID调整
    output_pwm = PID(rpm, goal_rate);
}

//PID算法
double PID(const double now_rpm, const double goal_rpm)
{
    err = goal_rpm - now_rpm; //计算当前误差
    d_pwm = Kp * (err - p1_err) + Ki * err + Kd * ((err - p1_err) - (err - p2_err));

    //更新参数
    p2_err = p1_err;
    p1_err = err;
    pwm += d_pwm;

    //返回值限制在[output_min, output_max]中间
    return constrain(pwm, output_min, output_max);
    // return pwm;
}

//初始化函数
void setup()
{
    //初始化串口波特率
    Serial.begin(9600);

    //初始化引脚
    pinMode(ENC_A, INPUT);
    pinMode(ENC_B, INPUT);
    pinMode(STBY, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(ENA, OUTPUT);

    //初始化接口
    digitalWrite(STBY, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    //初始化中断函数
    attachInterrupt(0, Count, FALLING);
    Timer1.initialize(time_period);
    Timer1.attachInterrupt(TimerIsr);
}

//循环函数
void loop()
{
    //串口显示
    Serial.print("goal: ");
    Serial.print(goal_rate);
    Serial.print("  rpm: ");
    Serial.println(rpm);
    analogWrite(ENA, output_pwm);
}