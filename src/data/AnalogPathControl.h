#ifndef _WM8721_AnalogPathControl_H
#define _WM8721_AnalogPathControl_H

enum SideToneAttenuation {
  NEG_6_DB = 0,  // 00
  NEG_9_DB = 1,  // 01
  NEG_12_DB = 2, // 10
  NEG_15_DB = 3  // 11
};

struct AnalogPathControl_s {
    unsigned MICBOOST   :1; // Microphone input level boost
    unsigned MUTEMIC    :1; // Mic Input Mute to ADC
    unsigned INSEL      :1; // Microphone/Line Input Select to ADC
    unsigned BYPASS     :1; // Bypass switch
    unsigned DACSEL     :1; // DAC Select
    unsigned SIDETONE   :1; // Side Tone Switch
    unsigned SIDEATT    :2; // Side Tone Attenuation
};

typedef struct AnalogPathControl_s AnalogPathControl;

void AnalogPathControl_init(AnalogPathControl *config);

unsigned int AnalogPathControl_build(AnalogPathControl *config);

#endif // AnalogPathControl
