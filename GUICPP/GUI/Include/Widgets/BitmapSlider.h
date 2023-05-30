#pragma once

#include "Slider.h"
#include <SFML/Audio.hpp>
#include <functional>

namespace GUICPP
{
    /**
     * \class BitmapSlider
     * \brief Represents a bitmap slider widget in a GUI.
     *
     * \details BitmapSlider is a GUI widget that extends the functionality of the Slider widget by
     * adding support for bitmap textures for the slider bar and cursor.
     */
    class BitmapSlider : public Slider {
    public:
        /**
         * \brief Constructs a BitmapSlider object.
         *
         * \param position The position of the bitmap slider.
         * \param size The size of the bitmap slider.
         * \param barColor The color of the slider bar (optional, default is sf::Color::White).
         * \param sliderColor The color of the slider cursor (optional, default is sf::Color::White).
         * \param isVertical Specifies whether the slider is vertical (optional, default is false).
         */
        BitmapSlider(const sf::Vector2f& position, const sf::Vector2f& size,
               const sf::Color& barColor = sf::Color::White, const sf::Color& sliderColor = sf::Color::White,
               bool isVertical = false);

        /**
         * \brief Moves the bitmap slider to a new position.
         *
         * \param position The new position of the bitmap slider.
         */
        void Move(const sf::Vector2f& position) override;

        /**
         * \brief Sets the color of the bitmap slider.
         *
         * \param color The new color of the bitmap slider.
         */
        void SetColor(const sf::Color& color) override;

        /**
         * \brief Sets the size of the bitmap slider.
         *
         * \param size The new size of the bitmap slider.
         */
        void SetSize(const sf::Vector2f& size) override;

        /**
         * \brief Sets the position of the bitmap slider.
         *
         * \param position The new position of the bitmap slider.
         */
        void SetPosition(sf::Vector2f position) override;

        /**
         * \brief Sets the color of the bitmap slider bar.
         *
         * \param color The new color of the bitmap slider bar.
         */
        void SetBarColor(const sf::Color& color) override;

        /**
         * \brief Sets the color of the bitmap slider cursor.
         *
         * \param color The new color of the bitmap slider cursor.
         */
        void SetSliderColor(const sf::Color& color) override;

        /**
         * \brief Sets the size of the bitmap slider cursor.
         *
         * \param size The new size of the bitmap slider cursor.
         */
        void SetCursorSize(const sf::Vector2f& size) override;

        /**
         * \brief Sets the value of the bitmap slider based on the cursor position.
         *
         * \param position The position of the cursor.
         * \param value The new value of the bitmap slider.
         */
        void SetSliderValue(const sf::Vector2f& position, float value) override;

        /**
         * \brief Sets whether the bitmap slider is vertical or horizontal.
         *
         * \param isVertical Specifies whether the bitmap slider is vertical.
         */
        void SetSliderVertical(bool isVertical) override;

        /**
         * \brief Sets the offset values for the bitmap slider.
         *
         * \param minOffset The minimum offset value.
         * \param maxOffset The maximum offset value.
         */
        void SetOffset(float minOffset, float maxOffset);

        /**
         * \brief Sets the delegate function for the bitmap slider.
         *
         * \tparam R The return type of the delegate function.
         * \tparam A The argument types of the delegate function.
         * \param func The delegate function to set.
         */
        template <class R, class ... A>
        void SetDelegate(R (*func)(A...));

        /**
         * \brief Sets the folder path and extension for the bitmap textures.
         *
         * \param pathToFolder The path to the folder containing the bitmap textures.
         * \param extension The file extension of the bitmap textures.
         */
        void SetBitmapFolder(const std::string& pathToFolder, const std::string& extension);

    protected:
        sf::Vector2f m_indicatorSize; /**< The size of the bitmap slider indicator. */

        /**
         * \brief Handles the events for the bitmap slider.
         *
         * \param e The event to handle.
         * \return True if the event was handled, false otherwise.
         */
        bool HandleEvents(const sf::Event& e) override;

        /**
         * \brief Draws the bitmap slider on the screen.
         *
         * \param states The render states to use for drawing.
         */
        void Draw(sf::RenderStates& states) override;

        /**
         * \brief Called when the mouse starts hovering over the bitmap slider.
         */
        void OnStartHover() override;

        /**
         * \brief Called when the mouse stops hovering over the bitmap slider.
         */
        void OnEndHover() override;

        /**
         * \brief Called when the bitmap slider is clicked.
         *
         * \param isCursorClicked Specifies whether the cursor was clicked directly.
         */
        void OnClick(bool isCursorClicked = false) override;

        /**
         * \brief Called when the bitmap slider is released.
         *
         * \param away Specifies whether the release occurred outside the bitmap slider.
         */
        void OnReleased(bool away = false) override;

        /**
         * \brief Called when the mouse is held down on the bitmap slider.
         */
        void OnMouseHold() override;

    private:
        sf::Texture m_barDefaultTexture; /**< The default texture for the slider bar. */
        sf::Texture m_barHoverTexture; /**< The hover texture for the slider bar. */
        sf::Texture m_cursorDefaultTexture; /**< The default texture for the slider cursor. */
        sf::Texture m_cursorHoverTexture; /**< The hover texture for the slider cursor. */
        sf::Sprite m_bar; /**< The sprite representing the slider bar. */
        sf::Sprite m_cursor; /**< The sprite representing the slider cursor. */
        float m_minOffset = 0; /**< The minimum offset value. */
        float m_maxOffset = 0; /**< The maximum offset value. */

        /**
         * \brief Sets the position of the bitmap slider cursor.
         *
         * \param position The new position of the cursor.
         */
        void SetCursorPosition(const sf::Vector2f& position) override;

        /**
         * \brief Computes the value of the bitmap slider based on the cursor position.
         *
         * \param position The position of the cursor.
         */
        void ComputeValue(sf::Vector2f position) override;
    };

    template <class R, class ... A>
    void BitmapSlider::SetDelegate(R (*func)(A ...)) {
        m_delegate = std::function<void(float)>(func);
    }
}
