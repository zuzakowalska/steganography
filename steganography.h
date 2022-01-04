//
// Created by Zuzanna Kowalska on 02/01/2022.
//

#ifndef STEGANOGRAFIA_OBRAZOWA_STEGANOGRAPHY_H
#define STEGANOGRAFIA_OBRAZOWA_STEGANOGRAPHY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "bmp.h"
#include "png.h"

void read_image_bmp(std::string filename, std::string message) {
    std::ifstream fs(filename, std::ios::in | std::ios::binary);
    if (!fs) {
        std::cerr << "Nie można otworzyć pliku" << "\n";
        std::exit(-1);
    }

    auto pixel_array_offset = bmp::get_pixel_array_offset(fs);
    auto width = bmp::get_width(fs);
    auto height = bmp::get_height(fs);
    auto bits_per_pixel = bmp::get_bits_per_pixel(fs);

    auto pixels = bmp::read_image(filename);
    bmp::encode_secret_message(pixels, message);

    // @TODO: pixel_array = create_pixel_array(pixels, width, bits_per_channel)
    // @TODO: write_bmp(source_file, target_file_path, pixel_array)
}
#endif //STEGANOGRAFIA_OBRAZOWA_STEGANOGRAPHY_H
