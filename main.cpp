#include <iostream>
#include <string>
#include <vector>
#include "steganography.h"

int main() {
    std::string file_bmp = "/Users/zuza/Studia/steganografia_obrazowa/test-bit.bmp";
    std::string file_png = "/Users/zuza/Studia/steganografia_obrazowa/test-bit_nn.png";

    auto bmp_vec = read_binary_image::read_bmp(file_bmp);
//    auto png_vec = read_binary_image::read_png(file_png);

    for (read_binary_image::rgba v : bmp_vec) {
        std::cout << v.r << v.g << v.b << v.a << "\n";
    }
    std::cout << "\n\n";

    secret_message::encode_secret_message(bmp_vec, "pjesek");

    for (read_binary_image::rgba v : bmp_vec) {
        std::cout << v.r << v.g << v.b << v.a << "\n";
    }
    std::cout << "\n\n";

    return 0;
}

