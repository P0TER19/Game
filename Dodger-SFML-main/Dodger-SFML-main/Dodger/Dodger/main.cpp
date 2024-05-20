#include <SFML/Graphics.hpp>
#include <chrono>

#include "Texture.h"
#include "TextureManager.h"
#include "Player.h"
#include "Zombie.h"
#include "ZombieManager.h"

#define WIDTH 640
#define HEIGHT 480

#define ZOMBIE_COUNT 25

void spawnZombies(sf::RenderWindow& window)
{
	for (int i = 0; i < ZOMBIE_COUNT; i++)
		TheZombieManager::Instance()->add(window.getSize().x, TheTextureManager::Instance()->getTexture("zombie"));
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Dodger", sf::Style::Titlebar | sf::Style::Close);
	sf::Event event;
	
	TheTextureManager::Instance()->add("player", Texture("../graphics/player.png"));
	TheTextureManager::Instance()->add("zombie", Texture("../graphics/zombie.png"));

	Player player(window.getSize().x / 2, window.getSize().y - 25, TheTextureManager::Instance()->getTexture("player"));
	spawnZombies(window);

	int score = 0;
	int lastScore = score;
	int topScore = 0;

	sf::Font font;
	font.loadFromFile("../fonts/Marlboro.ttf");

	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(32);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setString("Score: 0");
	scoreText.setPosition(0, 0);

	sf::Text topText;
	topText.setFont(font);
	topText.setCharacterSize(32);
	topText.setFillColor(sf::Color::White);
	topText.setString("Top Score: 0");
	topText.setPosition(0, 30);

	sf::Text message;
	message.setFont(font);
	message.setCharacterSize(64);
	message.setFillColor(sf::Color::White);
	message.setString("PRESS 'R' TO RESTART");

	sf::FloatRect textCenter = message.getLocalBounds();
	message.setOrigin(textCenter.left + textCenter.width / 2, textCenter.top + textCenter.height / 2);
	message.setPosition(WIDTH / 2, HEIGHT / 2);

	sf::Clock clock;

	auto now = std::chrono::system_clock::now() + std::chrono::seconds(1);

	bool paused = false;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		if (!paused)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				player.moveLeft();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				player.moveRight();
			else
				player.stop();

			if (now <= std::chrono::system_clock::now())
			{
				score++;
				now = std::chrono::system_clock::now() + std::chrono::seconds(1);
			}

			if (lastScore != score)
			{
				lastScore = score;
				scoreText.setString("Score: " + std::to_string(score));
			}

			if (TheZombieManager::Instance()->collision(player.getPosition()))
			{
				paused = true;
				if (score > topScore)
					topScore = score;
				topText.setString("Top Score: " + std::to_string(topScore));
			}

			sf::Time dt = clock.restart();

			player.update(dt, window.getSize().x);
			// Isnt really good to send texture again in update, seems a little bit complicated
			for (int i = 0; i < ZOMBIE_COUNT; i++)
				TheZombieManager::Instance()->update(dt, window.getSize().x, window.getSize().y, TheTextureManager::Instance()->getTexture("zombie"));
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				paused = false;
				TheZombieManager::Instance()->clear();
				spawnZombies(window);
				player.restart(window.getSize().x / 2, window.getSize().y - 25);
				score = 0;
			}
		}

		window.clear(sf::Color::Black);

		player.draw(window);
		for (int i = 0; i < ZOMBIE_COUNT; i++)
			TheZombieManager::Instance()->draw(window);

		window.draw(scoreText);
		window.draw(topText);

		if (paused)
			window.draw(message);

		window.display();
	}

	return 0;
}