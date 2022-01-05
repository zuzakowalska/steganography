//
// Created by Zuzanna Kowalska on 04/01/2022.
//

#ifndef STEGANOGRAFIA_OBRAZOWA_CHANNELS_H
#define STEGANOGRAFIA_OBRAZOWA_CHANNELS_H

#include <iostream>
#include "constants.h"

namespace channels {

    struct channels {
        CONSTANTS::byte r, g, b, a;
    };

    auto pixels_to_channels = [] (uint32_t num, channels& ch, int bits_per_pixel) {
        int bits_per_channel = 8;
        int bit_mask = (int) (pow(2,bits_per_channel)) - 1;

        ch.b = num & bit_mask;
        num = num >> bits_per_channel;
        ch.g = num & bit_mask;
        num = num >> bits_per_channel;
        ch.r = num & bit_mask;
        num = num >> bits_per_channel;
        ch.a = num & bit_mask;
    };

    auto channels_to_pixels = [] (channels& ch, bool is_alpha) {
        uint32_t num = 0;
        int bits_per_channel = 8;


        if (is_alpha) {
            num = (ch.a | num) << bits_per_channel;
        }
        num = (ch.r | num) << bits_per_channel;
        num = (ch.g | num) << bits_per_channel;
        num = (ch.b | num);

        return num;
    };

    auto channels_to_bytes = [] (channels& ch, bool is_alpha) {
        if (is_alpha) {
            return new std::vector<CONSTANTS::byte>{ch.a, ch.r, ch.g, ch.b};
        }
        return new std::vector<CONSTANTS::byte>{ch.r, ch.g, ch.b};
    };
}

#endif //STEGANOGRAFIA_OBRAZOWA_CHANNELS_H
