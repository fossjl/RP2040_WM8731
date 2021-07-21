#ifndef _WM8721_H
#define _WM8721_H

#include <stdio.h>
#include "i2c_handling.h"
#include "api/DigitalAudioInterfaceFormat.h"

//--------------------------------------------------------------------------------------------------------
// Standard initialization functions
//--------------------------------------------------------------------------------------------------------

void WM8731_init_playback(i2c_inst_t *i2c, uint baudrate, uint SDA_PIN, uint SCL_PIN, uint volumeOut, uint IWL);

//--------------------------------------------------------------------------------------------------------
// Operations
//--------------------------------------------------------------------------------------------------------

void WM8731_set_headphone_volume(uint leftVolume, uint rightVolume);

void WM8731_reset();

#endif //_WM8721_H