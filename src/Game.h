#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Constants.h"
#include "InputHandler.h"
#include "PlatformHandler.h"


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
    
    Game() = delete;
	Game(sf::RenderWindow& window);
    ~Game();
    
    bool initialise();
    void update(float deltaTime);
    void resetGame();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    State getState() const { return m_state; }
	void setState(State newState) { m_state = newState; };

    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);

	void activateCameraShake() { m_isCameraShaking = true; };

	sf::Font* getFont() { return &m_font; }
	InputData& getInputData() { return m_pGameInput->getInputData(); };
	float getFloorY() {return m_floor.getPosition().y; };
	sf::RenderWindow& getWindow() { return m_window; };
	std::vector<Platform>& getPlatformVec() { return m_pPlatformHandler->getPlatformVec(); };

private:

	void handleCameraShake();

	sf::RenderWindow& m_window;

    State m_state;

    std::unique_ptr<GameInput> m_pGameInput;
	std::unique_ptr<Player> m_pPlayer;
	std::unique_ptr<PlatformHandler> m_pPlatformHandler;

	sf::RectangleShape m_floor;
    sf::Font m_font;

	bool m_isCameraShaking = false;
	std::vector<sf::Vector2f> m_shakeOffsets = {
		{4, 4}, {-4, -4}, {4, -4}, {-4, 4},
		{4, 4}, {-4, -4}, {4, -4}, {-4, 4}
	};
	int m_shakeIdx = 0;


};