// Slider.h
#pragma once

#include "Widget.h"
#include <SFML/Audio.hpp>
#include <functional>
namespace GUICPP
{
    class Slider : public Widget {
    public:
        Slider(const sf::Vector2f& position, const sf::Vector2f& size,
               const sf::Color& barColor = sf::Color::White, const sf::Color& sliderColor = sf::Color(191,191,191),
               bool isVertical = false);
    
    
        void Move(const sf::Vector2f& position) override;
        void SetColor(const sf::Color& color) override;
        void SetSize(const sf::Vector2f& size) override;
        void SetPosition(sf::Vector2f position) override;

        virtual void SetBarColor(const sf::Color& color);
        virtual void SetSliderColor(const sf::Color& color);
        virtual void SetCursorSize(const sf::Vector2f& size);
        virtual void SetSliderValue(const sf::Vector2f& position, float value);
        virtual void SetSliderVertical(bool isVertical);

        virtual void SetSound(const std::shared_ptr<sf::SoundBuffer>& OnClickedBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnReleasedBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnStartHoverBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnEndHoverBuffer = nullptr);
    

        template <class R, class ... A>
        void SetDelegate(R (*func)(A ...));

    protected:
        sf::Vector2f m_cursorSize;
        sf::Color m_barColor;
        sf::Color m_sliderColor;

        bool m_isVertical = false;
        bool m_isMouseOver = false;
        bool m_isMousePressed = false;
    
        std::shared_ptr<sf::SoundBuffer> m_OnClickBuffer;
        std::shared_ptr<sf::SoundBuffer> m_OnReleasedBuffer;
        std::shared_ptr<sf::SoundBuffer> m_OnStartHoverBuffer;
        std::shared_ptr<sf::SoundBuffer> m_OnEndHoverBuffer;
    
        sf::Sound m_sound;
    
        std::function<void(float)> m_delegate;

        float m_value = 0;

        bool HandleEvents(const sf::Event& e) override;
        void Draw(sf::RenderStates& states) override;
    
        virtual void OnStartHover();
        virtual void OnEndHover();
        virtual void OnClick(bool isCursorClicked = false);
        virtual void OnReleased(bool away = false);
        virtual void OnMouseHold();
    
        virtual void ComputeValue(sf::Vector2f position);
    
    private:
        sf::RectangleShape m_bar;
        sf::RectangleShape m_cursor;

        virtual void SetCursorPosition(const sf::Vector2f& position);
    };

    template <class R, class ... A>
    void Slider::SetDelegate(R (*func)(A ...)) {
        m_delegate = std::function<void(float)>(func);
    }
}