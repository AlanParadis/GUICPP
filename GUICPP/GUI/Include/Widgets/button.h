#pragma once

#include <any>
#include <functional>
#include <SFML/Audio.hpp>

#include "widget.h"

namespace GUICPP
{
    /**
    * @class Button
    * @brief Represents a GUI button with event handling.
    *
    * @details This class is a part of GUICPP library and extends the Widget class. It provides various methods for event handling, drawing, positioning, color, and text setting.
    */
    class Button : public Widget
    {
    public:
        /**
         * @brief Constructs a new Button.
         *
         * @param position The position of the Button.
         * @param size The size of the Button.
         * @param color The color of the Button. Default is White.
         * @param text The text of the Button. Default is an empty string.
         * @param characterSize The character size of the Button text. Default is 31.
         */
        Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::White,
               const std::string& text = "", unsigned int characterSize = 31);

        /**
         * @brief Handles events for the Button.
         *
         * @param e The event to handle.
         * @return bool indicating success or failure.
         */
        bool HandleEvents(const sf::Event& e) override;

        /**
         * @brief Draws the Button.
         *
         * @param states The RenderStates to use when drawing.
         */
        void Draw(sf::RenderStates& states) override;

        /**
         * @brief Moves the Button.
         *
         * @param position The new position of the Button.
         */
        void Move(const sf::Vector2f& position) override;

        /**
         * @brief Sets the color of the Button.
         *
         * @param color The new color of the Button.
         */
        void SetColor(const sf::Color& color) override;

        /**
         * \brief Sets the size of the Button.
         * \param size The new size of the Button.
         */
        void SetSize(const sf::Vector2f& size) override;

        /**
         * @brief Sets the Button's position.
         *
         * @param position The new position of the Button.
         */
        void SetPosition(sf::Vector2f position) override;

        /**
         * @brief Sets the Button's font.
         *
         * @param font The new font of the Button.
         */
        void SetFont(const sf::Font& font);

        /**
         * @brief Sets the Button's text.
         *
         * @param text The new text of the Button.
         */
        void SetText(const std::string& text);

        /**
         * @brief Sets the Button's font size.
         *
         * @param size The new size of the Button's font.
         */
        void SetFontSize(unsigned int size);

        /**
         * @brief Sets the Button's sounds.
         *
         * @param OnClickBuffer The sound to be played when the button is clicked.
         * @param OnReleasedBuffer The sound to be played when the button is released.
         * @param OnStartHoverBuffer The sound to be played when the mouse starts hovering over the button.
         * @param OnEndHoverBuffer The sound to be played when the mouse stops hovering over the button.
         */
        virtual void SetSound(const std::shared_ptr<sf::SoundBuffer>& OnClickBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnReleasedBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnStartHoverBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnEndHoverBuffer = nullptr);

        /**
         * @brief Sets a delegate function to be called in some context.
         *
         * @param func The function to be used as delegate.
         * @param args The arguments to be passed to the delegate function.
         */
        template <typename Callable, typename... Args>
        void SetDelegate(Callable&& func, Args&&... args);
     
    protected:
        bool m_isMouseOver = false; ///< Indicates if the mouse is over the Button.
        bool m_wasClicked = false; ///< Indicates if the Button was clicked.
        bool m_isResetOnClicks = false; ///< Indicates if the Button should be reset after being clicked.

        std::shared_ptr<sf::SoundBuffer> m_OnClickBuffer; ///< The sound buffer to play when the Button is clicked.
        std::shared_ptr<sf::SoundBuffer> m_OnReleasedBuffer; ///< The sound buffer to play when the Button is released. */
        std::shared_ptr<sf::SoundBuffer> m_OnStartHoverBuffer; ///< The sound buffer to play when the mouse enters the Button. */
        std::shared_ptr<sf::SoundBuffer> m_OnEndHoverBuffer; ///< The sound buffer to play when the mouse leaves the Button. */

        sf::Sound m_sound; ///< The sound to play when the Button is clicked. */
        std::function<void(std::vector<std::any>&)> m_delegate; ///< The delegate function to be called. */
        std::vector<std::any> m_delegateArgs; ///< The arguments to be passed to the delegate function. */

        /**
         * \brief Called when the mouse enters the Button.
         */
        virtual void OnStartHover();
        /**
         * \brief Called when the mouse leaves the Button.
         */
        virtual void OnEndHover();
        /**
         * \brief Called when the Button is clicked.
         */
        virtual void OnClick();
        /**
         * \brief  Called when the Button is released.
         * \param away Indicates if the mouse is away from the Button.
         */
        virtual void OnReleased(bool away = false);
    private:
        sf::RectangleShape m_rect; ///< The shape of the Button.
        sf::Text m_text; ///< The text of the Button.

    };

    template <typename Callable, typename... Args>
    void Button::SetDelegate(Callable&& func, Args&&... args)
    {
        m_delegate = std::bind(std::forward<Callable>(func), std::forward<Args>(args)...);
    }
}
