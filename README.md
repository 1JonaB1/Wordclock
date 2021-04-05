# Wordclock
Diy Wordclock with an Esp32 and smart leds like ws2812b.

## Features: 
- Time from ntp server
- Confiurable over Webinterface
- OTA Updates in the Webinterface 
- No need for Hardcoding credentials
- Smooth Dimming which is stepless

## Plans for the Future:
- change LED color etc. over Webinterface 
- Photoresistor calibration
- sk6812 rgbw support (allready tested with fastled now need to implement it into the code)
- Auto Updating (almost done and getting tested)

## Status
- Im still working on it, but im trying to finish it in the next months
- Currently 9 Clocks run on this Firmware since 5 month with only a few bugs 

## Known Issues
- The date for the daylight saving folows the American and can currently not be canged ( Im working on it and a fix should be availible soon but it only affects <20 days a year)
- One Clock ran 3 minutes behind, but a restart solved it (I dont know anything about this issue and it happend to only one clock after 5months so im not working on it)

## Tipps for building:

The Build is somehow simple. You can use my PCB with an Esp32 and a levelshifter(please make soure they would fit in the PCB
and build an enclousure for it.
You can also build it with led strips which start at the top left and go in snakelines down(11rows wit 10 colums)first cornerled is the top right and then Corner under it then the Led down right and then top left(just look at the PCB). Connect the Strip with an Levelshifter to pin 23 of the Arduino and the Photoresistor to pin 34.

## How to Open the Sketch:
You can open the Folder Wordclock which is in Firmware/Code with Platform.io or rename the code main.cpp in  Firmware/Code/Wordclock/src to main.ino  and open it with the Arduino IDE. However the libarys need to be installed manually.

## How to Customize:
**Currently all customisation needs a bit of research, however i want to make it easier in the Future.**
#### Time
The time can be chagne by editing the Variable gmtOffset_sec, where the number is the Offset in Minutes from the UTC. For example Germany is 1 houre before the UTC time so the Value needs to be 3600. The other Variable for the Time is the daylightOffset_sec, which sets the difference between summmer and winter time, howerer most People dont need to change it.
#### Language
The Language of the Webconfiguration is in Englisch as Default. If you want to change it you need to folow the [simple Guide](https://hieromon.github.io/AutoConnect/adexterior.html) from and for the libary Autoconnect im using.
#### LED type and Pin
By Default the LED type is for the WS2812B, however you can change it easily. Just seach in setup  ```FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS)``` and replace it with your LED Type from the list below.
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
