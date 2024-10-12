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

  // wifi network init
  WiFi.begin(SSID,PASSWORD);

  // Signal LED pin function and state init
  pinMode(ONBOARD_LED_PIN,OUTPUT);     //--> On Board LED port Direction output
  digitalWrite(ONBOARD_LED_PIN, HIGH); //--> Turn off Led On Board

  // Connection init
  Serial.print("Connecting.");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ONBOARD_LED_PIN, LOW);
    delay(250);
    digitalWrite(ONBOARD_LED_PIN, HIGH);
    delay(250);
    //----------------------------------------
  }
  //----------------------------------------
  digitalWrite(ONBOARD_LED_PIN, LOW); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  delay(10000);

  dht_sensor.begin(); // initialize the DHT sensor
  //----------------------------------------

  Serial.println("Server started");
  Serial.println(WiFi.localIP());
  Serial.println("");
  Serial.print("connecting...");
  delay(10000);

}

