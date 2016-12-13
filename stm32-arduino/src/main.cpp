//
// Created by indrek on 4.12.2016.
//


#include "Arduino.h"
#include "camera/base/CameraOV7670.h"
#include "screen/Adafruit_ST7735_stm32arduino.h"



// A5 - SPI clock
// A6 - SPI in
// A7 - SPI out
// A8 - camera clock
// A9 serial TX
// A10 serial RX
// A10 serial RX
// PB4 - pixel clock
// PB5 - vsync
// PB6 - i2c Clock
// PB7 - i2c data
// PB8..PB15 pixel byte



CameraOV7670 camera(CameraOV7670::RESOLUTION_QQVGA_160x120, CameraOV7670::PIXEL_RGB565, 19);
Adafruit_ST7735_stm32Arduino tft(PA2, PA3, PA1);






void setup() {

  camera.init();
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);

  pinMode(PC13, OUTPUT);

  noInterrupts();
}



void processFrame();



void loop() {
  processFrame();
}










inline void screenLineStart(void) __attribute__((always_inline));
inline void screenLineEnd(void) __attribute__((always_inline));
inline void sendPixelByte(uint8_t byte) __attribute__((always_inline));
inline void pixelSendingDelay() __attribute__((always_inline));


static const uint16_t lineLength = 160;
static const uint16_t lineCount = 120;

// Normally it is a portrait screen. Use it as landscape
uint8_t screen_w = ST7735_TFTHEIGHT_18;
uint8_t screen_h = ST7735_TFTWIDTH;
uint8_t screenLineIndex;





// this is called in Arduino loop() function
void processFrame() {
  screenLineIndex = screen_h;

  camera.waitForVsync();

  uint8_t lowByte = 0;
  uint8_t bufferedLowByte = 0;

  for (uint16_t y = 0; y < lineCount; y++) {

    screenLineStart();

    // For full VGA resolution byte order from camera is low1, high1, low2, high2
    // We have to swap byte order for the screen.

    camera.waitForPixelClockRisingEdge();
    bufferedLowByte = camera.readPixelByte();

    for (uint16_t x = 0; x < lineLength-1; x++) {

      camera.waitForPixelClockRisingEdge();
      sendPixelByte(camera.readPixelByte()); // send pixel high byte

      lowByte = bufferedLowByte;
      camera.waitForPixelClockRisingEdge();
      bufferedLowByte = camera.readPixelByte();
      sendPixelByte(lowByte); // send pixel low byte
    }

    // send last pixel
    camera.waitForPixelClockRisingEdge();
    sendPixelByte(camera.readPixelByte()); // send pixel high byte
    pixelSendingDelay(); // prevent sending collision
    sendPixelByte(bufferedLowByte); // send pixel low byte
    pixelSendingDelay();


    screenLineEnd();
  }
}





void screenLineStart()   {
  if (screenLineIndex > 0) screenLineIndex--;
  tft.startAddrWindow(screenLineIndex, 0, screenLineIndex, screen_w-1);
}

void screenLineEnd() {
  tft.endAddrWindow();
}


void sendPixelByte(uint8_t byte) {
  SPI.transfer(byte);

  // this must be adjusted if sending loop has more/less instructions

  /*
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  */
}



void pixelSendingDelay() {
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");

}





