#pragma once

#include <SFML/Graphics.hpp>

class Zombie
{
private:
	sf::Vector2f v_position;
	sf::Sprite s_sprite;
	float f_speed = 5.0f;
	bool b_respawn;
public:
	Zombie(int sw, sf::Texture& t_tex);
	sf::FloatRect getPosition();
	bool getRespawn();
	void draw(sf::RenderWindow& window);
	void update(sf::Time dt, int sh);
};