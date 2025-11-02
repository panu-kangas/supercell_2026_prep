#include "Player.h"
#include "Game.h"

#include <iostream>

Player::Player(Game* gamePtr)
{
	m_gamePtr = gamePtr;

	m_shape.setRadius(PlayerShapeRadius);
	m_shape.setFillColor(PlayerColor);
	m_shape.setOutlineColor(sf::Color::White);
	m_shape.setOutlineThickness(0.f);
	m_shape.setOrigin({PlayerShapeRadius, PlayerShapeRadius});

	m_pos = {300, ScreenHeight - FloorLevel - m_shape.getLocalBounds().height / 2};
	m_shape.setPosition(m_pos);

	m_jumpLoadBar.setSize({0, 10});
	m_jumpLoadBar.setFillColor(sf::Color::Red);
	m_jumpLoadBar.setPosition({m_pos.x - TurboJumpBarLength / 2, m_pos.y - m_shape.getRadius() - m_jumpLoadBar.getSize().y - 15.f});
}

void Player::checkOutOfBounds()
{
	float leftLimit = 0 + m_shape.getLocalBounds().width / 2;
	float rightLimit = ScreenWidth - m_shape.getLocalBounds().width / 2;
	float lowLimit = ScreenHeight - FloorLevel - m_shape.getLocalBounds().height / 2;

	if (m_pos.x < leftLimit)
		m_pos.x = leftLimit;
	else if (m_pos.x > rightLimit)
		m_pos.x = rightLimit;

	// Grounded
	if (m_pos.y > lowLimit)
	{
		if (m_isDownDashing)
			m_gamePtr->activateCameraShake();

		m_isJumping = false;
		m_didDoubleJump = false;
		m_isTurboJumping = false;
		m_isDownDashing = false;
		m_shape.setOrigin({PlayerShapeRadius, PlayerShapeRadius});
		if (m_shape.getFillColor() != PlayerColor)
			m_shape.setFillColor(PlayerColor);
		m_pos.y = lowLimit;
	}
}

bool Player::handleTurboJump(float dt, InputData& inputData)
{
	if (m_isTurboJumping)
		return false;

	if (inputData.m_down && !m_isLoadingTurboJump && !m_isJumping)
	{
		inputData.m_downHold = true;
		m_turboJumpLoadClock.restart();
		m_isLoadingTurboJump = true;
		return true;
	}
	
	if (m_isLoadingTurboJump && m_turboJumpLoadClock.getElapsedTime().asSeconds() > TurboJumpLoadTime && inputData.m_downHold)
	{
		m_isTurboJumping = true;
		m_isLoadingTurboJump = false;
		m_velocity.y = TurboJumpPower;
		m_turboJumpEffectClock.restart();
		return true;
	}
	else if (m_isLoadingTurboJump && !inputData.m_downHold)
	{
		m_isLoadingTurboJump = false;
	}

	return false;
}

void Player::handleJump(float dt, InputData& inputData)
{
	if (m_isDashing || m_isDownDashing)
		return ;

	if (handleTurboJump(dt, inputData))
		return ;

	if (m_isTurboJumping && m_turboJumpEffectClock.getElapsedTime().asSeconds() > TurboJumpEffectTime)
	{
		m_isTurboJumping = false;
		m_isJumping = true;
		m_velocity.y = PlayerJumpPower;
	}

	if (!m_isJumping && !m_isTurboJumping && !m_isLoadingTurboJump && inputData.m_up)
	{
		m_isJumping = true;
		m_velocity.y = PlayerJumpPower;
		inputData.m_upHold = true;
	}
	else if (!m_didDoubleJump && m_isJumping && m_velocity.y > PlayerJumpPower / 2 && inputData.m_up && !inputData.m_upHold)
	{
		m_didDoubleJump = true;
		m_velocity.y = PlayerJumpPower;
	}

	if (m_isJumping)
	{
		if (m_velocity.y < 0)
			m_velocity.y += Gravity * 2.3 * dt;
		else
			m_velocity.y += Gravity * 3.3 * dt;
	}
}

bool Player::checkCanDash(InputData& inputData)
{
	if (m_dashCooldownClock.getElapsedTime().asSeconds() < PlayerDashCooldown)
		return false;

	if (inputData.m_ePress && !inputData.m_eHold && (inputData.m_left || inputData.m_right))
		return true;

	return false;
}

bool Player::checkCanDownDash(InputData& inputData)
{
	if (m_pos.y > DownDashMinHeight)
		return false;

	if (m_isJumping && inputData.m_down && !inputData.m_downHold)
		return true;

	return false;
}

void Player::handleDash(float dt, InputData& inputData)
{
	if (m_isDashing && m_dashEffectClock.getElapsedTime().asSeconds() > PlayerDashTime)
	{
		m_shape.setFillColor(PlayerColor);
		m_velocity.x = m_velocity.x > 0 ? m_speed : m_speed * -1;
		m_isDashing = false;
		return ;
	}

	if (m_isDashing || m_isDownDashing)
		return ;

	if (checkCanDownDash(inputData))
	{
		m_isDownDashing = true;
		m_shape.setFillColor(PlayerDashColor);
		m_velocity.y = PlayerDashSpeed;
	}
	else if (checkCanDash(inputData))
	{
		inputData.m_eHold = true;
		m_dashCooldownClock.restart();
		m_shape.setFillColor(PlayerDashColor);
		m_isDashing = true;
		m_velocity.x = m_velocity.x > 0 ? PlayerDashSpeed : PlayerDashSpeed * -1;
		m_velocity.y = 0;
		m_dashEffectClock.restart();
	}
}


void Player::handleMovement(float deltaTime, InputData& inputData)
{
	if ((inputData.m_left || inputData.m_right) && !m_isDownDashing && !m_isDashing && !m_isLoadingTurboJump)
	{
		m_velocity.x = ((-1 * inputData.m_left) + inputData.m_right) * m_speed;
	}
	else if (!m_isDashing)
	{
		m_velocity.x = 0;
	}

	handleDash(deltaTime, inputData);
	handleJump(deltaTime, inputData);
	if (!m_isJumping && !m_isDownDashing && !m_isTurboJumping)
	{
		m_velocity.y = 0;
	}

	m_pos.x += m_velocity.x * deltaTime;
	m_pos.y += m_velocity.y * deltaTime;

	checkOutOfBounds();
	m_shape.setPosition(m_pos);
}

void Player::updateJumpLoadBar()
{
	if (!isLoadingTurboJump())
	{
		if (m_jumpLoadBar.getSize().x > 0)
			m_jumpLoadBar.setSize({0, m_jumpLoadBar.getSize().y});
		if (m_jumpLoadBar.getFillColor() != sf::Color::Red)
			m_jumpLoadBar.setFillColor(sf::Color::Red);
		return;
	}

	float barLength = (getTurboJumpLoadTime() / TurboJumpLoadTime) * TurboJumpBarLength;
	if (barLength >= TurboJumpBarLength)
	{
		barLength = TurboJumpBarLength;
		m_jumpLoadBar.setFillColor(sf::Color::Green);
	}
	m_jumpLoadBar.setSize({barLength, m_jumpLoadBar.getLocalBounds().height});
	m_jumpLoadBar.setPosition({m_pos.x - TurboJumpBarLength / 2, m_pos.y - m_shape.getRadius() - m_jumpLoadBar.getSize().y - 15.f});

}

void Player::update(float deltaTime, InputData& inputData)
{
	handleMovement(deltaTime, inputData);
	updateJumpLoadBar();

	if (m_dashCooldownClock.getElapsedTime().asSeconds() > PlayerDashCooldown)
		m_shape.setOutlineThickness(3.f);
	else
		m_shape.setOutlineThickness(0.f);

}

void Player::draw(sf::RenderTarget &target) const
{
	target.draw(m_jumpLoadBar);
	target.draw(m_shape);
}