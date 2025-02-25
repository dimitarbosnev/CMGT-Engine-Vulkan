#include <iostream>
#include <string>
#include <stb_image.h>
#include <doctest/doctest.h>
#include "minimal/glm.h"
#include "core/Texture.h"
#include "vulkan-api/VulkanInstance.h"
#include "vulkan-api/GLFW_Window.h"
TEST_SUITE("Texture Object Tests") {
    TEST_CASE("PNG Texture") {
        std::string filePath = "test/assets/Background3.png";
        int  width, height, channels;
        stbi_uc* data = stbi_load(filePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);
        if (data) {
            std::cout << "Image loaded successfully!\n";
            std::cout << "Width: " << width << ", Height: " << height << ", Channels: " << channels << "\n";
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

                image[i] = glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);  // Normalize to [0, 1] range
            }
            // Free the image memory after use
            stbi_image_free(data);
        } else {
            std::cerr << "Failed to load image\n";
        }
    }

    TEST_CASE("Texture Builder Test") {
        std::string filePath = "test/assets/Background3.png";
        cmgt::Texture::Builder builder;
        builder.loadImage(filePath);
    }

    TEST_CASE("Load Texture in Vulkan") {
        cmgt::GLFWindow window(0,0,"Test");
        cmgt::VulkanInstance instance;
        std::string filePath = "test/assets/Background3.png";
        cmgt::Texture::Builder builder;
        builder.loadImage(filePath);
    }
}