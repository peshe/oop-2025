#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <cstdint>

struct Pixel
{
	std::uint8_t red;
	std::uint8_t green;
	std::uint8_t blue;
};

void toGrayscale(Pixel& pixel);

#endif // !PIXEL_HPP
