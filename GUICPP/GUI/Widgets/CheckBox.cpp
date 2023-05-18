#include "Widgets/CheckBox.h"

namespace GUICPP
{
    
    CheckBox::CheckBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color): Widget(position, size, color)
    {
        m_backrect.setPosition(position);
        m_backrect.setSize(size);
        m_backrect.setFillColor(color);

        m_checkrect.setPosition(position + size / 7.f);
        m_checkrect.setSize(size - size / 3.5f);
        m_checkrect.setFillColor(sf::Color::Black);
    }

    bool CheckBox::HandleEvents(const sf::Event& e)
    {
        if(m_window == nullptr)
            throw std::runtime_error("Window is nullptr");
    
        const sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

        // convert it to world coordinates
        const sf::Vector2f worldPos = m_window->mapPixelToCoords(mousePos);

        // Check if the mouse is outside the button bounds
        if (!m_backrect.getGlobalBounds().contains(static_cast<float>(worldPos.x), static_cast<float>(worldPos.y)))
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
    void CheckBox::Draw(sf::RenderStates& states)
    {
        if(m_window == nullptr) {
            throw std::runtime_error("Window is nullptr");
        }
        m_window->draw(m_backrect, states);
        if(m_isChecked) {
            m_window->draw(m_checkrect, states);
        }
    }

    // MoveCheckBox
    void CheckBox::Move(const sf::Vector2f& position)
    {
        m_position = position;
        m_backrect.setPosition(position);
        m_checkrect.setPosition(position + m_size / 7.f);
    }

    void CheckBox::SetColor(const sf::Color& color)
    {
        m_color = color;
        m_backrect.setFillColor(color);
    }

    // SetCheckBoxSize
    void CheckBox::SetSize(const sf::Vector2f& size)
    {
        m_size = size;
        m_backrect.setSize(size);
        m_checkrect.setSize(size * 5.f / 7.f);
    }

    void CheckBox::SetPosition(sf::Vector2f position)
    {
        m_position = position;
        m_backrect.setPosition(position);
        m_checkrect.setPosition(position + m_size / 7.f);
    }

    // SetCheckBoxState
    void CheckBox::SetChecked(bool state)
    {
        m_isChecked = state;
    }

    void CheckBox::SetSound(const std::shared_ptr<sf::SoundBuffer>& OnCheckedBuffer,
            const std::shared_ptr<sf::SoundBuffer>& OnUncheckedBuffer,
            const std::shared_ptr<sf::SoundBuffer>& OnStartHoverBuffer,
            const std::shared_ptr<sf::SoundBuffer>& OnEndHoverBuffer)
    {
        if(OnCheckedBuffer != nullptr)
        {
            m_OnCheckedBuffer = OnCheckedBuffer;
        }
        if(OnUncheckedBuffer != nullptr)
        {
            m_OnUncheckedBuffer = OnUncheckedBuffer;
        }
        if(OnStartHoverBuffer != nullptr)
        {
            m_OnStartHoverBuffer = OnStartHoverBuffer;
        }
        if(OnEndHoverBuffer != nullptr)
        {
            m_OnEndHoverBuffer = OnEndHoverBuffer;
        }
    }

    void CheckBox::OnStartHover()
    {
        m_isMouseOver = true;
    
        if (m_sound.getBuffer() == m_OnStartHoverBuffer.get())
        {
            m_sound.play();
        }
        else if (m_OnStartHoverBuffer)
        {
            m_sound.setBuffer(*m_OnStartHoverBuffer);
            m_sound.play();
        }

        // action when mouse over
        // darken the check box
        const sf::Color darkColor = sf::Color(
            static_cast<sf::Uint8>(static_cast<float>(m_color.r) * 0.75f),
            static_cast<sf::Uint8>(static_cast<float>(m_color.g) * 0.75f),
            static_cast<sf::Uint8>(static_cast<float>(m_color.b) * 0.75f),
            m_color.a
        );
        m_backrect.setFillColor(darkColor);
    }

    void CheckBox::OnEndHover()
    {
        m_isMouseOver = false;
        // action when mouse not over
        // reset color of the check box
        SetColor(m_color);
    }

    void CheckBox::OnClick()
    {
        m_wasClicked = true;
    }

    void CheckBox::OnReleased(bool away)
    {
        if (m_wasClicked && !away)
        {
            m_isChecked = !m_isChecked;
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

        if(m_delegate && !away)
        {
            m_delegate(m_isChecked);
        }
    }
    
}