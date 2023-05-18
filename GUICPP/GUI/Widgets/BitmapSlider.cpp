#include "Widgets/BitmapSlider.h"

#include <iostream>

namespace GUICPP
{
    
    BitmapSlider::BitmapSlider(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& barColor,
                               const sf::Color& sliderColor, bool isVertical): Slider(position, size, barColor, sliderColor, isVertical)
    {
        m_bar.setScale(size);
        m_bar.setColor(barColor);
        m_bar.setPosition(position);
        m_bar.setOrigin(size.x / 2, size.y / 2);
    
        if(m_isVertical)
        {
            m_cursor.setScale({ size.x * 1.2f, size.y / 10 });
        }
        else
        {
            m_cursor.setScale({ size.x / 10, size.y * 1.2f });
        }
        m_cursor.setOrigin(m_cursor.getGlobalBounds().width / 2, m_cursor.getGlobalBounds().height / 2);
    
        m_cursor.setColor(sliderColor);
        BitmapSlider::SetCursorPosition(position);
    }

    void BitmapSlider::Move(const sf::Vector2f& position)
    {
        m_bar.setPosition(position);
        SetCursorPosition(position);
    }

    void BitmapSlider::SetColor(const sf::Color& color)
    {
        m_bar.setColor(color);
        m_cursor.setColor(color);
    }

    void BitmapSlider::SetSize(const sf::Vector2f& size)
    {

        m_bar.setScale(m_size.x / static_cast<float>(m_bar.getTexture()->getSize().x),
                            m_size.y / static_cast<float>(m_bar.getTexture()->getSize().y));
        if(m_isVertical)
        {
            m_cursorSize = { size.x * 1.2f, size.y / 10 };
            m_bar.setScale(m_cursorSize.x / static_cast<float>(m_bar.getTexture()->getSize().x),
                            m_cursorSize.y / static_cast<float>(m_bar.getTexture()->getSize().y));
        }
        else
        {
            m_cursorSize = { size.x / 10, size.y * 1.2f };
            m_cursor.setScale(m_cursorSize.x / static_cast<float>(m_cursor.getTexture()->getSize().x),
                            m_cursorSize.y / static_cast<float>(m_cursor.getTexture()->getSize().y));
        }
    
        SetCursorPosition(m_position);
    }

    void BitmapSlider::SetPosition(sf::Vector2f position)
    {
        m_position = position;
        m_bar.setPosition(position);
        SetCursorPosition(position); 
    }


    void BitmapSlider::SetBarColor(const sf::Color& color)
    {
        m_barColor = color;
        if (!m_isMouseOver) {
            m_bar.setColor(color);
        }
    }

    void BitmapSlider::SetSliderColor(const sf::Color& color)
    {
        m_sliderColor = color;
        if (!m_isMouseOver) {
            m_cursor.setColor(color);
        }
    }

    void BitmapSlider::SetCursorSize(const sf::Vector2f& size)
    {
        m_cursorSize = size;
        m_cursor.setScale(size.x / static_cast<float>(m_cursor.getTexture()->getSize().x),
                            size.y / static_cast<float>(m_cursor.getTexture()->getSize().y));
        SetCursorPosition(m_bar.getPosition());
    }

    void BitmapSlider::SetSliderValue(const sf::Vector2f& position, float value)
    {
        m_value = value;
        SetCursorPosition(position);
    }

    void BitmapSlider::SetSliderVertical(bool isVertical)
    {
        if(m_isVertical == isVertical)
        {
            return;
        }
    
        m_isVertical = isVertical;
    

        m_size = { m_size.y, m_size.x };

        m_bar.setRotation(m_bar.getRotation() + 90);
    
        m_cursorSize = { m_cursorSize.y, m_cursorSize.x };
        m_cursor.setRotation(m_cursor.getRotation() + 90);
    
        SetCursorPosition(m_position);
    }

    void BitmapSlider::SetOffset(float minOffset, float maxOffset)
    {
        m_minOffset = minOffset;
        m_maxOffset = maxOffset;
    }

    bool BitmapSlider::HandleEvents(const sf::Event& e) {
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

    void BitmapSlider::Draw(sf::RenderStates& states) {
        m_window->draw(m_bar, states);
        m_window->draw(m_cursor, states);
    }

    void BitmapSlider::OnStartHover() {
        m_isMouseOver = true;

        if(m_sound.getBuffer() == m_OnEndHoverBuffer.get())
        {
            m_sound.play();
        }
        else if (m_OnStartHoverBuffer) {
            m_sound.setBuffer(*m_OnStartHoverBuffer);
            m_sound.play();
        }
    
        m_bar.setTexture(m_barHoverTexture);
        m_cursor.setTexture(m_cursorHoverTexture);
    }

    void BitmapSlider::OnEndHover()
    {
        m_isMouseOver = false;
    
        if (m_sound.getBuffer() == m_OnStartHoverBuffer.get()) {
            m_sound.stop();
        }
        else if (m_OnEndHoverBuffer) {
            m_sound.setBuffer(*m_OnEndHoverBuffer);
            m_sound.play();
        }
    
        m_bar.setTexture(m_barDefaultTexture);
        m_cursor.setTexture(m_cursorDefaultTexture);
    }

    void BitmapSlider::OnClick(bool isCursorClicked) {
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

    void BitmapSlider::OnReleased(bool away) {
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
            m_bar.setTexture(m_barDefaultTexture);
            m_cursor.setTexture(m_cursorDefaultTexture);
        }
    }

    void BitmapSlider::OnMouseHold()
    {
        // move slider to mouse position projected on bar
        const sf::Vector2i mousePos = sf::Mouse::getPosition(*m_window);
        const sf::Vector2f worldPos = m_window->mapPixelToCoords(mousePos);

        ComputeValue(worldPos);

        SetCursorPosition(m_position);
    
        if(m_delegate)
            m_delegate(m_value);
    }

    void BitmapSlider::SetCursorPosition(const sf::Vector2f& position) {
        sf::Vector2f midSliderPosition;
        if (m_isVertical) {
            midSliderPosition.x = position.x;
            midSliderPosition.y = (m_minOffset + position.y - m_bar.getGlobalBounds().height / 2.0f)
                + ((1 - m_value) * (m_bar.getGlobalBounds().height - m_maxOffset - m_minOffset));
        } else {
            midSliderPosition.x = (m_minOffset + position.x - m_bar.getGlobalBounds().width / 2.0f)
                + (m_value * (m_bar.getGlobalBounds().width - m_maxOffset - m_minOffset));
            midSliderPosition.y = position.y;
        }
        m_cursor.setPosition(midSliderPosition);
    }

    void BitmapSlider::ComputeValue(sf::Vector2f position)
    {
        if(m_isVertical) {
            m_value = 1 - ((position.y - m_bar.getPosition().y + m_bar.getGlobalBounds().height / 2.0f) / m_bar.getGlobalBounds().height);
            if(m_value < 0) m_value = 0;
            if(m_value > 1) m_value = 1;
        } else {
            m_value = (position.x - m_bar.getPosition().x + m_bar.getGlobalBounds().width / 2.0f) / m_bar.getGlobalBounds().width;
            if(m_value < 0) m_value = 0;
            if(m_value > 1) m_value = 1;
        }
    }

    void BitmapSlider::SetBitmapFolder(const std::string& pathToFolder, const std::string& extension)
    {
        // load the "Default", "Clicked" and "MouseOver" textures
        const std::string defaultBarPath = pathToFolder + "/BarDefault." + extension;
        if(m_barDefaultTexture.loadFromFile(defaultBarPath))
            std::cout << "Failed to load texture from " << defaultBarPath << std::endl;
        const std::string hoverBarPath = pathToFolder + "/BarMouseOver." + extension;
        if(m_barHoverTexture.loadFromFile(hoverBarPath))
            std::cout << "Failed to load texture from " << hoverBarPath << std::endl;
        const std::string defaultCursorPath = pathToFolder + "/CursorDefault." + extension;
        if(m_cursorDefaultTexture.loadFromFile(defaultCursorPath))
            std::cout << "Failed to load texture from " << defaultCursorPath << std::endl;
        const std::string hoverCursorPath = pathToFolder + "/CursorMouseOver." + extension;
        if(m_cursorHoverTexture.loadFromFile(hoverCursorPath))
            std::cout << "Failed to load texture from " << hoverCursorPath << std::endl;

        // set the default texture
        m_bar.setTexture(m_barDefaultTexture);
        m_cursor.setTexture(m_cursorDefaultTexture);

        // set size and origin
        m_bar.setScale(m_size.x / static_cast<float>(m_bar.getTexture()->getSize().x),
                            m_size.y / static_cast<float>(m_bar.getTexture()->getSize().y));

        m_cursor.setScale(m_cursorSize.x / static_cast<float>(m_cursor.getTexture()->getSize().x),
                            m_cursorSize.y / static_cast<float>(m_cursor.getTexture()->getSize().y));


        m_bar.setOrigin(static_cast<float>(m_bar.getTexture()->getSize().x) / 2.0f, static_cast<float>(m_bar.getTexture()->getSize().y) / 2.0f);
    
        m_cursor.setOrigin(static_cast<float>(m_cursor.getTexture()->getSize().x) / 2.0f, static_cast<float>(m_cursor.getTexture()->getSize().y) / 2.0f);
    
        m_bar.setPosition(m_position);

        SetCursorPosition(m_position);
    
    }
    
}
