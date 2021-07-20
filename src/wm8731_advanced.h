#ifndef _WM8721_ADVANCED_H
#define _WM8721_ADVANCED_H

#include "data/AnalogPathControl.h"
#include "data/DigitalAudioInterfaceFormat.h"
#include "data/DigitalPathControl.h"
#include "data/HeadphoneOutConfig.h"
#include "data/LineInConfig.h"
#include "data/PowerDownControl.h"
#include "data/SamplingControl.h"

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

static void WM8731_CMD(char address, unsigned int cmd);
static unsigned int convertNormalizedVolume(int vol);

void WM8731_send_REG_LLINE_IN(LineInConfig* cfg);
void WM8731_send_REG_RLINE_IN(LineInConfig* cfg);
void WM8731_send_REG_LHPHONE_OUT(HeadphoneOutConfig* cfg);
void WM8731_send_REG_RHPHONE_OUT(HeadphoneOutConfig* cfg);
void WM8731_send_REG_ANALOG_PATH(AnalogPathControl* cfg);
void WM8731_send_REG_DIGITAL_PATH(DigitalPathControl* cfg);
void WM8731_send_REG_PDOWN_CTRL(PowerDownControl* cfg);
void WM8731_send_REG_DIGITAL_IF(DigitalAudioInterfaceFormat* cfg);
void WM8731_send_REG_SAMPLING_CTRL(SamplingControl* cfg);
void WM8731_send_REG_ACTIVE_CTRL(bool active);
void WM8731_send_REG_RESET();

#endif // _WM8721_ADVANCED_H
