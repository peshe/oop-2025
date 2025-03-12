#include "BMP_Image.hpp"
#include "Pixel.hpp"
#include <iostream>

std::uint32_t read4Bytes(std::ifstream& input, std::size_t position) {
    std::uint32_t result;

    input.seekg(position);
    input.read(reinterpret_cast<char*>(&result), sizeof(result));

    return result;
}

bool loadImage(BMP_Image& image, const char fileName[])
{
    image.in.open(fileName, std::ios::binary);
    if (!image.in) {
        std::cerr << "Problem opening image!" << std::endl;
        return false;
    }

    image.size = read4Bytes(image.in, 2);
    image.contentStart = read4Bytes(image.in, 10);
    image.columns = read4Bytes(image.in, 18);
    image.rows = read4Bytes(image.in, 22);

    return true;
}

bool convertToGrayScale(BMP_Image& image, const char outputFileName[])
{
    std::ofstream out(outputFileName, std::ios::binary);
    if (!out) {
        std::cerr << "Error opeing new file!" << std::endl;
        return false;
    }

    image.in.seekg(0);

    char* metadata = new(std::nothrow) char[image.contentStart + 1];

    if (!metadata) {
        std::cerr << "Error metadata!" << std::endl;
        out.close();
        return false;
    }

    image.in.read(metadata, image.contentStart);
    out.write(metadata, image.contentStart);

    delete[] metadata;

    std::size_t imageWidth = image.columns * 3;
    std::size_t paddingLength = imageWidth % 4;

    for (std::uint32_t i = 0; i < image.rows; i++)
    {
        for (std::uint32_t j = 0; j < image.columns; j++) {
            Pixel pixel;

            image.in.read(reinterpret_cast<char*>(&pixel), sizeof(Pixel));
            toGrayscale(pixel);
            out.write(reinterpret_cast<const char*>(&pixel), sizeof(Pixel));
        }

        char* padding = new(std::nothrow) char[paddingLength + 1];
        if (!padding) {
            //...
        }

        image.in.read(padding, paddingLength);
        out.write(padding, paddingLength);

        delete[] padding;
    }

    out.close();

    return true;
}
