#pragma once

#include <memory>
#include "GameStateBase.h"
#include "Player.h"

class IntroScreen : public GameStateBase
{
	public:

	IntroScreen() = delete;
	IntroScreen(Game* gamePtr);
	~IntroScreen() = default;

	void update(float dt, InputData& inputData) override;
    void draw (sf::RenderTarget& target) override;

	private:

	sf::Text m_header;
	std::unique_ptr<Player> m_pPlayer;
	sf::RectangleShape m_floor;

};