#include "PlatformHandler.h"
#include "Player.h"
#include "utils.h"

#include <iostream>

PlatformHandler::PlatformHandler(Game* gamePtr)
{
	m_gamePtr = gamePtr;
}

void PlatformHandler::spawnPlatform()
{

	float platformX = ScreenWidth;
	float platformY = randomFloat(m_platformHeightLimits.first, m_platformHeightLimits.second);
	float platformSizeX = randomFloat(m_platformLengthLimits.first, m_platformLengthLimits.second);
	float platformSizeY = PlatformHeight;

	m_platformVec.push_back(Platform({platformX, platformY}, {platformSizeX, platformSizeY}, PlatformSpeed));

}

void PlatformHandler::update(float dt)
{

	for (auto& platform : m_platformVec)
	{
		platform.update(dt);
	}

	if (m_spawnClock.getElapsedTime().asSeconds() < m_spawnTime)
		return ;

	spawnPlatform();
	m_spawnClock.restart();
	
}


void PlatformHandler::draw(sf::RenderTarget& target)
{
	for (auto& platform : m_platformVec)
	{
		platform.draw(target);
	}
}

void PlatformHandler::resolvePlayerCollison(int idx, Player* player)
{
	sf::Vector2f prevPos = player->getPrevPos();
	float playerPrevBottom = prevPos.y + PlayerShapeRadius;
	float playerPrevTop = prevPos.y - PlayerShapeRadius;
	float playerPrevLeft = prevPos.x - PlayerShapeRadius;
	float playerPrevRight = prevPos.x + PlayerShapeRadius;

	sf::FloatRect platformBounds = m_platformVec[idx].getShape().getGlobalBounds();
	float platformTop = platformBounds.top;
	float platformBottom = platformBounds.top + platformBounds.height;
	float platformLeft = platformBounds.left;
	float platformRight = platformBounds.left + platformBounds.width;

	if (playerPrevBottom < platformTop)
	{
		player->setPlayerGrounded(platformTop - PlayerShapeRadius, true, idx);
	}
	else
	{
		if (playerPrevTop > platformBottom)
		{
			player->setPosition({playerPrevLeft + PlayerShapeRadius, playerPrevTop + PlayerShapeRadius});
			player->setVelocity({0, 20});
			player->setIsJumping(true); // Player is affected by gravity

		}
		else if (playerPrevLeft > platformRight)
		{
			player->setPosition({platformRight + PlayerShapeRadius, player->getCurPos().y});
			player->setPlatformCollision(true);
			player->setVelocity({20, 0});
		}
		else if (playerPrevRight < platformLeft)
		{
			player->setPosition({platformLeft - PlayerShapeRadius, player->getCurPos().y});
			player->setPlatformCollision(true);
			player->setVelocity({-20, 0});
		}
	}
	
}

void PlatformHandler::checkPlayerCollision(Player* player)
{
	sf::FloatRect playerBounds = player->getShape().getGlobalBounds();

	for (int i = 0; i < m_platformVec.size(); ++i)
	{
		if (m_platformVec[i].getShape().getGlobalBounds().intersects(playerBounds))
		{
			resolvePlayerCollison(i, player);
			return ;
		}
	}
}

