#pragma once

#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "Constants.h"


class Game;

class Player
{
	public:

	Player() = delete;
	Player(Game* gamePtr);

	void draw(sf::RenderTarget &target) const;
	void update(float deltaTime, InputData& inputData);

	void handleMovement(float deltaTime, InputData& inputData);


	private:

	sf::CircleShape m_shape;
	sf::Vector2f m_pos;
	float m_speed = PlayerSpeed;

	Game* m_gamePtr;

};