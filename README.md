# Wordclock
Diy Wordclock with an Esp32 and smart LEDs like ws2812b.
![20201223_222611](https://user-images.githubusercontent.com/57105059/205077834-c267bf58-da39-4d44-9e0c-c00d648075f7.jpg)

## Features: 
- Time from ntp server
- Confiurable over Webinterface
- OTA Updates Automaticaly and in the Webinterface
- No need for Hardcoding credentials
- Smooth Dimming which is stepless


## Plans for the Future if requestet:
- change LED color etc. over Webinterface 
- Photoresistor calibration

## Status
- Im currently looking at the project as done and wont implement new features unless Requestet (just write an issue). Ofcourse i will still fix bugs
- Currently 11 Clocks are running this Firmware
## Known Issues
- The date for the daylight saving folows the American and can currently not be canged (Currently the is not a fixe becouse the dst is planed to be removed in europe. in the mean time, i will make an OTA update to change time for my clocks

## Tipps for building:

The Build is somehow simple. You can use my PCB with an Esp32 and a levelshifter(please make soure they would fit in the PCB
and build an enclousure for it.
You can also build it with led strips which start at the top left and go in snakelines down(11rows wit 10 colums)first cornerled is the top right and then Corner under it then the Led down right and then top left(just look at the PCB). Connect the Strip with an Levelshifter to pin 23 of the Arduino and the Photoresistor to pin 34.

## How to Open the Sketch:
You can open the Folder Wordclock which is in Firmware/Code with Platform.io or rename the code main.cpp in  Firmware/Code/Wordclock/src to main.ino  and open it with the Arduino IDE. However the libarys need to be installed manually. Please ensure, that the right type of Led is selescted and that either Neopixel or Fastled is uncommented. Please read "Led type and Pin"

## How to Customize:
#### if you customize the firmware, you need to set ```secureEsp32FOTA secureEsp32FOTA("sk6812rgbw", 2);``` to 99 so you wont get OTA updates or create your own Type as update branch, so OTAs work (pls. refer to OTA update)

**If the Documentation is unclear pls ask, becouse i also know the Documentation is bad (:**

**Currently all customisation needs a bit of research, however i want to make it easier in the Future.**
#### Time
The time can be chagne by editing the Variable gmtOffset_sec, where the number is the Offset in Minutes from the UTC. For example Germany is 1 houre before the UTC time so the Value needs to be 3600. The other Variable for the Time is the daylightOffset_sec, which sets the difference between summmer and winter time, howerer most People dont need to change it.

#### OTA update
Im using the esp32 FOTA libary, which uses a json to check if there is a new firmware. To cusomize please read their documentation. If you want to use your own Firmware hosted in this Repository, edit the Json (and add the .bin file) or fork the repository and edit the url in the code to you repository

#### Language
The Language of the Webconfiguration is in Englisch as Default. If you want to change it you need to folow the [simple Guide](https://hieromon.github.io/AutoConnect/adexterior.html) from and for the libary Autoconnect im using.
#### LED type and Pin
By Default the LED type is for the WS2812B, however you can change it easily.
If you use RGBW Leds you need to search for #define FastLED set a // before it and remove the // at Neopixel. You can change the Led type for neopixel in ```Adafruit_NeoPixel pixels(NUM_LEDS, DATA_PIN, NEO_GRBW + NEO_KHZ800);```

If you use FastLEd cahnge in void setup  ```FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS)``` and replace it with your LED Type from the list below.
```
    FastLED.addLeds<SM16703, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<TM1829, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<TM1812, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<UCS1904, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<UCS2903, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    FastLED.addLeds<WS2852, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    FastLED.addLeds<GS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<SK6812, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    FastLED.addLeds<SK6822, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<APA106, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<PL9823, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<SK6822, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<WS2813, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<APA104, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<WS2811_400, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<GE8822, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<LPD1886, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<LPD1886_8BIT, DATA_PIN, RGB>(leds, NUM_LEDS);
    ## Clocked (SPI) types ##
    FastLED.addLeds<LPD6803, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
    FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<WS2803, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
    FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
    FastLED.addLeds<SK9822, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);  // BGR ordering is typical
```
#### Change LED
If you want to change the LED Pin, search for ``` #define DATA_PIN 23 ``` and change the Pin to where your LEDs are connected.
If you want to change the Photoresistor Pin, search for ``` #define lightSensor 34 ``` and change the Pin to where your Photoresistor is connected.
#### Correct color
If you want to correct the Color you need to change in Setup ``` FastLED.setCorrection(CRGB(255, 255, 230)); ``` The Numbers say the Strenght of each color first is Red secong Green and third Blue. I have set Blue lower becouse i wanted a warmer White.

**Contributions are Welcome and im happy to help at Issues**
