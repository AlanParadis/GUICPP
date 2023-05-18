#include "Widgets/Slider.h"

namespace GUICPP
{
    
    Slider::Slider(const sf::Vector2f& position, const sf::Vector2f& size, 
                   const sf::Color& barColor, const sf::Color& sliderColor, bool isVertical): Widget(position, size, barColor),
                                                                                              m_barColor(barColor), m_sliderColor(sliderColor),
                                                                                              m_isVertical(isVertical)
    {
        m_bar.setSize(size);
        m_bar.setFillColor(barColor);
        m_bar.setPosition(position);
        m_bar.setOrigin(size.x / 2, size.y / 2);


        if(m_isVertical)
        {
            m_cursorSize = { size.x * 1.2f, size.y / 10 };
            m_cursor.setSize(m_cursorSize);
        }
        else
        {
            m_cursorSize = { size.x / 10, size.y * 1.2f };
            m_cursor.setSize(m_cursorSize);
        }
        m_cursor.setOrigin(m_cursor.getSize().x / 2, m_cursor.getSize().y / 2);
    
        m_cursor.setFillColor(sliderColor);
        Slider::SetCursorPosition(position);
    }

    void Slider::Move(const sf::Vector2f& position)
    {
        m_bar.setPosition(position);
        SetCursorPosition(position);
    }

    void Slider::SetColor(const sf::Color& color)
    {
        m_bar.setFillColor(color);
        m_cursor.setFillColor(color);
    }

    void Slider::SetSize(const sf::Vector2f& size)
    {

        m_bar.setSize(size);
        if(m_isVertical)
        {
            m_cursor.setSize({ size.x * 1.2f, size.y / 10 });
        }
        else
        {
            m_cursor.setSize({ size.x / 10, size.y * 1.2f });
        }
    
        SetCursorPosition(m_position);
    }

    void Slider::SetPosition(sf::Vector2f position)
    {
        m_bar.setPosition(position);
        SetCursorPosition(position);
    }


    void Slider::SetBarColor(const sf::Color& color)
    {
        m_barColor = color;
        if (!m_isMouseOver) {
            m_bar.setFillColor(color);
        }
    }

    void Slider::SetSliderColor(const sf::Color& color)
    {
        m_sliderColor = color;
        if (!m_isMouseOver) {
            m_cursor.setFillColor(color);
        }
    }

    void Slider::SetCursorSize(const sf::Vector2f& size)
    {
        m_cursor.setSize(size);
        SetCursorPosition(m_bar.getPosition());
    }

    void Slider::SetSliderValue(const sf::Vector2f& position, float value)
    {
        m_value = value;
        SetCursorPosition(position);
    }

    void Slider::SetSliderVertical(bool isVertical)
    {

        if(m_isVertical == isVertical)
        {
            return;
        }
    
        m_isVertical = isVertical;

        m_size = { m_size.y, m_size.x };
        m_bar.setSize( m_size);
    
        m_cursorSize = { m_cursorSize.y, m_cursorSize.x};
        m_cursor.setSize(m_cursorSize);

        SetCursorPosition(m_position);
    }

    void Slider::SetSound(const std::shared_ptr<sf::SoundBuffer>& OnClickedBuffer,
        const std::shared_ptr<sf::SoundBuffer>& OnReleasedBuffer,
        const std::shared_ptr<sf::SoundBuffer>& OnStartHoverBuffer,
        const std::shared_ptr<sf::SoundBuffer>& OnEndHoverBuffer)
    {
        if(OnClickedBuffer)
            m_OnClickBuffer = OnClickedBuffer;
    
        if(OnReleasedBuffer)
            m_OnReleasedBuffer = OnReleasedBuffer;

        if(OnStartHoverBuffer)
            m_OnStartHoverBuffer = OnStartHoverBuffer;

        if(OnEndHoverBuffer)
            m_OnEndHoverBuffer = OnEndHoverBuffer;
    }

    void Slider::ComputeValue(const sf::Vector2f position)
    {
        if(m_isVertical) {
            m_value = 1 - ((position.y - m_bar.getPosition().y + m_bar.getSize().y / 2) / m_bar.getSize().y);
            if(m_value < 0) m_value = 0;
            if(m_value > 1) m_value = 1;
        } else {
            m_value = (position.x - m_bar.getPosition().x + m_bar.getSize().x / 2) / m_bar.getSize().x;
            if(m_value < 0) m_value = 0;
            if(m_value > 1) m_value = 1;
        }
    }

    bool Slider::HandleEvents(const sf::Event& e) {
        const sf::FloatRect hitboxBar = m_bar.getGlobalBounds();
        const sf::FloatRect hitboxIndicator = m_cursor.getGlobalBounds();
        const sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);

        // convert it to world coordinates
        const sf::Vector2f worldPos = m_window->mapPixelToCoords(mousePos);

        const bool isBarHovered = hitboxBar.contains(static_cast<float>(worldPos.x), static_cast<float>(worldPos.y));
        const bool isCursorHovered = hitboxIndicator.contains(static_cast<float>(worldPos.x), static_cast<float>(worldPos.y));
        const bool isHovered = isBarHovered || isCursorHovered;

        switch (e.type) {
        case sf::Event::MouseButtonPressed: {
                if (isHovered) {
                    OnClick(isCursorHovered);
                }
                break;
        }
        case sf::Event::MouseMoved: {
                if(isHovered && !m_isMouseOver)
                    OnStartHover();
                else if(!isHovered && m_isMouseOver)
                    OnEndHover();
                else if(m_isMousePressed)
                    OnMouseHold();
                break;
        }
        case sf::Event::MouseButtonReleased: {
                if (m_isMousePressed) OnReleased(!isHovered);
                break;
        }
        default:
            break;
        }
    
        ComputeValue(m_cursor.getPosition());

    
        return isHovered || m_isMousePressed;
    }

    void Slider::Draw(sf::RenderStates& states) {
        m_window->draw(m_bar, states);
        m_window->draw(m_cursor, states);
    }

    void Slider::OnStartHover() {
        m_isMouseOver = true;

        if(m_sound.getBuffer() == m_OnEndHoverBuffer.get())
        {
            m_sound.play();
        }
        else if (m_OnStartHoverBuffer) {
            m_sound.setBuffer(*m_OnStartHoverBuffer);
            m_sound.play();
        }
    
        m_bar.setFillColor(sf::Color(
            static_cast<sf::Uint8>(static_cast<float>(m_barColor.r) * 0.925f),
            static_cast<sf::Uint8>(static_cast<float>(m_barColor.g) * 0.925f),
            static_cast<sf::Uint8>(static_cast<float>(m_barColor.b) * 0.925f),
            m_barColor.a));

        m_cursor.setFillColor(sf::Color(
            static_cast<sf::Uint8>(static_cast<float>(m_sliderColor.r) * 0.925f),
            static_cast<sf::Uint8>(static_cast<float>(m_sliderColor.g) * 0.925f),
            static_cast<sf::Uint8>(static_cast<float>(m_sliderColor.b) * 0.925f),
            m_sliderColor.a));
    }

    void Slider::OnEndHover()
    {
        m_isMouseOver = false;
    
        if (m_sound.getBuffer() == m_OnStartHoverBuffer.get()) {
            m_sound.stop();
        }
        else if (m_OnEndHoverBuffer) {
            m_sound.setBuffer(*m_OnEndHoverBuffer);
            m_sound.play();
        }
    
        m_bar.setFillColor(m_barColor);
        m_cursor.setFillColor(m_sliderColor);
    }

    void Slider::OnClick(bool isCursorClicked) {
        m_isMousePressed = true;
        if (m_sound.getBuffer() == m_OnEndHoverBuffer.get()) {
            m_sound.play();
        }
        else if (m_OnClickBuffer) {
            m_sound.setBuffer(*m_OnClickBuffer);
            m_sound.play();
        }

        if(!isCursorClicked)
        {
            // project mouse position on bar and place cursor there if isCursorClicked is false
            const sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
            // convert it to world coordinates
            const sf::Vector2f worldPos = m_window->mapPixelToCoords(mousePos);
    
            ComputeValue(sf::Vector2f(static_cast<float>(worldPos.x), static_cast<float>(worldPos.y)));

            SetCursorPosition(m_position);

            if(m_delegate)
                m_delegate(m_value);
        }
    }

    void Slider::OnReleased(bool away) {
        m_isMousePressed = false;

        if(m_sound.getBuffer() == m_OnClickBuffer.get())
        {
            m_sound.play();
        }
        else if (m_OnReleasedBuffer) {
            m_sound.setBuffer(*m_OnReleasedBuffer);
            m_sound.play();
        }
    
        if (away) {
            m_isMouseOver = false;
            m_bar.setFillColor(m_barColor);
            m_cursor.setFillColor(m_sliderColor);
        }
    }

    void Slider::OnMouseHold()
    {
        // move slider to mouse position projected on bar
        const sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
        const sf::Vector2f worldPos = m_window->mapPixelToCoords(mousePos);

        ComputeValue(worldPos);

        SetCursorPosition(m_position);
    
        if(m_delegate)
            m_delegate(m_value);
    }

    void Slider::SetCursorPosition(const sf::Vector2f& position) {
        sf::Vector2f midSliderPosition;
        if (m_isVertical) {
            midSliderPosition.x = position.x;
            midSliderPosition.y = (position.y - m_bar.getSize().y / 2) + ((1 - m_value) * m_bar.getSize().y);
        } else {
            midSliderPosition.x = (position.x - m_bar.getSize().x / 2) + (m_value * m_bar.getSize().x);
            midSliderPosition.y = position.y;
        }
        m_cursor.setPosition(midSliderPosition);
    }
    
}