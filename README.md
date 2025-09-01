# IoT Codes Repository

### Overview
This repository contains sample IoT code for ESP32-based experiments, including:
- Bluetooth communication
- CoAP protocol implementations
- MQTT interactions (command-line and client mode)
- Web server integration
- Various sensor demos (LED, IR detection, accelerometer, temperature)

---

## Table of Contents
1. [Prerequisites](#prerequisites)  
2. [Setup Instructions](#setup-instructions)  
3. [Modules Overview](#modules-overview)  
   - bluetooth_ex  
   - coap  
   - coap_python_pc  
   - mqtt_cmdline  
   - mqtt_on_esp32_client_mode  
   - web_to_esp32  
   - lab_code_for_web_pages  
   - txt-file demos  
4. [Example Usage](#example-usage)  
5. [Dependencies](#dependencies)  
6. [Contributing](#contributing)  
7. [License](#license)

---

## Prerequisites
- ESP32 development board  
- Arduino IDE (version XX.x) / PlatformIO  
- Python 3.x with libraries: `paho-mqtt`, `aiocoap`, etc.

---

## Modules Overview

### `bluetooth_ex`
**Description:** *(your one-liner)*  
**How to run:**  
1. Install library X  
2. Upload to ESP32 via Arduino IDE  
3. Open Monitor, etc.

### `coap` & `coap_python_pc`
**Description:**  
**Instructions:**  
- Setup ESP32 as CoAP server/client  
- Run Python script `coap_python_pc/xyz.py`, etc.

*(...continue for other modules...)*

---

## Example Usage
```bash
cd mqtt_cmdline
python mqtt_pub.py --topic test --message "Hello"
