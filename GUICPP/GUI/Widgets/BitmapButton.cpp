#include "Widgets/BitmapButton.h"

#include <iostream>

namespace GUICPP
{
    
    BitmapButton::BitmapButton(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color): Button(position, size, color)
    {
        m_position = position;
        m_size = size;
    }

    bool BitmapButton::HandleEvents(const sf::Event& e)
    {
        if(m_window == nullptr)
            throw std::runtime_error("Window is nullptr");
    
        const sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

        // convert it to world coordinates
        const sf::Vector2f worldPos = m_window->mapPixelToCoords(mousePos);

        // Check if the mouse is outside the button bounds
        if (!m_sprite.getGlobalBounds().contains(static_cast<float>(worldPos.x), static_cast<float>(worldPos.y)))
        {
            if(m_isMouseOver)
            {
                OnEndHover();
                if (m_wasClicked) {
                    OnReleased(true);
                }
            }
            return false;
        }
    
        if (!m_isMouseOver)
        {
            OnStartHover();
        }
        if (e.type == sf::Event::MouseButtonPressed)
        {
            OnClick();
        }
        else if (e.type == sf::Event::MouseButtonReleased && m_wasClicked)
        {
            OnReleased();
        }

        return true;
    }

    void BitmapButton::Draw(sf::RenderStates& states)
    {
        if(m_window == nullptr) {
            throw std::runtime_error("Window is nullptr");
        }
        m_window->draw(m_sprite, states);
    }

    void BitmapButton::Move(const sf::Vector2f& position)
    {
        m_position = position;
        m_sprite.setPosition(position);
    }

    void BitmapButton::SetColor(const sf::Color& color)
    {
        m_color = color;
        m_sprite.setColor(color);
    }

    void BitmapButton::SetSize(const sf::Vector2f& size)
    {
        m_size = size;
        const auto texture_size = m_sprite.getTexture()->getSize();
        m_sprite.setScale(size.x / static_cast<float>(texture_size.x),
                            size.y / static_cast<float>(texture_size.y));
    }

    void BitmapButton::SetPosition(sf::Vector2f position)
    {
        m_position = position;
        m_sprite.setPosition(position);
    }

    void BitmapButton::SetBitmapFolder(const std::string& pathToFolder, const std::string& extension)
    {
        // load the "Default", "Clicked" and "MouseOver" textures
        const std::string defaultPath = pathToFolder + "/Default." + extension;
        if(m_defaultTexture.loadFromFile(defaultPath))
            std::cout << "Failed to load texture from " << defaultPath << std::endl;

        const std::string clickPath = pathToFolder + "/Clicked." + extension;
        if(m_clickTexture.loadFromFile(clickPath))
            std::cout << "Failed to load texture from " << clickPath << std::endl;

        const std::string hoverPath = pathToFolder + "/MouseOver." + extension;
        if(m_hoverTexture.loadFromFile(hoverPath))
            std::cout << "Failed to load texture from " << hoverPath << std::endl;

        m_sprite = sf::Sprite(m_defaultTexture);
        m_sprite.setPosition(m_position);
        m_sprite.setScale(m_size.x / static_cast<float>(m_defaultTexture.getSize().x),
                            m_size.y / static_cast<float>(m_defaultTexture.getSize().y));
    }

    void BitmapButton::OnStartHover()
    {
        if (m_sound.getBuffer() == m_OnStartHoverBuffer.get()) {
            m_sound.play();
        }
        else if(m_OnStartHoverBuffer)
        {
            m_sound.setBuffer(*m_OnStartHoverBuffer);
            m_sound.play();
        }
    
        m_isMouseOver = true;
        m_sprite.setTexture(m_hoverTexture);
    }

    void BitmapButton::OnEndHover()
    {
        if (m_sound.getBuffer() == m_OnEndHoverBuffer.get()) {
            m_sound.play();
        }
        else if(m_OnEndHoverBuffer)
        {
            m_sound.setBuffer(*m_OnEndHoverBuffer);
            m_sound.play();
        }
    
        m_isMouseOver = false;
        m_sprite.setTexture(m_defaultTexture);
    }

    void BitmapButton::OnClick()
    {
        if (m_sound .getBuffer() == m_OnClickBuffer.get()) {
            m_sound.play();
        }
        else if(m_OnClickBuffer)
        {
            m_sound.setBuffer(*m_OnClickBuffer);
            m_sound.play();
        }
    
        m_wasClicked = true;
        m_sprite.setTexture(m_clickTexture);
    }

    void BitmapButton::OnReleased(bool away)
    {
        if (m_sound.getBuffer() == m_OnReleasedBuffer.get()) {
            m_sound.play();
        }
        else if(m_OnReleasedBuffer)
        {
            m_sound.setBuffer(*m_OnReleasedBuffer);
            m_sound.play();
        }
    
        m_wasClicked = false;

        if(m_isResetOnClicks) {
            m_isMouseOver = false;
            m_sprite.setTexture(m_defaultTexture);
        }
        else
        {
            m_sprite.setTexture(m_hoverTexture);
        }

        if (m_delegate && !away) {
            m_delegate(m_delegateArgs);
        }
    }
    
}

