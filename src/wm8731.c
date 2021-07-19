#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

#include "hardware/i2c.h"
#include "pico/binary_info.h"

#include "i2c_handling.h"
#include "wm8731_advanced.h"

#include "data/HeadphoneOutConfig.h"
#include "data/LineInConfig.h"

#include "wm8731.h"

#define lo(param) ((char *)&param)[0]
#define hi(param) ((char *)&param)[1]

/**************************************************************************************************
* WM8731 sound chip register addresses
**************************************************************************************************/
static const char WM8731_REG_LLINE_IN        = 0x00;       // Left Channel Line Input Volume Control
static const char WM8731_REG_RLINE_IN        = 0x01;       // Right Channel Line Input Volume Control
static const char WM8731_REG_LHPHONE_OUT     = 0x02;       // Left Channel Headphone Output Volume Control
static const char WM8731_REG_RHPHONE_OUT     = 0x03;       // Right Channel Headphone Output Volume Control
static const char WM8731_REG_ANALOG_PATH     = 0x04;       // Analog Audio Path Control
static const char WM8731_REG_DIGITAL_PATH    = 0x05;       // Digital Audio Path Control
static const char WM8731_REG_PDOWN_CTRL      = 0x06;       // Power Down Control Register
static const char WM8731_REG_DIGITAL_IF      = 0x07;       // Digital Audio Interface Format
static const char WM8731_REG_SAMPLING_CTRL   = 0x08;       // Sampling Control Register
static const char WM8731_REG_ACTIVE_CTRL     = 0x09;       // Active Control
static const char WM8731_REG_RESET           = 0x0F;       // Reset register

/**************************************************************************************************
* WM8731 sound chip constants (for default set up)
**************************************************************************************************/
static const u_int32_t _WM8731_left_lineIn        = 0x0180;     // Mic settings: Enable mute, Enable simultaneous load to left and right channels
static const u_int32_t _WM8731_Right_lineIn       = 0x0180;     // Mic settings: Enable mute, Enable simultaneous load to left and right channels
static const u_int32_t _WM8731_Left_hp            = 0x00F0;     // Headphone settings : -9dB output
static const u_int32_t _WM8731_Right_hp           = 0x00F0;     // Headphone settings : -9dB output
static const u_int32_t _WM8731_AnalogAudio        = 0xD0;       // DAC Select
static const u_int32_t _WM8731_DigitalAudio       = 0x06;
static const u_int32_t _WM8731_power              = 0x00;       // Disable Power down
static const u_int32_t _WM8731_DAIF               = 0x43;       // Enable Master Mode and 32bit data
static const u_int32_t _WM8731_Sampling           = 0x23;       // 44100Hz
static const u_int32_t _WM8731_Activate           = 0x01;       // Module is ON
static const u_int32_t _WM8731_Deactivate         = 0x00;       // Module is OFF
static const u_int32_t _WM8731_Reset              = 0x00;       // Reset value


/**************************************************************************************************
* Function WM8731_CMD
* -------------------------------------------------------------------------------------------------
* Overview: Function write word of data to WM8731
* Input: register address, data
* Output: Nothing
**************************************************************************************************/
static void WM8731_CMD(char address, unsigned int cmd){
  char addr;
  // B[15:9] Are Control Address Bits
  // B[8:0]  Are Control Data Bits
  addr = address << 1;                 // Shift left for one positions
  addr = addr | (hi(cmd) & 1);

  _i2c_write_blocking(addr, lo(cmd));
}

/*
 * Converts a float (0...1) to a volume register value
 */
unsigned int convertNormalizedVolume(int vol) {
  unsigned int temp;
  if (vol <= 0) {
    temp = 0x0000;
  }
  else if (vol > 100) {
    temp = 80 + 0xAF;
  }
  else {
    temp = (int)(80 * vol/100.0) + 0x00AF;
  }

  return temp;
}

/*
 * Sets the normalized volume (0...100) on the two headphone channels
 */
void WM8731_set_headphone_volume(int leftVolume, int rightVolume) {


  // Build & initialize our control structure
  HeadphoneOutConfig config; 
  HeadphoneOutConfig_init(&config);

  // Set the left headphone volume
  config.HPVOL = convertNormalizedVolume(leftVolume);
  WM8731_CMD(WM8731_REG_LHPHONE_OUT, HeadphoneOutConfig_build(&config));     

  // Set the right headphone volume
  config.HPVOL = convertNormalizedVolume(rightVolume);
  WM8731_CMD(WM8731_REG_RHPHONE_OUT, HeadphoneOutConfig_build(&config));     

}

void WM8731_reset() {

  uint8_t buf[2];
  buf[0] = 0x12; 
  buf[1] = 0x00;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false);

}

void WM8731_activate_interface(bool active) {
  WM8731_CMD(WM8731_REG_ACTIVE_CTRL, active ? _WM8731_Activate : _WM8731_Deactivate);
}

void WM8731_configure_DAC(int iwl) {
  int iwl_val = 0;
  if (iwl == _20_BITS) {
    iwl_val = 1;
  }
  else if (iwl == _24_BITS) {
    iwl_val = 2;
  }
  else if (iwl == _32_BITS) {
    iwl_val = 3;
  }
  
  WM8731_CMD(WM8731_REG_ACTIVE_CTRL, (iwl_val << 3));
}

void WM8731_set_clock_out(bool divideByTwo) {

  uint8_t buf[2];
  buf[0] = 0x01; 
  buf[1] = 0x01 & divideByTwo;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false);

}













void WM8731_init(i2c_inst_t *i2c, uint baudrate, uint SDA_PIN, uint SCL_PIN) {

    // Initialize the i2c interface
    _i2c_init(i2c, baudrate, SDA_PIN, SCL_PIN);

    // Reset the device
    WM8731_reset();

  uint8_t buf[2];

  // i2cset -y 0 0x1a 0x1e 0x00 i
  buf[0] = 0x1e; 
  buf[1] = 0x00;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false);
  
  //i2cset -y 0 0x1a 0x01 0x80 i
  buf[0] = 0x01; 
  buf[1] = 0x80;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false);

  // i2cset -y 0 0x1a 0x03 0x80 i
  buf[0] = 0x03; 
  buf[1] = 0x80;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false);

  //i2cset -y 0 0x1a 0x05 0xf0 i
  buf[0] = 0x05; 
  buf[1] = 0xf0;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false);

  // i2cset -y 0 0x1a 0x07 0xf0 i
  buf[0] = 0x07; 
  buf[1] = 0xf0;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false);

  //i2cset -y 0 0x1a 0x08 0xd0 i
  buf[0] = 0x08; 
  buf[1] = 0xd0;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false);

  // i2cset -y 0 0x1a 0x0a 0x06 i
  buf[0] = 0x0a; 
  buf[1] = 0x06;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false);

  //i2cset -y 0 0x1a 0x0c 0x00 i
  buf[0] = 0x0c; 
  buf[1] = 0x00;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false);

  //i2cset -y 0 0x1a 0x0e 0x03 i
  buf[0] = 0x0e; 
  buf[1] = 0x03;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false); 

    // i2cset -y 0 0x1a 0x10 0x23 i
  buf[0] = 0x10; 
  buf[1] = 0x23;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false);

    printf("B...");
    // Set the volume
    WM8731_set_headphone_volume(75, 25);
  
    // Enable 16-bit DAC 
    WM8731_configure_DAC(_16_BITS);

    // Activate the interface
    WM8731_activate_interface(true);
}

//--------------------------------------------------------------------------------------------------------------
// init & build
//--------------------------------------------------------------------------------------------------------------




