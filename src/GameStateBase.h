#pragma once

#include <SFML/Graphics.hpp>
#include "InputHandler.h"

class Game;

class GameStateBase
{
	public:

	GameStateBase() = delete;
	GameStateBase(Game* gamePtr) { m_gamePtr = gamePtr; };
	virtual ~GameStateBase() = default;

	virtual void update(float dt, InputData& inputData) = 0;
    virtual void draw (sf::RenderTarget& target) = 0;

	bool isReady() { return m_isReady; };

	protected:

	Game* m_gamePtr;
	bool m_isReady{false};

};