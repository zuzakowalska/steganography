#include <iostream>
#include <string>
#include <vector>
#include "process_binary.h"

int main() {
    std::string file = "/Users/zuza/Studia/steganografia_obrazowa/test-bit.bmp";
    auto bmp_vec = read_binary::read_bmp(file);

//    for (int v : bmp_vec) {
//        std::cout << std::hex << v << " ";
//    }
//    std::cout << "\n\n";

    return 0;
}

