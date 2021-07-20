#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"

#include "hardware/i2c.h"
#include "pico/binary_info.h"

#include "i2c_handling.h"
#include "wm8731_advanced.h"
#include "wm8731.h"

#define lo(param) ((char *)&param)[0]
#define hi(param) ((char *)&param)[1]

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

void WM8731_send_reset() {
  WM8731_send_REG_RESET();
}

void WM8731_activate_interface(bool active) {
  WM8731_send_REG_ACTIVE_CTRL(active);
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

void WM8731_init(i2c_inst_t *i2c, uint baudrate, uint SDA_PIN, uint SCL_PIN) {

  // Initialize the i2c interface
  _i2c_init(i2c, baudrate, SDA_PIN, SCL_PIN);

  // Reset the device
  WM8731_send_reset();

  // Configure the line in
  LineInConfig lic;
  LineInConfig_init(&lic);

  WM8731_send_REG_LLINE_IN(&lic);
  WM8731_send_REG_RLINE_IN(&lic);
 
  // Set the headphone volumes
  WM8731_set_headphone_volume(25, 60);

  // Configure the analog path
  AnalogPathControl apc;
  AnalogPathControl_init(&apc);
  apc.DACSEL = 1;

  WM8731_send_REG_ANALOG_PATH(&apc);

  // Configure the digital path
  DigitalPathControl dpc;
  DigitalPathControl_init(&dpc);
  dpc.DACMU = 0;

  WM8731_send_REG_DIGITAL_PATH(&dpc);

  // Configure the power-down register
  PowerDownControl pdc;
  PowerDownControl_init(&pdc);
  pdc.DACPD    = 0;
  pdc.OUTPD    = 0;
  pdc.POWEROFF = 0;

  WM8731_send_REG_PDOWN_CTRL(&pdc);

  // Configure the digital audio interface format

  DigitalAudioInterfaceFormat daif;
  DigitalAudioInterfaceFormat_init(&daif);
  daif.IWL = _16_BITS;
  WM8731_send_REG_DIGITAL_IF(&daif);  

  // Configure the sampling control
  SamplingControl sc;
  SamplingControl_init(&sc);
  sc.USB_NORMAL = 1;
  sc.CLKIDIV2   = 1;
  sc.CLKODIV2   = 1;

  WM8731_send_REG_SAMPLING_CTRL(&sc);

  // Activate the interface
  WM8731_activate_interface(true);
}

//--------------------------------------------------------------------------------------------------------------
// Advanced API implementations
//--------------------------------------------------------------------------------------------------------------

/*
 * Converts a normalized volume (0...100) to a volume register value
 */
static unsigned int convertNormalizedVolume(int vol) {
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

void WM8731_send_REG_LLINE_IN(LineInConfig* cfg) {
  WM8731_CMD(WM8731_REG_LLINE_IN, LineInConfig_build(cfg));
}

void WM8731_send_REG_RLINE_IN(LineInConfig* cfg) {
  WM8731_CMD(WM8731_REG_RLINE_IN, LineInConfig_build(cfg));
}

void WM8731_send_REG_LHPHONE_OUT(HeadphoneOutConfig* cfg) {
  WM8731_CMD(WM8731_REG_LHPHONE_OUT, HeadphoneOutConfig_build(cfg));
}

void WM8731_send_REG_RHPHONE_OUT(HeadphoneOutConfig* cfg) {
  WM8731_CMD(WM8731_REG_RHPHONE_OUT, HeadphoneOutConfig_build(cfg));
}

void WM8731_send_REG_ANALOG_PATH(AnalogPathControl* cfg) {
  WM8731_CMD(WM8731_REG_ANALOG_PATH, AnalogPathControl_build(cfg));
}

void WM8731_send_REG_DIGITAL_PATH(DigitalPathControl* cfg) {
  WM8731_CMD(WM8731_REG_DIGITAL_PATH, DigitalPathControl_build(cfg));
}

void WM8731_send_REG_PDOWN_CTRL(PowerDownControl* cfg) {
  WM8731_CMD(WM8731_REG_PDOWN_CTRL, PowerDownControl_build(cfg));
}

void WM8731_send_REG_DIGITAL_IF(DigitalAudioInterfaceFormat* cfg) {
  WM8731_CMD(WM8731_REG_DIGITAL_IF, DigitalAudioInterfaceFormat_build(cfg));
}

void WM8731_send_REG_SAMPLING_CTRL(SamplingControl* cfg) {
  WM8731_CMD(WM8731_REG_SAMPLING_CTRL, SamplingControl_build(cfg));
}

void WM8731_send_REG_ACTIVE_CTRL(bool active) {
  WM8731_CMD(WM8731_REG_ACTIVE_CTRL, active ? _WM8731_Activate : _WM8731_Deactivate);
}

void WM8731_send_REG_RESET() {
  WM8731_CMD(WM8731_REG_RESET, 0x0);     
}

