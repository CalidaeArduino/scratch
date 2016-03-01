#include <Servo.h>

// Function prototypes
void initServo();

// int deadZone(int x, int x0, int width);
int deadZone(int x, int x0, int width, int deadOffset = 0);

// Pins
const int JOY_X_PIN = A0;
const int JOY_Y_PIN = A1;
const int MOTOR_PIN = A2;
const int LED_UP_PIN = 6;
const int LED_DOWN_PIN = 10;
const int LED_RIGHT_PIN = 3;
const int LED_LEFT_PIN = 11;
const int SERVO_PIN = 9;
// const int ledPin = 13; // ???

// Constants
const int OFFSET = 6;

// Globals
Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(JOY_X_PIN, INPUT);
  pinMode(JOY_Y_PIN, INPUT);
  pinMode(LED_UP_PIN, OUTPUT);
  pinMode(LED_DOWN_PIN, OUTPUT);
  pinMode(LED_RIGHT_PIN, OUTPUT);
  pinMode(LED_LEFT_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
  // initServo();
}

void loop() {
  // read the value from the sensor:
  int sensorX = analogRead(JOY_X_PIN);
  int sensorY = analogRead(JOY_Y_PIN);
  unsigned int graus = map(sensorY, 0, 1023, 0u, 180u);

  servo.write(graus);

  int xx = map(sensorX, 0, 1023, -256, 255);
  int yy = map(sensorY, 0, 1023, -256, 255);

  int xx0 = deadZone(xx, 0, OFFSET);
  int yy0 = deadZone(yy, 0, OFFSET);

  int aa = constrain(-xx0, 0, 255);
  int bb = constrain( xx0, 0, 255);
  int cc = constrain(-yy0, 0, 255);
  int dd = constrain( yy0, 0, 255);

  analogWrite(MOTOR_PIN, sensorX);
  analogWrite(LED_UP_PIN, aa);
  analogWrite(LED_RIGHT_PIN, cc);
  analogWrite(LED_LEFT_PIN, dd);
  analogWrite(LED_DOWN_PIN, bb);

}

int deadZone(int x, int x0, int width, int deadOffset)
{
  return abs(x - x0) < width ? deadOffset : x;
}

void initServo(Servo s)
{
  s.write(0);
  delay(500);
  for (int i = 0; i < 180 ; i++)
  {
    s.write(i);
    delay(20);
  }
  delay(0);
}
