#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder
{
private:
	//a map container from the stl
	//that holds related pairs of String and Texture
	std::map<std::string, Texture> m_Textures;
	
	//A pointer of the same type as the class itself
	//the one and only instance
	static TextureHolder* m_s_Instance;

public:
	TextureHolder();
	static Texture& GetTexture(string const& filename);

};

#endif