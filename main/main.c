#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "i2c.h"
#include "bme280.h"
#include "ina226.h"

void app_main(void)
{
	printf("BMP280/BME280 Pressure/Humidity/Temperature Sensor Example\r\n");

	i2c_init(I2C_CONTROLLER_0, 25, 26);
	bme280_init(I2C_CONTROLLER_0);

	i2c_init(I2C_CONTROLLER_1, 22, 23);
	ina226_init(I2C_CONTROLLER_1);

	while (true) {
		printf("Temperature = %.02f degC, ", bme280_temp(I2C_CONTROLLER_0));
		printf("Pressure = %.02f hPa, ",bme280_pressure(I2C_CONTROLLER_0));

		printf("Voltage = %.02f V, ", ina226_voltage(I2C_CONTROLLER_1));
		printf("Current = %.02f A, ", ina226_current(I2C_CONTROLLER_1));
		printf("Power = %.02f W\r\n", ina226_power(I2C_CONTROLLER_1));

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

