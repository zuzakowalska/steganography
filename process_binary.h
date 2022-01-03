//
// Created by Zuzanna Kowalska on 02/01/2022.
//

#ifndef STEGANOGRAFIA_OBRAZOWA_PROCESS_BINARY_H
#define STEGANOGRAFIA_OBRAZOWA_PROCESS_BINARY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>

namespace read_binary {

    struct rgba {
        int r, g, b, a;
    };

    auto convert_to_channels = [] (uint32_t num, read_binary::rgba& channels, int bits_per_pixel) {
        int bits_per_channel = 8;
        int bit_mask = (pow(2,bits_per_channel)) - 1;

        channels.b = num & bit_mask;
        num = num >> bits_per_channel;
        channels.g = num & bit_mask;
        num = num >> bits_per_channel;
        channels.r = num & bit_mask;
        num = num >> bits_per_channel;
        channels.a = num & bit_mask;

//        std::cout << std::dec << channels.r << " " << channels.g << " " << channels.b << " " << channels.a << "\n";

    };


    std::vector<uint32_t> read_bmp(std::string& file_name) {
        int32_t      pixel_array_offset,
                     width,
                     height;
        int16_t      bits_per_pixel;
        std::vector<uint32_t>     pixels;
        unsigned int padded_row_size,
                     unpadded_row_size;

        std::ifstream fs(file_name, std::ios::in | std::ios::binary);
        if (!fs) {
            std::cerr << "Can't open file!" << "\n";
            std::exit(-1);
        }

        fs.seekg(10, std::ios::beg);
        fs.read((char*) &pixel_array_offset, sizeof(pixel_array_offset));

        fs.seekg(18, std::ios::beg);
        fs.read((char*) &width, sizeof(width));

        fs.seekg(22, std::ios::beg);
        fs.read((char*) &height, sizeof(height));

        fs.seekg(28, std::ios::beg);
        fs.read((char*) &bits_per_pixel, sizeof(bits_per_pixel));

        if (bits_per_pixel <= 8) {
            std::cerr << "Nie można zapisać wiadomości, obraz o zbyt małej głębi kolorów" << "\n";
            exit(-1);
        }

        // in bits
        padded_row_size = ceil((bits_per_pixel * width) / 32) * 4;
        unpadded_row_size = bits_per_pixel * width;
        pixels = std::vector<uint32_t>(abs(width * height));

        for (int i = 0; i < abs(height); i++) {
            fs.seekg(pixel_array_offset + (i * padded_row_size), std::ios::beg);
            fs.read((char*) &pixels[i], unpadded_row_size);
        }

        read_binary::rgba channels;
        for (auto p : pixels) {
            std::cout << p << "    " << std::hex << p << "\n";
            read_binary::convert_to_channels(p, channels, bits_per_pixel);
        }

        return pixels;
    }
}

namespace write_binary {

}
#endif //STEGANOGRAFIA_OBRAZOWA_PROCESS_BINARY_H
