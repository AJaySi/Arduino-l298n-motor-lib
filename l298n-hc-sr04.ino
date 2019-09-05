//Credits: The NewPing library written by Tim Eckel.
#include <NewPing.h>

/*
  Most of the present self driving car are Visual image based and
  mimiced around human brain's neural network. This is computationally expensive.

  A BlindCar is devoid of visuals, and self drives much like a blind person.

  Design Details:
  1) Obstacle Detection:
  In its infancy, there is only obstacle detection with HC-SR04.

  2). Movement:
  At all points, always Avoid collision. A BlindCar cannot judge the impact collision.
  With #1, we can reliably, move in front & Back.

  -> Reliable sensor readings:
  1). Using kalman filters, when required.
  2). For HC-SR04, median filter is used
  (Refer: http://dlacko.org/blog/2016/01/24/remove-impulse-noise-from-ultrasonic/)

*/


// Include the NewPing library. Instructions at https://playground.arduino.cc/Code/NewPing/
#define triggerPinFront 8
#define echoPinFront 7
#define triggerPinBack 13
#define echoPinBack 12
#define MAX_DISTANCE_BACK 250
#define MAX_DISTANCE_FRONT 350

// Front Motor A connections
int enA = 5;
int in1 = 2;
int in2 = 11;
// Back Motor B connections
int enB = 6;
int in3 = 9;
int in4 = 10;

// Constructor: NewPing sonar(trigger_pin, echo_pin [, max_cm_distance]);
// Initializes NewPing to use pin 12(trigger output) and pin 11 for echo input, with max_ping_distance to 350cm
NewPing sonarFront(triggerPinFront, echoPinFront, MAX_DISTANCE_FRONT);
NewPing sonarBack(triggerPinBack, echoPinBack, MAX_DISTANCE_BACK);

float duration, distance;

void setup()
{
  // Start the serial monitor, at 9600 baudrate.
  Serial.begin(9600);

  Serial.println(F("Engine Initialise"));
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  Serial.println(F("Setup Complete."));
}

void loop()
{
  Serial.println("############## NEW LOOP : ################");
  float backDistance = back_distance();
  Serial.println(F("Back Object distance is: "));
  Serial.print(backDistance);
  Serial.println(" cms");

  float frontDistance = front_distance();
  Serial.println(F("Front object distance is: "));
  Serial.print(frontDistance);
  Serial.println(" cms");

  // StopAll Condition: Back & Obstacle are at collision danger.
  // Present threshold is 4cms.
  if (frontDistance <= 5 && backDistance <= 5)
  {
    Serial.println(F("---- CONDITION: STOP: No Where To Go !"));
    // Set StopAll Flag. Motors Down.
    stopCar();
    // TBD : Getting out of tight corners.
  }
  // StopThink : When there are no obstacles, what to do.
  // Does BlindCar need obstacles to move around ?
  else if (frontDistance >= 50 && backDistance >= 50)
  {
    Serial.println(F("---- CONDITION : PAUSE: No Obstacles in Front/Back at 50 cms."));
  }
  // GoFront : If frontDistance is greater than backDistance by 20 cms
  else if ((frontDistance - backDistance) > 20)
  {
    Serial.println(F("---- CONDITION : FRONT: Front_obstacle > Back_obstacle by 20cms."));
    moveFront();
  }
  else if ((backDistance - frontDistance) > 20)
  {
    Serial.println(F("---- CONDITION : BACK: Front_obstacle < Back_obstacle by 20cms."));
    moveBack();
  }
  else if ((frontDistance > backDistance) && (frontDistance - backDistance) > 10)
  {
    Serial.println(F("---- CONDITION : FRONT: Safe for 10cms"));
    moveFront();
  }
  else if ((backDistance > frontDistance) && (backDistance - frontDistance) > 10)
  {
    Serial.println(F("---- CONDITION : BACK: Safe for 10cms"));
    moveBack();
  }

  //Debug
  Serial.println("");
  
}


// Common function to Move the car forward
void moveFront()
{
  Serial.println(F("Move Front."));
  analogWrite(enB, 250);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Common function to move the car back
void moveBack()
{
  Serial.println(F("Move Back"));
  analogWrite(enB, 250);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Common function to move Left
void left()
{
  Serial.println(F(" Move Left"));
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

// Common function to move right
void right()
{
  Serial.println(F("Move Right"));
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

// Common function to stop the car.
void stopCar()
{
  Serial.println(("STOP Both Motors."));
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


// Common function to get the distance to nearest object at the back.
float back_distance()
{
  // Wait 50ms between pings (about 20 pings/sec).
  // 29ms should be the shortest delay between pings.

  Serial.print("Using sonar.ping_cm: ");
  Serial.print(sonarBack.ping_cm());
  Serial.println("cm");

  // The ping_median() function takes 'n' duration measurements in a row,
  // throws away the out of range readings and then averages the remaining ones.
  int iterations = 5;
  duration = sonarBack.ping_median(iterations);
  distance = (duration / 2) * 0.0343;
  Serial.print("Median Calculated: ");
  Serial.print(distance);
  Serial.println(" cms");

  // return the median calculated distance from duration.
  return distance;
}

// Common function to get distance to nearest object, in front.
float front_distance()
{
  // Wait 50ms between pings (about 20 pings/sec).
  // 29ms should be the shortest delay between pings.

  Serial.print("Using sonar.ping_cm: ");
  Serial.print(sonarFront.ping_cm());
  Serial.println("cm");

  // The ping_median() function takes 'n' duration measurements in a row,
  // throws away the out of range readings and then averages the remaining ones.
  int iterations = 5;
  duration = sonarFront.ping_median(iterations);
  distance = (duration / 2) * 0.0343;
  Serial.print("Median Calculated: ");
  Serial.print(distance);
  Serial.println(" cms");

  //return calculated distance from median duration
  return distance;
}
