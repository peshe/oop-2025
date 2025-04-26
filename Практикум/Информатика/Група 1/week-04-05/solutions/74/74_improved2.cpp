#include <iostream>
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

bool createTemporary(std::fstream& file, const char* name) {
	file.open(name, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
	if(!file) {
		return false;
	}
	std::filesystem::remove(name);
	return true;
}

void sortAndWriteArray(std::uint32_t* arr, size_t size, std::fstream& fileRead, std::fstream& fileWrite) {
	fileRead.read((char*)arr, size * sizeof(std::uint32_t));
	std::qsort(arr, size, sizeof(std::uint32_t), cmpLess_uint32);
	fileWrite.write((const char*)arr, size * sizeof(std::uint32_t));
}

class input_filebuf_iterator_uint32
{
	std::fstream* file;
	std::uint32_t val;

	void readNext()
	{
		file->read(reinterpret_cast<char*>(&val), sizeof(val));
		if(!*file) file = nullptr;
	}
public:
	input_filebuf_iterator_uint32(): file(nullptr) {}
	input_filebuf_iterator_uint32(std::fstream& file): file(&file)
	{
		readNext();
	}
	std::uint32_t operator*() const
	{
		return val;
	}
	input_filebuf_iterator_uint32& operator++() // prefix
	{
		readNext();
		return *this;
	}
	input_filebuf_iterator_uint32 operator++(int dummy) // postfix
	{
		input_filebuf_iterator_uint32 old = *this;
		++*this;
		return old;
	}

	bool operator==(const input_filebuf_iterator_uint32& rhs) const
	{
		return file == rhs.file;
	}
	bool operator!=(const input_filebuf_iterator_uint32& rhs) const
	{
		return !(*this == rhs);
	}
};

class output_filebuf_iterator_uint32
{
	std::fstream* file;
public:
	output_filebuf_iterator_uint32(std::fstream& file): file(&file) {}
	output_filebuf_iterator_uint32& operator=(std::uint32_t val)
	{
		file->write(reinterpret_cast<const char*>(&val), sizeof(val));
		return *this;
	}
	output_filebuf_iterator_uint32& operator*()
	{
		return *this;
	}
	output_filebuf_iterator_uint32& operator++()
	{
		return *this;
	}
	output_filebuf_iterator_uint32 operator++(int)
	{
		return *this;
	}
};

// note that the body of this function is *exactly* the same as in
// https://github.com/StanimirSP/ip_pract_inf-1-2024-2025/blob/main/week-A/solutions/task02.cpp
output_filebuf_iterator_uint32 copy(input_filebuf_iterator_uint32 first, input_filebuf_iterator_uint32 last,
									output_filebuf_iterator_uint32 dest)
{
	for(; first != last; first++, dest++)
		*dest = *first;
	return dest;
}

// note that the body of this function is *exactly* the same as in
// https://github.com/StanimirSP/ip_pract_inf-1-2024-2025/blob/main/week-A/solutions/task02.cpp
output_filebuf_iterator_uint32 merge(input_filebuf_iterator_uint32 first1, input_filebuf_iterator_uint32 last1,
									 input_filebuf_iterator_uint32 first2, input_filebuf_iterator_uint32 last2,
									 output_filebuf_iterator_uint32 dest, int cmp(std::uint32_t, std::uint32_t))
{
	while(first1 != last1 && first2 != last2)
		if(cmp(*first1, *first2))
			*dest++ = *first1++;
		else
			*dest++ = *first2++;

	// at this point either first1 == last1 or first2 == last2, i.e. at least one of [first1, last1) and [first2, last2) is empty
	// therefore one of the next 2 calls of copy will do nothing and return immediately
	dest = copy(first1, last1, dest);
	dest = copy(first2, last2, dest);
	return dest;
}

// previously used `merge` function left here for comparison only
/*void merge(std::fstream& file, std::fstream& leftFile, std::fstream& rightFile) {
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
}*/

int less(std::uint32_t a, std::uint32_t b)
{
	return a < b;
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		std::cerr << "Usage: " << (argv[0] ? argv[0] : "<program name>") << " <file to sort>\n";
		return 1;
	}
	std::fstream file(argv[1], std::ios::in | std::ios::out | std::ios::binary);
	if(!file) {
		std::cout << "Unable to open file.\n";
		return 1;
	}
	size_t size = fileSize(file);
	if((size % sizeof(std::uint32_t))) {
		std::cout << "Error.\n";
		return 1;
	}
	size /= sizeof(std::uint32_t);
	size_t halfSize = size / 2;

	std::fstream temp1, temp2;
	char tmp1_name[64], tmp2_name[64];
	random_hexnumber(tmp1_name, 32);
	random_hexnumber(tmp2_name, 32);
	if(!createTemporary(temp1, tmp1_name) || !createTemporary(temp2, tmp2_name)) { // think of better ways to choose names for temporary files
																						// so that it is impossible (or almost impossible, e.g. the probability is less than 2^(-128)) to collide with existing files
		std::cout << "Error with opening temp files.\n";
		return 1;
	}
	std::uint32_t* arr;
	try {
		arr = new std::uint32_t[halfSize + 1];
	}
	catch(const std::bad_alloc& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}


	sortAndWriteArray(arr, halfSize, file, temp1);
	sortAndWriteArray(arr, size - halfSize, file, temp2);
	delete[] arr;

	temp1.seekp(0, std::ios::beg);
	temp2.seekp(0, std::ios::beg);
	file.seekp(0, std::ios::beg);
	//merge(file, temp1, temp2);
	merge(input_filebuf_iterator_uint32(temp1), input_filebuf_iterator_uint32(),
		  input_filebuf_iterator_uint32(temp2), input_filebuf_iterator_uint32(),
		  output_filebuf_iterator_uint32(file), less);

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
