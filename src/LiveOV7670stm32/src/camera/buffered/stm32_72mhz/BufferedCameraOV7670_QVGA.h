//
// Created by indrek on 30.04.2016.
//

#ifndef _BUFFEREDCAMERAOV7670_QVGA_H
#define _BUFFEREDCAMERAOV7670_QVGA_H

#include "../BufferedCameraOV7670.h"


class BufferedCameraOV7670_QVGA : public BufferedCameraOV7670<uint16_t, 640, uint16_t, 320, uint16_t, 240> {

public:
  enum FramesPerSecond {
      FPS_7p5_Hz,
      FPS_6p4_Hz,
      FPS_5p6_Hz,
      FPS_5_Hz,
      FPS_4p5_Hz
  };


private:
  FramesPerSecond framesPerSecond;

public:
  BufferedCameraOV7670_QVGA(PixelFormat format, FramesPerSecond fps) :
      BufferedCameraOV7670(Resolution::RESOLUTION_QVGA_320x240, format, getPreScalerForFps(fps)),
      framesPerSecond(fps)
  {};

  inline void readLine() override __attribute__((always_inline));


private:
  static uint8_t getPreScalerForFps(FramesPerSecond fps) {
    switch (fps) {
      case FPS_7p5_Hz:
        return 5;
      case FPS_6p4_Hz:
        return 6;
      case FPS_5p6_Hz:
        return 7;
      case FPS_5_Hz:
        return 8;
      default:
      case FPS_4p5_Hz:
        return 9;
    }
  }
};




void BufferedCameraOV7670_QVGA::readLine() {


  switch (framesPerSecond) {

    case FPS_7p5_Hz: {
      waitForPixelClockHigh();

      pixelBuffer.writeBufferPadding = 0;
      uint16_t bufferIndex = 0;
      while (bufferIndex < getPixelBufferLength()) {
        waitForPixelClockLow();
        asm volatile("nop");
        readPixelByte(pixelBuffer.writeBuffer[bufferIndex++]);

        waitForPixelClockLow();
        asm volatile("nop");
        readPixelByte(pixelBuffer.writeBuffer[bufferIndex++]);
      }
    } break;

    case FPS_6p4_Hz:
    case FPS_5p6_Hz:
    case FPS_5_Hz: {
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
        readPixelByte(pixelBuffer.writeBuffer[bufferIndex++]);

        waitForPixelClockLow();
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        asm volatile("nop");
        readPixelByte(pixelBuffer.writeBuffer[bufferIndex++]);
      }
    } break;

    default: {
      BufferedCameraOV7670::readLine();
    } break;
  }


}






#endif //_BUFFEREDCAMERAOV7670_QVGA_H
