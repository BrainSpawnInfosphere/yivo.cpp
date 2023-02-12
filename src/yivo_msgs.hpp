/******************************************************************************
MIT License

Copyright (c) 2020 Mom's Friendly Robot Company

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/
#pragma once
#include <stdint.h>

// Message IDs                 Payload B
constexpr uint8_t PING      = 10; // 0B
constexpr uint8_t HEARTBEAT = 11;

constexpr uint8_t IMU_AGMQPT= 139; // 68B
constexpr uint8_t IMU_AGMQT = 140; // 56B
constexpr uint8_t IMU_AGMT  = 141;
constexpr uint8_t IMU_AGT   = 142;
constexpr uint8_t IMU_AT    = 143;
constexpr uint8_t MAGNETIC  = 144;
constexpr uint8_t RANGE     = 145;
constexpr uint8_t GPS       = 146;
constexpr uint8_t PRES_TEMP = 147;
constexpr uint8_t VOLTAGE   = 148;

constexpr uint8_t MOTORS    = 200;

constexpr uint8_t SET_MOTORS    = 201;
constexpr uint8_t SET_ACCEL_CAL = 202;
constexpr uint8_t SET_GYRO_CAL  = 203;
constexpr uint8_t SET_MAG_CAL   = 204;
constexpr uint8_t SET_TEL_STREAM= 205;

constexpr uint8_t YIVO_ERROR= 250;

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

struct Distance_t {
  enum Distance_Sensor: uint8_t {
    LASER=1,
    ULTRASOUND=2,
    INFRARED=4,
    RADAR=8,
    LIDAR=16,
    UNKNOWN=32
  };
  uint16_t min_distance; // cm
  uint16_t max_distance; // cm
  uint16_t distance; // cm
  uint8_t type;
  uint8_t id;
  uint32_t timestamp;
};

// struct Axis_t {
//   float x,y,z;
// };
// union Axis_t {
//   float v[3];
//   uint8_t b[12]; // 4b * 3
//   struct {
//     float x,y,z;
//   };
// };

struct Axis_t {
  union {
    float v[3];
    uint8_t b[12]; // 4b * 3
    struct {
      float x,y,z;
    };
  };
};

struct Heartbeat_t {
  enum Sensors: uint16_t {
    AUTOPILOT = 1,
    ACCEL = 2,
    GYRO = 4,
    BAROMETER = 8,
    TEMPERATURE = 16,
    RANGE = 32,
    GPS = 64,
    BATTERY = 128,
    CAMERA = 256,
    VIDEODOMETRY = 1024,
    COMPASS = 2048
  };
  uint8_t id;
  uint8_t has_autopilot;
  uint16_t sensors;
  uint32_t timestamp;
};