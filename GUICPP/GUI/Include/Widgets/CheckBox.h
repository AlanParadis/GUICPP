#pragma once
#include <any>
#include <functional>
#include <SFML/Audio.hpp>

#include "widget.h"

namespace GUICPP
{
    /**
     * @class CheckBox
     * @brief This class provides CheckBox widget functionalities.
     * 
     * @details The CheckBox is derived from the base Widget class.
     */
    class CheckBox : public Widget
    {
    public:
    
        /**
         * @brief Constructs a CheckBox with the specified parameters.
         *
         * @param position The initial position of the CheckBox.
         * @param size The size of the CheckBox.
         * @param color The color of the CheckBox. Default is white.
         */
        CheckBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::White);

        /**
         * @brief Handles the events.
         *
         * @param e The event to handle.
         * @return Returns a bool indicating if the event has been handled.
         */
        bool HandleEvents(const sf::Event& e) override;

        /**
         * @brief Draws the CheckBox with the given render states.
         *
         * @param states The render states to use while drawing.
         */
        void Draw(sf::RenderStates& states) override;

        /**
         * @brief Moves the CheckBox to the given position.
         *
         * @param position The position to move the CheckBox to.
         */
        void Move(const sf::Vector2f& position) override;

        /**
         * @brief Sets the color of the CheckBox.
         *
         * @param color The color to set.
         */
        void SetColor(const sf::Color& color) override;

        /**
         * @brief Sets the size of the CheckBox.
         *
         * @param size The size to set.
         */
        void SetSize(const sf::Vector2f& size) override;

        /**
         * @brief Sets the position of the CheckBox.
         *
         * @param position The position to set.
         */
        void SetPosition(sf::Vector2f position) override;

        /**
         * @brief Sets the checked state of the CheckBox.
         *
         * @param state The checked state to set.
         */
        virtual void SetChecked(bool state);

        /**
         * @brief Sets the sound buffer for different events of CheckBox.
         *
         * @param OnCheckedBuffer Sound buffer when CheckBox is checked.
         * @param OnUncheckedBuffer Sound buffer when CheckBox is unchecked.
         * @param OnStartHoverBuffer Sound buffer when mouse starts to hover over the CheckBox.
         * @param OnEndHoverBuffer Sound buffer when mouse stops hovering over the CheckBox.
         */
        virtual void SetSound(const std::shared_ptr<sf::SoundBuffer>& OnCheckedBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnUncheckedBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnStartHoverBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnEndHoverBuffer = nullptr);
    
        /**
         * @brief Sets the delegate function to be executed when checkbox state is changed.
         *
         * @param func The function to be set as delegate.
         */
        template <class R, class ... A>
        void SetDelegate(R (*func)(A ...));
    
    protected:
        bool m_isMouseOver = false; ///< Indicates whether the mouse is over the checkbox.
        bool m_wasClicked = false; ///< Indicates whether the checkbox was clicked.
        bool m_isResetOnClicks = false; ///< Indicates whether to reset the checkbox state on clicks.
        int m_isChecked{}; ///< Indicates whether the checkbox is checked.

        std::shared_ptr<sf::SoundBuffer> m_OnCheckedBuffer; ///< Sound buffer for the checked state.
        std::shared_ptr<sf::SoundBuffer> m_OnUncheckedBuffer; ///< Sound buffer for the unchecked state.
        std::shared_ptr<sf::SoundBuffer> m_OnStartHoverBuffer; ///< Sound buffer for the start hover state.
        std::shared_ptr<sf::SoundBuffer> m_OnEndHoverBuffer; ///< Sound buffer for the end hover state.
    
        sf::Sound m_sound; ///< The sound to play during checkbox events.

        /**
         * @brief Handler for the start hover event.
         */
        virtual void OnStartHover();

        /**
         * @brief Handler for the end hover event.
         */
        virtual void OnEndHover();

        /**
         * @brief Handler for the click event.
         */
        virtual void OnClick();

        /**
         * @brief Handler for the release event.
         *
         * @param away A boolean indicating whether the release event occurred away from the checkbox. Default is false.
         */
        virtual void OnReleased(bool away = false);
    
        std::function<void(bool)> m_delegate; ///< The delegate function to execute when checkbox state is changed.
    
    private:
        sf::RectangleShape m_backrect; ///< The background rectangle of the checkbox.
        sf::RectangleShape m_checkrect; ///< The check mark rectangle of the checkbox.
    
    };

    /**
     * @brief Sets the delegate function to be executed when checkbox state is changed.
     *
     * @param func The function to be set as delegate.
     */
    template< typename R, typename ... A >
    void CheckBox::SetDelegate(R(*func)(A...))
    {
        m_delegate = std::function<R(A...)>(func);
    }
}