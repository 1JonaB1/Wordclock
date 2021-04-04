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
- sk6812 rgbw support
- Auto Updating (almost done and getting tested)

## Tipps for building:

The Build is somehow simple. You can use my PCB with an Esp32 and a levelshifter(please make soure they would fit in the PCB
and build an enclousure for it.
You can also build it with led strips which start at the top left and go in snakelines down(11rows wit 10 colums)first cornerled is the top right and then Corner under it then the Led down right and then top left(just look at the PCB). Connect the Strip with an Levelshifter to pin 23 of the Arduino and the Photoresistor to pin 34.

## How to Open the Sketch:
You can open the Folder Wordclock which is in Firmware/Code with Platform.io or rename the code main.cpp in  Firmware/Code/Wordclock/src to main.ino  and open it with the Arduino IDE. However the libarys need to be installed manually.

## How to Customize:
**Currently all customisation needs a bit of research, however i want to make it easier in the Future.**
### Time
The time can be chagne by editing the Variable gmtOffset_sec, where the number is the Offset in Minutes from the UTC. For example Germany is 1 houre before the UTC time so the Value needs to be 3600. The other Variable for the Time is the daylightOffset_sec, which sets the difference between summmer and winter time, howerer most People dont need to change it.
### Language
The Language of the Webconfiguration is in Englisch as Default. If you want to change it you need to folow the [simple Guide](https://hieromon.github.io/AutoConnect/adexterior.html) from and for the libary Autoconnect im using.



**Contributions are Welcome and im happy to help at Issues**
