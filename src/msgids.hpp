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