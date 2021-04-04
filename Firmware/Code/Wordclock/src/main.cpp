#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
typedef WebServer WiFiWebServer;
#include <AutoConnect.h>
#include <FastLED.h>
#include "time.h"


#define NUM_LEDS 114
#define DATA_PIN 23
#define lightSensor 34
//#define touch_pin_numer T0


WiFiWebServer server;
AutoConnect portal(server);
AutoConnectConfig config;


const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
int brightnessvalue = 400;
int brightness_max = 200;
int brightness_min = 30;
int lightstate;
int brightness_last = brightness_min;
float light; 





// Zeit variablen
int led = 0;
int tm_min;
int tm_min_old = 99;
int tm_hour;
int H = 0;
int S = 0;
int V = 160;
CRGB leds[NUM_LEDS];



void getTime()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  delay(1000);

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    delay(4000);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    delay(3000);
    if (!getLocalTime(&timeinfo)){
      leds[0] = CRGB::Red;
      FastLED.show();
    }
 
  }
}

void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    getTime();
  }

  tm_min = timeinfo.tm_min;
  tm_hour = timeinfo.tm_hour;

}


void displayTime() {


  switch (tm_min % 5) { // Punkte min

    case 0:
      leds[110].setHSV( 0, 0, 0);
      leds[111].setHSV( 0, 0, 0);
      leds[112].setHSV( 0, 0, 0);
      leds[113].setHSV( 0, 0, 0);

      break;

    case 1:
      leds[110].setHSV( H, S, V);
      break;

    case 2:
      leds[110].setHSV( H, S, V);
      leds[111].setHSV( H, S, V);
      break;

    case 3:
      leds[110].setHSV( H, S, V);
      leds[111].setHSV( H, S, V);
      leds[112].setHSV( H, S, V);
      break;

    case 4:
      leds[110].setHSV( H, S, V);
      leds[111].setHSV( H, S, V);
      leds[112].setHSV( H, S, V);
      leds[113].setHSV( H, S, V);
      break;

    default:
      leds[0] = CRGB::Red;
      //get time
      break;

  }

  switch (tm_min / 5)
  {

    case 0:
      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setHSV( 0, 0, 0);
      }

      for (int i = 41; i < 44; i++) { //Vor
        leds[i].setHSV( 0, 0, 0);
      }

      for (int i = 99; i < 102; i++) { //Uhr
        leds[i].setHSV( H, S, V);
      }


      break;

    case 1:
      for (int i = 99; i < 102; i++) { //Uhr
        leds[i].setHSV( 0, 0, 0);
      }

      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setHSV( H, S, V);
      }

      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setHSV( H, S, V);
      }
      break;
    case 2:
      for (int i = 18; i < 22; i++) { // Zehn
        leds[i].setHSV( H, S, V);
      }
      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setHSV( H, S, V);
      }
      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setHSV( 0, 0, 0);
      }
      break;

    case 3:
      for (int i = 18; i < 22; i++) { // Zehn
        leds[i].setHSV( 0, 0, 0);
      }

      for (int i = 26; i < 33; i++) { //Viertel
        leds[i].setHSV( H, S, V);
      }
      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setHSV( H, S, V);
      }

      break;

    case 4:
      for (int i = 11; i < 18; i++) { //Zwanzig
        leds[i].setHSV( H, S, V);
      }
      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setHSV( H, S, V);
      }

      for (int i = 26; i < 33; i++) { //Viertel
        leds[i].setHSV( 0, 0, 0);
      }
      break;

    case 5:
      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setHSV( 0, 0, 0);
      }
      for (int i = 11; i < 18; i++) { //Zwanzig
        leds[i].setHSV( 0, 0, 0);
      }
      for (int i = 41; i < 44; i++) { // Vor
        leds[i].setHSV( H, S, V);
      }
      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setHSV( H, S, V);
      }
      for (int i = 44; i < 48; i++) { //Halb
        leds[i].setHSV( H, S, V);
      }
      break;

    case 6:
      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setRGB(0, 0, 0);
      }

      for (int i = 41; i < 44; i++) { // Vor
        leds[i].setRGB(0, 0, 0);
      }

      for (int i = 44; i < 48; i++) { //Halb
        leds[i].setHSV( H, S, V);
      }
      break;
    case 7:
      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setHSV( H, S, V);
      }

      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setHSV( H, S, V);
      }

      for (int i = 44; i < 48; i++) { //Halb
        leds[i].setHSV( H, S, V);
      }

      break;

    case 8:
      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setHSV( 0, 0, 0);
      }
      for (int i = 11; i < 18; i++) { //Zwanzig
        leds[i].setHSV( H, S, V);
      }
      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setHSV( 0, 0, 0);
      }
      for (int i = 44; i < 48; i++) { //Halb
        leds[i].setHSV( 0, 0, 0);
      }
      for (int i = 41; i < 44; i++) { // Vor
        leds[i].setHSV( H, S, V);
      }
      break;

    case 9:
      for (int i = 11; i < 18; i++) { //Zwanzig
        leds[i].setHSV( 0, 0, 0);
      }
      for (int i = 26; i < 33; i++) { //Viertel
        leds[i].setHSV( H, S, V);
      }
      for (int i = 41; i < 44; i++) { // Vor
        leds[i].setHSV( H, S, V);
      }


      break;

    case 10:
      for (int i = 26; i < 33; i++) { //Viertel
        leds[i].setHSV( 0, 0, 0);
      }

      for (int i = 18; i < 22; i++) { //Zehn
        leds[i].setHSV( H, S, V);
      }
      for (int i = 41; i < 44; i++) { // Vor
        leds[i].setHSV( H, S, V);
      }

      break;

    case 11:
      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setHSV( H, S, V);
      }

      for (int i = 18; i < 22; i++) { //Zehn
        leds[i].setHSV( 0, 0, 0);
      }
      for (int i = 41; i < 44; i++) { // Vor
        leds[i].setHSV( H, S, V);
      }

      break;

    default:
      leds[0] = CRGB::Red;
      break;
  }



    if (tm_hour > 12) {
      tm_hour = tm_hour - 12;
    }
    if (tm_min> 24){
      if(tm_hour == 12){
        tm_hour = 1;
      }
      else {
        tm_hour = tm_hour + 1;}
    }

    switch (tm_hour) {
      case 1:
        for (int i = 94; i < 99; i++) { //Zwölf
          leds[i].setHSV( 0, 0, 0);
        }
        for (int i = 63; i < 66; i++) { //Eins
          leds[i].setHSV( H, S, V);}
          if (tm_min > 4) {
            leds[62].setHSV( H, S, V);
          }
          if (tm_min == 5){
            getTime();
          }
        
        break;
      case 2:
        for (int i = 62; i < 66; i++) { //Eins
          leds[i].setHSV( 0, 0, 0);
        }
        for (int i = 55; i < 59; i++) { //Zwei
          leds[i].setHSV( H, S, V);
        }
        break;
      case 3:
        for (int i = 55; i < 59; i++) { //Zwei
          leds[i].setHSV( 0, 0, 0);
        }
        for (int i = 66; i < 70; i++) { //Drei
          leds[i].setHSV( H, S, V);
        }
        break;
      case 4:
        for (int i = 66; i < 70; i++) { //Drei
          leds[i].setHSV( 0, 0, 0);
        }
        for (int i = 73; i < 77; i++) { //Vier
          leds[i].setHSV( H, S, V);
        }
        break;
      case 5:
        for (int i = 73; i < 77; i++) { //Vier
          leds[i].setHSV( 0, 0, 0);
        }
        for (int i = 51; i < 55; i++) { //Fünf
          leds[i].setHSV( H, S, V);
        }
        break;
      case 6:
        for (int i = 51; i < 55; i++) { //Fünf
          leds[i].setHSV( 0, 0, 0);
        }
        for (int i = 83; i < 88; i++) { //Sechs
          leds[i].setHSV( H, S, V);
        }
        break;
      case 7:
        for (int i = 83; i < 88; i++) { //Sechs
          leds[i].setHSV( 0, 0, 0);
        }
        for (int i = 88; i < 94; i++) { //Sieben
          leds[i].setHSV( H, S, V);
        }
        break;
      case 8:
        for (int i = 88; i < 94; i++) { //Sieben
          leds[i].setHSV( 0, 0, 0);
        }
        for (int i = 77; i < 81; i++) { //Acht
          leds[i].setHSV( H, S, V);
        }
        break;
      case 9:
        for (int i = 77; i < 81; i++) { //Acht
          leds[i].setHSV( 0, 0, 0);
        }
        for (int i = 103; i < 107; i++) { //Neun
          leds[i].setHSV( H, S, V);
        }
        break;
      case 10:
        for (int i = 103; i < 107; i++) { //Neun
          leds[i].setHSV( 0, 0, 0);
        }
        for (int i = 106; i < 110; i++) { //Zehn
          leds[i].setHSV( H, S, V);
        }
        break;
      case 11:
        for (int i = 106; i < 110; i++) { //Zehn
          leds[i].setHSV( 0, 0, 0);
        }
        for (int i = 49; i < 52; i++) { //Elf
          leds[i].setHSV( H, S, V);
        }
        break;
      case 12:
        for (int i = 49; i < 52; i++) { //Elf
          leds[i].setHSV( 0, 0, 0);
        }
        for (int i = 94; i < 99; i++) { //Zwölf
          leds[i].setHSV( H, S, V);
        }
        break;

    }
  leds[0].setHSV( H, S, V);  //E
  leds[1].setHSV( H, S, V);  //S
  leds[3].setHSV( H, S, V);  //I
  leds[4].setHSV( H, S, V);  //S
  leds[5].setHSV( H, S, V);  //T

  FastLED.show();

}


void time()
{
    printLocalTime();
    if (tm_min != tm_min_old) {
      tm_min_old = tm_min;
      displayTime();
    }
  
}


void setup() {
    Serial.begin(115200);
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
    FastLED.clear();
    FastLED.setCorrection( CRGB( 255, 255, 230) );

  // Responder of root page and apply page handled directly from WebServer class.
  server.on("/", []() {
    String content = R"(
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <html>
      <body>
      <button onclick="window.location.href='http://wortuhr/_ac'">Wlan und Updates</button>
      </body>
      </html>
    )";
    server.send(200, "text/html", content);
  });
  
  

  config.ota = AC_OTA_BUILTIN;
  config.autoReconnect = true;
  config.title = "Wortuhr";
  config.hostName = "Wortuhr";
  config.apid = "Wortuhr";
  portal.config(config);
  portal.begin();

  getTime();
  
}

void dimmen() {
  int light_in = analogRead(lightSensor);
  float light_new = light_in *1.0;
  float temp = 0.0;
  int i = 0;


  light = light + (light_new -light)*0.001;

// normalize light to values between 0 and 1 (0 = dunkel 1 = hell)
temp = light /2000.0;
if (temp>1.0) temp=1.0;

//calculate new brightness 
 i = temp * (brightness_max - brightness_min) + brightness_min;
// write new Brightness
 if (i<brightness_last-2 || i >brightness_last+2){
 FastLED.setBrightness(i);
 FastLED.show();
 brightness_last = i;}
}
 // if((lightstate != 0 ) && (light < brightnessvalue))
 // {
//       for (int i = brightness_max; i > brightness_min; i--){
//      FastLED.setBrightness(i);
//      FastLED.show();
//      delay(15);
//    }
//    lightstate = 0;}

//  else if ((lightstate != 1 ) && (light > brightnessvalue))
//  {
//    for (int i = brightness_min; i < brightness_max; i++){
//    FastLED.setBrightness(i);
//    FastLED.show();
//    delay(15);}
//    lightstate = 1;
//  }


void loop() {
  portal.handleClient();
  time();
  dimmen();
}