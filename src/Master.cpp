#include <esp_now.h>
#include <WiFi.h>

const int joyPinX = 34;  
const int joyPinY = 35;  

uint8_t receiverAddress[] = {0xAC, 0x15, 0x18, 0x63, 0x09, 0x8C}; // <-- Please do not forget to change, s2pid

// Data structure to send
typedef struct struct_message {
  int joyX;
  int joyY;
} struct_message;

struct_message joystickData;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  Serial.println("Sender ready");
}

void loop() {
  
  joystickData.joyX = analogRead(joyPinX);  // 0 - 4095
  joystickData.joyY = analogRead(joyPinY);

  // For debugging purposes, print joystick values
  Serial.print("X: "); Serial.print(joystickData.joyX);
  Serial.print(" | Y: "); Serial.println(joystickData.joyY);

  // Send via ESP-NOW
  esp_err_t result = esp_now_send(receiverAddress, (uint8_t *) &joystickData, sizeof(joystickData));

  if (result == ESP_OK) {
    Serial.println("Sent successfully");
  } else {
    Serial.println("Error sending data");
  }

  delay(100);
}
