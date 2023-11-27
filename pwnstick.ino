#if ARDUINO_USB_MODE
#warning This sketch should be used when USB is in OTG mode
void setup(){}
void loop(){}
#else

#include "TFT_eSPI.h"
#include "dokkaebi.h"

#include "filemanager.h"
#include "luascript.h"
#include "webserver.h"

#define HAS_SCREEN

#ifdef HAS_SCREEN
TFT_eSPI tft = TFT_eSPI();
#endif

// Button handling
const int buttonPin = 0;
int previousButtonState = HIGH;
bool pauseAnimation = false;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

#ifdef HAS_SCREEN
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);
  digitalWrite(TFT_LEDA_PIN, 0);
#endif

  FileManager::start();
  HTTPServer::start();
  LuaScript::start();
}

uint8_t current_frame = 0;
long lastMillis = 0;

void loop() {

  HTTPServer::update();
  
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  if ((buttonState != previousButtonState) && (buttonState == LOW)) {
    pauseAnimation = !pauseAnimation;
  }

#ifdef HAS_SCREEN
  if(!pauseAnimation) {
    if((millis() - lastMillis) >= 140) {
        current_frame++;
        if(current_frame > 6) {
          current_frame = 0;
        }
        lastMillis = millis();
        tft.fillScreen(TFT_BLACK);
        tft.setSwapBytes(true);

        uint8_t xPos = 48;
        uint8_t yPos = 7;
        uint8_t xSize = 65;
        uint8_t ySize = 65;

        switch(current_frame) {
          default:
            tft.pushImage(xPos, yPos, xSize, ySize, (uint16_t*)dokkaebi1_bits);
            break;
          case 1:
            tft.pushImage(xPos, yPos, xSize, ySize, (uint16_t*)dokkaebi2_bits);
            break;
          case 2:
            tft.pushImage(xPos, yPos, xSize, ySize, (uint16_t*)dokkaebi3_bits);
            break;
          case 3:
            tft.pushImage(xPos, yPos, xSize, ySize, (uint16_t*)dokkaebi4_bits);
            break;
          case 4:
            tft.pushImage(xPos, yPos, xSize, ySize, (uint16_t*)dokkaebi5_bits);
            break;
          case 5:
            tft.pushImage(xPos, yPos, xSize, ySize, (uint16_t*)dokkaebi6_bits);
            break;
          case 6:
            tft.pushImage(xPos, yPos, xSize, ySize, (uint16_t*)dokkaebi7_bits);
            break;
        }
    }
  }
#endif
  
  // save the current button state for comparison next time:
  previousButtonState = buttonState;
}
#endif /* ARDUINO_USB_MODE */
