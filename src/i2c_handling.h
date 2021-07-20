/*
 * This file is where the low-level i2c handling code is contained.
 *
 * If you're wanting to port this library to another micro-controller, this
 * should be the only file you need to change
 */

#ifndef _I2C_HANDLING_H
#define _I2C_HANDLING_H

static const char WM8731_ADDRESS = 0x1a;       // WM8731 chip address on I2C bus

static uint8_t _i2c_cmd_buff[2];

static inline int _i2c_write_blocking(const uint8_t a, const uint8_t b) {
  _i2c_cmd_buff[0] = a; 
  _i2c_cmd_buff[1] = b;

  return i2c_write_blocking(i2c_default, WM8731_ADDRESS, _i2c_cmd_buff, 2, false);
}

static int _i2c_init(i2c_inst_t *i2c, uint baudrate, uint SDA_PIN, uint SCL_PIN) {
  
  i2c_init(i2c_default, 100 * 1000);
  gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
  gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

}

#endif // _I2C_HANDLING_H