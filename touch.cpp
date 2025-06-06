#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        if (!fs::exists(argv[i])) std::ofstream ofs(argv[i]);
    }

    return 0;
}
