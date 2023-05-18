#pragma once

#include <SFML/Graphics.hpp>

#include "GUI.h"

class Game
{
public:
    Game(sf::RenderWindow& window);
    void HandleEvents(sf::Event evt);
    void Update(float dt);
    void Draw() const;
private:
    sf::RenderWindow& m_window;
    GUICPP::GUI m_gui;

    
    
};
