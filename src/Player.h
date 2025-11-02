#pragma once

#include <SFML/Graphics.hpp>
#include "InputHandler.h"
#include "Constants.h"
#include "PlayerStatsInfoBox.h"

class Game;
class Platform;

class Player
{
	public:

	Player() = delete;
	Player(Game* gamePtr);

	void draw(sf::RenderTarget &target) const;
	void update(float deltaTime, InputData& inputData);

	bool isLoadingTurboJump() { return m_isLoadingTurboJump; };
	float getTurboJumpLoadTime() { return m_turboJumpLoadClock.getElapsedTime().asSeconds(); };

	void setPosition(sf::Vector2f position) { m_pos = position; };
	void setVelocity(sf::Vector2f velocity) { m_velocity = velocity; };
	void setIsJumping(bool status) { m_isJumping = status; };
	void setPlatformCollision(bool status) { m_platformCollision = status; };
	void invertVelocity() { m_velocity.x *= -1; m_velocity.y *= -1; };
	sf::CircleShape& getShape() { return m_shape; };
	sf::Vector2f getPrevPos() { return m_prevPos; };
	sf::Vector2f getCurPos() { return m_pos; };
	bool getIsDownDashing() { return m_isDownDashing; };
	void setPlayerGrounded(float posY, bool isOnPlatform = false, int platformIdx = -1);

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
	sf::Vector2f m_prevPos;
	sf::Vector2f m_velocity;

	bool m_isLoadingTurboJump = false;
	bool m_isJumping = false;
	bool m_didDoubleJump = false;
	bool m_isTurboJumping = false;
	bool m_isDashing = false;
	bool m_isDownDashing = false;
	bool m_isOnPlatform = false;
	bool m_platformCollision = false;

	float m_speed = PlayerSpeed;
	float m_jumpPower = PlayerJumpPower;

	Game* m_gamePtr;
	sf::Clock m_dashEffectClock;
	sf::Clock m_dashCooldownClock;
	sf::Clock m_turboJumpLoadClock;
	sf::Clock m_turboJumpEffectClock;

	int m_curPlatformIdx = -1;

//	PlayerStatsInfoBox m_infoBox;
	sf::RectangleShape m_jumpLoadBar;


};