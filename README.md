# Unofficial Gateway for Nilan Ventilation System

This project allows you to control your Nilan air vent system (e.g., Comfort 300 LR with CTS602 panel) via Modbus, MQTT, and HTTP. It is designed to work with **M5Stack Core (ESP32)** with COMMU module, as well as ESP8266/ESP32 boards with RS485 adapters.

## Features
- **Protocols**: Modbus RTU (RS485), MQTT, HTTP API.
- **Hardware Support**: M5Stack Core (with Display), ESP32, ESP8266.
- **Dynamic Configuration**: 
    - **WiFi**: Fallback to SoftAP ("NilanGW") if connection fails. Configurable via API.
    - **MQTT**: Broker, User, and Password configurable via API.
    - **Modbus**: Baud rate and Configurable via `configuration.h`.
- **Multi-Slave Support**: Query different Modbus slave IDs via API (e.g. `/30/read/temp`).
- **Diagnostics**: Detailed, readable Modbus error messages on M5Stack display.

## Installation
1. Config `src/configuration.h` is mainly for defaults. Use API to set actual WiFi/MQTT credentials.
2. Compile and upload using **PlatformIO**.
    - For M5Stack: `pio run --target upload` (Environment: `m5stack-basic`)
3. Connect RS485 adapter to Nilan unit.

## Configuration & Usage

### 1. WiFi Setup
If the device cannot connect to WiFi, it starts an Access Point:
- **SSID**: `NilanGW`
- **IP**: `192.168.4.1`

Connect to this AP and use the API to set your WiFi credentials:
- Set SSID: `http://192.168.4.1/set/wifi/ssid/YOUR_SSID`
- Set Password: `http://192.168.4.1/set/wifi/password/YOUR_PASSWORD`

*Device will restart automatically.*

### 2. MQTT Setup
Configure MQTT broker via API (persisted in flash):
- Set Server: `http://[IP]/set/mqtt/server/192.168.1.50`
- Set User: `http://[IP]/set/mqtt/user/myuser`
- Set Password: `http://[IP]/set/mqtt/password/mypass`

### 3. Modbus & Nilan Connection
**Nilan CTS602 8-pin Connector (CN7) Pinout:**
- **Pin 2**: Data + (A)
- **Pin 3**: Data - (B)
- **Pin 6**: GND
*(Pin 1 is typically 12V - do not connect to ESP)*

**Multi-Slave API:**
You can target specific slave IDs by prefixing the URL:
- `http://[IP]/30/read/temp` (Read temp from slave 30)
- `http://[IP]/2/read/temp` (Read temp from slave 2)
- `http://[IP]/read/temp` (Uses default slave ID from config)

## HTTP API Reference
| Method | URL Format | Description |
|---|---|---|
| GET | `/read/app` | Read application status |
| GET | `/help` | List available registers |
| GET | `/get/[addr]/[count]/[type]` | Raw Modbus Read (`type`: 0=Input, 1=Holding) |
| GET | `/set/[group]/[addr]/[val]` | Write Modbus register |
| GET | `/set/wifi/ssid/[ssid]` | Set WiFi SSID |
| GET | `/set/wifi/password/[pass]` | Set WiFi Password |
| GET | `/set/mqtt/server/[ip]` | Set MQTT Broker IP |
| GET | `/set/mqtt/user/[user]` | Set MQTT User |
| GET | `/set/mqtt/password/[pass]` | Set MQTT Password |

## MQTT Topics
**Listen**:
- `ventilation/temp/#`: Sensor temperatures.
- `ventilation/moist/#`: Humidity.
- `ventilation/error/modbus`: Error codes (0=OK, E0=Inv Slave, E2=Timeout).

**Control** (Publish to `ventilation/cmd/...`):
- `ventilation/cmd/ventset` (0-4): Fan speed.
- `ventilation/cmd/tempset` (e.g. 2100 for 21.0°C).
- `ventilation/cmd/modeset` (0=Off, 1=Heat, 2=Cool, 3=Auto).
- `ventilation/cmd/runset` (0=Off, 1=On).

## M5Stack Display
- Shows WiFi SSID & IP.
- Shows MQTT Connection Status.
- Shows Valid Modbus Read Status or Human-Readable Error Text.

![SVG preview of system](images/overview.svg)


