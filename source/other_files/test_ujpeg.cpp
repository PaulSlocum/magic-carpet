#include <iostream>
#include <fstream>

#include "ujpeg.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " <input.jpg> <output.ppm>" << std::endl;
        return 2;
    }

    uJPEG uj;
    //uj.setChromaMode(UJ_CHROMA_MODE_FAST);
    uj.decodeFile(argv[1]);
    if (uj.bad()) {
        std::cerr << "uJPEG error #" << ujGetError() << std::endl;
        return 1;
    }

    std::ofstream f(argv[2], std::ios_base::binary);
    f << (uj.isColor() ? "P6\n" : "P5\n") << uj.getWidth() << " " << uj.getHeight() << "\n255\n";
    f.write((const char*) uj.getImage(), uj.getImageSize());
    f.close();

    return 0;
}
