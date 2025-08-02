#define BLYNK_PRINT Serial
// LDR Sensor
#define LDR_PIN 32
#define LED_LDR_STATUS_PIN 33
// Soil Moisture Sensor
#define SOIL_ANALOG_PIN 34 // analog pin
#define LED_SOIL_RED_PIN 18
#define LED_SOIL_GREEN_PIN 19

// Set Value For Blynk
#define BLYNK_TEMPLATE_ID "TMPL6iG1K6bo1"
#define BLYNK_TEMPLATE_NAME "SmartPlantCare"
#define BLYNK_AUTH_TOKEN "BxNAr5_6HwoA-Y0HM-c1Djly_SxOH7-r"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

int lastMoisture = -1; // ตัวแปรสำหรับเช็คค่าความเปลี่ยนแปลงของ Soil Moisture Sensor ค่า Percent
int lastMoistureState = -1; // ตัวแปรสำหรับเช็คค่าความเปลี่ยนแปลงของ Soil Moisture Sensor ค่าสถานะของดิน
int lastLDR = -1; // ตัวแปรสำหรับเช็คค่าความเปลี่ยนแปลงของ LDR Sensor

char ssid[] = "Mod_wifi";
char pass[] = "88888888";

void sendSensorData(){
  int moistureAnalog = analogRead(SOIL_ANALOG_PIN); // อ่านค่าจากขา SOIL_ANALOG_PIN ซืึ่งเป็นค่า analog
  int moisturePercent = map(moistureAnalog, 0, 4095, 100, 0); // แปลงค่า analog เป็นค่า percent
  int ldrState = digitalRead(LDR_PIN); // อ่านค่าจากขา LDR_PIN ซึ่งเป็นค่า Digital 

  // เงื่อนไขการส่งข้อมูลไปที่ Blynk
    // LDR Sensor
    if(ldrState != lastLDR){
      Blynk.virtualWrite(V4, ldrState); // ส่งค่าของ LDR ไปที่ Blynk
      lastLDR = ldrState; // ให้ lastLDR = ค่าล่าสุดของ ldrState
    }
    // Soil Moisture Sensor
    if(moisturePercent != lastMoisture){
      Blynk.virtualWrite(V3, moisturePercent);
      lastMoisture = moisturePercent;
    }
    
  int moistureStateNow = (moisturePercent <= 40) ? 1 : 0; // หาก moisturePercent น้อยกว่า หรือเท่ากับ 40 % ให้ moistureStateNow = 1 และหากมากกว่า 40 % ให้ moistureStateNow = 0

  if(moistureStateNow != lastMoistureState){
    if(moistureStateNow == 1){
      digitalWrite(LED_SOIL_GREEN_PIN, LOW);
      digitalWrite(LED_SOIL_RED_PIN, HIGH);
      Blynk.setProperty(V2,"color","#D3435C");
      Blynk.virtualWrite(V2, 1);
    } else{
      digitalWrite(LED_SOIL_RED_PIN, LOW);
      digitalWrite(LED_SOIL_GREEN_PIN, HIGH);
      Blynk.setProperty(V2,"color","#32A852");
      Blynk.virtualWrite(V2, 1);
    }
    lastMoistureState = moistureStateNow;
  }

  digitalWrite(LED_LDR_STATUS_PIN, ldrState);
}

void setup() {
  Serial.begin(115200); 
  // LDR Sensor
  pinMode(LDR_PIN, INPUT); // set input pin for LDR sensor
  pinMode(LED_LDR_STATUS_PIN, OUTPUT); // status led for LDR sensor

  // Soil Moisture Sensor
  pinMode(SOIL_ANALOG_PIN, INPUT); // set input pin for Soil Moisture Sensor
  pinMode(LED_SOIL_RED_PIN, OUTPUT); // danger status led for Soil Moisture Sensor  
  pinMode(LED_SOIL_GREEN_PIN, OUTPUT); // normal status led for Soil Moisture Sensor  

  // Set Default led 
  digitalWrite(LED_LDR_STATUS_PIN, LOW);
  digitalWrite(LED_SOIL_RED_PIN, LOW);
  digitalWrite(LED_SOIL_GREEN_PIN, LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // ตั้งค่า WIFI ที่เราต้องการเชื่อม และ Token ของอุปกรณ์ที่เราสร้างบน Blynk
  timer.setInterval(5000L, sendSensorData); // ตั้งค่าเวลาให้เรียกใช้ void sendSensorData() ทุกๆ 5 วิ
}

void loop() {
  Blynk.run(); // เรียกให้ Blynk ทำงาน
  timer.run(); // เรียกให้ timer ทำงาน
}
