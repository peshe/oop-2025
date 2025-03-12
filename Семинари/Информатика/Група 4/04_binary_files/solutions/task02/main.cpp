#include "BMP_Image.hpp"
#include <iostream>

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        std::cerr << "Wrong number of command arguments!" << std::endl;
        return 1;
    }

    BMP_Image image;
    if (!loadImage(image, argv[1])) {
        return 2;
    }

    if (!convertToGrayScale(image, argv[2])) {
        image.in.close();
        return 3;
    }

    image.in.close();
    return 0;
}
