#pragma once

#include <SFML/Graphics.hpp>

const int ScreenWidth = 1400;
const int ScreenHeight = 950;

const float FloorLevel = 200.f;
const float Gravity = 800.f;
const float TurboJumpLoadTime = 0.8f;
const float TurboJumpEffectTime = 0.4f;
const float TurboJumpPower = -900.f;
const float TurboJumpBarLength = 100.f;

const float PlayerSpeed = 400.f;
const float PlayerShapeRadius = 20.f;
const float PlayerShapeMinRadius = 10.f;
const float PlayerJumpPower = -700.f;
const float PlayerDashSpeed = 1000.f;
const float PlayerDashTime = 0.15f;
const float PlayerDashCooldown = 1.0f;

const float DownDashMinHeight = ScreenHeight - FloorLevel - PlayerShapeRadius * 6;

const sf::Color FloorColor = sf::Color(21, 71, 35);
const sf::Color PlayerColor = sf::Color(240, 217, 43);
const sf::Color PlayerDashColor = sf::Color(250, 99, 35);