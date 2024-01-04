#ifndef LIBBITSTREAM_BITSTREAM_H
#define LIBBITSTREAM_BITSTREAM_H

#include <cinttypes>

/*
Made by Fran 1024, 2019
Modified by Steven Song (izwb003), 2024
*/

namespace libbitstream {

    class BitStream {
    private:
        uint8_t *data; // where bitstream is contained
        size_t size;   // size of the bitstream

        static bool getbit(uint8_t x, uint32_t y);
        static uint32_t chbit(uint32_t x, uint32_t i, bool v);
        static size_t calcbit(uint32_t dat);
    public:
        // construct
        BitStream(uint8_t *bytes, size_t _size);
        explicit BitStream(size_t _size);
        BitStream();
        // returns data as a byte array
        uint8_t *toByteArray();
        // opens an existing byte array as bitstream
        void openBytes(uint8_t *bytes, size_t _size);
        // creates a new bit stream
        void open(size_t _size);
        // closes bit stream (frees memory)
        void close();
        // writes to bitstream
        void write(size_t ind, size_t bits, uint32_t dat);
        // reads from bitstream
        uint32_t read(size_t ind, size_t bits);
        // write align bits
        // return new ind
        size_t writeAlignBits(size_t ind);
        // read align bits
        // return new ind
        static size_t readAlignBits(size_t ind);
    };

} // libbitstream

#endif //LIBBITSTREAM_BITSTREAM_H
