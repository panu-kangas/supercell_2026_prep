#include "IntroScreen.h"

IntroScreen::IntroScreen(Game* gamePtr) : GameStateBase(gamePtr)
{
	m_pPlayer = std::make_unique<Player>(gamePtr);

	m_floor.setSize({ScreenWidth, FloorLevel});
	m_floor.setPosition({0, ScreenHeight - m_floor.getSize().y});
	m_floor.setFillColor(FloorColor);
}

void IntroScreen::update(float dt, InputData& inputData)
{
	m_pPlayer->update(dt, inputData);

	if (inputData.m_ePress)
		m_isReady = true;
}


void IntroScreen::draw(sf::RenderTarget& target)
{
	target.draw(m_floor);
	m_pPlayer->draw(target);
}