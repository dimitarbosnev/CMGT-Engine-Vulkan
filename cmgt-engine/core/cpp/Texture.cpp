#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <string>
#include <stb_image.h>
#include "core/Texture.h"
#include "minimal/log.h"
namespace cmgt {
    Texture::Texture(Builder& builder) {
        
    }

    Texture::~Texture()
    {
    }

    void Texture::Builder::loadImage(const std::string& filePath){

        stbi_uc* data = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
        if (data) {
            Log::msg("Image loaded successfully!");
            std::stringstream ss;
            ss << "Width: " << width << ", Height: " << height << ", Channels: " << channels;
            Log::msg(ss.str());
            std::vector<glm::vec4> image(height*width);
            for (int i = 0; i < height*width; i++) {
                int x = i % height;
                int y = i / height;

                // Calculate the index of the pixel (each pixel has 3 or 4 components depending on channels)
                int index = (x * height + y) * channels;

                // Extract the RGB values (assuming the image has at least 3 channels)
                unsigned char r = data[index    ];      // Red channel
                unsigned char g = data[index + 1];      // Green channel
                unsigned char b = data[index + 2];      // Blue channel
                unsigned char a = data[index + 3];      // Alpha channel 

                // Store the RGB values in a glm::vec4

                pixels[i] = glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);  // Normalize to [0, 1] range
            }
            move(image.begin(), image.end(), back_inserter(pixels));
            // Free the image memory after use
            stbi_image_free(data);
        } else {
            Log::error("Failed to load image");
        }
    }
}









