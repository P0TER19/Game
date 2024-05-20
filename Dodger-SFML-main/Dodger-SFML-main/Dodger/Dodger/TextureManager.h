#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "Texture.h"

class TextureManager
{
private:
	static TextureManager* s_instance;
	std::map<std::string, sf::Texture> textureMap;
	TextureManager() {};
	~TextureManager();
public:
	static TextureManager* Instance()
	{
		if (s_instance == nullptr)
			s_instance = new TextureManager;

		return s_instance;
	}
	void add(std::string id, Texture t_tex);
	sf::Texture& getTexture(std::string id);
};

typedef TextureManager TheTextureManager;