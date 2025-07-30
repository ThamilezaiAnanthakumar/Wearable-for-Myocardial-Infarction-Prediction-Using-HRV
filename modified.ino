
#include "spo2_algorithm.h"
#include <Wire.h>
#include <WiFi.h>
#include "MAX30105.h"


const char* ssid = "Thush";
const char* password = "thusa123";
const char* host = "192.168.112.198"; 
const uint16_t port = 5000;
int ValueSend =0;


#define MAX_BRIGHTNESS 255



uint32_t irBuffer;
uint32_t redBuffer;
uint32_t buffer[2100];

int32_t spo2; //SPO2 value
int8_t validSPO2; //indicator to show if the SPO2 calculation is valid
int32_t heartRate; //heart rate value
int8_t validHeartRate; //indicator to show if the heart rate calculation is valid

MAX30105 particleSensor;
WiFiClient client;



#define RED 12
#define GREEN 13

void setup() {
  
  pinMode(RED,OUTPUT);
  pinMode(GREEN,OUTPUT);

  Serial.begin(115200);
  delay(2000);
 
  Serial.println("Serial Begin.");


  Wire.begin(8,7);  

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  if (client.connect(host, port)) {
    Serial.println("Connected to server");
   
  } else {
    Serial.println("Connection failed");
   
  }

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println(F("MAX30105 was not found. Please check wiring/power."));
    
    while (1);
  }

  Serial.println(F("Attach sensor to finger with rubber band. Press any key to start conversion"));
  while (Serial.available() == 0) ; //wait until user presses a key
  Serial.read();


  byte ledBrightness = 60; //Options: 0=Off to 255=50mA
  byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
}

void loop() {

  //long irValue = particleSensor.getIR(); // IR = PPG
  if (!client.connected()) {  
    // Try reconnect if lost
    Serial.println("Reconnecting...");
    if (client.connect(host, port)) {
      Serial.println("Reconnected to server");
    } else {
      Serial.println("Reconnect failed");
      delay(1000);
      return;
    }
  }

  while (particleSensor.available() == false) //do we have new data?
      particleSensor.check(); //Check the sensor for new data

  redBuffer = particleSensor.getRed();
  irBuffer = particleSensor.getIR();
  particleSensor.nextSample(); //We're finished with this sample so move to next sample
    
  buffer[ValueSend] = irBuffer;
  Serial.println(irBuffer, DEC);
  client.println(irBuffer);
  ValueSend = ValueSend + 1;
  if (ValueSend >=2010){
    Serial.print("[");
    for (int i = 0; i < 2010; i++) {
      Serial.print(buffer[i]); // 3 decimal places
      if (i < 2010 - 1) {
        Serial.print(", ");
      }
    }
    Serial.println("]");
    ValueSend=0;  
  }
  while (client.available()) {
    String line = client.readStringUntil('\n');
    Serial.print("Received from server: ");
    Serial.println(line);
    if (line == "1"){
      Serial.println("predicted 1");
    }
    else{
      Serial.println("predicted 0");
    }
    client.println("OK");
  }
}