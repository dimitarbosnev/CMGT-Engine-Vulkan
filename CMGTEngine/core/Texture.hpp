#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#pragma once
#include <map>
#include <string>
using namespace std;
namespace cmgt {
	class Texture
	{
	public:
		static Texture* load(const string& pTexturePath);

		//GLuint getId();

	protected:
		Texture();
		virtual ~Texture();

		static Texture* _loadFromFile(const string pTexturePath);

		//OpenGL id for texture buffer
		//GLuint _id;
	};
}
#endif // TEXTURE_HPP
