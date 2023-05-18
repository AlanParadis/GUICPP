#pragma once

#include <any>
#include <functional>
#include <SFML/Audio.hpp>

#include "widget.h"

namespace GUICPP
{
    class Button : public Widget
    {
    public:
    
        Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::White,
               const std::string& text = "", unsigned int characterSize = 31);

        bool HandleEvents(const sf::Event& e) override;
        void Draw(sf::RenderStates& states) override;
        void Move(const sf::Vector2f& position) override;
        void SetColor(const sf::Color& color) override;
        void SetSize(const sf::Vector2f& size) override;
        void SetPosition(sf::Vector2f position) override;
    
        void SetFont(const sf::Font& font);
        void SetText(const std::string& text);
        void SetFontSize(unsigned int size);
        virtual void SetSound(const std::shared_ptr<sf::SoundBuffer>& OnClickBuffer = nullptr,
            const std::shared_ptr<sf::SoundBuffer>& OnReleasedBuffer = nullptr,
            const std::shared_ptr<sf::SoundBuffer>& OnStartHoverBuffer = nullptr,
            const std::shared_ptr<sf::SoundBuffer>& OnEndHoverBuffer = nullptr);
    
        template<typename Callable, typename... Args>
        void SetDelegate(Callable&& func, Args&&... args);

    protected:
        bool m_isMouseOver = false;
        bool m_wasClicked = false;
        bool m_isResetOnClicks = false;

        std::shared_ptr<sf::SoundBuffer> m_OnClickBuffer;
        std::shared_ptr<sf::SoundBuffer> m_OnReleasedBuffer;
        std::shared_ptr<sf::SoundBuffer> m_OnStartHoverBuffer;
        std::shared_ptr<sf::SoundBuffer> m_OnEndHoverBuffer;
    
        sf::Sound m_sound;
        std::function<void(std::vector<std::any>&)> m_delegate;
        std::vector<std::any> m_delegateArgs;
    
        virtual void OnStartHover();
        virtual void OnEndHover();
        virtual void OnClick();
        virtual void OnReleased(bool away = false);
    
    private:
        sf::RectangleShape m_rect;
        sf::Text m_text;
    
    };

    template <typename Callable, typename ... Args>
    void Button::SetDelegate(Callable&& func, Args&&... args)
    {
        m_delegate = std::bind(std::forward<Callable>(func), std::forward<Args>(args)...);
    }
}
