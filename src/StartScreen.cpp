#include "StartScreen.h"
#include "Game.h"
#include "Constants.h"

#include <iostream>

StartScreen::StartScreen(Game* gamePtr) : GameStateBase(gamePtr), m_font(gamePtr->getFont())
{

	m_headerText.setFont(*gamePtr->getFont());
	m_headerText.setCharacterSize(50.f);
	m_headerText.setString("Run baby, run");

	m_midText.setFont(*m_font);
	m_midText.setCharacterSize(30.f);
	m_midText.setString("Press Enter to start the game");

}

void StartScreen::handleInput(InputData& inputData)
{
	if (inputData.m_enter)
	{
		m_isReady = true;
	}
}


void StartScreen::update(float dt, InputData& inputData)
{
	m_headerText.setPosition(ScreenWidth / 2 - m_headerText.getLocalBounds().width / 2, 70.f);
	m_midText.setPosition(ScreenWidth / 2 - m_midText.getLocalBounds().width / 2, ScreenHeight / 2);
	handleInput(inputData);
}

void StartScreen::draw(sf::RenderTarget& target)
{
	target.draw(m_headerText);
	target.draw(m_midText);
}