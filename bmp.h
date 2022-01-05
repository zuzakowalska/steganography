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
#include <algorithm>
#include "constants.h"
#include "channels.h"


namespace bmp {

    int32_t get_pixel_array_offset(std::ifstream &fs) {
        int32_t pixel_array_offset;
        fs.seekg(CONSTANTS::PIXEL_ARRAY_OFFSET_OFFSET, std::ios::beg);
        fs.read((char *) &pixel_array_offset, sizeof(pixel_array_offset));

        return pixel_array_offset;
    }

    int32_t get_width(std::ifstream &fs) {
        int32_t width;
        fs.seekg(CONSTANTS::WIDTH_BMP_OFFSET, std::ios::beg);
        fs.read((char *) &width, sizeof(width));

        return width;
    }

    int32_t get_height(std::ifstream &fs) {
        int32_t height;
        fs.seekg(CONSTANTS::HEIGHT_BMP_OFFSET, std::ios::beg);
        fs.read((char *) &height, sizeof(height));

        return height;
    }

    int16_t get_bits_per_pixel(std::ifstream &fs) {
        int16_t bits_per_pixel;
        fs.seekg(CONSTANTS::BITS_PER_PIXEL_OFFSET, std::ios::beg);
        fs.read((char *) &bits_per_pixel, sizeof(bits_per_pixel));

        return bits_per_pixel;
    }

    std::vector<channels::channels>
    read_image(int32_t pixel_array_offset, int32_t width, int32_t height, int16_t bits_per_pixel, std::ifstream &fs) {
        std::vector<uint32_t>           pixels;
        channels::channels              channels{};
        std::vector<channels::channels> pixels_channels;

        // in bits
        unsigned int padded_row_size   = ceil((bits_per_pixel * width) / 32) * 4;
        unsigned int unpadded_row_size = bits_per_pixel * width;
        pixels = std::vector<uint32_t>(abs(width * height));

        for (int i = 0; i < abs(height); i++) {
            fs.seekg(pixel_array_offset + (i * padded_row_size), std::ios::beg);
            fs.read((char *) &pixels[i], unpadded_row_size);
        }

        for (auto p: pixels) {
            channels::pixels_to_channels(p, channels, bits_per_pixel);
            pixels_channels.push_back(channels);
        }

        // wektor struktow rgba
        return pixels_channels;
    }

    std::vector<CONSTANTS::byte>*
    create_pixel_array(std::vector<channels::channels> &pixels, int32_t width, int16_t bits_per_pixel) {
        unsigned int padded_row_size   = ceil((bits_per_pixel * width) / 32) * 4;
        unsigned int unpadded_row_size = bits_per_pixel * width;
        unsigned int pad_size          = padded_row_size - unpadded_row_size;
        int bytes_per_pixel = bits_per_pixel / CONSTANTS::BITS_PER_CHANNEL;

        std::vector<uint32_t> pixel_array;
//        auto pixel_bytes = std::vector<CONSTANTS::byte>(pixels.size() * (bytes_per_pixel));
        std::vector<CONSTANTS::byte>* pixel_bytes;
        pixel_bytes->reserve(pixels.size() * (bytes_per_pixel));
        bool is_alpha = bits_per_pixel == 32;
        std::vector<CONSTANTS::byte> *current_bytes;
        current_bytes->reserve(bytes_per_pixel);

        for (int i = 0; i < pixels.size(); ++i) {
            current_bytes = channels::channels_to_bytes(pixels[i], is_alpha);
            for (int j = 0; j < bytes_per_pixel; ++j) {
                pixel_bytes[i*bytes_per_pixel+j] = current_bytes[j];

            }
        }
        for (CONSTANTS::byte p : *pixel_bytes) {
            std::cout << p << " ";
        }
        std::cout << "\n";

        return pixel_bytes;

    }


    void encode_secret_message(std::vector<channels::channels> &pixels, std::string &message) {
        int            target_pixel_idx;
        int            target_channel_idx;
        int            current_char_chunk_idx;
        CONSTANTS::byte      current_char_chunk;
        std::bitset<8> current_char_bits;

        for (int i = 0; i < message.length(); i++) {
            // 8 - wielkosc ASCII char
            for (int j = 0; j < 8 / CONSTANTS::BITS_PER_CHANNEL; j++) {
                current_char_chunk_idx = i * 4 + j;
                target_pixel_idx       = current_char_chunk_idx / CONSTANTS::BITS_PER_CHANNEL;
                target_channel_idx     = current_char_chunk_idx % CONSTANTS::CHANNELS_PER_PIXEL_3;
                current_char_bits      = std::bitset<8>(message[i]);

                // zrobic to w petli
                current_char_chunk = current_char_bits[j * 2] << 1 | current_char_bits[j * 2 + 1];

                switch (target_channel_idx) {
                    case 0:
                        pixels[target_pixel_idx].r =
                                ((pixels[target_pixel_idx].r >> CONSTANTS::BITS_PER_CHANNEL)
                                        << CONSTANTS::BITS_PER_CHANNEL) |
                                current_char_chunk;
                        break;
                    case 1:
                        pixels[target_pixel_idx].g =
                                ((pixels[target_pixel_idx].g >> CONSTANTS::BITS_PER_CHANNEL)
                                        << CONSTANTS::BITS_PER_CHANNEL) |
                                current_char_chunk;
                        break;
                    case 2:
                        pixels[target_pixel_idx].b =
                                ((pixels[target_pixel_idx].b >> CONSTANTS::BITS_PER_CHANNEL)
                                        << CONSTANTS::BITS_PER_CHANNEL) |
                                current_char_chunk;
                        break;
                    case 3:
                        pixels[target_pixel_idx].a =
                                ((pixels[target_pixel_idx].a >> CONSTANTS::BITS_PER_CHANNEL)
                                        << CONSTANTS::BITS_PER_CHANNEL) |
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
