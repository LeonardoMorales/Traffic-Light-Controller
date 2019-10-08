#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <FastLED.h>

//Wi-Fi Credentials
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASSWORD "YOUR_PASSWORD"

//Firebase Credentials
#define FIREBASE_HOST "YOUR_FIREBASE_HOST"
#define FIREBASE_AUTH "YOUR_FIREBASE_AUTH"

//Define FirebaseESP32 data object
FirebaseData firebaseData;

//Traffic Light Path
String path = "/ESP32/Traffic-Light";

//Firebase Vars
String jsonData = "";

FirebaseJson jsonLightColor;
FirebaseJsonObject jsonParseLightColor;

String actualColor = "green";

//FastLED
#define NUM_LEDS 3
#define DATA_PIN 0

CRGB leds[NUM_LEDS];

void setup()
{
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop()
{
  
  if (Firebase.getJSON(firebaseData, path))
  {
    if (firebaseData.dataType() == "json")
    {
      jsonData = firebaseData.jsonData();
      Serial.println(firebaseData.jsonData());
    }

    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    ESP.restart();
    Serial.println("------------------------------------");
    Serial.println();
  }

  jsonLightColor.clear().setJsonData(jsonData);
  jsonLightColor.parse(false).get("Value");

  jsonParseLightColor = jsonLightColor.parseResult();

  if (jsonParseLightColor.success)
      {

        if (jsonParseLightColor.stringValue == actualColor)
        {
          return;
        }
        else
        {
          if (jsonParseLightColor.stringValue == "red")
          {
            leds[0] = CRGB::Red;
            leds[1] = CRGB::Black;
            leds[2] = CRGB::Black;
            FastLED.show();
            actualColor = jsonParseLightColor.stringValue;
          }
          else if (jsonParseLightColor.stringValue == "yellow")
          {
            leds[0] = CRGB::Black;
            leds[1] = CRGB::Yellow;
            leds[2] = CRGB::Black;
            FastLED.show();
            actualColor = jsonParseLightColor.stringValue;
          }
          else if (jsonParseLightColor.stringValue == "green")
          {
            leds[0] = CRGB::Black;
            leds[1] = CRGB::Black;
            leds[2] = CRGB::Green;
            FastLED.show();
            actualColor = jsonParseLightColor.stringValue;
          }
          else if (jsonParseLightColor.stringValue == "off")
          {
            leds[0] = CRGB::Black;
            leds[1] = CRGB::Black;
            leds[2] = CRGB::Black;
            FastLED.show();
            actualColor = jsonParseLightColor.stringValue;
          }
          else
          {
            leds[0] = CRGB::Red;
            leds[1] = CRGB::Yellow;
            leds[2] = CRGB::Green;
            FastLED.show();
            actualColor = jsonParseLightColor.stringValue;
          }
        }
      }
      else
      {
        Serial.println("1. Parse json data COLOR was failed!");
      }

  delay(200);
}