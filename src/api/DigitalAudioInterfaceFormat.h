#ifndef _WM8721_DigitalAudioInterfaceFormat_H
#define _WM8721_DigitalAudioInterfaceFormat_H

#include "wm8731_api.h"

enum AudioDataFormat {
  MSB_FIRST_RIGHT_JUSTIFIED = 0, // 00
  MSB_FIRST_LEFT_JUSTIFIED  = 1, // 01
  I2S                       = 2, // 10
  DSP_MODE                  = 3  // 11
};

enum InputWorldLength {
  _16_BITS = 0, // 00
  _20_BITS = 1, // 01
  _24_BITS = 2, // 10
  _32_BITS = 3  // 11
};

struct DigitalAudioInterfaceFormat_s {
    unsigned FORMAT     :2; // Audio Data Format Select
    unsigned IWL        :2; // Input Audio Data Bit Length Select
    unsigned LRP        :1; // DACLRC phase control
    unsigned LRSWAP     :1; // DAC Left Right Clock Swap
    unsigned MS         :1; // Master Slave Mode Control
    unsigned BCLKINV    :1; // Bit Clock Invert
};

typedef struct DigitalAudioInterfaceFormat_s DigitalAudioInterfaceFormat;

void DigitalAudioInterfaceFormat_init(DigitalAudioInterfaceFormat *config);

unsigned int DigitalAudioInterfaceFormat_build(DigitalAudioInterfaceFormat *config);

static inline void DigitalAudioInterfaceFormat_send(DigitalAudioInterfaceFormat* cfg) {
  WM8731_CMD(WM8731_REG_DIGITAL_IF, DigitalAudioInterfaceFormat_build(cfg));
}

#endif // DigitalAudioInterfaceFormat
