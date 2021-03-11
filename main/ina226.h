
#ifndef MAIN_INA226_H_
#define MAIN_INA226_H_

#define INA226_SLAVE_ADDRESS	0x40
#define INA226_CFG_REG		0x00
#define INA226_SHUNT_VOLT_REG	0x01
#define INA226_BUS_VOLT_REG	0x02
#define INA226_POWER_REG	0x03
#define INA226_CURRENT_REG	0x04
#define INA226_CAL_REG		0x05
#define INA226_MASKEN_REG	0x06
#define INA226_ALERT_LMT_REG	0x07
#define INA226_MANUFACTURER_ID	0xFE
#define INA226_DIE_ID		0xFF

void ina226_init(uint8_t i2c_master_port);
float ina226_voltage(uint8_t i2c_master_port);
float ina226_current(uint8_t i2c_master_port);
float ina226_power(uint8_t i2c_master_port);

#endif
