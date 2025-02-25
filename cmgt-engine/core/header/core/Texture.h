#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once
#include <map>
#include <string>
#include "core/Object.h"
#include "vulkan-api/VulkanImage.h"
namespace cmgt {
	class Texture : public Object
	{
	public:
	struct Builder {
		public:
			std::vector<glm::vec4> pixels{};

			int width = 0;
			int height = 0;
			int channels = 0;
			uint32_t layers;
			void loadImage(const std::string& filePath);
		};

	public:
		Texture(Builder& builder);
		~Texture();

	private:
	};
}
#endif // TEXTURE_H
