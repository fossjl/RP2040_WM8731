C header to handle generating i2c commands to control a WM8731 over i2c. Written against the RP2040 "PICO-SDK" but architected to be easily portable to work with any microcontroller SDK.

Tested with a Mikroe 506 Audio Codec Proto Board connected to a Raspberry Pi PICO / Sparkfun RP2040 Plus.

# Note on wiring

Under standard usage conditions (i2c + i2s), you can think of the Mikroe 506 as being 3 distinct devices
* An i2c device - for configuration commands
* An i2s device - the DAC
* An i2s device - the ADC
 
You have 2 i2s devices, but the Mikroe board labels them as SPI pins (SCK, COPI(MOSI), CIPO(MISO), and CS(SS))

They each use the SCK clock line

For the serial data line of the i2s interface, DAC is the COPI device, and the ADC is the COPI device.

The DACL / ADCL are used as the WS lines. You'll sometime see those wired together, which you can do if you're sychronizing reading/writing as they do with the standard Linux driver for the WM8731.

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
