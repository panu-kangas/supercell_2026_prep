#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System.hpp>

class Player;
class Game;

struct InputData
{
    bool m_up = false;
	bool m_upHold = false;
    bool m_down = false;
	bool m_downHold = false;
    bool m_left = false;
    bool m_right = false;
	bool m_enter = false;
	bool m_enterHold = false;
    bool m_ePress = false;
    bool m_eHold = false;
	bool m_wPress = false;
    bool m_wHold = false;

    bool hasInputs() { return m_up || m_down || m_left || m_right || m_ePress || m_wPress || m_enter;}
};

class GameInput
{
public:
    GameInput(Game* pGame, Player* pPlayer);
    ~GameInput();
    
    void onKeyPressed(sf::Keyboard::Key key);
    void onKeyReleased(sf::Keyboard::Key key);
	bool isEnterPressed();
	bool isDownPressed();
	bool isUpPressed();
	InputData& getInputData() { return m_inputData; };
	
    
private:
    InputData m_inputData;
    Game* m_pGame;
    Player* m_pPlayer;
	sf::Clock m_enterClock;


};