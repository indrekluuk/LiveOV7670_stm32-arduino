//
// Created by indrek on 4.12.2016.
//


#include "Arduino.h"
#include "screen/Adafruit_ST7735_stm32arduino.h"




// A5 - SPI clock
// A6 - SPI in
// A7 - SPI out
// A8 - camera clock
// A9 serial TX
// A10 serial RX
// A10 serial RX




Adafruit_ST7735_stm32Arduino tft(PA2, PA3, PA1);




void setup() {

  // configure PA8 to output PLL/2 clock
  gpio_set_mode(GPIOA, 8, GPIO_AF_OUTPUT_PP);
  *(volatile uint8_t *)(0x40021007) = 0x7; // MCO_Config(PLL/2);


  /*
  SPI.begin();
  SPI.setClockDivider(1);
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
   */

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);

  pinMode(PC13, OUTPUT);
}



bool color = true;
void loop() {
  digitalWrite(PC13, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(PC13, HIGH);    // turn the LED off by making the voltage LOW
  delay(500);

  //SPI.write(17);

  tft.fillScreen(color ? ST7735_RED : ST7735_CYAN);
  color = !color;

}

