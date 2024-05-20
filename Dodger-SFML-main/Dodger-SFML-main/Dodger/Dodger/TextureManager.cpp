#include "TextureManager.h"

TextureManager* TextureManager::s_instance = nullptr;

void TextureManager::add(std::string id, Texture t_tex)
{
	textureMap[id] = t_tex.getTexture();
}

sf::Texture& TextureManager::getTexture(std::string id)
{
	return textureMap[id];
}

TextureManager::~TextureManager()
{
	delete s_instance;
}