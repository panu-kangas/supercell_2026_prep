#pragma once

#include <SFML/Graphics.hpp>

class Player;

class Platform
{
	public:

	Platform() = delete;
	Platform(sf::Vector2f position, sf::Vector2f size, float speed);

	void draw(sf::RenderTarget& target);
	void update(float dt);

	sf::RectangleShape& getShape() { return m_shape; };
	bool isPlayerOOB(Player* player);
	float getSpeed() { return m_speed; };

	private:

	sf::RectangleShape m_shape;
	float m_speed;

};