#ifndef _WM8721_DEFS_H
#define _WM8721_DEFS_H

#include <stdio.h>
#include "i2c_handling.h"

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
static inline void WM8731_CMD(char address, unsigned int cmd) {
  char addr;
  // B[15:9] Are Control Address Bits
  // B[8:0]  Are Control Data Bits
  addr = address << 1;                 // Shift left for one positions
  addr = addr | (((char *)&cmd)[1] & 1);

  _i2c_write_blocking(addr, ((char *)&cmd)[0]);
}

static inline void WM8731_send_REG_ACTIVE_CTRL(bool active) {
  WM8731_CMD(WM8731_REG_ACTIVE_CTRL, active ? _WM8731_Activate : _WM8731_Deactivate);
}

static inline void WM8731_send_REG_RESET() {
  WM8731_CMD(WM8731_REG_RESET, 0x0);     
}

#endif // _WM8721_DEFS_H