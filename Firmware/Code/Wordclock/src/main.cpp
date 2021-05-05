#include <Arduino.h>
#include <AutoConnect.h>
#include <FastLED.h>
#include <time.h>
#include "ArduinoJson.h"
#include <WiFiMulti.h>
#include "esp32fota.h"
#include <WiFiClientSecure.h>
#include <Adafruit_NeoPixel.h>


#define Neopixel
//#define FastLED

//Autoconnect dependencys
#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>

#include <WebServer.h>

#endif
//Autoconnect stuff
#if defined(ARDUINO_ARCH_ESP8266)
ESP8266WebServer server;

#elif defined(ARDUINO_ARCH_ESP32)
WebServer server;
#endif

AutoConnect portal(server);
AutoConnectConfig config;

bool UpdateChecked = false;

//FastLED definitions
#define NUM_LEDS 114
#define DATA_PIN 23
#define lightSensor 34
CRGB leds[NUM_LEDS];
//Time variables
const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
//dimming variable

#if defined(Neopixel)
Adafruit_NeoPixel pixels(NUM_LEDS, DATA_PIN, NEO_GRBW + NEO_KHZ800);
#endif


int brightnessvalue = 400;
int brightness_max = 200;
int brightness_min = 30;
int lightstate;
int brightness_last = brightness_min;
float light;
//Time variables
int tm_min;
int tm_min_old;
int tm_hour;
//LED color
int H = 0;
int S = 0;
int V = 160;

char* test_root_ca= \
     "-----BEGIN CERTIFICATE-----\n"  
  "MIIDxTCCAq2gAwIBAgIQAqxcJmoLQJuPC3nyrkYldzANBgkqhkiG9w0BAQUFADBsMQswCQYDVQQG\n"  
  "EwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3d3cuZGlnaWNlcnQuY29tMSsw\n"  
  "KQYDVQQDEyJEaWdpQ2VydCBIaWdoIEFzc3VyYW5jZSBFViBSb290IENBMB4XDTA2MTExMDAwMDAw\n"  
  "MFoXDTMxMTExMDAwMDAwMFowbDELMAkGA1UEBhMCVVMxFTATBgNVBAoTDERpZ2lDZXJ0IEluYzEZ\n"  
  "MBcGA1UECxMQd3d3LmRpZ2ljZXJ0LmNvbTErMCkGA1UEAxMiRGlnaUNlcnQgSGlnaCBBc3N1cmFu\n"  
  "Y2UgRVYgUm9vdCBDQTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMbM5XPm+9S75S0t\n"  
  "Mqbf5YE/yc0lSbZxKsPVlDRnogocsF9ppkCxxLeyj9CYpKlBWTrT3JTWPNt0OKRKzE0lgvdKpVMS\n"  
  "OO7zSW1xkX5jtqumX8OkhPhPYlG++MXs2ziS4wblCJEMxChBVfvLWokVfnHoNb9Ncgk9vjo4UFt3\n"  
  "MRuNs8ckRZqnrG0AFFoEt7oT61EKmEFBIk5lYYeBQVCmeVyJ3hlKV9Uu5l0cUyx+mM0aBhakaHPQ\n"  
  "NAQTXKFx01p8VdteZOE3hzBWBOURtCmAEvF5OYiiAhF8J2a3iLd48soKqDirCmTCv2ZdlYTBoSUe\n"  
  "h10aUAsgEsxBu24LUTi4S8sCAwEAAaNjMGEwDgYDVR0PAQH/BAQDAgGGMA8GA1UdEwEB/wQFMAMB\n"  
  "Af8wHQYDVR0OBBYEFLE+w2kD+L9HAdSYJhoIAu9jZCvDMB8GA1UdIwQYMBaAFLE+w2kD+L9HAdSY\n"  
  "JhoIAu9jZCvDMA0GCSqGSIb3DQEBBQUAA4IBAQAcGgaX3NecnzyIZgYIVyHbIUf4KmeqvxgydkAQ\n"  
  "V8GK83rZEWWONfqe/EW1ntlMMUu4kehDLI6zeM7b41N5cdblIZQB2lWHmiRk9opmzN6cN82oNLFp\n"  
  "myPInngiK3BD41VHMWEZ71jFhS9OMPagMRYjyOfiZRYzy78aG6A9+MpeizGLYAiJLQwGXFK3xPkK\n"  
  "mNEVX58Svnw2Yzi9RKR/5CYrCsSXaQ3pjOLAEFe4yHYSkVXySGnYvCoCWw9E1CAx2/S6cCZdkGCe\n"  
  "vEsXCS+0yx5DaMkHJ8HSXPfqIbloEpw8nL+e/IBcm2PN7EeqJSdnoDfzAIJ9VNep+OkuE6N36B9K\n" 
  "-----END CERTIFICATE-----\n" ;

WiFiClientSecure clientForOta;
secureEsp32FOTA secureEsp32FOTA("sk6812rgbw", 2);




void setLedOn(int number){
    #if defined(FastLED)
    leds[number].setHSV(H, S, V);
    #elif defined(Neopixel)
    pixels.setPixelColor(number, pixels.Color(0, 0, 0, 100));
    #endif
}
void setLedOff(int number){
  #if defined(FastLED)
  leds[number].setHSV(0, 0, 0);
  #elif defined(Neopixel)
  pixels.setPixelColor(number, pixels.Color(0, 0, 0, 0));
  #endif
}

void getTime()
{

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  delay(1000);

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    delay(4000);
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    delay(3000);
    if (!getLocalTime(&timeinfo))
    {
      setLedOn(2);
      FastLED.show();
    }
  }
}

void checkUpdate(){
  secureEsp32FOTA._host="raw.githubusercontent.com";
  secureEsp32FOTA._descriptionOfFirmwareURL="/1JonaB1/Wordclock/master/Firmware/.bin%20and%20json%20for%20AutoUpdate/Versions.json";
  secureEsp32FOTA._certificate=test_root_ca;
  secureEsp32FOTA.clientForOta=clientForOta;

  bool shouldExecuteFirmwareUpdate=secureEsp32FOTA.execHTTPSCheck();
  if(shouldExecuteFirmwareUpdate)
  {
    Serial.println("Firmware update available!");
    secureEsp32FOTA.executeOTA();
  }
}

void displayTime()
{
  switch (tm_min % 5)
  { // Punkte min

  case 0:

    setLedOff(110);
    setLedOff(111);
    setLedOff(112);
    setLedOff(113);

    break;

  case 1:
    setLedOn(110);
    break;

  case 2:
    setLedOn(110);
    setLedOn(111);
    break;

  case 3:
    setLedOn(110);
    setLedOn(111);
    setLedOn(112);
    break;

  case 4:
    setLedOn(110);
    setLedOn(111);
    setLedOn(112);
    setLedOn(113);
    break;

  default:
    setLedOn(2);
    //get time
    break;
  }

  switch (tm_min / 5)
  {

  case 0:
    for (int i = 7; i < 11; i++)
    { //Fünf
      setLedOff(i);
    }

    for (int i = 41; i < 44; i++)
    { //Vor
      setLedOff(i);
    }

    for (int i = 99; i < 102; i++)
    { //Uhr
      setLedOn(i);
    }

    break;

  case 1:
    for (int i = 99; i < 102; i++)
    { //Uhr
      setLedOff(i);
    }

    for (int i = 7; i < 11; i++)
    { //Fünf
      setLedOn(i);
    }

    for (int i = 33; i < 37; i++)
    { //Nach
      setLedOn(i);
    }
    break;
  case 2:
    for (int i = 18; i < 22; i++)
    { // Zehn
      setLedOn(i);
    }
    for (int i = 33; i < 37; i++)
    { //Nach
      setLedOn(i);
    }
    for (int i = 7; i < 11; i++)
    { //Fünf
      setLedOff(i);
    }
    break;

  case 3:
    for (int i = 18; i < 22; i++)
    { // Zehn
      setLedOff(i);
    }

    for (int i = 26; i < 33; i++)
    { //Viertel
      setLedOn(i);
    }
    for (int i = 33; i < 37; i++)
    { //Nach
      setLedOn(i);
    }

    break;

  case 4:
    for (int i = 11; i < 18; i++)
    { //Zwanzig
      setLedOn(i);
    }
    for (int i = 33; i < 37; i++)
    { //Nach
      setLedOn(i);
    }

    for (int i = 26; i < 33; i++)
    { //Viertel
      setLedOff(i);
    }
    break;

  case 5:
    for (int i = 33; i < 37; i++)
    { //Nach
      setLedOff(i);
    }
    for (int i = 11; i < 18; i++)
    { //Zwanzig
      setLedOff(i);
    }
    for (int i = 41; i < 44; i++)
    { // Vor
      setLedOn(i);
    }
    for (int i = 7; i < 11; i++)
    { //Fünf
      setLedOn(i);
    }
    for (int i = 44; i < 48; i++)
    { //Halb
      setLedOn(i);
    }
    break;

  case 6:
    for (int i = 7; i < 11; i++)
    { //Fünf
      setLedOff(i);
    }

    for (int i = 41; i < 44; i++)
    { // Vor
      setLedOff(i);
    }

    for (int i = 44; i < 48; i++)
    { //Halb
      setLedOn(i);
    }
    break;
  case 7:
    for (int i = 33; i < 37; i++)
    { //Nach
      setLedOn(i);
    }

    for (int i = 7; i < 11; i++)
    { //Fünf
      setLedOn(i);
    }

    for (int i = 44; i < 48; i++)
    { //Halb
      setLedOn(i);
    }

    break;

  case 8:
    for (int i = 7; i < 11; i++)
    { //Fünf
      setLedOff(i);
    }
    for (int i = 11; i < 18; i++)
    { //Zwanzig
      setLedOn(i);
    }
    for (int i = 33; i < 37; i++)
    { //Nach
      setLedOff(i);
    }
    for (int i = 44; i < 48; i++)
    { //Halb
      setLedOff(i);
    }
    for (int i = 41; i < 44; i++)
    { // Vor
      setLedOn(i);
    }
    break;

  case 9:
    for (int i = 11; i < 18; i++)
    { //Zwanzig
      setLedOff(i);
    }
    for (int i = 26; i < 33; i++)
    { //Viertel
      setLedOn(i);
    }
    for (int i = 41; i < 44; i++)
    { // Vor
      setLedOn(i);
    }

    break;

  case 10:
    for (int i = 26; i < 33; i++)
    { //Viertel
      setLedOff(i);
    }

    for (int i = 18; i < 22; i++)
    { //Zehn
      setLedOn(i);
    }
    for (int i = 41; i < 44; i++)
    { // Vor
      setLedOn(i);
    }

    break;

  case 11:
    for (int i = 7; i < 11; i++)
    { //Fünf
      setLedOn(i);
    }

    for (int i = 18; i < 22; i++)
    { //Zehn
      setLedOff(i);
    }
    for (int i = 41; i < 44; i++)
    { // Vor
      setLedOn(i);
    }

    break;

  default:
      setLedOn(2);
    break;
  }

  if (tm_hour > 12)
  {
    tm_hour = tm_hour - 12;
  }
  if (tm_min > 24)
  {
    if (tm_hour == 12)
    {
      tm_hour = 1;
    }
    else
    {
      tm_hour = tm_hour + 1;
    }
  }

  switch (tm_hour)
  {
  case 1:
    for (int i = 94; i < 99; i++)
    { //Zwölf
      setLedOff(i);
    }
    for (int i = 63; i < 66; i++)
    { //Eins
      setLedOn(i);
    }
    if (tm_min > 4)
    {
      setLedOn(62);
    }


    break;
  case 2:
    for (int i = 62; i < 66; i++)
    { //Eins
      setLedOff(i);
    }
    for (int i = 55; i < 59; i++)
    { //Zwei
      setLedOn(i);
    }
    break;
  case 3:
    for (int i = 55; i < 59; i++)
    { //Zwei
      setLedOff(i);
    }
    for (int i = 66; i < 70; i++)
    { //Drei
      setLedOn(i);
    }
    break;
  case 4:
    for (int i = 66; i < 70; i++)
    { //Drei
      setLedOff(i);
    }
    for (int i = 73; i < 77; i++)
    { //Vier
      setLedOn(i);
    }
    break;
  case 5:
    for (int i = 73; i < 77; i++)
    { //Vier
      setLedOff(i);
    }
    for (int i = 51; i < 55; i++)
    { //Fünf
      setLedOn(i);
    }
    break;
  case 6:
    for (int i = 51; i < 55; i++)
    { //Fünf
      setLedOff(i);
    }
    for (int i = 83; i < 88; i++)
    { //Sechs
      setLedOn(i);
    }
    break;
  case 7:
    for (int i = 83; i < 88; i++)
    { //Sechs
      setLedOff(i);
    }
    for (int i = 88; i < 94; i++)
    { //Sieben
      setLedOn(i);
    }
    break;
  case 8:

    for (int i = 88; i < 94; i++)
    { //Sieben
      setLedOff(i);
    }
    for (int i = 77; i < 81; i++)
    { //Acht
      setLedOn(i);
    }
    break;
  case 9:
    for (int i = 77; i < 81; i++)
    { //Acht
      setLedOff(i);
    }
    for (int i = 103; i < 107; i++)
    { //Neun
      setLedOn(i);

    }
    break;
  case 10:
    for (int i = 103; i < 107; i++)
    { //Neun
      setLedOff(i);
    }
    for (int i = 106; i < 110; i++)
    { //Zehn
      setLedOn(i);
    }
    break;
  case 11:
    for (int i = 106; i < 110; i++)
    { //Zehn
      setLedOff(i);
    }
    for (int i = 49; i < 52; i++)
    { //Elf
      setLedOn(i);
    }
    break;
  case 12:
    for (int i = 49; i < 52; i++)
    { //Elf
      setLedOff(i);
    }
    for (int i = 94; i < 99; i++)
    { //Zwölf
      setLedOn(i);
    }
    break;
  }
  setLedOn(0); //E
  setLedOn(1); //S
  setLedOn(3); //I
  setLedOn(4); //S
  setLedOn(5); //T  
  
  #if defined(FastLED)
  FastLED.show();   // Send the updated pixel colors to the hardware.
  #elif defined(Neopixel)
  pixels.show();   // Send the updated pixel colors to the hardware.
  #endif
}

void time()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    getTime();
  }

  tm_min = timeinfo.tm_min;
  tm_hour = timeinfo.tm_hour;

  if (tm_min != tm_min_old)
  {
    tm_min_old = tm_min;
    displayTime();
  }
   if (tm_hour == 19)  {
     if(tm_min == 40){ 
       if(UpdateChecked == false){
          checkUpdate();
          UpdateChecked = true;
          getTime();
        }
      }
      else{
        UpdateChecked = false;
      }
    }
}

void setup()
{
  Serial.begin(115200);
  //FastLED
  #if defined(FastLED)
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.setCorrection(CRGB(255, 255, 230));
  FastLED.show();
  #elif defined(Neopixel)
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
  pixels.show();
  #endif


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

  //Autoconnect configuration
  config.ota = AC_OTA_BUILTIN;
  config.autoReconnect = true;
  config.title = "Wortuhr";
  config.apid = "Wortuhr";
  portal.config(config);
  portal.begin();


  getTime();
  checkUpdate();
}

void brightness()
{
  int light_in = analogRead(lightSensor);
  float light_new = light_in * 1.0;
  float temp = 0.0;
  int i = 0;

  light = light + (light_new - light) * 0.001;

  // normalize light to values between 0 and 1 (0 = dark 1 = light)
  temp = light / 2000.0;
  if (temp > 1.0)
    temp = 1.0;

  //calculate new brightness
  i = temp * (brightness_max - brightness_min) + brightness_min;
  // write new Brightness
  if (i < brightness_last - 6 || i > brightness_last + 6)
  {
    #if defined(FastLED)
    FastLED.setBrightness(i);
    FastLED.show();
    #elif defined(Neopixel)
    pixels.setBrightness(i);
    pixels.show();
    #endif
    brightness_last = i;
  }
}

void loop()
{
  time();
  brightness();
}