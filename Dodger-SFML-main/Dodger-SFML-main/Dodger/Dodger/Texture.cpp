#include "Texture.h"

Texture::Texture(const char* path)
{
	t_tex.loadFromFile(path);
}

sf::Texture& Texture::getTexture()
{
	return t_tex;
}