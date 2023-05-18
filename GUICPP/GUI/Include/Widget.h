#pragma once

#include <SFML/Graphics.hpp>

namespace GUICPP
{
    class Widget
    {
    public:
        Widget(const sf::Vector2f& m_position, const sf::Vector2f& m_size,
               const sf::Color& m_color) : m_position(m_position),
                                           m_size(m_size),
                                           m_color(m_color){}
        virtual ~Widget() = default;
    
        virtual void Move(const sf::Vector2f& position) = 0;
        virtual void SetColor(const sf::Color& color) = 0;
        virtual void SetSize(const sf::Vector2f& size) = 0;
        virtual void SetPosition(sf::Vector2f position) = 0;
        sf::Vector2f GetPosition();
        sf::Vector2f GetRelativePosition(class Group& Group);
    protected:
        sf::Vector2f m_position = sf::Vector2f(0, 0);
        sf::Vector2f m_size;
        sf::Color m_color = sf::Color::White;
    
        sf::RenderWindow* m_window = nullptr;

        virtual bool HandleEvents(const sf::Event& e) = 0;
        virtual void Draw(sf::RenderStates& states) = 0;
    
    private:
        void SetWindow(sf::RenderWindow* window);
    
        friend class GUI;
        friend class Group;
    };
}

