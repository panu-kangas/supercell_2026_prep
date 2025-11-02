#pragma once

#include <SFML/Graphics.hpp>

class Game;
class Player;

class PlayerStatsInfoBox
{
	public:

	PlayerStatsInfoBox() = delete;
	PlayerStatsInfoBox(Game *gamePtr, Player* playerPtr);

	void updateJumpLoadBar();

	private:

	Game* m_gamePtr;
	Player* m_playerPtr;

	sf::Font* m_font;
	sf::Text m_headtext;
	sf::Text m_dashText;

	sf::RectangleShape m_statsBox;
	sf::RectangleShape m_jumpLoadBar;
	sf::RectangleShape m_dashLoadBar;


};