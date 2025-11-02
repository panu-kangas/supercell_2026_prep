#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "ResourceManager.h"
#include "InputHandler.h"
#include "Player.h"


Game::Game(sf::RenderWindow& window) :
    m_state(State::START_SCREEN),
	m_window(window),
    m_pPlayer(std::make_unique<Player>(this))

{
    m_pGameInput = std::make_unique<GameInput>(this, m_pPlayer.get());
}

Game::~Game()
{
}

bool Game::initialise()
{
    /*
        PAY ATTENTION HIVER!
            If you want to load any assets (fonts, textures) please use the pattern shown below
    */

    if (!m_font.loadFromFile(ResourceManager::getFilePath("Lavigne.ttf")))
    {
        std::cerr << "Unable to load font" << std::endl;
        return false;
    }

	m_floor.setSize({ScreenWidth, FloorLevel});
	m_floor.setPosition({0, ScreenHeight - m_floor.getSize().y});
	m_floor.setFillColor(FloorColor);
    

    return true;
}

void Game::resetGame()
{
    
}

void Game::update(float deltaTime)
{
    
	
	m_pPlayer->update(deltaTime, getInputData());

	handleCameraShake();

	/*switch (m_state)
    {
		case State::START_SCREEN:
		{
			
			break ;
		}
            
        case State::ACTIVE:
        {
			
			break ;
        }

		case State::GAME_OVER:
		{
			
			break ;
		}

        break;
    } */

}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(m_floor);
	m_pPlayer->draw(target);
}

void Game::handleCameraShake()
{
	if (!m_isCameraShaking)
		return ;

	if (m_shakeIdx == m_shakeOffsets.size())
	{
		m_shakeIdx = 0;
		m_isCameraShaking = false;
		m_window.setView(m_window.getDefaultView());
		return ;
	}
	
	sf::View view = m_window.getDefaultView();
	sf::Vector2f offset = m_shakeOffsets[m_shakeIdx];
	view.move(offset);
	m_window.setView(view);

	m_shakeIdx++;
}


void Game::onKeyPressed(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyPressed(key);
}

void Game::onKeyReleased(sf::Keyboard::Key key)
{
    m_pGameInput->onKeyReleased(key);
}

