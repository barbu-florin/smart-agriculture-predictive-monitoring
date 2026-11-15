#ifndef SENSORS_H
#define SENSORS_H

struct TemperatureHumiditySensorData
{
    float temperature;
    float humidity;
    bool valid;
};

struct LightSensorData
{
    int raw;
    float voltage;
    float lux;
};

struct SoilMoistureSensorData
{
    int raw;
    float voltage;
    float percentage;
};

struct SensorData
{
    TemperatureHumiditySensorData temperatureHumidity;
    LightSensorData light;
    SoilMoistureSensorData soil;
};

void initSensors();
SensorData readSensors();

#endif