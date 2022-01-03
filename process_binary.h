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

namespace read_binary {
    std::vector<int> read_bmp(std::string& file_name) {
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

        // in bits
        padded_row_size = ceil((bits_per_pixel * width) / 32) * 4;
        unpadded_row_size = bits_per_pixel * width;
        pixels = std::vector<uint32_t>(abs(width * height));

        for (int i = 0; i < abs(height); i++) {
            fs.seekg(pixel_array_offset + (i * padded_row_size), std::ios::beg);
            fs.read((char*) &pixels[i], unpadded_row_size);
        }





//        res.push_back(pixel_array_offset);
//        res.push_back(width);
//        res.push_back(height);
//        res.push_back(bits_per_pixel);
        return res;
    }
}

namespace write_binary {

}
#endif //STEGANOGRAFIA_OBRAZOWA_PROCESS_BINARY_H
