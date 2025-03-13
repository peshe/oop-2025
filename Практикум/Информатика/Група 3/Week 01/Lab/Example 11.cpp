#include <iostream>



// `argc` - ARGument Count
// `argv` - ARGument Vector



int main(int argc, char* argv[]) {
    std::cout << "Argument Count: " << argc << std::endl;


    std::cout << "The arguments are: " << std::endl;

    for (int i = 0; i < argc; ++i) {
        std::cout << "Argument " << i + 1 << ": " << argv[i] << std::endl;
    }


    return 0;
}
