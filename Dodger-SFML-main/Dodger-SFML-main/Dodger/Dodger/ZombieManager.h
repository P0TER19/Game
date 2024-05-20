#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Zombie.h"

class ZombieManager
{
private:
	static ZombieManager* s_instance;
	std::vector<Zombie> zombies;
	ZombieManager() {};
	~ZombieManager();
public:
	static ZombieManager* Instance()
	{
		if (s_instance == nullptr)
			s_instance = new ZombieManager;

		return s_instance;
	}
	bool collision(sf::FloatRect position);
	void add(int sw, sf::Texture& t_tex);
	void clear();
	void draw(sf::RenderWindow& window);
	void update(sf::Time dt, int sw, int sh, sf::Texture& t_tex);
};

typedef ZombieManager TheZombieManager;