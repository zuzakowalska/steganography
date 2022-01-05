//
// Created by Zuzanna Kowalska on 04/01/2022.
//

#ifndef STEGANOGRAFIA_OBRAZOWA_CONSTANTS_H
#define STEGANOGRAFIA_OBRAZOWA_CONSTANTS_H

namespace CONSTANTS {

    typedef unsigned char byte;

    const int PIXEL_ARRAY_OFFSET_OFFSET = 10;
    const int WIDTH_BMP_OFFSET          = 18;
    const int HEIGHT_BMP_OFFSET         = 22;
    const int WIDTH_PNG_OFFSET          = 16;
    const int HEIGHT_PNG_OFFSET         = 20;
    const int BITS_DEPTH_OFFSET         = 24;
    const int BITS_PER_PIXEL_OFFSET     = 28;
    const int BITS_PER_CHANNEL          = 2;
    const int CHANNELS_PER_PIXEL_3      = 3;
    const int CHANNELS_PER_PIXEL_4      = 4;
    const int ASCII_LENGTH              = 8;
}

#endif //STEGANOGRAFIA_OBRAZOWA_CONSTANTS_H
