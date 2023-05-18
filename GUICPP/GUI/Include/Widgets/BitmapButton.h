#pragma once
#include "Widgets/button.h"

namespace GUICPP
{
    class BitmapButton : public Button
    {
    public:
        BitmapButton( const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::White);
        bool HandleEvents(const sf::Event& e) override;
        void Draw(sf::RenderStates& states) override;
        void Move(const sf::Vector2f& position) override;
        void SetColor(const sf::Color& color) override;
        void SetSize(const sf::Vector2f& size) override;
        void SetPosition(sf::Vector2f position) override;

        void SetBitmapFolder(const std::string& pathToFolder, const std::string& extension);
    
    protected:
        void OnStartHover() override;
        void OnEndHover() override;
        void OnClick() override;
        void OnReleased(bool away = false) override;

    private:
        sf::Texture m_defaultTexture;
        sf::Texture m_hoverTexture;
        sf::Texture m_clickTexture;

        sf::Sprite m_sprite;

        sf::Vector2f m_size;
    
    };
}