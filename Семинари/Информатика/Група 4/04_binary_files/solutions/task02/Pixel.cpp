#include "Pixel.hpp"

void toGrayscale(Pixel& pixel)
{
	std::uint8_t newValue = (pixel.red + pixel.blue + pixel.green) / 3;

	pixel.blue = pixel.green = pixel.red = newValue;
}
