#include "pch.h"
#include "TextureHolder.h"

//include the "assert features"
#include <assert.h>

TextureHolder* TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
	assert(m_s_Instance == nullptr);
	m_s_Instance = this;
}

sf::Texture& TextureHolder::GetTexture(std::string const& filename)
{
	//get a reference to m_Textures using m_s_Instance
	auto& m = m_s_Instance->m_Textures;
	//auto is the equivilent of map<string, Texture>

	//create an iterator to hold a key-value-pair (kvp)
	//and seach for the required kvp
	//using the passed in filename
	auto keyValuePair = m.find(filename);
	//auto is equiv of map<string, Texture>::iterator
	//Did e find a match?
	if (keyValuePair != m.end())
	{
		//yes
		//return the texture,
		//the second part of the kvp, the texture
		return keyValuePair->second;
	}
	else
	{
		//filename not found
		//create a new key value pair using the filename
		auto& texture = m[filename];
		//load the texture from file in the usual way
		texture.loadFromFile(filename);

		//return the texture to the calling code
		return texture;
	}
}