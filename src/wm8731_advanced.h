#ifndef _WM8721_ADVANCED_H
#define _WM8721_ADVANCED_H

enum InputWorldLength {
  _16_BITS = 0, // 00
  _20_BITS = 1, // 01
  _24_BITS = 2, // 10
  _32_BITS = 3  // 11
};

enum SideToneAttenuation {
  NEG_6_DB = 0,  // 00
  NEG_9_DB = 1,  // 01
  NEG_12_DB = 2, // 10
  NEG_15_DB = 3  // 11
};

//--------------------------------------------------------------------------------------------------------------
// AnalogPathControl
//--------------------------------------------------------------------------------------------------------------


struct AnalogPathControl_s {
    unsigned MICBOOST   :1; // Microphone input level boost
    unsigned MUTEMIC    :1; // Mic Input Mute to ADC
    unsigned INSEL      :1; // Microphone/Line Input Select to ADC
    unsigned BYPASS     :1; // Bypass switch
    unsigned DACSEL     :1; // DAC Select
    unsigned SIDETONE   :1; // Side Tone Switch
    unsigned SIDEATT    :2; // Side Tone Attenuation
};

#define AnalogPathControl_default {0, 1, 0, 1, 0, 0, 0x00};

typedef struct AnalogPathControl_s AnalogPathControl;

//--------------------------------------------------------------------------------------------------------------
// DigitalPathControl
//--------------------------------------------------------------------------------------------------------------


struct DigitalPathControl_s {
    unsigned ADCHPD     :1; // ADC High Pass Filter Enable
    unsigned DEEMP      :2; // De-emphasis Control
    unsigned DACMU      :1; // DAC Soft Mute Control
    unsigned HPOR       :1; // Store DC offset when High Pass filter disabled
};

#define DigitalPathControl_default {0, 0x00, 1, 0};

typedef struct DigitalPathControl_s DigitalPathControl;

//--------------------------------------------------------------------------------------------------------------
// PowerDownControl
//--------------------------------------------------------------------------------------------------------------


struct PowerDownControl_s {
    unsigned LINEINPD   :1; // Line Input Power Down
    unsigned MICPD      :1; // Microphone Input As Bias Power Down
    unsigned ADCPD      :1; // ADC Power Down
    unsigned DACPD      :1; // DAC Power Down
    unsigned OUTPD      :1; // Outputs Power Down
    unsigned OSCPD      :1; // Oscillator Power Down
    unsigned CLKOUTPD   :1; // CLKOUT Power Down
    unsigned POWEROFF   :1; // POWEROFF mode
};

#define  PowerDownControl_default {1, 1, 1, 1, 1, 0, 0, 1};

typedef struct PowerDownControl_s PowerDownControl;

//--------------------------------------------------------------------------------------------------------------
// DigitalAudioInterfaceFormat
//--------------------------------------------------------------------------------------------------------------


struct DigitalAudioInterfaceFormat_s {
    unsigned FORMAT     :2; // Audio Data Format Select
    unsigned IWL        :2; // Input Audio Data Bit Length Select
    unsigned LRP        :1; // DACLRC phase control
    unsigned LRSWAP     :1; // DAC Left Right Clock Swap
    unsigned MS         :1; // Master Slave Mode Control
    unsigned BCLKINV    :1; // Bit Clock Invert
};

#define  DigitalAudioInterfaceFormat_default {0x2, 0x2, 0, 0, 0, 0};

typedef struct DigitalAudioInterfaceFormat_s DigitalAudioInterfaceFormat;

//--------------------------------------------------------------------------------------------------------------
// SamplingControl
//--------------------------------------------------------------------------------------------------------------


struct SamplingControl_s {
    unsigned USB_NORMAL :2; // Mode Select
    unsigned BOSR       :2; // Base Over-Sampling Rate 
    unsigned SR         :1; // ADC and DAC Sample rate control
    unsigned CLKDIV2    :1; // Core Clock divider Select
    unsigned CLKODIV2   :1; // CLKOUT divider select
};

#define  SamplingControl_default {0, 0, 0x0, 0, 0};

typedef struct SamplingControl_s SamplingControl;


//--------------------------------------------------------------------------------------------------------------
// LineInConfig
//--------------------------------------------------------------------------------------------------------------


unsigned int convertNormalizedVolume(int vol);

#endif // _WM8721_ADVANCED_H