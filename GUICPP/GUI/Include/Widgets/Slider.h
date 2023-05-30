// Slider.h
#pragma once

#include "Widget.h"
#include <SFML/Audio.hpp>
#include <functional>
namespace GUICPP
{
    /**
     * \class Slider
     * \brief Represents a slider widget in a GUI.
     *
     * \details The Slider class is a GUI widget that can be used to select a value from a range of values.
     */
    class Slider : public Widget {
    public:
        /**
         * \brief Constructs a Slider object.
         *
         * \param position The position of the slider.
         * \param size The size of the slider.
         * \param barColor The color of the slider bar (optional, default is sf::Color::White).
         * \param sliderColor The color of the slider cursor (optional, default is sf::Color(191, 191, 191)).
         * \param isVertical Specifies whether the slider is vertical (optional, default is false).
         */
        Slider(const sf::Vector2f& position, const sf::Vector2f& size,
               const sf::Color& barColor = sf::Color::White, const sf::Color& sliderColor = sf::Color(191,191,191),
               bool isVertical = false);

        /**
         * \brief Moves the slider to a new position.
         *
         * \param position The new position of the slider.
         */
        void Move(const sf::Vector2f& position) override;

        /**
         * \brief Sets the color of the slider.
         *
         * \param color The new color of the slider.
         */
        void SetColor(const sf::Color& color) override;

        /**
         * \brief Sets the size of the slider.
         *
         * \param size The new size of the slider.
         */
        void SetSize(const sf::Vector2f& size) override;

        /**
         * \brief Sets the position of the slider.
         *
         * \param position The new position of the slider.
         */
        void SetPosition(sf::Vector2f position) override;

        /**
         * \brief Sets the color of the slider bar.
         *
         * \param color The new color of the slider bar.
         */
        virtual void SetBarColor(const sf::Color& color);

        /**
         * \brief Sets the color of the slider cursor.
         *
         * \param color The new color of the slider cursor.
         */
        virtual void SetSliderColor(const sf::Color& color);

        /**
         * \brief Sets the size of the slider cursor.
         *
         * \param size The new size of the slider cursor.
         */
        virtual void SetCursorSize(const sf::Vector2f& size);

        /**
         * \brief Sets the value of the slider based on the cursor position.
         *
         * \param position The position of the cursor.
         * \param value The new value of the slider.
         */
        virtual void SetSliderValue(const sf::Vector2f& position, float value);

        /**
         * \brief Sets whether the slider is vertical or horizontal.
         *
         * \param isVertical Specifies whether the slider is vertical.
         */
        virtual void SetSliderVertical(bool isVertical);

        /**
         * \brief Sets the sound buffers for different slider events.
         *
         * \param OnClickedBuffer Sound buffer for the click event (optional, default is nullptr).
         * \param OnReleasedBuffer Sound buffer for the release event (optional, default is nullptr).
         * \param OnStartHoverBuffer Sound buffer for the start hover event (optional, default is nullptr).
         * \param OnEndHoverBuffer Sound buffer for the end hover event (optional, default is nullptr).
         */
        virtual void SetSound(const std::shared_ptr<sf::SoundBuffer>& OnClickedBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnReleasedBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnStartHoverBuffer = nullptr,
                              const std::shared_ptr<sf::SoundBuffer>& OnEndHoverBuffer = nullptr);

        /**
         * \brief Sets the delegate function for the slider.
         *
         * \tparam R The return type of the delegate function.
         * \tparam A The argument types of the delegate function.
         * \param func The delegate function to set.
         */
        template <class R, class ... A>
        void SetDelegate(R (*func)(A ...));

    protected:
        sf::Vector2f m_cursorSize; /**< The size of the slider cursor. */
        sf::Color m_barColor; /**< The color of the slider bar. */
        sf::Color m_sliderColor; /**< The color of the slider cursor. */
        bool m_isVertical = false; /**< Specifies whether the slider is vertical. */
        bool m_isMouseOver = false; /**< Specifies whether the mouse is over the slider. */
        bool m_isMousePressed = false; /**< Specifies whether the mouse is pressed on the slider. */
        std::shared_ptr<sf::SoundBuffer> m_OnClickBuffer; /**< Sound buffer for the click event. */
        std::shared_ptr<sf::SoundBuffer> m_OnReleasedBuffer; /**< Sound buffer for the release event. */
        std::shared_ptr<sf::SoundBuffer> m_OnStartHoverBuffer; /**< Sound buffer for the start hover event. */
        std::shared_ptr<sf::SoundBuffer> m_OnEndHoverBuffer; /**< Sound buffer for the end hover event. */
        sf::Sound m_sound; /**< Sound object for playing the sound buffers. */
        std::function<void(float)> m_delegate; /**< Delegate function for handling slider events. */
        float m_value = 0; /**< The value of the slider. */
        
        /**
         * \brief Handles the events for the slider.
         *
         * \param e The event to handle.
         * \return True if the event was handled, false otherwise.
         */
        bool HandleEvents(const sf::Event& e) override;

        /**
         * \brief Draws the slider on the screen.
         *
         * \param states The render states to use for drawing.
         */
        void Draw(sf::RenderStates& states) override;

        /**
         * \brief Called when the mouse starts hovering over the slider.
         */
        virtual void OnStartHover();

        /**
         * \brief Called when the mouse stops hovering over the slider.
         */
        virtual void OnEndHover();

        /**
         * \brief Called when the slider is clicked.
         *
         * \param isCursorClicked Specifies whether the cursor was clicked directly.
         */
        virtual void OnClick(bool isCursorClicked = false);

        /**
         * \brief Called when the slider is released.
         *
         * \param away Specifies whether the release occurred outside the slider.
         */
        virtual void OnReleased(bool away = false);

        /**
         * \brief Called when the mouse is held down on the slider.
         */
        virtual void OnMouseHold();

        /**
         * \brief Computes the value of the slider based on the cursor position.
         *
         * \param position The position of the cursor.
         */
        virtual void ComputeValue(sf::Vector2f position);

    private:
        sf::RectangleShape m_bar; /**< The slider bar shape. */
        sf::RectangleShape m_cursor; /**< The slider cursor shape. */

        /**
         * \brief Sets the position of the slider cursor.
         *
         * \param position The new position of the cursor.
         */
        virtual void SetCursorPosition(const sf::Vector2f& position);
    };

    template <class R, class ... A>
    void Slider::SetDelegate(R (*func)(A ...)) {
        m_delegate = std::function<void(float)>(func);
    }
}
