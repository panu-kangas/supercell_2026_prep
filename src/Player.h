#pragma once

#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "Constants.h"
#include "PlayerStatsInfoBox.h"

class Game;

class Player
{
	public:

	Player() = delete;
	Player(Game* gamePtr);

	void draw(sf::RenderTarget &target) const;
	void update(float deltaTime, InputData& inputData);

	bool isLoadingTurboJump() { return m_isLoadingTurboJump; };
	float getTurboJumpLoadTime() { return m_turboJumpLoadClock.getElapsedTime().asSeconds(); }; 

	private:

	void handleMovement(float deltaTime, InputData& inputData);
	void handleJump(float dt, InputData& inputData);
	bool handleTurboJump(float dt, InputData& inputData);
	void handleDash(float dt, InputData& inputData);
	bool checkCanDash(InputData& inputData);	
	bool checkCanDownDash(InputData& inputData);
	void checkOutOfBounds();
	void updateJumpLoadBar();

	sf::CircleShape m_shape;
	sf::Vector2f m_pos;
	sf::Vector2f m_velocity;

	bool m_isLoadingTurboJump = false;
	bool m_isJumping = false;
	bool m_didDoubleJump = false;
	bool m_isTurboJumping = false;
	bool m_isDashing = false;
	bool m_isDownDashing = false;

	float m_speed = PlayerSpeed;
	float m_jumpPower = PlayerJumpPower;

	Game* m_gamePtr;
	sf::Clock m_dashEffectClock;
	sf::Clock m_dashCooldownClock;
	sf::Clock m_turboJumpLoadClock;
	sf::Clock m_turboJumpEffectClock;

//	PlayerStatsInfoBox m_infoBox;
	sf::RectangleShape m_jumpLoadBar;

};