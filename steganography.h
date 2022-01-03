//
// Created by Zuzanna Kowalska on 02/01/2022.
//

#ifndef STEGANOGRAFIA_OBRAZOWA_STEGANOGRAPHY_H
#define STEGANOGRAFIA_OBRAZOWA_STEGANOGRAPHY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>

namespace read_binary_image {

    struct rgba {
        unsigned int r, g, b, a;
    };

    typedef unsigned char byte;

    auto convert_to_channels = [] (uint32_t num, read_binary_image::rgba& channels, int bits_per_pixel) {
        int bits_per_channel = 8;
        int bit_mask = (int) (pow(2,bits_per_channel)) - 1;

        channels.b = num & bit_mask;
        num = num >> bits_per_channel;
        channels.g = num & bit_mask;
        num = num >> bits_per_channel;
        channels.r = num & bit_mask;
        num = num >> bits_per_channel;
        channels.a = num & bit_mask;

//        std::cout << std::dec << channels.r << " " << channels.g << " " << channels.b << " " << channels.a << "\n";

    };


    std::vector<read_binary_image::rgba> read_bmp(std::string& file_name) {
        int32_t      pixel_array_offset,
                     width,
                     height;
        int16_t      bits_per_pixel;
        std::vector<uint32_t>     pixels;
        unsigned int padded_row_size,
                     unpadded_row_size;
        read_binary_image::rgba channels{};
        std::vector<read_binary_image::rgba> pixels_channels;

        std::ifstream fs(file_name, std::ios::in | std::ios::binary);
        if (!fs) {
            std::cerr << "Nie można otworzyć pliku" << "\n";
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

        for (auto p : pixels) {
//            std::cout << p << "    " << std::hex << p << "\n";
            read_binary_image::convert_to_channels(p, channels, bits_per_pixel);
            pixels_channels.push_back(channels);
        }

//        for (auto pc : pixels_channels) {
//            std::cout << pc.r << " " << pc.g << " " << pc.b << " " << pc.a <<  "\n";
//        }

        // wektor struktow rgba
        return pixels_channels;
    }

    std::vector<read_binary_image::rgba> read_png(std::string& file_name) {
        uint32_t width,
                height;
        uint8_t bits_depth;
        std::vector<uint32_t> pixels;
        read_binary_image::rgba channels{};
        std::vector<read_binary_image::rgba> pixels_channels;

        std::ifstream fs(file_name, std::ios::in | std::ios::binary);
        if (!fs) {
            std::cerr << "Nie można otworzyć pliku" << "\n";
            std::exit(-1);
        }

        char* width_ch = new char[4];
        char* height_ch = new char[4];

        fs.seekg(16, std::ios::beg);
        fs.read(width_ch, sizeof(width_ch));
        fs.seekg(20, std::ios::beg);
        fs.read(height_ch, sizeof(height_ch));
        fs.seekg(24, std::ios::beg);
        fs.read((char*) &bits_depth, 1);

        width = (width_ch[0] << 24 | width_ch[1] << 16 | width_ch[2] << 8 | width_ch[3]);
        height = (height_ch[0] << 24 | height_ch[1] << 16 | height_ch[2] << 8 | height_ch[3]);

        std::cout << width << "\n" << height << "\n" << (int) bits_depth << "\n";

        unsigned long current_offset = 8;
        auto chunk_size = new byte[4];
        auto chunk_type = new byte[4];
        uint32_t chunk_size_num;

        while (true) {
            fs.seekg(current_offset, std::ios::beg);
            fs.read((char*) chunk_size, sizeof(chunk_size));
            fs.seekg(current_offset + 4, std::ios::beg);
            fs.read((char*) chunk_type, sizeof(chunk_type));

//            std::cout << chunk_size << "\n\n";
            std::cout << chunk_type[0] << " " << chunk_type[1] << " " << chunk_type[2] << " " << chunk_type[3] << "\n";
            if (chunk_type[0] == 'I' && chunk_type[1] == 'E' && chunk_type[2] == 'N' && chunk_type[3] == 'D') {
                break;
            }

            std::cout << (int) chunk_size[0] << " " << (int) chunk_size[1] << " " << (int) chunk_size[2] << " " << (int) chunk_size[3] << "\n";
            chunk_size_num = (chunk_size[0] << 24 | chunk_size[1] << 16 | chunk_size[2] << 8 | chunk_size[3]);
            std::cout << (int) (chunk_size[0] << 24) << " " << (int) (chunk_size[1] << 16) << " " << (int) (chunk_size[2] << 8) << " " << (int) chunk_size[3] << "\n";

            std::cout << current_offset << "\n";

            std::cout << chunk_size_num << "\n";

            current_offset += chunk_size_num + 12;

            std::cout << current_offset << "\n\n";

        }


        return pixels_channels;
    }
}

namespace write_binary_image {

}

namespace secret_message {



    void encode_secret_message(std::vector<read_binary_image::rgba>& pixels, std::string message) {
        int bits_per_channel = 2;
        int channels_per_pixel = 4;



    }
}
#endif //STEGANOGRAFIA_OBRAZOWA_STEGANOGRAPHY_H
