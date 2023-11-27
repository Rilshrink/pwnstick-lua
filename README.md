# PwnStick
Just a basic usb rubber ducky clone with a wifi enabled web interface and an embedded lua scripting api
A modified version of LockManipulator's T-Dongle-Ducky
# Inspiration / Sources
* https://github.com/LockManipulator/T-Dongle-Ducky
* https://github.com/SpacehuhnTech/WiFiDuck

# How to use?
## Libraries
Please install these libraries into the Arduino `/libraries` folder
* https://github.com/Xinyuan-LilyGO/T-Dongle-S3
* https://github.com/me-no-dev/ESPAsyncWebServer
* https://github.com/me-no-dev/AsyncTCP
* https://github.com/fdu/ESP8266-Arduino-Lua/

## Arduino Settings
Follow the settings as described in the `https://github.com/Xinyuan-LilyGO/T-Dongle-S3` github repo, and change the board to **ESP32-S3-USB-OTG**

You can then configure the access point and webui settings in `webserver.h`

## Usage
> Be sure to insert a Fat32 formatted microsd card into the t-dongle-s3 or you'll be missing a lot of functionality!

Connect to the AP using the credentials you set or default is:
* ssid: 'PwnStick'
* psk: 'pwnedpwned'

Then using your browser connect to `192.168.1.1`
Then use the credentials you set or default is:
* user: 'root'
* pass: 'toor'

## Known Issues
Executing lua scripts from the web interface has a size limit, I have yet to figure out why, so try not to make them too long.

# FAQ
- [Why not duckyscript?](#why-not-duckyscript)
- [How do I get a script to autorun when inserted?](#autorun)
- [Help! I flashed it in USB-OTG mode and now I can't reflash it](#help-i-cant-reflash)
- [I don't have a screen how can I remove that portion of code?](#i-dont-have-a-tft-screen)
- [How do I interface with lua?](#how-do-i-interface-with-lua)

## Why not duckyscript?
Because the ESP32-S3 is more than powerful enough to run a full lua vm I decided it would just be easier to implement lua, and it can be easily expandable in the future!

The only negative I see with this change is it will **not** be compatible with already existing duckyscripts and will have to be rewritten!

## Autorun?
Just create a file named `autorun.lua` on the microsd card and it will run when the usb stick is inserted. If you want to make sure it doesn't run before the computer recognises it: be sure to add a delay!

Don't worry if there isn't a script named autorun.lua **NO** other script will automatically run!

## Help I can't reflash!
Just hold down the button on the back of the T-Dongle-S3 when inserting it into the device!

## I don't have a tft screen!
In pwnstick.ino there is a ```#define HAS_SCREEN``` statement just remove or comment it out!

## How do I interface with lua?
In this repo there is a directory named 'examples' it includes how to write with the keyboard and move the mouse, and yes you can use the mouse and keyboard at the same time, and only 1 script may run at any given time.

The lua documentation is a **WIP**

## TODO
- Fix the web interface max upload size, possibly fixed using websockets.
- Lua documentation.
- Implement print method.
- Send errors and other diagnostic information to web interface.
- Add OS detection using the HAK5 capslock keylight detection.
- Cleanup the code.