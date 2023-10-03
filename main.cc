#include <iostream>

int main() {
    /*image initialization*/
    int image_width = 256;
    int image_height = 256;

    /*render*/

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    //render for loop
    for (int i = 0; i < image_height; ++i) {
        std::clog << "\rScanlines remaining: " << (image_height - i) << ' ' << std::flush;
        for (int j = 0; j < image_width; ++j) {
            auto red = double(j)/ (image_width - 1);
            auto green = double(i) / (image_height - 1);
            auto blue = 0;

            int iRed = static_cast<int>(255.999 * red);
            int iGreen = static_cast<int>(255.999 * green);
            int iBlue = static_cast<int>(255.999 * blue);

            std::cout << iRed << ' ' << iGreen << ' ' << iBlue << '\n';
        }
    }
    std::clog << "\rDone.                 \n";
}