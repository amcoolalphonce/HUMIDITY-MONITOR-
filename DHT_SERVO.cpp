#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFiClientSecure.h>
#include "secrets.h"
#include "pin_configurations.h"
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define DHT_SENSOR_TYPE DHT22
DHT dht_sensor(DHT_PIN, DHT_SENSOR_TYPE); // Create  DHT sensor object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* server_url="https://smart-home-iot.angazaelimu.com/api/dht_data_insert";
WiFiClientSecure *client = new WiFiClientSecure;
String httpRequestData;
int httpResponseCode;
int humid_threshold;
int temp_threshold;
HTTPClient https;
float humi  = 0;
float tempC = 0;
String payload;


void setup() {
  Serial.begin(115200);
  // setting up custom I2C pins
  Wire.begin(I2C_SDA, I2C_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  // initialize display
  display.clearDisplay();
  display.setTextColor(WHITE);

  // pins functionality definition
  pinMode(INA_PIN, OUTPUT);
  pinMode(INB_PIN, OUTPUT);
