#ifndef _WM8721_H
#define _WM8721_H

#include "hardware/i2c.h"
#include "pico/binary_info.h"

#define lo(param) ((char *)&param)[0]
#define hi(param) ((char *)&param)[1]

/**************************************************************************************************
* WM8731 sound chip register addresses
**************************************************************************************************/
const char WM8731_ADDRESS             = 0x1a;       // WM8731 chip address on I2C bus
const char WM8731_REG_LLINE_IN        = 0x00;       // Left Channel Line Input Volume Control
const char WM8731_REG_RLINE_IN        = 0x01;       // Right Channel Line Input Volume Control
const char WM8731_REG_LHPHONE_OUT     = 0x02;       // Left Channel Headphone Output Volume Control
const char WM8731_REG_RHPHONE_OUT     = 0x03;       // Right Channel Headphone Output Volume Control
const char WM8731_REG_ANALOG_PATH     = 0x04;       // Analog Audio Path Control
const char WM8731_REG_DIGITAL_PATH    = 0x05;       // Digital Audio Path Control
const char WM8731_REG_PDOWN_CTRL      = 0x06;       // Power Down Control Register
const char WM8731_REG_DIGITAL_IF      = 0x07;       // Digital Audio Interface Format
const char WM8731_REG_SAMPLING_CTRL   = 0x08;       // Sampling Control Register
const char WM8731_REG_ACTIVE_CTRL     = 0x09;       // Active Control
const char WM8731_REG_RESET           = 0x0F;       // Reset register

/**************************************************************************************************
* WM8731 sound chip constants (for default set up)
**************************************************************************************************/
const u_int32_t _WM8731_left_lineIn        = 0x0180;     // Mic settings: Enable mute, Enable simultaneous load to left and right channels
const u_int32_t _WM8731_Right_lineIn       = 0x0180;     // Mic settings: Enable mute, Enable simultaneous load to left and right channels
const u_int32_t _WM8731_Left_hp            = 0x00F0;     // Headphone settings : -9dB output
const u_int32_t _WM8731_Right_hp           = 0x00F0;     // Headphone settings : -9dB output
const u_int32_t _WM8731_AnalogAudio        = 0xD0;       // DAC Select
const u_int32_t _WM8731_DigitalAudio       = 0x06;
const u_int32_t _WM8731_power              = 0x00;       // Disable Power down
const u_int32_t _WM8731_DAIF               = 0x43;       // Enable Master Mode and 32bit data
const u_int32_t _WM8731_Sampling           = 0x23;       // 44100Hz
const u_int32_t _WM8731_Activate           = 0x01;       // Module is ON
const u_int32_t _WM8731_Deactivate         = 0x00;       // Module is OFF
const u_int32_t _WM8731_Reset              = 0x00;       // Reset value


/**************************************************************************************************
* Function WM8731_CMD
* -------------------------------------------------------------------------------------------------
* Overview: Function write word of data to WM8731
* Input: register address, data
* Output: Nothing
**************************************************************************************************/
void WM8731_CMD(char address, unsigned int cmd){
  char addr;
  // B[15:9] Are Control Address Bits
  // B[8:0]  Are Control Data Bits
  addr = address << 1;                 // Shift left for one positions
  addr = addr | (hi(cmd) & 1);

  uint8_t buf[2];
  buf[0] = addr; 
  buf[1] = lo(cmd);

  printf("CMD: %x %x\n", 0xff & buf[0], 0xff & buf[1]);

  i2c_write_blocking(i2c_default, WM8731_ADDRESS, buf, 2, false);
}

void WM8731_SetVolume(float leftVolume, float rightVolume){
unsigned int temp;

  if (leftVolume <= 0) {
    temp = 0x0000;
  }
  else if (leftVolume > 1) {
    temp = 80 + 0xAF;
  }
  else {
    temp = (int)(80 * leftVolume) + 0x00AF;
  }
  WM8731_CMD(WM8731_REG_LHPHONE_OUT, temp);      //left headphone out

  if (rightVolume <= 0) {
    temp = 0x0000;
  }
  else if (rightVolume > 1) {
    temp = 80 + 0xAF;
  }
  else {
    temp = (int)(80 * rightVolume) + 0x00AF;
  }
  WM8731_CMD(WM8731_REG_RHPHONE_OUT, temp);      //left headphone out
}

static inline void resetDevice() {

  uint8_t buf[2];
  buf[0] = 0x12; 
  buf[1] = 0x00;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false);

}

static inline void activateInterface(bool active) {
  WM8731_CMD(WM8731_REG_ACTIVE_CTRL, active ? _WM8731_Activate : _WM8731_Deactivate);
}

enum InputWorldLength {
  _16_BITS = 0, // 00
  _20_BITS = 1, // 01
  _24_BITS = 2, // 10
  _32_BITS = 3  // 11
};

static inline void configureDAC(int iwl) {
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

static inline void init_wm8731() {

    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

  resetDevice();

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

  WM8731_SetVolume(0.75, 0.25);
  
  configureDAC(_16_BITS);

  activateInterface(true);



}

static inline void setClockOut(bool divideByTwo) {

  uint8_t buf[2];
  buf[0] = 0x01; 
  buf[1] = 0x01 & divideByTwo;
  i2c_write_blocking(i2c_default, 0x1a, buf, 2, false);

}

#endif //_WM8721_H