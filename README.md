# 🌱 Smart Plant Care with ESP32 + Blynk 2.0

ระบบดูแลต้นไม้อัจฉริยะที่สามารถตรวจสอบความชื้นในดินและความสว่างของแสง พร้อมควบคุม LED และแสดงผลผ่านแอป Blynk แบบเรียลไทม์

---

## 📦 อุปกรณ์ที่ใช้

| อุปกรณ์                  | จำนวน |
|--------------------------|--------|
| ESP32 Dev Board (38 PIN) | 1      |
| Soil Moisture Sensor     | 1      |
| LDR Sensor Module        | 1      |
| LED (สถานะ)              | 3      |
| สายไฟ Jumper            | หลายเส้น |
| Blynk IoT App (Mobile)   | 1 แอคเคานต์ |

---

## 🔌 การเชื่อมต่ออุปกรณ์

### Soil Moisture Sensor (Analog Output)
- AO → GPIO **34**
- VCC → 3.3V
- GND → GND

### LDR Sensor (Digital Output)
- DO → GPIO **32**
- VCC → 3.3V
- GND → GND

### LED สถานะ
- แดง (ดินแห้ง) → GPIO **18**
- เขียว (ดินชื้น) → GPIO **19**
- ฟ้า (แสงสว่าง) → GPIO **33**

---

## 📲 การตั้งค่าใน Blynk

### Template ID / Auth Token
```cpp
#define BLYNK_TEMPLATE_ID "TMPLxxxxxxx"
#define BLYNK_TEMPLATE_NAME "SmartPlantCare"
#define BLYNK_AUTH_TOKEN "Your_Auth_Token"
