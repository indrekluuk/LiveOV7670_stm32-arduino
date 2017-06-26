//
// Created by indrek on 30.04.2016.
//

#ifndef _BUFFEREDCAMERAOV7670_QQVGA_H
#define _BUFFEREDCAMERAOV7670_QQVGA_H

#include "../BufferedCameraOV7670.h"


// 160 x 120 @ 5Hz or less
class BufferedCameraOV7670_QQVGA : public BufferedCameraOV7670<uint16_t, 320, uint8_t, 160, uint8_t, 120> {

public:
  enum FramesPerSecond {
      FPS_XX_Hz,
      FPS_15_Hz,
      FPS_12_Hz,
      FPS_9_Hz,
      FPS_7p2_Hz
  };


private:
  FramesPerSecond framesPerSecond;

public:
  BufferedCameraOV7670_QQVGA(PixelFormat format, FramesPerSecond fps) :
      BufferedCameraOV7670(Resolution::RESOLUTION_QQVGA_160x120, format, getPreScalerForFps(fps)),
      framesPerSecond(fps)
  {};

  inline void readLine() override __attribute__((always_inline));


private:
  static uint8_t getPreScalerForFps(FramesPerSecond fps) {
    switch (fps) {
      default:
      case FPS_XX_Hz:
        return 1;
      case FPS_15_Hz:
        return 2;
      case FPS_12_Hz:
        return 3;
      case FPS_9_Hz:
        return 4;
      case FPS_7p2_Hz:
        return 5;
    }
  }
};




void BufferedCameraOV7670_QQVGA::readLine() {

  // reading loop is too tight for 12Hz and above to wait for raising clock edge
  if (framesPerSecond == FPS_XX_Hz) {
//    while(OV7670_HREF);

    pixelBuffer.writeBufferPadding = 0;
    uint16_t bufferIndex = 0;



    while(!OV7670_HREF);

    //C14_ON;
    //C14_OFF;

    while (bufferIndex < getPixelBufferLength()) {
      pixelBuffer.writeBuffer[bufferIndex++] = readPixelByte();
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");

      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");

      pixelBuffer.writeBuffer[bufferIndex++] = readPixelByte();

      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
//      asm volatile("nop");

      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
    }

    //C14_ON;
    //C14_OFF;
  } else if (framesPerSecond == FPS_15_Hz) {


    waitForPixelClockHigh();

    pixelBuffer.writeBufferPadding = 0;
    uint16_t bufferIndex = 0;
    while (bufferIndex < getPixelBufferLength()) {
      waitForPixelClockLow();
      asm volatile("nop");
      pixelBuffer.writeBuffer[bufferIndex++] = readPixelByte();

      waitForPixelClockLow();
      asm volatile("nop");
      pixelBuffer.writeBuffer[bufferIndex++] = readPixelByte();
    }


  } else if (framesPerSecond == FPS_12_Hz) {

    waitForPixelClockHigh();

    pixelBuffer.writeBufferPadding = 0;
    uint16_t bufferIndex = 0;
    while (bufferIndex < getPixelBufferLength()) {
      waitForPixelClockLow();
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      pixelBuffer.writeBuffer[bufferIndex++] = readPixelByte();

      waitForPixelClockLow();
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      asm volatile("nop");
      pixelBuffer.writeBuffer[bufferIndex++] = readPixelByte();
    }

  } else {
    BufferedCameraOV7670::readLine();
  }

}






#endif //_BUFFEREDCAMERAOV7670_QQVGA_H
