#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once
#include <map>
#include <string>

namespace cmgt {
	class Texture
	{
	public:
		static Texture* load(const std::string& pTexturePath);

		//GLuint getId();

	protected:
		Texture();
		virtual ~Texture();

		static Texture* _loadFromFile(const std::string pTexturePath);

		//OpenGL id for texture buffer
		//GLuint _id;
	};
}
#endif // TEXTURE_H
