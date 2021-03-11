#include <stdio.h>
#include <string.h>
#include "esp_event.h"
#include "i2c.h"
#include "ina226.h"

void ina226_init(uint8_t i2c_master_port)
{
	i2c_write_short(i2c_master_port, INA226_SLAVE_ADDRESS, INA226_CFG_REG, 0x8000);	// Reset
	i2c_write_short(i2c_master_port, INA226_SLAVE_ADDRESS, INA226_CFG_REG, 0x4527);	// Average over 16 Samples
	i2c_write_short(i2c_master_port, INA226_SLAVE_ADDRESS, INA226_CAL_REG, 1024);		// 1A, 0.100Ohm Resistor

	printf("Manufacturer ID:        0x%04X\r\n",i2c_read_short(i2c_master_port, INA226_SLAVE_ADDRESS, INA226_MANUFACTURER_ID));
	printf("Die ID Register:        0x%04X\r\n",i2c_read_short(i2c_master_port, INA226_SLAVE_ADDRESS, INA226_DIE_ID));
	printf("Configuration Register: 0x%04X\r\n",i2c_read_short(i2c_master_port, INA226_SLAVE_ADDRESS, INA226_CFG_REG));
}

float ina226_voltage(uint8_t i2c_master_port)
{
	unsigned int iBusVoltage;
	float fBusVoltage;

	iBusVoltage = i2c_read_short(i2c_master_port, INA226_SLAVE_ADDRESS, INA226_BUS_VOLT_REG);
	fBusVoltage = (iBusVoltage) * 0.00125;
	//printf("Bus Voltage = %.2fV, ", fBusVoltage);

	return (fBusVoltage);
}

float ina226_current(uint8_t i2c_master_port)
{
	unsigned int iCurrent;
	float fCurrent;

	iCurrent = i2c_read_short(i2c_master_port, INA226_SLAVE_ADDRESS, INA226_CURRENT_REG);
	// Internally Calculated as Current = ((ShuntVoltage * CalibrationRegister) / 2048)
	fCurrent = iCurrent * 0.0005;
	//printf("Current = %.3fA\r\n", fCurrent);

	return (fCurrent);
}

float ina226_power(uint8_t i2c_master_port)
{
	unsigned int iPower;
	float fPower;

	iPower = i2c_read_short(i2c_master_port, INA226_SLAVE_ADDRESS, INA226_POWER_REG);
	// The Power Register LSB is internally programmed to equal 25 times the programmed value of the Current_LSB
	fPower = iPower * 0.0125;

	//printf("Power = %.2fW\r\n", fPower);
	return (fPower);
}

