int TrgPin = 11;
int EcoPin = 12;
int beep = A3;
int R = 2;
int G = 3;
float dist;

void setup()
{
	Serial.begin(9600);
	pinMode(TrgPin, OUTPUT);
	pinMode(EcoPin, INPUT);
	pinMode(beep, OUTPUT);
}

void loop()
{
	digitalWrite(TrgPin, LOW);
	delayMicroseconds(8);
	digitalWrite(TrgPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrgPin, LOW);
	dist = pulseIn(EcoPin, HIGH) / 58.0;
	digitalWrite(G, LOW);

	if (dist <= 20)
	{
		digitalWrite(beep, HIGH);
		digitalWrite(R, HIGH);
		delay(100);
		digitalWrite(beep, LOW);
		digitalWrite(R, LOW);
		delay(150);
	}
	else
	{
		digitalWrite(G, HIGH);
		delay(100);
	}
}