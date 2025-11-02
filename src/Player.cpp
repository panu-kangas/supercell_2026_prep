#include "Player.h"
#include "Game.h"

Player::Player(Game* gamePtr)
{
	m_gamePtr = gamePtr;

	m_shape.setRadius(30);
	m_shape.setFillColor(PlayerColor);

	m_pos = {300, ScreenHeight - FloorLevel - m_shape.getLocalBounds().height / 2};
	m_shape.setPosition(m_pos);

}

void Player::handleMovement(float deltaTime, InputData& inputData)
{
	if (inputData.m_movingLeft)
	{
		m_pos.x -= m_speed * deltaTime;
	}
	else if (inputData.m_movingRight)
	{
		m_pos.x += m_speed * deltaTime;
	}

	m_shape.setPosition(m_pos);
}

void Player::update(float deltaTime, InputData& inputData)
{
	handleMovement(deltaTime, inputData);
}

void Player::draw(sf::RenderTarget &target) const
{
	target.draw(m_shape);
}