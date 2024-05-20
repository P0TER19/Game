#pragma once

#include <SFML/Graphics.hpp>

class Texture
{
private:
	sf::Texture t_tex;
public:
	Texture(const char* path);
	sf::Texture& getTexture();
};