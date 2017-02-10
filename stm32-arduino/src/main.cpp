//
// Created by indrek on 4.12.2016.
//


#include "Arduino.h"
#include "camera/buffered/BufferedCameraOV7670.h"
#include "camera/buffered/stm32_72mhz/BufferedCameraOV7670_QQVGA_30hz.h"
#include "camera/buffered/stm32_72mhz/BufferedCameraOV7670_QQVGA.h"
#include "screen/Adafruit_ST7735_stm32arduino.h"



// A5 - SPI clock
// A6 - SPI in
// A7 - SPI out
// A8 - camera clock
// A9 serial TX
// A10 serial RX
// A10 serial RX
// PB3 - href
// PB4 - pixel clock
// PB5 - vsync
// PB6 - i2c Clock
// PB7 - i2c data
// PB8..PB15 pixel byte


BufferedCameraOV7670_QQVGA camera(CameraOV7670::PIXEL_RGB565, BufferedCameraOV7670_QQVGA::FPS_12_Hz);

//BufferedCameraOV7670_QQVGA_30hz camera(CameraOV7670::PIXEL_RGB565);

//BufferedCameraOV7670<uint16_t, 320, uint8_t, 160, uint8_t, 120> camera(
//    CameraOV7670::RESOLUTION_QQVGA_160x120,
//    CameraOV7670::PIXEL_RGB565,
//    4);


Adafruit_ST7735_stm32Arduino tft(PA2, PA3, PA1);






void setup() {

  camera.init();
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);

  pinMode(PC13, OUTPUT);
  pinMode(PC14, OUTPUT);

  noInterrupts();
}



void processFrame();



void loop() {
  processFrame();
}





inline void sendLineToDisplay() __attribute__((always_inline));

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

  for (uint8_t i = 0; i < camera.getLineCount(); i++) {
    camera.readLine();
    sendLineToDisplay();
  }
}



void sendLineToDisplay() {
  if (screenLineIndex > 0) {
    screenLineStart();
    for (uint16_t i=0; i<camera.getPixelBufferLength(); i++) {
      sendPixelByte(camera.getPixelByte(i));
    }
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
  spi_tx_reg(SPI1, byte);


  //SPI.transfer(byte);

  // this must be adjusted if sending loop has more/less instructions

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





