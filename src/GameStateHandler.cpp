#include "GameStateHandler.h"
#include "StartScreen.h"
#include "IntroScreen.h"


GameStateHandler::GameStateHandler(Game* gamePtr)
{
	m_curState = std::make_unique<StartScreen>(gamePtr);
	m_state = State::START_SCREEN;
	m_gamePtr = gamePtr;
}

void GameStateHandler::setNextState()
{
	switch(m_state)
	{
		case State::START_SCREEN:
		{
			m_curState = std::make_unique<IntroScreen>(m_gamePtr);
			m_state = State::INTRO;
			break ;
		}

		case State::INTRO:
		{
			break ;
		}

		case State::RUN:
		{
			break ;
		}


		case State::END_SCREEN:
		{
			break ;
		}

		default:
		{
			break ;
		}
	}
}
