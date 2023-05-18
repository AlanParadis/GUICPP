#include "Widgets/BitmapCheckBox.h"

#include <iostream>

namespace GUICPP
{
    
    BitmapCheckBox::BitmapCheckBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color): CheckBox(position, size, color)
    {
        m_sprite.setPosition(position);
        m_sprite.setColor(color);
    }

    bool BitmapCheckBox::HandleEvents(const sf::Event& e)
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

    // DrawCheckBox
    void BitmapCheckBox::Draw(sf::RenderStates& states)
    {
        if(m_window == nullptr) {
            throw std::runtime_error("Window is nullptr");
        }
        m_window->draw(m_sprite, states);
    }

    // MoveCheckBox
    void BitmapCheckBox::Move(const sf::Vector2f& position)
    {
        m_position = position;
        m_sprite.setPosition(position);
    }

    void BitmapCheckBox::SetColor(const sf::Color& color)
    {
        m_color = color;
        m_sprite.setColor(color);
    }

    // SetCheckBoxSize
    void BitmapCheckBox::SetSize(const sf::Vector2f& size)
    {
        m_size = size;
        const sf::Rect rect = m_sprite.getTextureRect();
        m_sprite.setScale(size.x / static_cast<float>(rect.width), size.y / static_cast<float>(rect.height));
    }

    void BitmapCheckBox::SetPosition(sf::Vector2f position)
    {
        m_position = position;
        m_sprite.setPosition(position); 
    }

    // SetCheckBoxState
    void BitmapCheckBox::SetChecked(bool state)
    {
        m_isChecked = state;
    }

    void BitmapCheckBox::SetBitmapFolder(const std::string& pathToFolder, const std::string& extension)
    {
        //They are 4 variant of the checkbox : Checked, CheckedMouseOver, Unchecked, UncheckedMouseOver
        const std::string checkedPath = pathToFolder + "/Checked." + extension;
        if(!m_CheckedTexture.loadFromFile(checkedPath))
        {
            std::cout << "Error while loading texture from file : " << checkedPath << std::endl;
        }
        const std::string checkedMouseOverPath = pathToFolder + "/CheckedMouseOver." + extension;
        if(!m_CheckedMouseOverTexture.loadFromFile(checkedMouseOverPath))
        {
            std::cout << "Error while loading texture from file : " << checkedMouseOverPath << std::endl;
        }
        const std::string uncheckedPath = pathToFolder + "/Unchecked." + extension;
        if(!m_UncheckedTexture.loadFromFile(uncheckedPath))
        {
            std::cout << "Error while loading texture from file : " << uncheckedPath << std::endl;
        }
        const std::string uncheckedMouseOverPath = pathToFolder + "/UncheckedMouseOver." + extension;
        if(!m_UncheckedMouseOverTexture.loadFromFile(uncheckedMouseOverPath))
        {
            std::cout << "Error while loading texture from file : " << uncheckedMouseOverPath << std::endl;
        }

        m_sprite = sf::Sprite(m_isChecked ? m_CheckedTexture : m_UncheckedTexture);
        sf::Rect rect = m_sprite.getTextureRect();
        m_sprite.setPosition(m_position);
        m_sprite.setScale(m_size.x / static_cast<float>(rect.width),
                            m_size.y / static_cast<float>(rect.height));
    }

    void BitmapCheckBox::OnStartHover()
    {
        m_isMouseOver = true;
    
        if (m_sound.getBuffer() == m_OnStartHoverBuffer.get()) {
            m_sound.play();
        }
        else if (m_OnStartHoverBuffer) {
            m_sound.setBuffer(*m_OnStartHoverBuffer);
            m_sound.play();
        }

        // action when mouse over
        m_sprite.setTexture(m_isChecked ? m_CheckedMouseOverTexture : m_UncheckedMouseOverTexture);
    }

    void BitmapCheckBox::OnEndHover()
    {
        m_isMouseOver = false;
        // action when mouse not over
        m_sprite.setTexture(m_isChecked ? m_CheckedTexture : m_UncheckedTexture);
    }

    void BitmapCheckBox::OnClick()
    {
        m_wasClicked = true;
    }

    void BitmapCheckBox::OnReleased(bool away)
    {
        if (m_wasClicked && !away)
        {
            // swap state
            m_isChecked = !m_isChecked;

            // play sound
            if(m_isChecked)
            {
                if(m_OnCheckedBuffer)
                {
                    if(m_sound.getBuffer() == m_OnCheckedBuffer.get())
                    {
                        m_sound.play();
                    }
                    else if(m_OnCheckedBuffer)
                    {
                        m_sound.setBuffer(*m_OnCheckedBuffer);
                        m_sound.play();
                    }
                }
            }
            else
            {
                if(m_OnUncheckedBuffer)
                {
                    if(m_sound.getBuffer() == m_OnUncheckedBuffer.get())
                    {
                        m_sound.play();
                    }
                    else if(m_OnUncheckedBuffer)
                    {
                        m_sound.setBuffer(*m_OnUncheckedBuffer);
                        m_sound.play();
                    }
                }
            }
        }
        m_wasClicked = false;

        // change sprite
        if(m_isChecked)
        {
            if(m_isMouseOver)
                m_sprite.setTexture(m_CheckedMouseOverTexture);
            else
                m_sprite.setTexture(m_CheckedTexture);
        }
        else
        {
            if(m_isMouseOver)
                m_sprite.setTexture(m_UncheckedMouseOverTexture);
            else
                m_sprite.setTexture(m_UncheckedTexture);
        }

        if(m_delegate && !away)
        {
            m_delegate(m_isChecked);
        }
    }
    
}