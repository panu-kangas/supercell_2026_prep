#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Constants.h"
#include "InputHandler.h"


class Player;

namespace sf { class Clock; }

class Game : public sf::Drawable
{
public:
    
    enum class State
    {
		START_SCREEN,
        ACTIVE,
		GAME_OVER
    };
    
    Game();
    ~Game();
    
    bool initialise();
    void update(float deltaTime);
    void resetGame();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    State getState() const { return m_state; }
	void setState(State newState) { m_state = newState; };

    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);

	sf::Font* getFont() { return &m_font; }
	InputData& getInputData() { return m_pGameInput->getInputData(); };
	float getFloorY() {return m_floor.getPosition().y; };

private:

    State m_state;

    std::unique_ptr<GameInput> m_pGameInput;
	std::unique_ptr<Player> m_pPlayer;

	sf::RectangleShape m_floor;

    sf::Font m_font;

};