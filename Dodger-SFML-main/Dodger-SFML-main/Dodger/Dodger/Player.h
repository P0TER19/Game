#pragma once

#include <SFML/Graphics.hpp>

class Player
{
private:
	sf::Vector2f v_position;
	sf::Sprite s_sprite;
	float f_speed = 400.0f;
	char c_direction;
public:
	Player(float startX, float startY, sf::Texture& t_tex);
	sf::FloatRect getPosition();
	void moveLeft();
	void moveRight();
	void stop();
	void restart(float startX, float startY);
	void draw(sf::RenderWindow& window);
	void update(sf::Time dt, int sw);
};