#pragma once

#include "Slider.h"
#include <SFML/Audio.hpp>
#include <functional>

namespace GUICPP
{
    class BitmapSlider : public Slider {
    public:
        BitmapSlider(const sf::Vector2f& position, const sf::Vector2f& size,
               const sf::Color& barColor = sf::Color::White, const sf::Color& sliderColor = sf::Color::White,
               bool isVertical = false);
    
    
        void Move(const sf::Vector2f& position) override;
        void SetColor(const sf::Color& color) override;
        void SetSize(const sf::Vector2f& size) override;
        void SetPosition(sf::Vector2f position) override;

        void SetBarColor(const sf::Color& color) override;
        void SetSliderColor(const sf::Color& color) override;
        void SetCursorSize(const sf::Vector2f& size) override;
        void SetSliderValue(const sf::Vector2f& position, float value) override;
        void SetSliderVertical(bool isVertical) override;
        void SetOffset(float minOffset, float maxOffset);

        template <class R, class ... A>
        void SetDelegate(R (*func)(A...));
    
        void SetBitmapFolder(const std::string& pathToFolder, const std::string& extension);
    
    protected:
        sf::Vector2f m_indicatorSize;

        bool HandleEvents(const sf::Event& e) override;
        void Draw(sf::RenderStates& states) override;

        void OnStartHover() override;
        void OnEndHover() override;
        void OnClick(bool isCursorClicked = false) override;
        void OnReleased(bool away = false) override;
        void OnMouseHold() override;
    
    private:
        sf::Texture m_barDefaultTexture;
        sf::Texture m_barHoverTexture;
        sf::Texture m_cursorDefaultTexture;
        sf::Texture m_cursorHoverTexture;
    
        sf::Sprite m_bar;
        sf::Sprite m_cursor;

        float m_minOffset = 0;
        float m_maxOffset = 0;
    
        void SetCursorPosition(const sf::Vector2f& position) override;
        void ComputeValue(sf::Vector2f position) override;
    };

    template <class R, class ... A>
    void BitmapSlider::SetDelegate(R (*func)(A ...)) {
        m_delegate = std::function<void(float)>(func);
    }
}