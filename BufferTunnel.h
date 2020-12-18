//
// Created by jianyuelin on 12/17/2020.
//

#ifndef ROKU_BUFFERTUNNEL_H
#define ROKU_BUFFERTUNNEL_H

#include <iostream>
#include <fstream>
#include <cstring>
#include "utils.h"

namespace roku {
    template<typename T, typename Out> requires roku::utils::HasCtyleStr<T>
    class BufferTunnel {
    public:
        BufferTunnel(T &str) : _buffer{str} {
//            _u32_buffer = roku::utils::utf8_to_utf32(str);
        }

        friend class Iterator;

        class Iterator {
        private:
            BufferTunnel &_tunnel;
            std::string::iterator _start;
            std::string::iterator _end;

        public:
            Iterator(BufferTunnel &bufferTunnel) : _tunnel{bufferTunnel} {
                _start = bufferTunnel._buffer.begin();
                _end = bufferTunnel._buffer.end();
            }

            Iterator(BufferTunnel &bufferTunnel, bool) : _tunnel{bufferTunnel} {
                _start = bufferTunnel._buffer.end();
                _end = bufferTunnel._buffer.end();
            }

            T operator*() const { return *_start; }

            T operator++() { // Prefix form
                return *(++_start);
            }

            char operator++(int) { // Postfix form

                return *(_start++);
            }

            // Jump an iterator forward
            Iterator &operator+=(int amount) {

                _start += amount;
                return *this;
            }

            // To see if you're at the end:
            bool operator==(const Iterator &rv) const {
                return _start == rv._start;
            }

            bool operator!=(const Iterator &rv) const {
                return _start != rv._start;
            }

            friend std::ostream &operator<<(
                    std::ostream &os, const Iterator &it) {
                return os << *it;
            }


        };

        Iterator begin() { return Iterator(*this); }

        // Create the "end sentinel":
        Iterator end() { return Iterator(*this, true); }


//        BufferTunnel(BufferTunnel<T, Out> &&other) noexcept: _tunnel{nullptr} {
//            _tunnel = other._tunnel;
//            _length = other._length;
//            other._tunnel = nullptr;
//            other._length = 0;
//        }
//
//
//        BufferTunnel &operator=(BufferTunnel &&other) noexcept {
//            if (this != other) {
//                delete[] _tunnel;
//                _tunnel = other._tunnel;
//                _length = other._length;
//
//                other._tunnel = nullptr;
//                other._length = 0;
//
//            }
//
//            return *this;
//        }
    private:
        std::string _buffer;
        std::u32string _u32_buffer;
    };


}


#endif //ROKU_BUFFERTUNNEL_H
