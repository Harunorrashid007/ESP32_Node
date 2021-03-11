#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "esp_system.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "i2c.h"
#include "bme280.h"

void app_main(void)
{
	printf("BMP280/BME280 Pressure/Humidity/Temperature Sensor Example\r\n");

	i2c_init(I2C_CONTROLLER_0);
	bme280_init(I2C_CONTROLLER_0);

	while (true) {
		printf("Temperature = %.02f degC ", bme280_temp(I2C_CONTROLLER_0));
		printf("Pressure = %.02f hPa\r\n",bme280_pressure(I2C_CONTROLLER_0));
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

