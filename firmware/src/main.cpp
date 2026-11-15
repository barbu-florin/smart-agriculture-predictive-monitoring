#include <Arduino.h>
#include "sensors.h"

void setup()
{
    Serial.begin(115200);
    initSensors();
}

void loop()
{
    SensorData data = readSensors();

    if (data.temperatureHumidity.valid)
    {
        Serial.printf(
            "Temperature: %.2f °C | Humidity: %.2f %%\n",
            data.temperatureHumidity.temperature,
            data.temperatureHumidity.humidity);
    }

    Serial.printf(
        "Light: %d ADC | %.3f V | %.1f lux\n",
        data.light.raw,
        data.light.voltage,
        data.light.lux);

    Serial.printf(
        "Soil: %d ADC | %.3f V | %.1f %%\n",
        data.soil.raw,
        data.soil.voltage,
        data.soil.percentage);

    delay(2000);
}