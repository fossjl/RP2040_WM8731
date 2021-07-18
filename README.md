C header to handle generating i2c commands to control a WM8731 over i2c. Written against the RP2040 "PICO-SDK" but architected to be easily portable to work with any microcontroller SDK.

Tested with a Mikroe 506 Audio Codec Proto Board connected to a Raspberry Pi PICO / Sparkfun RP2040 Plus.

# Note on wiring

You can think of the Mikroe 506 as being 3 distinct devices
* An i2c device - for configuration commands
* An SPI device - the DAC
* An SPI device - the ADC
 
You have 2 SPI devices with 2 sets of the 4-pins (SCK, COPI(MOSI), CIPO(MISO), and CS(SS))
* SPI devices automatically share the SCK line, so there's no need to duplicate that pin
* The DAC is read-only, and the ADC is write-only... so there's no need for those pins to appear on the board
* You'll often see people plug both the CS pins for the DAC And ADC to the same GPIO. That's because they cannot conflict, so there's no need to waste an extra GPIO on them.

## So you end up with...

### Power
* GND->GND
* VCC->VCC

### (i2c)
* SDA<->SDA
* SCL<->SCL

### (i2s)
* SCK<->SCK
* DACL<->GPIO x
* ADCL<->GPIO x (or y)
* COPI<->COPI (for the DAC)
* CIPO<->CIPO (for the ADC)
* SCK <->SCK  
