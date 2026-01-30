# Nilan Gateway API Reference

## URL Structure
All commands support an optional Modbus Slave ID prefix.
- Default: `http://[IP]/[operation]/...`
- Explicit Slave ID: `http://[IP]/[SlaveID]/[operation]/...`

Example: `http://192.168.1.10/30/read/temp1`

---

## READ Commands
**Format:** `/read/[group]`

| Group | Description |
| :--- | :--- |
| `temp1` | Exhaust, Outlet temperatures |
| `temp2` | Inlet, Outdoor, Room temperatures + RH |
| `temp3` | RH (Humidity) |
| `alarm` | Current status and alarm list logs |
| `time` | System time (Second, Minute, Hour, Day, Month, Year) |
| `control` | RunSet, ModeSet, VentSet, TempSet, ServiceMode |
| `speed` | ExhaustSpeed, InletSpeed (Actual RPM/Level) |
| `airtemp` | CoolSet, TempMinSum, TempMinWin, etc. |
| `airflow` | AirExchMode, CoolVent |
| `program` | Current Program |
| `user` | User settings (FuncAct, TimeSet, VentSet, TempSet) |
| `info` | UserFunc, AirFilter, DoorOpen, Smoke, AirFlow, etc. |
| `inputairtemp` | IsSummer, TempInletSet, TempRoom, CapSet |
| `app` | Bus Version, Version Major/Minor |
| `output` | AirFlap, SmokeFlap, Bypass, AirHeat, Compressor, etc. |
| `display1` | Text lines 1-2, 3-4, 5-6, 7-8 |
| `display2` | Text lines 9-10, 11-12, 13-14, 15-16 |

---

## SET Commands (Write)
**Format:** `/set/[ignored]/[address]/[value]`
*Note: The second segment is ignored by the parser but must be present. You can use it as a label.*
*Example:* `/set/speed/1003/4`

### Common Registers
| Function | Register Address | Value Range | Description |
| :--- | :--- | :--- | :--- |
| **Speed** | `1003` | `0` - `4` | Fan speed level (0=Off, 4=Max) |
| **Mode** | `1002` | `0` - `4` | 0=Auto, 1=Cool, 2=Heat... |
| **Run** | `1001` | `0` - `1` | 0=Off, 1=On |
| **Setpoint** | `1004` | `500` - `3000` | Target Temp (e.g. `2300` = 23.00°C) |
| **Program** | `500` | `0` - `4` | Select Week Program |

### Examples
- **Set Speed to 2 (Default Slave):** `http://[IP]/set/motor/1003/2`
- **Set Speed to 2 (Slave 30):** `http://[IP]/30/set/motor/1003/2`
- **Set Temp to 21.5°C (Slave 30):** `http://[IP]/30/set/temp/1004/2150`
- **Turn On (Slave 30):** `http://[IP]/30/set/power/1001/1`

---

## Special Commands
### System
- **WiFi Scan:** `/get/wifi/scan`
- **Raw Modbus Read:** `/get/[address]/[count]/[type]`
  - `type`: 0=Input, 1=Holding
  - *Example:* `/get/100/4/0` (Read 4 Input registers starting at 100)

### Configuration (Requires Reboot)
- **Set WiFi SSID:** `/set/wifi/ssid/[ssid]`
- **Set WiFi Password:** `/set/wifi/password/[password]`
- **Set MQTT Server:** `/set/mqtt/server/[ip]`
- **Set MQTT User:** `/set/mqtt/user/[username]`
- **Set MQTT Password:** `/set/mqtt/password/[password]`
Basic Auth is not supported for these URL configuration commands.
