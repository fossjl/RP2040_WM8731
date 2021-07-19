#ifndef _WM8721_H
#define _WM8721_H

void WM8731_reset();
void WM8731_activate_interface(bool active);

void WM8731_configure_DAC(int iwl);
void WM8731_set_clock_out(bool divideByTwo);
void WM8731_set_volume(float leftVolume, float rightVolume);

void WM8731_init();

#endif //_WM8721_H