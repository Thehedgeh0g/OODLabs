//
// Created by thehedgeh0g on 11.12.24.
//

#ifndef PPMHANDLER_H
#define PPMHANDLER_H
#include <fstream>
#include <string>

#include "Image.h"

class ImageService {
public:
    static void SaveToPPM(const std::string& filename, const Image& image) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            throw std::ios_base::failure("Failed to open file");
        }

        Size size = image.GetSize();

        // Write PPM header
        file << "P6\n" << size.width << " " << size.height << "\n255\n";

        // Write pixel data
        for (int y = 0; y < size.height; ++y)
        {
            for (int x = 0; x < size.width; ++x)
            {
                uint32_t color = image.GetPixel({x, y});

                uint8_t r = (color >> 16) & 0xFF;
                uint8_t g = (color >> 8) & 0xFF;
                uint8_t b = color & 0xFF;

                file.write(reinterpret_cast<char*>(&r), 1);
                file.write(reinterpret_cast<char*>(&g), 1);
                file.write(reinterpret_cast<char*>(&b), 1);
            }
        }

        file.close();
    }

    static Image LoadFromPPM(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            throw std::ios_base::failure("Failed to open file");
        }

        std::string format;
        file >> format;
        if (format != "P6") {
            throw std::runtime_error("Unsupported file format");
        }

        int width, height, maxColor;
        file >> width >> height >> maxColor;
        file.get(); // Consume the newline character

        if (maxColor != 255) {
            throw std::runtime_error("Unsupported max color value");
        }

        Image image({width, height});

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                unsigned char rgb[3];
                file.read(reinterpret_cast<char*>(rgb), 3);
                uint32_t color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
                image.SetPixel({x, y}, color);
            }
        }

        file.close();
        return image;
    }

    static void Print(const Image& img, std::ostream& out) {
        Size size = img.GetSize();
        for (int y = 0; y < size.height; ++y) {
            for (int x = 0; x < size.width; ++x) {
                char pixel = img.GetPixel({x, y});
                out.put(pixel);
            }
            out.put('\n');
        }
    }

    static Image LoadImage(const std::string& pixels)
    {
        std::istringstream s(pixels);
        Size size{};
        std::string line;
        while (std::getline(s, line))
        {
            size.width = std::max(size.width, static_cast<int>(line.length()));
            ++size.height;
        }

        Image img(size);

        s = std::istringstream(pixels);
        for (int y = 0; y < size.height; ++y)
        {
            if (!std::getline(s, line))
                break;

            int x = 0;
            for (char ch : line)
            {
                img.SetPixel({ x++, y }, ch);
            }
        }

        return img;
    }
};
#endif //PPMHANDLER_H
