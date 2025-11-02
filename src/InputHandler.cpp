#include "Constants.h"
#include "InputHandler.h"

#include <iostream>

GameInput::GameInput(Game* pGame, Player* pPlayer) :
    m_pGame(pGame), m_pPlayer(pPlayer)
{
}

GameInput::~GameInput()
{
    
}


void GameInput::onKeyPressed(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_inputData.m_up = true;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_down = true;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_left = true;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_right = true;
    }
    else if (key == sf::Keyboard::E)
    {
        m_inputData.m_ePress = true;
    }
	else if (key == sf::Keyboard::W)
    {
        m_inputData.m_wPress = true;
    }
	else if (key == sf::Keyboard::Enter)
    {
        m_inputData.m_enter = true;
    }

}

void GameInput::onKeyReleased(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Up)
    {
        m_inputData.m_up = false;
		m_inputData.m_upHold = false;
    }
    else if (key == sf::Keyboard::Down)
    {
        m_inputData.m_down = false;
		m_inputData.m_downHold = false;
    }
    else if (key == sf::Keyboard::Left)
    {
        m_inputData.m_left = false;
    }
    else if (key == sf::Keyboard::Right)
    {
        m_inputData.m_right = false;
    }
    else if (key == sf::Keyboard::E)
    {
        m_inputData.m_ePress = false;
		m_inputData.m_eHold = false;
    }
	else if (key == sf::Keyboard::W)
    {
        m_inputData.m_wPress = false;
		m_inputData.m_wHold = false;
    }
	else if (key == sf::Keyboard::Enter)
    {
        m_inputData.m_enter = false;
		m_inputData.m_enterHold = false;
    }
}

bool GameInput::isEnterPressed()
{
	return false;
}

bool GameInput::isDownPressed()
{
	if (m_inputData.m_down && !m_inputData.m_downHold)
	{
		m_inputData.m_downHold = true;
		return true;
	}

	return false;
}

bool GameInput::isUpPressed()
{
	if (m_inputData.m_up && !m_inputData.m_upHold)
	{
		m_inputData.m_upHold = true;
		return true;
	}

	return false;
}