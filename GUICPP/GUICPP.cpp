// GUICPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Game.h"

int main()
{
    // check if the version is debug or release
    #ifdef NDEBUG
    // hide console on release
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
#elif _DEBUG
    // activate console on debug
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOW);
#endif

    // seed random number generator
    srand(static_cast<unsigned>(time(nullptr)) );  // NOLINT(cert-msc51-cpp)

    auto  window = sf::RenderWindow(sf::VideoMode(1024, 768), "GUI CPP");

    sf::Clock clock;

    Game game(window);

    while (window.isOpen())
    {
        //Get delta time
        float dt = clock.restart().asSeconds();
        
        sf::Event event{};
        while (window.pollEvent(event))
        {
            game.HandleEvents(event);
            if (event.type == sf::Event::Closed) 
            {
                window.close();
            }
        }

        if(dt  < 0.1f || IsDebuggerPresent())
        {
            game.Update(dt);
        }

        //Draw
        window.clear(sf::Color(100,149,237));
        game.Draw();
        window.display();  
    }
}
