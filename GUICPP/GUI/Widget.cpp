#include "Widget.h"
#include "Group.h"

namespace GUICPP
{

    sf::Vector2f Widget::GetPosition()
    {
        return m_position;
    }

    sf::Vector2f Widget::GetRelativePosition(Group& Group)
    {
        return m_position - Group.m_globalPosition;
    }

    void Widget::SetWindow(sf::RenderWindow* window)
    {
        if(window == nullptr)
            throw std::runtime_error("Window is nullptr");
    
        m_window = window;
    }
    
}