Datasheet for OV7670:  
https://www.voti.nl/docs/OV7670.pdf

----

STM32 support for Arduino IDE.  
Add this to File->Preferences->Additional Boards Manager URLs:  
http://dan.drown.org/stm32duino/package_STM32duino_index.json

<br>
<br>

TFT connection:  
A1 - TFT reset  
A2 - TFT chip select  
A3 - TFT D/C (data/command)  
A5 - SPI clock  
A7 - MOSI  
  
Camera connections:  
A8 - XCLCK (camera clock)  
PB3 - HREF (Connecting this is not mandatory. Code is not using it)  
PB4 - PCLCK (pixel clock)  
PB5 - VSYNC (vertical sync)  
PB6 - i2c Clock (10K resistor to 3.3V)  
PB7 - i2c data (10K resistor to 3.3V)  
PB8..PB15 - D0..D7 (pixel byte)  
