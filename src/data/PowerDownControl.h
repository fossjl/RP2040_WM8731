#ifndef _WM8721_PowerDownControl_H
#define _WM8721_PowerDownControl_H

struct PowerDownControl_s {
    unsigned LINEINPD   :1; // Line Input Power Down (1 = Power Down, 0 = Powered Up)
    unsigned MICPD      :1; // Microphone Input As Bias Power Down (1 = Power Down, 0 = Powered Up)
    unsigned ADCPD      :1; // ADC Power Down (1 = Power Down, 0 = Powered Up)
    unsigned DACPD      :1; // DAC Power Down (1 = Power Down, 0 = Powered Up)
    unsigned OUTPD      :1; // Outputs Power Down (1 = Power Down, 0 = Powered Up)
    unsigned OSCPD      :1; // Oscillator Power Down (1 = Power Down, 0 = Powered Up)
    unsigned CLKOUTPD   :1; // CLKOUT Power Down  (1 = Power Down, 0 = Powered Up)
    unsigned POWEROFF   :1; // POWEROFF mode (1 = Power Down, 0 = Powered Up)
};

typedef struct PowerDownControl_s PowerDownControl;

void PowerDownControl_init(PowerDownControl *config);

unsigned int PowerDownControl_build(PowerDownControl *config);

#endif // PowerDownControl
