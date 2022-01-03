#include <iostream>
#include <fstream>
#include <vector>
#include <string>

//std::vector<char> read_file(std::string filename) {
//    std::ifstream file(filename, std::ios::binary);
//
//    file.unsetf(std::ios::skipws);
//
//    // chcemy wiedziec jaka ten plik ma wielkosc
//    std::streampos filesize;
//    // wskaznik na koniec
//    file.seekg(0, std::ios::end);
//    // powiedz mi jaka wielkosc
//    filesize = file.tellg();
//    // wskaznik wraca na poczatek
//    file.seekg(0, std::ios::beg);
//
//    std::vector<char> vec;
//    // rezerwujemy miejsce zeby bylo szybciej
//    vec.reserve(filesize);
//
//    vec.insert(vec.begin(), std::istream_iterator<char>(file), std::istream_iterator<char>());
//
//    return vec;
//}

void read_bmp(std::string file_name, int32_t* pixel_array_offset, int32_t* width, int32_t* weight, int16_t* bits_per_pixel) {

}

int test() {

    int32_t pixel_array_offset;
    int32_t width,
            height;
    int16_t bits_per_pixel;

    FILE* file = fopen("/Users/zuza/Studia/steganografia_obrazowa/test-bit.bmp", "rb");
    fseek(file, 10, SEEK_SET);
    fread(&pixel_array_offset, 4, 1, file);
    std::cout << pixel_array_offset << "\n";

    fseek(file, 18, SEEK_SET);
    fread(&width, 4, 1, file);
    fseek(file, 22, SEEK_SET);
    fread(&height, 4, 1, file);
    std::cout << width<< "\n";
    std::cout << height << "\n";

    fseek(file, 28, SEEK_SET);
    fread(&bits_per_pixel, 2, 1, file);
    std::cout << bits_per_pixel<< "\n";

//    file.read(&pixel_array_offset, sizeof(pixel_array_offset));

//    auto vec = read_file("/Users/zuza/Studia/steganografia_obrazowa/test-bit.bmp");
//    auto bitmap_file_header = std::vector(vec.begin(), vec.begin() + 13);
//
//    // czy na polu gdzie jest DIB header mamy BITMAPINFOHEADER o dlugosci 40 (innych nie wspieramy)
//    bool is_supported = vec[14] == 40;
//
//    char width = vec[18];
//    char height = vec[22];
//
//    auto pixel_array_offset = std::vector(bitmap_file_header.begin() + 10, bitmap_file_header.begin() + 13);
//
//
//    std::cout << is_supported << '\n';
//    std::cout << (int32_t) width << '\n';
//    std::cout << (int32_t) height << '\n';


//    for (char v : vec) {
//        std::cout << (uint8_t) v << " ";
//    }
//
//    std::ofstream out("/Users/zuza/Studia/steganografia_obrazowa/out.bmp");
//    out.write(&vec[0], vec.size()*sizeof(char));
//    out.close();
//    std::cout << "\n";
    return 0;
}
