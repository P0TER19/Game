#include "Player.h"

Player::Player(float startX, float startY, sf::Texture& t_tex)
{
	c_direction = 0;

	v_position.x = startX;
	v_position.y = startY;

	s_sprite.setTexture(t_tex);
	s_sprite.setOrigin(s_sprite.getLocalBounds().left + s_sprite.getLocalBounds().width / 2,
		s_sprite.getLocalBounds().top + s_sprite.getLocalBounds().height / 2);
	s_sprite.setPosition(v_position);
}

sf::FloatRect Player::getPosition()
{
	return s_sprite.getGlobalBounds();
}

void Player::moveLeft()
{
	c_direction = -1;
}

void Player::moveRight()
{
	c_direction = 1;
}

void Player::stop()
{
	c_direction = 0;
}

void Player::restart(float startX, float startY)
{
	v_position.x = startX;
	v_position.y = startY;
	s_sprite.setPosition(v_position);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(s_sprite);
}

void Player::update(sf::Time dt, int sw)
{
	if (c_direction ==  -1)
	{
		v_position.x -= f_speed * dt.asSeconds();
	}
	if (c_direction == 1)
	{
		v_position.x += f_speed * dt.asSeconds();
	}

	if (v_position.x < s_sprite.getLocalBounds().width / 2) v_position.x = s_sprite.getLocalBounds().width / 2;
	if (v_position.x > sw - s_sprite.getLocalBounds().width / 2) v_position.x = sw - s_sprite.getLocalBounds().width / 2;

	s_sprite.setPosition(v_position);
}
