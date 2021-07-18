#ifndef _WM8721_H
#define _WM8721_H

#include "i2c_handling.h"

enum InputWorldLength {
  _16_BITS = 0, // 00
  _20_BITS = 1, // 01
  _24_BITS = 2, // 10
  _32_BITS = 3  // 11
};

void WM8731_reset();
void WM8731_activate_interface(bool active);

void WM8731_configure_DAC(int iwl);
void WM8731_set_clock_out(bool divideByTwo);
void WM8731_set_volume(float leftVolume, float rightVolume);





void WM8731_init();


#endif //_WM8721_H