#include "Game.h"

#include <iostream>
#include <filesystem>

#include "GUI.h"

// function implementation
void sayHello() {
    std::cout << "hello world" << std::endl;
}

void sayString(std::string str)
{
    std::cout << str << std::endl;
}

void sayState(bool state)
{
    std::cout << state << std::endl;
}

void sayValue(float val)
{
    std::cout << val << std::endl;
}

Game::Game(sf::RenderWindow& window): m_window(window), m_gui(window)
{
    const auto buff0 = std::make_shared<sf::SoundBuffer>();
    if(!buff0->loadFromFile("./Assets/Sounds/jump.ogg"))
    {
        std::cout << "Error loading sound" << std::endl; 
    }
    const auto buff1 = std::make_shared<sf::SoundBuffer>();
    if(buff1->loadFromFile("./Assets/Sounds/gold.ogg"))
    {
        std::cout << "Error loading sound" << std::endl;
    }
    const auto buff2 = std::make_shared<sf::SoundBuffer>();
    if(buff2->loadFromFile("./Assets/Sounds/gold_ground.ogg"))
    {
        std::cout << "Error loading sound" << std::endl;
    }


    const auto button1 = std::make_shared<GUICPP::Button>(sf::Vector2f(200, 200), sf::Vector2f(200, 75));
    button1->SetSound(buff0, buff1, buff2, buff2);
    button1->SetText("Hello World");
    button1->SetFontSize(20);
    button1->SetDelegate(sayHello);

    m_gui.AddWidgetToGui(button1);

    const auto button2 = std::make_shared<GUICPP::BitmapButton>(sf::Vector2f(250, 300), sf::Vector2f(200, 75));
    button2->SetSound(buff0, buff1, buff2, buff2);
    button2->SetBitmapFolder("Assets/ButtonImg","png");
    button2->SetDelegate(sayString, "Hey there!");

    m_gui.AddWidgetToGui(button2);

    const auto checkbox = std::make_shared<GUICPP::CheckBox>(sf::Vector2f(150, 100), sf::Vector2f(50, 50));
    checkbox->SetSound(buff0, buff1, buff2, buff2);
    checkbox->SetDelegate(sayState);

    m_gui.AddWidgetToGui(checkbox);

    const auto checkbox1  = std::make_shared<GUICPP::BitmapCheckBox>(sf::Vector2f(250, 100), sf::Vector2f(50, 50));
    checkbox1->SetSound(buff0, buff1, buff2, buff2);
    checkbox1->SetBitmapFolder("Assets/CheckBoxImg", "png");
    checkbox1->SetDelegate(sayState);

    m_gui.AddWidgetToGui(checkbox1);

    const auto slider = std::make_shared<GUICPP::Slider>(sf::Vector2f(200, 450), sf::Vector2f(200, 25));
    slider->SetSound(buff0, buff1, buff2, buff2);
    slider->SetDelegate(sayValue);

    m_gui.AddWidgetToGui(slider);

    const auto slider1 = std::make_shared<GUICPP::BitmapSlider>(sf::Vector2f(600, 400), sf::Vector2f(404, 32));
    slider1->SetSound(buff0, buff1, buff2, buff2);
    slider1->SetBitmapFolder("Assets/SliderImg", "png");
    slider1->SetDelegate(sayValue);
    slider1->SetCursorSize({32,54});
    slider1->SetOffset(25,25);
    slider1->SetSliderVertical(true);

    m_gui.AddWidgetToGui(slider1);
}

void Game::HandleEvents(sf::Event evt)
{
    m_gui.HandleEvents(evt);
}

void Game::Update(float dt)
{
}

void Game::Draw() const
{
    sf::RenderStates states = sf::RenderStates::Default;
    m_gui.Draw(states);
}



