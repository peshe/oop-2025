#include <iostream>
#include <fstream>
#include <cstdint>

void copy(std::ifstream& src, std::ofstream& dst)
{
	std::uint8_t byte;
	while(src.read((char*)&byte, sizeof(byte)))
		dst.write((const char*)&byte, sizeof(byte));
}

struct Patch
{
	std::uint16_t offset;
	std::uint8_t old_byte;
	std::uint8_t new_byte;
}; // it is important that there are no padding bytes!

bool apply_patch(std::ifstream& src, std::ofstream& dst, const Patch& p, std::uint16_t file_size)
{
	if(p.offset >= file_size)
		return false;
	src.seekg(p.offset, std::ios::beg);
	if(p.old_byte != src.get())
		return false;

	dst.seekp(p.offset, std::ios::beg);
	dst.write((const char*)&p.new_byte, sizeof(p.new_byte));
	return true;
}

bool apply_patches(std::ifstream& src, std::ofstream& dst, std::ifstream& fpatches, std::uint16_t file_size)
{
	Patch p;
	while(fpatches.read((char*)&p, sizeof(p)))
		if(!apply_patch(src, dst, p, file_size))
			return false;
	return true;
}

int main()
{
	std::ifstream ifs;
	ifs.open("f1.bin", std::ios::binary);
	if(!ifs)
	{
		std::cerr << "could not open f1.bin\n";
		return 1;
	}

	std::ofstream ofs;
	ofs.open("f2.bin", std::ios::binary);
	if(!ofs)
	{
		std::cerr << "could not open f2.bin\n";
		ifs.close();
		return 1;
	}

	copy(ifs, ofs);

	std::ifstream fpatches;
	fpatches.open("patch.bin", std::ios::binary);
	if(!fpatches)
	{
		ifs.close();
		ofs.close();
		std::cerr << "could not open patch.bin\n";
		return 1;
	}

	ifs.clear();
	if(!apply_patches(ifs, ofs, fpatches, ifs.tellg()))
	{
		ifs.close();
		ofs.close();
		fpatches.close();
		std::cerr << "could not apply patches\n";
		return 1;
	}

	ifs.close();
	ofs.close();
	fpatches.close();

	// all closes can be omitted and the files will still be correctly closed
	// we will see how this works later :)
	return 0;
}
