#include "yivo.hpp"


uint8_t checksum(uint16_t size, uint8_t msgid, uint8_t *data){
    uint8_t cs = 0;
    // uint8_t hb = uint8_t(size >> 8);
    // uint8_t lb = uint8_t(size & 0xFFFF);
    // cs = lb ^ hb;
    int_t v;
    v.b16 = size;
    cs = v.b8[0] ^ v.b8[1];
    cs ^= msgid;
    for (int i=0; i < size; ++i) {
        cs ^= data[i];
    }

    return cs;
}