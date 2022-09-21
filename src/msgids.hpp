#pragma once

// Message IDs                 Payload B
constexpr int PING      = 10; // 0B

constexpr int IMU_AGMQPT= 139; // 68B
constexpr int IMU_AGMQT = 140; // 56B
constexpr int IMU_AGMT  = 141;
constexpr int IMU_AGT   = 142;
constexpr int IMU_AT    = 143;
constexpr int MAGNETIC  = 144;
constexpr int RANGE     = 145;
constexpr int GPS       = 146;
constexpr int PRES_TEMP = 147;
constexpr int VOLTAGE   = 148;

constexpr int MOTORS    = 200;
constexpr int SET_MOTORS= 201;
constexpr int SET_ACCEL_CAL = 202;
constexpr int SET_GYRO_CAL  = 203;
constexpr int SET_MAG_CAL   = 204;
constexpr int SET_TEL_STREAM= 205;

constexpr int YIVO_ERROR= 250;