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

// class Yivo;


// class ArduinoSerial {
//   public:
//   ArduinoSerial(Yivo* y, Stream* s): yivo(y), stream(s) {}

//     // inline Error pack_n_send(uint8_t msgid) {
//     //     // return pack_n_send(msgid, nullptr, 0);
//     //     return pack_n_send(msgid, this->buff, this->payload_size);
//     // }

//     Error pack_n_send(uint8_t msgid, uint8_t *data, uint16_t sz) {
//       Error err = yivo->pack(msgid, data, sz);
//       if (err == Error::NONE) {
//         stream->write(buff, sz + 6); // FIXME: be able to redefine serial
//       }
//       return err;
//     }

//     /*
//     Reads in a packet from a serial connection.

//     Returns: message ID
//     */
//     uint8_t read_packet() {
//       int retry = 16;
//       while (retry-- > 0) {
//         if (stream.available() > 5) {
//           buff[0] = buff[1];
//           buff[1] = stream->read();
//           if ((buff[0] == this->h0) && (buff[1] == this->h1)) {
//             buff[2] = stream->read(); // low byte
//             buff[3] = stream->read(); // high byte
//             uint16_t payload_size = (buff[3] << 8) + buff[2];
//             buff[4] = stream->read(); // msgid
//             stream.readBytes(reinterpret_cast<char*>(&buff[5]), payload_size); // payload
//             buff[5+payload_size] = stream->read(); // checksum
//             return buff[4]; // msgid
//           }
//         }
//         else delay(10);
//       }

//       return 0;
//     }

//     Yivo* yivo;
//     Stream* stream;
// };

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
    int pack(uint8_t msgid, uint8_t *data, uint16_t sz) {
        if (sz+6 > BUFFER_SIZE) {
            // return Error::EXCEED_BUFFER;
            return -1;
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
        // return Error::NONE;
        return sz + 6;
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
    // inline int pack_n_send(uint8_t msgid) {
    //     // return pack_n_send(msgid, nullptr, 0);
    //     return pack_n_send(msgid, this->buff, this->payload_size);
    // }

    int pack_n_send(uint8_t msgid, uint8_t *data, uint16_t sz) {
      int size = pack(msgid, data, sz);
      if (size != -1) {
        Serial.write(buff, size);
      }
      return size;
    }

    /*
    Reads in a packet from a serial connection.

    Returns: message ID or -1 on error
    */
    int read_packet() {
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

      return -1;
    }
#else
    int read_packet() {
        return -1;
    }

    inline int pack_n_send(uint8_t msgid, uint8_t *data=nullptr, uint16_t sz=0) {
        return -1;
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