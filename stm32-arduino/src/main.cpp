//
// Created by indrek on 4.12.2016.
//


#include "Arduino.h"

void setup() {


  // configure PA8 to output PLL/2 clock
  gpio_set_mode(GPIOA, 8, GPIO_AF_OUTPUT_PP);
  *(volatile uint8_t *)(0x40021007) = 0x7; // MCO_Config(PLL/2);


  pinMode(PC13, OUTPUT);
}




void loop() {
  digitalWrite(PC13, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(PC13, HIGH);    // turn the LED off by making the voltage LOW
  delay(200);

  digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW
  delay(100);

  digitalWrite(PC13, HIGH);    // turn the LED off by making the voltage LOW
  delay(100);

  digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW
  delay(100);

  digitalWrite(PC13, HIGH);    // turn the LED off by making the voltage LOW
  delay(100);
}

