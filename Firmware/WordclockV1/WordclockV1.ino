#include <WiFi.h>
#include <WebServer.h>
typedef WebServer WiFiWebServer;
#include <AutoConnect.h>
#include <FastLED.h>
#include "time.h"




#define NUM_LEDS 114
#define DATA_PIN 23

WiFiWebServer server;
AutoConnect portal(server);
AutoConnectConfig config;


const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

// Zeit variablen
int led = 0;
int tm_min;
int tm_min_old = 99;
int tm_hour;
int tm_hour_old = 99;
int R = 50;
int G = 50;
int B = 30;
CRGB leds[NUM_LEDS];


void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    // when failed to obtain time
    return;
  }

  tm_min = timeinfo.tm_min;
  tm_hour = timeinfo.tm_hour;

}

void getTime()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  delay(1000);
  printLocalTime();

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    delay(3000);
    if (!getLocalTime(&timeinfo)){
      leds[0] = CRGB::Red;
      FastLED.show();
    }
 
  }
}




void displayTime() {


  switch (tm_min % 5) { // Punkte min

    case 0:
      leds[110].setRGB( 0, 0, 0);
      leds[111].setRGB( 0, 0, 0);
      leds[112].setRGB( 0, 0, 0);
      leds[113].setRGB( 0, 0, 0);

      break;

    case 1:
      leds[110].setRGB( R, G, B);
      break;

    case 2:
      leds[110].setRGB( R, G, B);
      leds[111].setRGB( R, G, B);
      break;

    case 3:
      leds[110].setRGB( R, G, B);
      leds[111].setRGB( R, G, B);
      leds[112].setRGB( R, G, B);
      break;

    case 4:
      leds[110].setRGB( R, G, B);
      leds[111].setRGB( R, G, B);
      leds[112].setRGB( R, G, B);
      leds[113].setRGB( R, G, B);
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
        leds[i].setRGB( 0, 0, 0);
      }

      for (int i = 41; i < 44; i++) { //Vor
        leds[i].setRGB( 0, 0, 0);
      }

      for (int i = 99; i < 102; i++) { //Uhr
        leds[i].setRGB( R, G, B);
      }


      break;

    case 1:
      for (int i = 99; i < 102; i++) { //Uhr
        leds[i].setRGB( 0, 0, 0);
      }

      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setRGB( R, G, B);
      }

      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setRGB( R, G, B);
      }
      break;
    case 2:
      for (int i = 18; i < 22; i++) { // Zehn
        leds[i].setRGB( R, G, B);
      }
      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setRGB( R, G, B);
      }
      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setRGB( 0, 0, 0);
      }
      break;

    case 3:
      for (int i = 18; i < 22; i++) { // Zehn
        leds[i].setRGB( 0, 0, 0);
      }

      for (int i = 26; i < 33; i++) { //Viertel
        leds[i].setRGB( R, G, B);
      }
      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setRGB( R, G, B);
      }

      break;

    case 4:
      for (int i = 11; i < 18; i++) { //Zwanzig
        leds[i].setRGB( R, G, B);
      }
      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setRGB( R, G, B);
      }

      for (int i = 26; i < 33; i++) { //Viertel
        leds[i].setRGB( 0, 0, 0);
      }
      break;

    case 5:
      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setRGB( 0, 0, 0);
      }
      for (int i = 11; i < 18; i++) { //Zwanzig
        leds[i].setRGB( 0, 0, 0);
      }
      for (int i = 41; i < 44; i++) { // Vor
        leds[i].setRGB( R, G, B);
      }
      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setRGB( R, G, B);
      }
      for (int i = 44; i < 48; i++) { //Halb
        leds[i].setRGB( R, G, B);
      }
      break;

    case 6:
      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setRGB(0, 0, 0);
      }

      for (int i = 41; i < 44; i++) { // Vor
        leds[i].setRGB(0, 0, 0);
      }
      break;

      for (int i = 44; i < 48; i++) { //Halb
        leds[i].setRGB( R, G, B);
      }

    case 7:
      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setRGB( R, G, B);
      }

      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setRGB( R, G, B);
      }

      for (int i = 44; i < 48; i++) { //Halb
        leds[i].setRGB( R, G, B);
      }

      break;

    case 8:
      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setRGB( 0, 0, 0);
      }
      for (int i = 11; i < 18; i++) { //Zwanzig
        leds[i].setRGB( R, G, B);
      }
      for (int i = 33; i < 37; i++) { //Nach
        leds[i].setRGB( 0, 0, 0);
      }
      for (int i = 44; i < 48; i++) { //Halb
        leds[i].setRGB( 0, 0, 0);
      }
      for (int i = 41; i < 44; i++) { // Vor
        leds[i].setRGB(R, G, B);
      }
      break;

    case 9:
      for (int i = 11; i < 18; i++) { //Zwanzig
        leds[i].setRGB( 0, 0, 0);
      }
      for (int i = 26; i < 33; i++) { //Viertel
        leds[i].setRGB( R, G, B);
      }
      for (int i = 41; i < 44; i++) { // Vor
        leds[i].setRGB(R, G, B);
      }


      break;

    case 10:
      for (int i = 26; i < 33; i++) { //Viertel
        leds[i].setRGB( 0, 0, 0);
      }

      for (int i = 18; i < 22; i++) { //Zehn
        leds[i].setRGB( R, G, B);
      }
      for (int i = 41; i < 44; i++) { // Vor
        leds[i].setRGB(R, G, B);
      }

      break;

    case 11:
      for (int i = 7; i < 11; i++) { //Fünf
        leds[i].setRGB( R, G, B);
      }

      for (int i = 18; i < 22; i++) { //Zehn
        leds[i].setRGB( 0, 0, 0);
      }
      for (int i = 41; i < 44; i++) { // Vor
        leds[i].setRGB(R, G, B);
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
    tm_hour_old = tm_hour;

    switch (tm_hour) {
      case 1:
        for (int i = 94; i < 99; i++) { //Zwölf
          leds[i].setRGB( 0, 0, 0);
        }
        for (int i = 63; i < 66; i++) { //Eins
          leds[i].setRGB( R, G, B);}
          if (tm_min > 4) {
            leds[62].setRGB( R, G, B);
          }
          if (tm_min == 5){
            getTime();
          }
        
        break;
      case 2:
        for (int i = 62; i < 66; i++) { //Eins
          leds[i].setRGB( 0, 0, 0);
        }
        for (int i = 55; i < 59; i++) { //Zwei
          leds[i].setRGB( R, G, B);
        }
        break;
      case 3:
        for (int i = 55; i < 59; i++) { //Zwei
          leds[i].setRGB( 0, 0, 0);
        }
        for (int i = 66; i < 70; i++) { //Drei
          leds[i].setRGB( R, G, B);
        }
        break;
      case 4:
        for (int i = 66; i < 70; i++) { //Drei
          leds[i].setRGB( 0, 0, 0);
        }
        for (int i = 73; i < 77; i++) { //Vier
          leds[i].setRGB( R, G, B);
        }
        break;
      case 5:
        for (int i = 73; i < 77; i++) { //Vier
          leds[i].setRGB( 0, 0, 0);
        }
        for (int i = 51; i < 55; i++) { //Fünf
          leds[i].setRGB( R, G, B);
        }
        break;
      case 6:
        for (int i = 51; i < 55; i++) { //Fünf
          leds[i].setRGB( 0, 0, 0);
        }
        for (int i = 83; i < 88; i++) { //Sechs
          leds[i].setRGB( R, G, B);
        }
        break;
      case 7:
        for (int i = 83; i < 88; i++) { //Sechs
          leds[i].setRGB( 0, 0, 0);
        }
        for (int i = 88; i < 94; i++) { //Sieben
          leds[i].setRGB( R, G, B);
        }
        break;
      case 8:
        for (int i = 88; i < 94; i++) { //Sieben
          leds[i].setRGB( 0, 0, 0);
        }
        for (int i = 77; i < 81; i++) { //Acht
          leds[i].setRGB( R, G, B);
        }
        break;
      case 9:
        for (int i = 77; i < 81; i++) { //Acht
          leds[i].setRGB( 0, 0, 0);
        }
        for (int i = 103; i < 107; i++) { //Neun
          leds[i].setRGB( R, G, B);
        }
        break;
      case 10:
        for (int i = 103; i < 107; i++) { //Neun
          leds[i].setRGB( 0, 0, 0);
        }
        for (int i = 106; i < 110; i++) { //Zehn
          leds[i].setRGB( R, G, B);
        }
        break;
      case 11:
        for (int i = 62; i < 66; i++) { //Zehn
          leds[i].setRGB( 0, 0, 0);
        }
        for (int i = 49; i < 52; i++) { //Elf
          leds[i].setRGB( R, G, B);
        }
        break;
      case 12:
        for (int i = 49; i < 52; i++) { //Elf
          leds[i].setRGB( 0, 0, 0);
        }
        for (int i = 94; i < 99; i++) { //Zwölf
          leds[i].setRGB( R, G, B);
        }
        break;

    }
  leds[0].setRGB( R, G, B);  //E
  leds[1].setRGB( R, G, B);  //S
  leds[3].setRGB( R, G, B);  //I
  leds[4].setRGB( R, G, B);  //S
  leds[5].setRGB( R, G, B);  //T

  FastLED.show();

}


void time() {
    printLocalTime();
    if (tm_min != tm_min_old) {
      tm_min_old = tm_min;
      displayTime();
    }
  
}


void setup() {

  // Responder of root page and apply page handled directly from WebServer class.
  server.on("/", []() {
    String content = R"(
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8" name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
Place the root page with the sketch application.&ensp;
__AC_LINK__
</body>
</html>
    )";
    content.replace("__AC_LINK__", String(AUTOCONNECT_LINK(COG_16)));
    server.send(200, "text/html", content);
  });

  config.ota = AC_OTA_BUILTIN;
  config.autoReconnect = true;
  config.hostName = "Wortuhr";
  portal.config(config);
  portal.begin();


  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  //connect to WiFi

  FastLED.clear();
  getTime();
  
}

void loop() {
  portal.handleClient();
  time();
}
