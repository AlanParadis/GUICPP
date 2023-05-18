#include "Widgets/button.h"

namespace GUICPP
{
    
    Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color,
                   const std::string& text, unsigned int characterSize): Widget(position, size, color)
    {
        m_rect.setSize(m_size);
        m_rect.setPosition(m_position);
        m_rect.setFillColor(m_color);
    
        m_text.setString(text);
        m_text.setCharacterSize(characterSize);
        m_text.setFillColor(sf::Color::Black);
        m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
        m_text.setPosition(m_position.x + (m_size.x / 2.0f), m_position.y + (m_size.y / 2.0f));
    }

    bool Button::HandleEvents(const sf::Event& e) {
        if(m_window == nullptr)
            throw std::runtime_error("Window is nullptr");
    
        const sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
    
        // convert it to world coordinates
        const sf::Vector2f worldPos = m_window->mapPixelToCoords(mousePos);

        // Check if the mouse is outside the button bounds
        if (!m_rect.getGlobalBounds().contains(static_cast<float>(worldPos.x), static_cast<float>(worldPos.y)))
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

    void Button::Draw(sf::RenderStates& states) {
        if(m_window == nullptr) {
            throw std::runtime_error("Window is nullptr");
        }
        m_window->draw(m_rect, states);
        m_window->draw(m_text, states);
    }

    void Button::Move(const sf::Vector2f& position) {
        m_position = position;
        m_rect.setPosition(position);
        m_text.setPosition(position.x + (m_size.x / 2.0f), position.y + (m_size.y / 2.0f));
    }

    void Button::SetColor(const sf::Color& color) {
        m_color = color;
        m_rect.setFillColor(color);
    }

    void Button::SetSize(const sf::Vector2f& size) {
        m_size = size;
        m_rect.setSize(size);
    }

    void Button::SetPosition(sf::Vector2f position)
    {
        m_position = position;
        m_rect.setPosition(position);
        m_text.setPosition(position.x + (m_size.x / 2.0f), position.y + (m_size.y / 2.0f));
    }

    void Button::SetSound(const std::shared_ptr<sf::SoundBuffer>& OnClickBuffer, const std::shared_ptr<sf::SoundBuffer>& OnReleasedBuffer,
                          const std::shared_ptr<sf::SoundBuffer>& OnStartHoverBuffer, const std::shared_ptr<sf::SoundBuffer>& OnEndHoverBuffer)
    {
        if (OnClickBuffer)
        {
            m_OnClickBuffer = OnClickBuffer;
        }
        if (OnReleasedBuffer)
        {
            m_OnReleasedBuffer = OnReleasedBuffer;
        }
        if (OnStartHoverBuffer)
        {
            m_OnStartHoverBuffer = OnStartHoverBuffer;
        }
        if (OnEndHoverBuffer)
        {
            m_OnEndHoverBuffer = OnEndHoverBuffer;
        }
    }

    void Button::OnStartHover() {
        if (m_sound.getBuffer() == m_OnStartHoverBuffer.get()) {
            m_sound.play();
        }
        else if(m_OnStartHoverBuffer)
        {
            m_sound.setBuffer(*m_OnStartHoverBuffer);
            m_sound.play();
        }

        m_isMouseOver = true;
        m_rect.setFillColor(sf::Color(static_cast<sf::Uint8>(static_cast<float>(m_color.r) * 0.75f),
                                      static_cast<sf::Uint8>(static_cast<float>(m_color.g) * 0.75f),
                                      static_cast<sf::Uint8>(static_cast<float>(m_color.b) * 0.75f),
                                      m_color.a));
    }

    void Button::OnEndHover()
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
        m_rect.setFillColor(m_color);
    }

    void Button::OnClick() {
        if (m_sound.getBuffer() == m_OnClickBuffer.get()) {
            m_sound.play();
        }
        else if (m_OnClickBuffer)
        {
            m_sound.setBuffer(*m_OnClickBuffer);
            m_sound.play();
        }
    
        const unsigned int cSize = m_text.getCharacterSize();
        m_text.setCharacterSize(cSize - 1);
        m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
        m_wasClicked = true;

        m_rect.setScale(0.975f, 0.975f);
        m_rect.move(3, 3);
    }

    void Button::OnReleased(bool away) {
        m_wasClicked = false;
    
        if (m_sound.getBuffer() == m_OnReleasedBuffer.get())
        {
            m_sound.play();        
        }
        else if(m_OnReleasedBuffer)
        {
            m_sound.setBuffer(*m_OnReleasedBuffer);
            m_sound.play();
        }

        const unsigned int cSize = m_text.getCharacterSize();
        m_text.setCharacterSize(cSize + 1);
        m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);

        m_rect.setScale(1.025f, 1.025f);
        m_rect.move(-3, -3);

        if (m_isResetOnClicks) {
            m_rect.setFillColor(m_color);
            m_isMouseOver = false;
        }

        if (m_delegate && !away) {
            m_delegate(m_delegateArgs);
        }
    }

    void Button::SetFont(const sf::Font& font)
    {
        m_text.setFont(font);
        m_text.setPosition(m_position.x + (m_size.x / 2.0f), m_position.y + (m_size.y / 2.0f));
        m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
    }

    void Button::SetText(const std::string& text)
    {
        m_text.setString(text);

        m_text.setPosition(m_position.x + (m_size.x / 2.0f), m_position.y + (m_size.y / 2.0f));
        m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
    }

    void Button::SetFontSize(unsigned size)
    {
        m_text.setCharacterSize(size);
        m_text.setPosition(m_position.x + (m_size.x / 2.0f), m_position.y + (m_size.y / 2.0f));
        m_text.setOrigin(m_text.getLocalBounds().width / 2.0f, m_text.getLocalBounds().height / 2.0f);
    }
    
}