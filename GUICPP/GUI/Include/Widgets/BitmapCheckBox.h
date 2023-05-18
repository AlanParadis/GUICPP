#pragma once
#include "Widgets/CheckBox.h"

namespace GUICPP
{
    class BitmapCheckBox : public CheckBox
    {
    public:
        BitmapCheckBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::White);

        bool HandleEvents(const sf::Event& e) override;
        void Draw(sf::RenderStates& states) override;
        void Move(const sf::Vector2f& position) override;
        void SetColor(const sf::Color& color) override;
        void SetSize(const sf::Vector2f& size) override;
        void SetPosition(sf::Vector2f position) override;
        void SetChecked(bool state) override;

        void SetBitmapFolder(const std::string& pathToFolder, const std::string& extension);
    
    protected:
        void OnStartHover() override;
        void OnEndHover() override;
        void OnClick() override;
        void OnReleased(bool away = false) override;

    private:
        sf::Texture m_CheckedTexture;
        sf::Texture m_CheckedMouseOverTexture;
        sf::Texture m_UncheckedTexture;
        sf::Texture m_UncheckedMouseOverTexture;
        sf::Sprite m_sprite;
    
    };
}