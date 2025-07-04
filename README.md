# ESP-Peer-To-Peer-Servo-and-Joystick

This project demonstrates a wireless, peer-to-peer joystick-to-servo system using three ESP32-CAM microcontrollers and ESP-NOW. A Wokwi simulation (non-P2P) of the core `main.cpp` logic is also included.

---

## 🔗 Wokwi Simulation

The Wokwi demo uses **`src/main.cpp`** to drive two servos directly from a joystick on a single ESP32:

[▶️ Run the Wokwi Simulation (main.cpp)](https://wokwi.com/projects/428278953614511105)

> **Note:** This sim does **not** use ESP-NOW. For the full peer-to-peer example, see **master.cpp** and **slave.cpp** below.

---

## 📁 Repository Structure

```
├─ .vscode/              # VSCode & PlatformIO settings
├─ include/              # Custom headers
├─ lib/                  # External libraries
├─ src/
│   ├─ main.cpp          # Single-ESP32 joystick→servo demo (Wokwi)
│   ├─ master.cpp        # ESP32-CAM “Master” (joystick transmitter via ESP-NOW)
│   ├─ slave.cpp         # ESP32-CAM “Slave” (servo receiver via ESP-NOW)
│   └─ camera_stream.cpp # ESP32-CAM camera streaming (IDE example)
├─ platformio.ini        # PlatformIO build configuration
└─ README.md             # This file
```

---

## 🚀 Getting Started

### Prerequisites

* [PlatformIO](https://platformio.org/) (VSCode or CLI)
* **Three** ESP32-CAM boards (two for joystick/servo P2P, one for camera stream)
* Analog joystick module
* Two hobby servos (5 V, \~1 A stall current each)
* 5 V power supply (≥2 A)
* Common GND wiring (for boards sharing the same power)

### 1. Clone the Repo

```bash
git clone https://github.com/KillWasHere/ESP-Peer-To-Peer-Servo-and-Joystick.git
cd ESP-Peer-To-Peer-Servo-and-Joystick
```

### 2. Run the Simulation (Optional)

* Open **`src/main.cpp`** in VSCode and press the Wokwi "▶️" button,
  or click the link above.

### 3. Hardware Setup

#### Master (ESP32-CAM + Joystick)

```
Joystick VCC → 5 V
Joystick GND → GND
Joystick X → GPIO 34
Joystick Y → GPIO 35
```

#### Slave (ESP32-CAM + Pan-Tilt Bracket)

```
Power servos with 5 V (tie GND to master)
Servo pan signal → GPIO 14
Servo tilt signal → GPIO 15
Mount device (camera or sensor) on pan-tilt bracket
```

#### Camera Streamer (ESP32-CAM)

```
Flash ESP32-CAM with Arduino IDE example "CameraWebServer"
Connect camera power & GND
Access camera via IP address on Wi-Fi network
```

### 4. Configure ESP-NOW Peers

* In **`src/master.cpp`**, replace `receiverAddress[]` with your servo-slave ESP32-CAM’s MAC (print via `Serial.println(WiFi.macAddress());`).
* **`src/slave.cpp`** requires no MAC edits.

### 5. Build & Upload

1. Open the **PlatformIO** sidebar in VSCode.
2. Select **master** environment → Upload to joystick ESP32-CAM.
3. Select **slave** environment → Upload to servo ESP32-CAM.
4. Use Arduino IDE to flash **camera\_stream.cpp** (IDE example) to the third ESP32-CAM.

---

## 📝 Sketch Overviews

### `src/main.cpp` (Standalone Demo)

* Reads joystick on GPIO 34/35
* Maps 0–4095 → 0–180°
* Drives two servos directly
* **Wokwi only** (no ESP-NOW)

### `src/master.cpp` (P2P Transmitter)

* Calibrates joystick center at boot
* Normalizes ±range to ±1.0 → maps to 0–180° around 90°
* Sends `angleX`/`angleY` via ESP-NOW to a specific MAC

### `src/slave.cpp` (P2P Receiver)

* Listens for ESP-NOW messages
* Parses `angleX`/`angleY`
* Drives servos on GPIO 14/15
* Serial debug output

### `src/camera_stream.cpp` (IDE Example)

* Standard ESP32-CAM "CameraWebServer" sketch
* Streams MJPEG to a browser
* Provided by Arduino IDE's ESP32 boards package

---

## 🌐 Wireless Protocol

* **ESP-NOW**: Low-latency, peer-to-peer, no router needed
* **Three ESP32-CAM MCUs**:

  * Master (joystick sender)
  * Slave (servo head)
  * Camera streamer (IDE example)

---

## 📦 PlatformIO Environments

```ini
[env:master]
platform = espressif32
board    = esp32cam
framework= arduino
src_dir  = src

[env:slave]
platform = espressif32
board    = esp32cam
framework= arduino
src_dir  = src
```

---
Yvx
