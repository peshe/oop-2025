#ifndef BMP_IMAGE_HPP
#define BMP_IMAGE_HPP

#include <cstdint>
#include <fstream>

struct BMP_Image
{
	std::uint32_t size;
	std::uint32_t contentStart;
	std::uint32_t columns;
	std::uint32_t rows;
	std::ifstream in;
};

bool loadImage(BMP_Image& image, const char fileName[]);

bool convertToGrayScale(BMP_Image& image, const char outputFileName[]);

#endif // !BMP_IMAGE_HPP
