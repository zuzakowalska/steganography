//
// Created by Zuzanna Kowalska on 04/01/2022.
//

#ifndef STEGANOGRAFIA_OBRAZOWA_PNG_H
#define STEGANOGRAFIA_OBRAZOWA_PNG_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "constants.h"
#include "channels.h"

namespace png {

    typedef unsigned char byte;

    std::vector<channels::channels> read_png(std::string &file_name) {
        uint32_t                        width,
                                        height;
        uint8_t                         bits_depth;
        std::vector<uint32_t>           pixels;
        channels::channels              channels{};
        std::vector<channels::channels> pixels_channels;

        std::ifstream fs(file_name, std::ios::in | std::ios::binary);
        if (!fs) {
            std::cerr << "Nie można otworzyć pliku" << "\n";
            std::exit(-1);
        }

        char *width_ch  = new char[4];
        char *height_ch = new char[4];

        fs.seekg(CONSTANTS::WIDTH_PNG_OFFSET, std::ios::beg);
        fs.read(width_ch, sizeof(width_ch));
        fs.seekg(CONSTANTS::HEIGHT_PNG_OFFSET, std::ios::beg);
        fs.read(height_ch, sizeof(height_ch));
        fs.seekg(CONSTANTS::BITS_DEPTH_OFFSET, std::ios::beg);
        fs.read((char *) &bits_depth, 1);

        width  = (width_ch[0] << 24 | width_ch[1] << 16 | width_ch[2] << 8 | width_ch[3]);
        height = (height_ch[0] << 24 | height_ch[1] << 16 | height_ch[2] << 8 | height_ch[3]);

        std::cout << width << "\n" << height << "\n" << (int) bits_depth << "\n";

        unsigned long current_offset = 8;
        auto          chunk_size     = new byte[4];
        auto          chunk_type     = new byte[4];
        uint32_t      chunk_size_num;

        while (true) {
            fs.seekg(current_offset, std::ios::beg);
            fs.read((char *) chunk_size, sizeof(chunk_size));
            fs.seekg(current_offset + 4, std::ios::beg);
            fs.read((char *) chunk_type, sizeof(chunk_type));

//            std::cout << chunk_size << "\n\n";
            std::cout << chunk_type[0] << " " << chunk_type[1] << " " << chunk_type[2] << " " << chunk_type[3] << "\n";
            if (chunk_type[0] == 'I' && chunk_type[1] == 'E' && chunk_type[2] == 'N' && chunk_type[3] == 'D') {
                break;
            }

            std::cout << (int) chunk_size[0] << " " << (int) chunk_size[1] << " " << (int) chunk_size[2] << " "
                      << (int) chunk_size[3] << "\n";
            chunk_size_num = (chunk_size[0] << 24 | chunk_size[1] << 16 | chunk_size[2] << 8 | chunk_size[3]);
            std::cout << (int) (chunk_size[0] << 24) << " " << (int) (chunk_size[1] << 16) << " "
                      << (int) (chunk_size[2] << 8) << " " << (int) chunk_size[3] << "\n";

            std::cout << current_offset << "\n";

            std::cout << chunk_size_num << "\n";

            current_offset += chunk_size_num + 12;

            std::cout << current_offset << "\n\n";

        }


        return pixels_channels;
    }
}
#endif //STEGANOGRAFIA_OBRAZOWA_PNG_H
