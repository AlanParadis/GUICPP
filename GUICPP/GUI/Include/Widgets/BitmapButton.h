#pragma once
#include "Widgets/button.h"

namespace GUICPP
{
    /**
     * @class BitmapButton
     * @brief This class provides button functionality with custom bitmaps.
     * 
     * @details The BitmapButton is derived from the base Button class. It has additional properties like setting custom bitmap for different states of the button.
     */
    class BitmapButton : public Button
    {
    public:

        /**
         * @brief Constructs a BitmapButton with the specified parameters.
         *
         * @param position The initial position of the BitmapButton.
         * @param size The size of the BitmapButton.
         * @param color The color of the BitmapButton. Default is white.
         */
        BitmapButton( const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::White);
        
        /**
         * @brief Handles the events.
         *
         * @param e The event to handle.
         * @return Returns a bool indicating if the event has been handled.
         */
        bool HandleEvents(const sf::Event& e) override;

        /**
         * @brief Draws the button with the given render states.
         *
         * @param states The render states to use while drawing.
         */
        void Draw(sf::RenderStates& states) override;

        /**
         * @brief Moves the button to the given position.
         *
         * @param position The position to move the button to.
         */
        void Move(const sf::Vector2f& position) override;

        /**
         * @brief Sets the color of the button.
         *
         * @param color The color to set.
         */
        void SetColor(const sf::Color& color) override;

        /**
         * @brief Sets the size of the button.
         *
         * @param size The size to set.
         */
        void SetSize(const sf::Vector2f& size) override;

        /**
         * @brief Sets the position of the button.
         *
         * @param position The position to set.
         */
        void SetPosition(sf::Vector2f position) override;

        /**
         * @brief Sets the bitmap for the button.
         *
         * @param pathToFolder The path to the folder containing the bitmap files.
         * @param extension The extension of the bitmap files.
         */
        void SetBitmapFolder(const std::string& pathToFolder, const std::string& extension);

    protected:
        /**
         * @brief Handler for the start hover event.
         */
        void OnStartHover() override;

        /**
         * @brief Handler for the end hover event.
         */
        void OnEndHover() override;

        /**
         * @brief Handler for the click event.
         */
        void OnClick() override;

        /**
         * @brief Handler for the release event.
         *
         * @param away A boolean indicating whether the release event occurred away from the button. Default is false.
         */
        void OnReleased(bool away = false) override;

    private:
        sf::Texture m_defaultTexture; ///< Texture for the default state of the button.
        sf::Texture m_hoverTexture; ///< Texture for the hover state of the button.
        sf::Texture m_clickTexture; ///< Texture for the click state of the button.

        sf::Sprite m_sprite; ///< Sprite used to render the button.

        sf::Vector2f m_size; ///< Size of the button.
    
    };
}