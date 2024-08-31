# esp8266TemperaturePanel
** This is a project made for fun, it has a good user interface and is very user friendly. **
# HTML Language
- ES from Spain

Fix it in the HTML code or translate it with Browser translation.

# Images of the websocket website

![image](https://github.com/user-attachments/assets/b66fb6e0-cbe6-496d-93a0-17751e477f67)
![image](https://github.com/user-attachments/assets/36549c8a-3774-4df7-ab21-f3fed469cf99)

## Features
- **Websocket**: to always be able to see the temperature and humidity in real time.
- **NTP Client**: as an user you can see where did the maximum vulue or minimun value were taken.
- Average temperature and humidity.

## Modules to compile
- **ArduinoJson** by _Benoit Blanchon_ ( 7.1.0 )
- **DHT22** by _dvarrel_ ( 1.1.4 )
- **ESPAsyncWebServer** by _lacamera_ ( 3.1.0 )
- **NTPClient** by _Fabrice Weinberg_ ( 3.2.1 )
- **ESPAsyncTCP** by _dvarrel_ ( 1.1.4 )

If somethings missing then install
-** WiFi Link** by _Arduino_ ( 1.0.1 ).

## What do i need to use this?
- ESP8266 microcontroller
- 3 wires
- DHT22 Temperature and Humidity sensor
- Internet

## What do you need to change
After downloading the code you need to change 2 lines of the code to make it work.
- Line 205: ssid, you need to change this to match your WiFi name.
- Line 206: password, change it to your WiFi password.

>[!warning] Known features that are missing
> - You can't know what IP did the DHCP give to the ESP8266 from outside. ( You can see it in Serial Monitor ).


