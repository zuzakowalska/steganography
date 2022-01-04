//
// Created by Zuzanna Kowalska on 04/01/2022.
//

#ifndef STEGANOGRAFIA_OBRAZOWA_BMP_H
#define STEGANOGRAFIA_OBRAZOWA_BMP_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <bitset>

#include "channels.h"

namespace bmp {

    typedef unsigned char byte;

    uint32_t get_pixel_array_offset(std::ifstream &fs) {
        uint32_t pixel_array_offset;
        fs.seekg(10, std::ios::beg);
        fs.read((char *) &pixel_array_offset, sizeof(pixel_array_offset));

        return pixel_array_offset;
    }

    uint32_t get_width(std::ifstream &fs) {
        uint32_t width;
        fs.seekg(18, std::ios::beg);
        fs.read((char *) &width, sizeof(width));

        return width;
    }

    uint32_t get_height(std::ifstream &fs) {
        uint32_t height;
        fs.seekg(22, std::ios::beg);
        fs.read((char *) &height, sizeof(height));

        return height;
    }

    int16_t get_bits_per_pixel(std::ifstream &fs) {
        uint16_t bits_per_pixel;
        fs.seekg(28, std::ios::beg);
        fs.read((char *) &bits_per_pixel, sizeof(bits_per_pixel));

        return bits_per_pixel;
    }

    std::vector<channels::channels> read_image(std::string &file_name) {
        int32_t pixel_array_offset,
                width,
                height;
        int16_t bits_per_pixel;
        std::vector<uint32_t> pixels;
        unsigned int padded_row_size,
                unpadded_row_size;
        channels::channels channels{};
        std::vector<channels::channels> pixels_channels;

        std::ifstream fs(file_name, std::ios::in | std::ios::binary);
        if (!fs) {
            std::cerr << "Nie można otworzyć pliku" << "\n";
            std::exit(-1);
        }

        pixel_array_offset = bmp::get_pixel_array_offset(fs);
        width = bmp::get_width(fs);
        height = bmp::get_height(fs);
        bits_per_pixel = bmp::get_bits_per_pixel(fs);

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
            fs.read((char *) &pixels[i], unpadded_row_size);
        }

        for (auto p: pixels) {
//            std::cout << p << "    " << std::hex << p << "\n";
            channels::convert_to_channels(p, channels, bits_per_pixel);
            pixels_channels.push_back(channels);
        }

//        for (auto pc : pixels_channels) {
//            std::cout << pc.r << " " << pc.g << " " << pc.b << " " << pc.a <<  "\n";
//        }

        // wektor struktow rgba
        return pixels_channels;
    }

    void encode_secret_message(std::vector<channels::channels> &pixels, std::string message) {
        int bits_per_channel = 2;
        int channels_per_pixel = 3;
        int target_pixel_idx;
        int target_channel_idx;
        int current_char_chunk_idx;
        bmp::byte current_char_chunk;
        std::bitset<8> current_char_bits;

        for (int i = 0; i < message.length(); i++) {
            // 8 - wielkosc ASCII char
            for (int j = 0; j < 8 / bits_per_channel; j++) {
                current_char_chunk_idx = i * 4 + j;
                target_pixel_idx = current_char_chunk_idx / channels_per_pixel;
                target_channel_idx = current_char_chunk_idx % channels_per_pixel;
                current_char_bits = std::bitset<8>(message[i]);

                // zrobic to w petli
                current_char_chunk = current_char_bits[j * 2] << 1 | current_char_bits[j * 2 + 1];

                switch (target_channel_idx) {
                    case 0:
                        pixels[target_pixel_idx].r =
                                ((pixels[target_pixel_idx].r >> bits_per_channel) << bits_per_channel) |
                                current_char_chunk;
                        break;
                    case 1:
                        pixels[target_pixel_idx].g =
                                ((pixels[target_pixel_idx].g >> bits_per_channel) << bits_per_channel) |
                                current_char_chunk;
                        break;
                    case 2:
                        pixels[target_pixel_idx].b =
                                ((pixels[target_pixel_idx].b >> bits_per_channel) << bits_per_channel) |
                                current_char_chunk;
                        break;
                    case 3:
                        pixels[target_pixel_idx].a =
                                ((pixels[target_pixel_idx].a >> bits_per_channel) << bits_per_channel) |
                                current_char_chunk;
                        break;
                    default:
                        // dodac tu error
                        break;
                }
            }

        }
    }
}

#endif //STEGANOGRAFIA_OBRAZOWA_BMP_H
