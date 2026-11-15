#include <Arduino.h>
#include <DHT.h>
#include "sensors.h"

#define DHT_TYPE DHT22
#define DHT_PIN 4

#define SOIL_MOISTURE_PIN 34
#define TEMT6000_PIN 35

DHT dht(DHT_PIN, DHT_TYPE);

constexpr float VCC = 3.3f;
constexpr int ADC_RESOLUTION = 4095;

constexpr float R_OHMS = 10000.0f;
constexpr float UA_PER_LUX = 0.5f;

constexpr int SOIL_DRY = 4095;
constexpr int SOIL_WET = 1300;

void initSensors()
{
    dht.begin();

    analogReadResolution(12);

    analogSetPinAttenuation(TEMT6000_PIN, ADC_11db);
    analogSetPinAttenuation(SOIL_MOISTURE_PIN, ADC_11db);

    delay(2000);
}

TemperatureHumiditySensorData readTemperatureHumiditySensorData()
{
    TemperatureHumiditySensorData data{};

    data.temperature = dht.readTemperature();
    data.humidity = dht.readHumidity();
    data.valid = !isnan(data.temperature) && !isnan(data.humidity);

    return data;
}

LightSensorData readLightSensorData()
{
    LightSensorData data{};

    data.raw = analogRead(TEMT6000_PIN);
    data.voltage = (float)data.raw / ADC_RESOLUTION * VCC;
    data.lux = ((data.voltage / R_OHMS) * 1e6f) / UA_PER_LUX;

    return data;
}

SoilMoistureSensorData readSoilMoistureSensorData()
{
    SoilMoistureSensorData data{};

    data.raw = analogRead(SOIL_MOISTURE_PIN);
    data.voltage = (float)data.raw / ADC_RESOLUTION * VCC;
    data.percentage = 100.0f * (data.raw - SOIL_DRY) / (SOIL_WET - SOIL_DRY);
    data.percentage = constrain(data.percentage, 0.0f, 100.0f);

    return data;
}

SensorData readSensors()
{
    SensorData data{};

    data.temperatureHumidity = readTemperatureHumiditySensorData();
    data.light = readLightSensorData();
    data.soil = readSoilMoistureSensorData();

    return data;
}