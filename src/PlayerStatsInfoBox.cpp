#include "PlayerStatsInfoBox.h"
#include "Constants.h"
#include "Player.h"
#include "Game.h"

PlayerStatsInfoBox::PlayerStatsInfoBox(Game *gamePtr, Player* playerPtr)
{
	m_gamePtr = gamePtr;
	m_playerPtr = playerPtr;
	m_font = m_gamePtr->getFont();

	m_statsBox.setSize({350, 150});
	m_statsBox.setPosition({20, ScreenHeight - m_statsBox.getSize().y - 20});
	m_statsBox.setOutlineThickness(4.f);
	m_statsBox.setOutlineColor(sf::Color::Black);
	m_statsBox.setFillColor(FloorColor);

	m_jumpLoadBar.setSize({0, 30});
	m_jumpLoadBar.setFillColor(sf::Color::Red);
	m_jumpLoadBar.setPosition({100, 100});
}


void PlayerStatsInfoBox::updateJumpLoadBar()
{
	if (!m_playerPtr->isLoadingTurboJump())
	{
		if (m_jumpLoadBar.getSize().x > 0)
			m_jumpLoadBar.setSize({0, m_jumpLoadBar.getSize().y});
		if (m_jumpLoadBar.getFillColor() != sf::Color::Red)
			m_jumpLoadBar.setFillColor(sf::Color::Red);
		return;
	}

	float loadBarMaxLength = 200.f;
	float barLength = (m_playerPtr->getTurboJumpLoadTime() / TurboJumpLoadTime) * loadBarMaxLength;
	if (barLength >= loadBarMaxLength)
	{
		barLength = loadBarMaxLength;
		m_jumpLoadBar.setFillColor(sf::Color::Green);
	}
	m_jumpLoadBar.setSize({barLength, m_jumpLoadBar.getLocalBounds().height});
}