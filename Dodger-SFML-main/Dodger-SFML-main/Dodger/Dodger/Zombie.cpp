#include "Zombie.h"
#include <random>

Zombie::Zombie(int sw, sf::Texture& t_tex)
{
	s_sprite.setTexture(t_tex);
	s_sprite.setOrigin(s_sprite.getLocalBounds().left + s_sprite.getLocalBounds().width / 2,
		s_sprite.getLocalBounds().top + s_sprite.getLocalBounds().height / 2);

	std::random_device rd;
	std::mt19937 gen(rd());
	float x1 = s_sprite.getLocalBounds().width / 2;
	float x2 = sw - s_sprite.getLocalBounds().width / 2;
	std::uniform_real_distribution<float> spawnX(x1, x2);
	std::uniform_real_distribution<float> spawnY(-1000, -10);
	std::uniform_real_distribution<float> scale(0.5f, 1.0f);

	v_position.x = spawnX(gen);
	v_position.y = spawnY(gen);

	float randomScale = scale(gen);
	s_sprite.setScale(sf::Vector2f(randomScale, randomScale));
	s_sprite.setPosition(v_position);

	b_respawn = false;
}

bool Zombie::getRespawn()
{
	return b_respawn;
}

sf::FloatRect Zombie::getPosition()
{
	return s_sprite.getGlobalBounds();
}

void Zombie::draw(sf::RenderWindow& window)
{
	window.draw(s_sprite);
}

void Zombie::update(sf::Time dt, int sh)
{
	v_position.y += f_speed * dt.asSeconds();

	if (v_position.y > sh + s_sprite.getLocalBounds().height / 2)
		b_respawn = true;

	s_sprite.setPosition(v_position);
}
