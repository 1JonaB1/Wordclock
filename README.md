# Wordclock
My cheap Diy Wordclock with an Esp32 and WS2812b leds 

Features: 
- Time from ntp server
- Confiurable over Webinterface
- OTA Updates in the Webinterface 
- No need for Hardcoding credentials
- Smooth Dimming which is stepless

Plans for the Future:
- change LED color and other thinks over Webinterface 
- Photoresistor calibration


Tipps for building:

The Build is somehow simple. You can use my PCB with an Esp32 and a levelshifter(please make soure they would fit in the PCB
and build an enclousure for it.
You can also build it with led strips which start at the top left and go in snakelines down(11rows wit 10 colums)first cornerled is the top right and then Corner under it then the Led down right and then top left(just look at the PCB). Connect the Strip with an Levelshifter to pin 23 of the Arduino and the Photoresistor to pin 34.


I would apreciate if people help and make the Code better!
If you have questions contakt me.
