#include <Arduino.h>
#include <ESP32Servo.h>

// For LED or buzzer
int ledPin = 12;

// For analog joystick
int yPin = 14;
int xPin = 27;
int buttonPin = 26;

int yVal;
int xVal;
int buttonState;

// For servo pins
int xServoPin = 4;
int yServoPin = 15;

int xServoPos;
int yServoPos;

// Utilizing servo library
Servo xServo;
Servo yServo;

void setup() {
  Serial.begin(115200);
  
  pinMode(yPin, INPUT);
  pinMode(xPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  xServo.attach(xServoPin);
  yServo.attach(yServoPin);
}

void loop() {
  xVal = analogRead(xPin);   // Returns 0-4095 with neutral at 2048.
  yVal = analogRead(yPin);
  buttonState = digitalRead(buttonPin);

  // For debugging purposes only
  /**
  // Convert raw values to a symmetric range: 
  int adjustedX = xVal - 2048;  // When xVal is 2048, adjustedX = 0.
  int adjustedY = yVal - 2048;

  // For debugging
  Serial.print("Adjusted X: ");
  Serial.print(adjustedX);
  Serial.print(" | Adjusted Y: ");
  Serial.println(adjustedY);
  **/

  // Mapping 0-4095 to 0-180 (with neutral roughly at 90).
  xServoPos = map(xVal, 0, 4095, 0, 180);
  yServoPos = map(yVal, 0, 4095, 0, 180);

  xServo.write(xServoPos);
  yServo.write(yServoPos);

  if (buttonState == LOW){
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  delay(100);
}
