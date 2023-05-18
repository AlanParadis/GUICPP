#pragma once
#include <any>
#include <functional>
#include <SFML/Audio.hpp>

#include "widget.h"

namespace GUICPP
{
    class CheckBox : public Widget
    {
    public:
    
        CheckBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::White);

        bool HandleEvents(const sf::Event& e) override;
        void Draw(sf::RenderStates& states) override;
        void Move(const sf::Vector2f& position) override;
        void SetColor(const sf::Color& color) override;
        void SetSize(const sf::Vector2f& size) override;
        void SetPosition(sf::Vector2f position) override;
        virtual void SetChecked(bool state);

        virtual void SetSound(const std::shared_ptr<sf::SoundBuffer>& OnCheckedBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnUncheckedBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnStartHoverBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnEndHoverBuffer = nullptr);
    
        template <class R, class ... A>
        void SetDelegate(R (*func)(A ...));
    
    protected:
        bool m_isMouseOver = false;
        bool m_wasClicked = false;
        bool m_isResetOnClicks = false;
        int m_isChecked{};

        std::shared_ptr<sf::SoundBuffer> m_OnCheckedBuffer;
        std::shared_ptr<sf::SoundBuffer> m_OnUncheckedBuffer;
        std::shared_ptr<sf::SoundBuffer> m_OnStartHoverBuffer;
        std::shared_ptr<sf::SoundBuffer> m_OnEndHoverBuffer;
    
        sf::Sound m_sound;

        virtual void OnStartHover();
        virtual void OnEndHover();
        virtual void OnClick();
        virtual void OnReleased(bool away = false);
    
        std::function<void(bool)> m_delegate;
    
    private:
        sf::RectangleShape m_backrect;
        sf::RectangleShape m_checkrect;
    
    };

    template< typename R, typename ... A >
    void CheckBox::SetDelegate(R(*func)(A...))
    {
        m_delegate = std::function<R(A...)>(func);
    }
}
