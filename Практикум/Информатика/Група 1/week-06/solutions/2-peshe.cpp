#include <iostream>
#include <fstream>
#include <cstddef>

void copy(std::ifstream& src, std::ofstream& dst)
{
	char c;
	while(src.get(c))
		dst.put(c);
}

bool concat_files(const char* const* input_filenames, std::size_t input_files_cnt, const char* output_filename)
{
	std::ofstream ofile;
	ofile.open(output_filename);
	if(!ofile) return false;

	for(std::size_t i = 0; i < input_files_cnt; i++)
	{
		std::ifstream ifile;
		ifile.open(input_filenames[i]);
		if(!ifile)
		{
			ofile.close();
			return false;
		}
		copy(ifile, ofile);
		ifile.close();
	}

	ofile.close();
	return true;
}

bool copy_stdin(const char* output_filename)
{
	std::ofstream ofile;
	ofile.open(output_filename);
	if(!ofile) return false;

	char c;
	while(std::cin.get(c))
		ofile.put(c);
	return true;
}

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		std::cerr << "Usage: " << (argv[0] ? argv[0] : "<program name>") << " <input file>... <output file>\n";
		return 1;
	}
	if(argc > 2)
	{
		if(!concat_files(argv + 1, argc - 2, argv[argc - 1]))
		{
			std::cerr << "file concatenation failed\n";
			return 1;
		}
	}
	else
	{
		// const char* stdin[1] = {"/dev/stdin"};
		// if(!concat_files(stdin, 1, argv[argc-1])) // !!! non-portable -- only unix !!!
		if(!copy_stdin(argv[argc - 1]))
		{
			std::cerr << "file concatenation failed\n";
			return 1;
		}
	}
	return 0;
}