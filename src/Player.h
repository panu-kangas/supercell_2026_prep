#pragma once

#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "Constants.h"


class Game;

class Player
{
	public:

	Player() = delete;
	Player(Game* gamePtr);

	void draw(sf::RenderTarget &target) const;
	void update(float deltaTime, InputData& inputData);

	private:

	void handleMovement(float deltaTime, InputData& inputData);
	void handleJump(float dt, InputData& inputData);
	bool handleTurboJump(float dt, InputData& inputData);
	void updateJumpLoadBar();
	void handleDash(float dt, InputData& inputData);
	bool checkCanDash(InputData& inputData);
	void checkOutOfBounds();

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
	sf::RectangleShape m_jumpLoadBar;

};