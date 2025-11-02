#pragma once

#include "GameStateBase.h"

class StartScreen : public GameStateBase
{
	public:

	StartScreen() = delete;
	StartScreen(Game* gamePtr);

	void update(float dt, InputData& inputData) override;
    void draw(sf::RenderTarget& target) override;

	private:

	void handleInput(InputData& inputData);

	sf::Font* m_font;
	sf::Text m_headerText;
	sf::Text m_midText;

};