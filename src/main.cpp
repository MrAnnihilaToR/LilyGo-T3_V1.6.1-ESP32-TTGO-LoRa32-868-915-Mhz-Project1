/*
LilyGo T3_V1.6.1, ESP32, TTGO with LoRa32 - 868-915 Mhz, Sensor Values simulation;
Created by Mario Andreev, 13.12.22
*/

//Arduino header
#include <Arduino.h>

// Libraries for LoRa 
#include <SPI.h>
#include <LoRa.h>

// Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// define the pins used by the LoRa transceiver module
#define SCK 5 
#define MISO 19 
#define MOSI 27 
#define SS 18 
#define RST 23 
#define DIO0 26 

// 433E6 for Asia
// 866E6 for Europe
// 915E6 for North America
#define BAND 866E6 //Europe

// OLED pins
#define OLED_SDA 21 
#define OLED_SCL 22 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// packet counter
int counter = 0;

// Let's make 4 integers and simulate sensor values
int num1 = 100;
int num2 = 150;
int num3 = 200;
int num4 = 250;

///We need a variable to know when to start again from the beginning
int num_counter = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire); /// no LED_RST here


////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  // initialize Serial Monitor
  Serial.begin(115200);

  while (!Serial)
    yield();

  // initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false))
  { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever -> smart
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("LORA SENDER ");
  display.display();

  Serial.println("LoRa Sender Test");

  // SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);

  // setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  Serial.println("LoRa Initializing OK!");
  display.setCursor(0, 10);
  display.print("LoRa Initializing OK!");
  display.display();
  delay(2000);
}

void loop()
{
  Serial.print("Sending packet: ");
  Serial.println(counter);
  
  display.clearDisplay();
 
  switch (num_counter)
  {
    case 0:
    num_counter++;
    break;
  case 1:
  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("hello, 1st sensor value: ");
  LoRa.println(num1);
  LoRa.endPacket();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("LORA SENDER"); /// First thing on the display
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.print("LoRa packet sent.");
  display.setCursor(0, 30);
  display.print("Counter:");
  display.setCursor(50, 30);
  display.println(counter);

  /// New Code is here
  display.setCursor(0, 50);
  display.print("Sensor 1: ");
  display.println(num1);
  display.display();

  num_counter++;
  break;
  case 2:
  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("hello, 2nd sensor value: ");
  LoRa.print(num2);
  LoRa.endPacket();

   display.clearDisplay();
  display.setCursor(0, 0);
  display.println("LORA SENDER"); /// First thing on the display
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.print("LoRa packet sent.");
  display.setCursor(0, 30);
  display.print("Counter:");
  display.setCursor(50, 30);
  display.println(counter);
 
  /// New Code is here
  display.setCursor(0, 50);
  display.print("Sensor 2: ");
  display.println(num2);
  display.display();

  num_counter++;
  break;
  case 3:
  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("hello, 3rd sensor value: ");
  LoRa.print(num3);
  LoRa.endPacket();

   display.clearDisplay();
  display.setCursor(0, 0);
  display.println("LORA SENDER"); /// First thing on the display
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.print("LoRa packet sent.");
  display.setCursor(0, 30);
  display.print("Counter:");
  display.setCursor(50, 30);
  display.println(counter);
 
  /// New Code is here
  display.setCursor(0, 50);
  display.print("Sensor 3: ");
  display.println(num3);
  display.display();

  num_counter++;
  break;
  case 4:
  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("hello, 4th sensor value: ");
  LoRa.print(num4);
  LoRa.endPacket();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("LORA SENDER"); /// First thing on the display
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.print("LoRa packet sent.");
  display.setCursor(0, 30);
  display.print("Counter:");
  display.setCursor(50, 30);
  display.print(counter);

  /// New Code is here
  display.setCursor(0, 50);
  display.print("Sensor 4: ");
  display.println(num4);
  display.display();

  num_counter = num_counter - 3;
  break;
  default:
    LoRa.println("Unknown value");
    display.display();
    break;
  }

  counter++;

  delay(10000);
}


