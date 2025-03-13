#include <iostream>



int main(int argc, const char** argv) {
    std::cout << "Argument Count: " << argc << std::endl;

    
    for (int i = 0; i < argc; ++i) {
        std::cout << "Argument " << i + 1 << ": " << argv[i] << std::endl;
    }


    return 0;
}
