#pragma once

#include <memory>

#include "GameStateBase.h"

struct InputData;
class Game;

enum class State
{
	START_SCREEN,
	INTRO,
	RUN,
	END_SCREEN
};


class GameStateHandler
{
	
	enum class State
	{
		START_SCREEN,
		INTRO,
		RUN,
		END_SCREEN
	};

	public:

	GameStateHandler() = delete;
	GameStateHandler(Game* gamePtr);

	void update(float dt, InputData& inputData) { m_curState->update(dt, inputData); };
	void draw(sf::RenderTarget& target) { m_curState->draw(target); };

	bool isStateReady() { return m_curState->isReady(); };
	void setNextState();

	private:

	std::unique_ptr<GameStateBase> m_curState;
	Game* m_gamePtr;
	State m_state;

};