#pragma once

struct ImuA_t {
    float ax, ay, az;
    // float temperature;
    long timestamp;
};

struct ImuAGT_t {
    float ax, ay, az;
    float gx, gy, gz;
    float temperature;
    long timestamp;
};

struct ImuAGMT_t {
    float ax, ay, az;
    float gx, gy, gz;
    float mx, my, mz;
    float temperature;
    long timestamp;
};

struct ImuAGMQPT_t {
    float ax, ay, az;
    float gx, gy, gz;
    float imu_temp;
    float mx, my, mz;
    float qw,qx,qy,qz;
    float pressure;
    float temperature;
    long timestamp;
};


struct ImuAGMQT_t {
    float ax, ay, az;
    float gx, gy, gz;
    float mx, my, mz;
    float qw,qx,qy,qz;
    float temperature;
    long timestamp;
};

struct PressureTemperature {
    float pressure, temperature;
};

struct Motors4_t {
    uint16_t m0, m1, m2, m3, armed;
};
struct Motors6_t {
    uint16_t m0, m1, m2, m3, m4, m5, armed;
};