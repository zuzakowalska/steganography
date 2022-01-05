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

namespace steganography {

    void read_image_bmp(std::string &filename, std::string message) {
        std::ifstream fs;
        fs.open(filename, std::ios::in | std::ios::binary);
        if (!fs) {
            std::cerr << "Nie można otworzyć pliku" << "\n";
            std::exit(-1);
        }

        auto pixel_array_offset = bmp::get_pixel_array_offset(fs);
        auto width              = bmp::get_width(fs);
        auto height             = bmp::get_height(fs);
        auto bits_per_pixel     = bmp::get_bits_per_pixel(fs);


        if (bits_per_pixel <= 8) {
            std::cerr << "Nie można zapisać wiadomości, obraz o zbyt małej głębi kolorów" << "\n";
            exit(-1);
        }

        auto pixels = bmp::read_image(pixel_array_offset, width, height, bits_per_pixel, fs);
        fs.close();
        bmp::encode_secret_message(pixels, message);

        auto pixel_array = bmp::create_pixel_array(pixels, width, bits_per_pixel);
        std::string output = "/Users/zuza/Studia/steganografia_obrazowa/out1.bmp";
        bmp::write_bmp(filename, output, pixel_array, pixel_array_offset);
    }
}


#endif //STEGANOGRAFIA_OBRAZOWA_STEGANOGRAPHY_H
