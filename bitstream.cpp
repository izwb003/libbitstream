#include <cstdlib>
#include "bitstream.h"

/*
Made by Fran 1024, 2019
Modified by Steven Song (izwb003), 2024
*/

namespace libbitstream {
    BitStream::BitStream(uint8_t *bytes, size_t _size) {
        data = bytes;
        size = _size;
    }

    BitStream::BitStream(size_t _size) {
        data = (uint8_t*)malloc(_size);
        size = _size;
    }

    BitStream::BitStream() = default;

    bool BitStream::getbit(uint8_t x, uint32_t y) {
        return (x >> (7 - y)) & 1;
    }

    uint32_t BitStream::chbit(uint32_t x, uint32_t i, bool v) {
        if(v) return x | (1 << (7 - i));
        return x & ~(1 << (7 - i));
    }

    size_t BitStream::calcbit(uint32_t dat) {
        size_t bits = 0;
        while((dat >> bits) != 0)
            bits++;
        return bits;
    }

    uint8_t *BitStream::toByteArray() {
        return data;
    }

    void BitStream::openBytes(uint8_t *bytes, size_t _size) {
        data = bytes;
        size = _size;
    }

    void BitStream::open(size_t _size) {
        data = (uint8_t*)malloc(_size);
        size = _size;
    }

    void BitStream::close() {
        free(data);
    }

    void BitStream::write(size_t ind, size_t bits, uint32_t dat) {
        for(size_t i = 0; i < bits; i++) {
            uint32_t bitToWrite = (dat >> (bits - 1 - i)) & 1;
            data[ind / 8] = chbit(data[ind / 8], ind % 8, bitToWrite);
            ind++;
        }
    }

    uint32_t BitStream::read(size_t ind, size_t bits) {
        uint32_t dat = 0;
        for(size_t i = ind; i < ind + bits; i++) {
            dat = dat * 2 + getbit(data[i / 8], i % 8);
        }
        return dat;
    }

    size_t BitStream::writeAlignBits(size_t ind) {
        size_t alignBits = 8 - (ind % 8);
        if(alignBits == 8)
            return ind;
        write(ind, alignBits, 0);
        return ind + alignBits;
    }

    size_t BitStream::readAlignBits(size_t ind) {
        size_t alignBits = 8 - (ind % 8);
        if(alignBits == 8)
            alignBits = 0;
        return ind + alignBits;
    }
} // libbitstream