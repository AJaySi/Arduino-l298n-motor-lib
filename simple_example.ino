// Motor A connections
int steerPin = 5;
int in1 = 4;
int in2 = 2;
// Motor B connections
int speedPin = 6;
int in3 = 9;
int in4 = 10;

void setup()
{
	// Set all the motor control pins to outputs
	pinMode(steerPin, OUTPUT);
	pinMode(speedPin, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void loop()
{
	directionControl();
	delay(1000);
	speedControl();
	delay(1000);
}

// This function lets you control spinning direction of motors
void directionControl()
{
	// Set motors to maximum speed
	// For PWM maximum possible values are 0 to 255
	analogWrite(steerPin, 255);
	analogWrite(speedPin, 255);

	// Turn on motor A & B
	digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
	delay(2000);
	
	// Now change motor directions
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	delay(2000);
	
	// Turn off motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

// This function lets you control speed of the motors
void speedControl()
{
	// Turn on motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	
	// Accelerate from zero to maximum speed
	for (int i = 0; i < 256; i++)
	{
		analogWrite(enA, i);
		analogWrite(enB, i);
		delay(20);
	}
	
	// Reduce Speed from maximum speed to zero
	for (int i = 255; i >= 0; --i)
	{
		analogWrite(enA, i);
		analogWrite(enB, i);
		delay(20);
	}
	
	// Turn off motors
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}
