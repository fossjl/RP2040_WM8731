#ifndef _WM8721_DigitalPathControl_H
#define _WM8721_DigitalPathControl_H

enum DeemphasisControl {
  DISABLE  = 0,  // 00
  _32000Hz  = 1, // 01
  _44100Hz = 2,  // 10
  _48000Hz = 3   // 11
};

struct DigitalPathControl_s {
    unsigned ADCHPD     :1; // ADC High Pass Filter Enable
    unsigned DEEMP      :2; // De-emphasis Control
    unsigned DACMU      :1; // DAC Soft Mute Control
    unsigned HPOR       :1; // Store DC offset when High Pass filter disabled
};

typedef struct DigitalPathControl_s DigitalPathControl;

void DigitalPathControl_init(DigitalPathControl *config);

unsigned int DigitalPathControl_build(DigitalPathControl *config);

#endif // DigitalPathControl
