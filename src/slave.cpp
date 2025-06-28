// === RECEIVER: ESP32-CAM with Servo Control ===
#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

const int servoXPin = 14;  
const int servoYPin = 15;  

Servo servoX;
Servo servoY;

// Data structure to receive from sender
typedef struct struct_message {
  int joyX;
  int joyY;
} struct_message;

struct_message incomingData;

// Callback function to handle received data
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) {
  if (len == sizeof(incomingData)) {
    memcpy(&incomingData, data, sizeof(incomingData));

    // Debug prints
    Serial.print("Received X: ");
    Serial.print(incomingData.joyX);
    Serial.print(" | Y: ");
    Serial.println(incomingData.joyY);

    // Map joystick values to servo angles
    int servoAngleX = map(incomingData.joyX, 0, 4095, 0, 180);
    int servoAngleY = map(incomingData.joyY, 0, 4095, 0, 180);

    // Constrain and write to servos
    servoX.write(constrain(servoAngleX, 0, 180));
    servoY.write(constrain(servoAngleY, 0, 180));
  } else {
    Serial.println("Received data length mismatch");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW initialization failed");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  
  servoX.attach(servoXPin);
  servoY.attach(servoYPin);

  Serial.println("ESP32-CAM Receiver Ready");
}

void loop() {
  delay(100);
}
