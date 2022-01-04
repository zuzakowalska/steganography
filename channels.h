//
// Created by Zuzanna Kowalska on 04/01/2022.
//

#ifndef STEGANOGRAFIA_OBRAZOWA_CHANNELS_H
#define STEGANOGRAFIA_OBRAZOWA_CHANNELS_H

#include <iostream>

namespace channels {

    struct channels {
        unsigned int r, g, b, a;
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

    int channels_to_pixels = [&] (channels& ch) {
        uint32_t num = 0;
        int bits_per_channel = 8;

        num = (ch.a | num) << bits_per_channel;
//        std::cout << num << "\n";
        num = (ch.r | num) << bits_per_channel;
//        std::cout << num << "\n";
        num = (ch.g | num) << bits_per_channel;
//        std::cout << num << "\n";
        num = (ch.b | num) << bits_per_channel;
//        std::cout << num << "\n";
        std::cout << typeid(num).name() << "\n";

        return 1;
    };
}

#endif //STEGANOGRAFIA_OBRAZOWA_CHANNELS_H
