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

#include <cstdint>
#include <cstring>
#include "messages.hpp"
#include "msgids.hpp"

// constexpr int BUFFER_SIZE = 256;

// // Message IDs
// constexpr int PING      = 10;

// constexpr int IMU_AGMQT = 140;
// constexpr int IMU_AGMT  = 141;
// constexpr int IMU_AGT   = 142;
// constexpr int IMU_AT    = 143;
// constexpr int MAGNETIC  = 144;
// constexpr int RANGE     = 145;
// constexpr int GPS       = 146;
// constexpr int PRES_TEMP = 147;
// constexpr int VOLTAGE   = 148;

// constexpr int MOTORS    = 200;
// constexpr int SET_MOTORS= 201;
// constexpr int SET_ACCEL_CAL = 202;
// constexpr int SET_GYRO_CAL  = 203;
// constexpr int SET_MAG_CAL   = 204;
// constexpr int SET_TEL_STREAM= 205;

// constexpr int YIVO_ERROR= 250;

union int_t {
  uint16_t b16;
  uint8_t b8[2];
};

enum Error {
    NONE = 0,
    INVALID_HEADER   = 1,
    INVALID_LENGTH   = 2,
    INVALID_CHECKSUM = 4,
    INVALID_COMMAND  = 8,
    INVALID_MSGID    = 16,
    EXCEED_BUFFER    = 32
};


uint8_t checksum(uint16_t payload_size, uint8_t msgid, uint8_t *data);

// template<uint32_t size>
// struct Buffer {
//   union {
//     float    f[size];   // float
//     uint32_t l[size];   // long
//     uint16_t s[size*2]; // short
//     uint8_t  b[size*4]; // byte
//   };

//   void clear() {
//     memset(b, 0, size);
//   }
// };

// template<typename T, uint32_t size>
template<uint16_t BUFFER_SIZE>
class Yivo {
    public:
    Yivo(char a='$', char b='K'): h0(a), h1(b) {}
    ~Yivo() {}

    /*
    msgid: message ID (0-255)
    data: buffer containing data to be sent
    sz: size of data to be sent, sz < (BUFFER_SIZE - 6)
    */
    Error pack(uint8_t msgid, uint8_t *data, uint16_t sz) {
        if (sz+6 > BUFFER_SIZE) {
            return Error::EXCEED_BUFFER;
        }

        memset(this->buff, 0, BUFFER_SIZE);
        this->buff[0] = h0;
        this->buff[1] = h1;
        this->buff[2] = uint8_t(sz & 0xFF); // low byte
        this->buff[3] = uint8_t(sz >> 8); // high byte
        this->buff[4] = msgid;

        uint8_t cs;
        if (sz > 0) {
            memcpy(&this->buff[5], data, sz);
            cs = checksum(sz, msgid, data);
        }
        else {
            cs = msgid;
        }
        this->buff[5+sz] = cs; // off by 1?

        this->payload_size = sz;
        return Error::NONE;
    }

    template<typename T>
    T unpack(uint8_t *payload, uint16_t payload_size) {
        T val;
        memcpy(&val, payload, payload_size);
        return val;
    }

    template<typename T>
    T unpack() {
        T val;
        memcpy(&val, this->get_payload_buffer(), this->get_payload_size());
        return val;
    }

#ifdef Arduino_h
    inline Error pack_n_send(uint8_t msgid) {
        // return pack_n_send(msgid, nullptr, 0);
        return pack_n_send(msgid, this->buff, this->payload_size);
    }

    Error pack_n_send(uint8_t msgid, uint8_t *data, uint16_t sz) {
      Error err = pack(msgid, data, sz);
      if (err == Error::NONE) {
        Serial.write(buff, sz + 6);
      }
      return err;
    }

    /*
    Reads in a packet from a serial connection.

    Returns: message ID
    */
    uint8_t read_packet() {
      int retry = 16;
      while (retry-- > 0) {
        if (Serial.available() > 5) {
          buff[0] = buff[1];
          buff[1] = Serial.read();
          if ((buff[0] == this->h0) && (buff[1] == this->h1)) {
            buff[2] = Serial.read(); // low byte
            buff[3] = Serial.read(); // high byte
            uint16_t payload_size = (buff[3] << 8) + buff[2];
            buff[4] = Serial.read(); // msgid
            Serial.readBytes(reinterpret_cast<char*>(&buff[5]), payload_size); // payload
            buff[5+payload_size] = Serial.read(); // checksum
            return buff[4]; // msgid
          }
        }
        else delay(100);
      }

      return 0;
    }
#else
    uint8_t read_packet() {
        return 0;
    }

    inline Error pack_n_send(uint8_t msgid, uint8_t *data=nullptr, uint16_t sz=0) {
        return Error::NONE;
    }
#endif

    inline uint8_t* get_buffer() {
        return this->buff;
    }

    inline uint8_t* get_payload_buffer() {
        return &this->buff[5];
    }

    inline uint16_t get_total_size() const {
        return this->payload_size + 6;
    }

    inline uint16_t get_payload_size() const {
        return this->payload_size;
    }

    protected:
    uint8_t buff[BUFFER_SIZE];
    uint16_t payload_size; // payload size, doesn't count header/cs (+6B more)
    char h0, h1; // header bytes
};