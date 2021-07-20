C header to handle generating i2c commands to control a WM8731 audio codec. Written against the RP2040 "PICO-SDK" but architected to be easily portable to work with any microcontroller SDK.

Tested with a Mikroe 506 Audio Codec Proto Board connected to a Raspberry Pi PICO / Sparkfun RP2040 Plus.

# Note on wiring

Under standard usage conditions (i2c + i2s), you can think of the Mikroe 506 as being 3 distinct devices
* An i2c device - for configuration commands
* An i2s device - the DAC
* An i2s device - the ADC
 
The Mikroe board uses SPI labels (SCK, COPI(MOSI), CIPO(MISO), and CS(SS)) for the i2s devices.

* SCK - They share the common SCK pin
* SD - The DAC is a COPI device (MOSI), and the ADC is a CIPO device (MISO)
* WS - The DACL / ADCL are used for their respective devices, but you'll often see those wired to a single GPIO on the board, which you can do if you sychronize / serialize your IO as they do with the standard Linux driver for the WM8731.

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
