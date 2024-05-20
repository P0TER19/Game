#include "ZombieManager.h"

ZombieManager* ZombieManager::s_instance = nullptr;

bool ZombieManager::collision(sf::FloatRect position)
{
	for (auto it = zombies.begin(); it != zombies.end();)
	{
		if (it->getPosition().intersects(position))
			return true;
		else
			it++;
	}

	return false;
}

void ZombieManager::add(int sw, sf::Texture& t_tex)
{
	zombies.push_back(Zombie(sw, t_tex));
}

void ZombieManager::clear()
{
	zombies.clear();
}

void ZombieManager::draw(sf::RenderWindow& window)
{
	for (Zombie& z : zombies)
		z.draw(window);
}

void ZombieManager::update(sf::Time dt, int sw, int sh, sf::Texture& t_tex)
{
	for (Zombie& z : zombies)
		z.update(dt, sh);

	for (auto it = zombies.begin(); it != zombies.end();)
	{
		if (it->getRespawn())
		{
			it = zombies.erase(it);
			zombies.push_back(Zombie(sw, t_tex));
		}
		else
			it++;
	}
}

ZombieManager::~ZombieManager()
{
	delete s_instance;
}