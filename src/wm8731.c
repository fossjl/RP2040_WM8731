#include "wm8731.h"

#include "api/wm8731_api.h"
#include "api/AnalogPathControl.h"
#include "api/DigitalAudioInterfaceFormat.h"
#include "api/DigitalPathControl.h"
#include "api/HeadphoneOutConfig.h"
#include "api/LineInConfig.h"
#include "api/PowerDownControl.h"
#include "api/SamplingControl.h"

//--------------------------------------------------------------------------------------------------------
// Standard initialization functions
//--------------------------------------------------------------------------------------------------------

void WM8731_init_playback(i2c_inst_t *i2c, uint baudrate, uint SDA_PIN, uint SCL_PIN, uint volumeOut, uint IWL) {

  // Initialize the i2c interface
  _i2c_init(i2c, baudrate, SDA_PIN, SCL_PIN);

  // Reset the device
  WM8731_send_REG_RESET();

  // Configure the line in
  LineInConfig lic;
  LineInConfig_init(&lic);

  LineInConfig_send_left(&lic);
  LineInConfig_send_right(&lic);
 
  // Set the headphone volumes
  WM8731_set_headphone_volume(volumeOut, volumeOut);

  // Configure the analog path
  AnalogPathControl apc;
  AnalogPathControl_init(&apc);
  apc.DACSEL = 1;

  AnalogPathControl_send(&apc);

  // Configure the digital path
  DigitalPathControl dpc;
  DigitalPathControl_init(&dpc);
  dpc.DACMU = 0;

  DigitalPathControl_send(&dpc);

  // Configure the power-down register
  PowerDownControl pdc;
  PowerDownControl_init(&pdc);
  pdc.DACPD    = 0;
  pdc.OUTPD    = 0;
  pdc.POWEROFF = 0;

  PowerDownControl_send(&pdc);

  // Configure the digital audio interface format

  DigitalAudioInterfaceFormat daif;
  DigitalAudioInterfaceFormat_init(&daif);
  daif.IWL = IWL;
  DigitalAudioInterfaceFormat_send(&daif);  

  // Configure the sampling control
  SamplingControl sc;
  SamplingControl_init(&sc);
  sc.USB_NORMAL = 1;
  sc.CLKIDIV2   = 1;
  sc.CLKODIV2   = 1;

  SamplingControl_send(&sc);

  // Activate the interface
  WM8731_send_REG_ACTIVE_CTRL(true);
}

//--------------------------------------------------------------------------------------------------------
// Operations
//--------------------------------------------------------------------------------------------------------

/*
 * Sets the normalized volume (0...100) on the two headphone channels
 */
void WM8731_set_headphone_volume(uint leftVolume, uint rightVolume) {

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
  WM8731_send_REG_RESET();
}
