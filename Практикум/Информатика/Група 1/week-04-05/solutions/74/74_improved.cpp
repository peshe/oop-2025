#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <new>
#include <filesystem>

size_t fileSize(std::fstream& file) {
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	file.seekg(0, std::ios::beg);
	return size;
}

int cmpLess_uint32(const void* a, const void* b) // callback for std::qsort
{
	std::uint32_t p = *(const std::uint32_t*)a;
	std::uint32_t q = *(const std::uint32_t*)b;
	return (p > q) - (p < q);
}

void random_hexnumber(char* buf, size_t chars)
{
	static const char charset[] = "0123456789ABCDEF";
	constexpr std::size_t charset_len = sizeof(charset) / sizeof(charset[0]) - 1;
	for(std::size_t i = 0; i < chars; i++)
		buf[i] = charset[rand() % charset_len];
	buf[chars] = '\0';
}

bool createTemporary(std::fstream& file) {
	char temp_name[64];
	random_hexnumber(temp_name, 32);
	random_hexnumber(temp_name, 32);
	file.open(temp_name, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
	std::filesystem::remove(temp_name);
	return (bool)file;
}

void sortAndWriteArray(std::uint32_t* arr, size_t size, std::fstream& fileRead, std::fstream& fileWrite) {
	fileRead.read((char*)arr, size * sizeof(std::uint32_t));
	std::qsort(arr, size, sizeof(std::uint32_t), cmpLess_uint32);
	fileWrite.write((const char*)arr, size * sizeof(std::uint32_t));
}

void merge(std::fstream& file, std::fstream& leftFile, std::fstream& rightFile) {
	std::uint32_t left;
	std::uint32_t right;
	leftFile.read((char*)&left, sizeof(left));
	rightFile.read((char*)&right, sizeof(right));
	while(leftFile && rightFile) {
		if(left > right) {
			file.write((const char*)&right, sizeof(right));
			rightFile.read((char*)&right, sizeof(right));
		}
		else {
			file.write((const char*)&left, sizeof(left));
			leftFile.read((char*)&left, sizeof(left));
		}
	}
	while(leftFile) {
		file.write((const char*)&left, sizeof(left));
		leftFile.read((char*)&left, sizeof(left));
	}
	while(rightFile) {
		file.write((const char*)&right, sizeof(right));
		rightFile.read((char*)&right, sizeof(right));
	}
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cerr << "Usage: " << (argv[0] ? argv[0] : "<program name>") << " <file to sort>\n";
		return 1;
	}
	std::fstream file;
	file.open(argv[1], std::ios::in | std::ios::out | std::ios::binary);
	if(!file) {
		std::cout << "Unable to open file.\n";
		return 1;
	}
	size_t size = fileSize(file);
	if((size % sizeof(std::uint32_t))) {
		std::cout << "Error.\n";
		file.close();
		return 1;
	}
	size /= sizeof(std::uint32_t);
	size_t halfSize = size / 2;

	std::fstream temp1, temp2;
	if(!createTemporary(temp1) || !createTemporary(temp2)) {
		std::cout << "Error with opening temp files.\n";
		file.close();
		temp1.close();
		temp2.close(); // note that opening temp2 may have never been attempted (if opening file1 failed)
					   // nevertheless, closing it is safe (closing a stream which is not open does nothing)
		return 1;
	}
	std::uint32_t* arr = new(std::nothrow) std::uint32_t[halfSize + 1];
	if(!arr) {
		std::cout << "Unable to reserve memory for array.\n";
		file.close();
		temp1.close();
		temp2.close();
		return 1;
	}

	sortAndWriteArray(arr, halfSize, file, temp1);
	sortAndWriteArray(arr, size - halfSize, file, temp2);
	delete[] arr;

	temp1.seekp(0, std::ios::beg);
	temp2.seekp(0, std::ios::beg);
	file.seekp(0, std::ios::beg);
	merge(file, temp1, temp2);

	file.close();
	temp1.close();
	temp2.close();
	return 0;
}

/*
Note that most systems are little endian. If this is the case, after sorting (task74.bin)

00000000: 5d8c 0444 5f10 410a 1555 a83c 8e2f 01e0  ]..D_.A..U.<./..
00000010: 85d2 4cae 4d7a 6632 fc0e 005d 2a7a 5a9c  ..L.Mzf2...]*zZ.
00000020: 4710 e047 6cfd f76d                      G..Gl..m

the result will be

		  LSB of the first uint32
		  ||
------------------- MSB of the first uint32
		  ||     ||
00000000: 5f10 410a 4d7a 6632 1555 a83c 5d8c 0444  _.A.Mzf2.U.<]..D
00000010: 4710 e047 fc0e 005d 6cfd f76d 2a7a 5a9c  G..G...]l..m*zZ.
00000020: 85d2 4cae 8e2f 01e0                      ..L../..

Indeed, the least uint32 is 0x0a41105f and the greatest is 0xe0012f8e

*/
