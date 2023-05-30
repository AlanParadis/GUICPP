#pragma once
#include "Widgets/CheckBox.h"

namespace GUICPP
{
    /**
     * @class BitmapCheckBox
     * @brief This class provides CheckBox widget functionalities with custom bitmaps.
     * 
     * @details The BitmapCheckBox is derived from the base CheckBox class. It has additional properties like setting custom bitmap for different states of the checkbox.
     */
    class BitmapCheckBox : public CheckBox
    {
    public:

        /**
         * @brief Constructs a BitmapCheckBox with the specified parameters.
         *
         * @param position The initial position of the BitmapCheckBox.
         * @param size The size of the BitmapCheckBox.
         * @param color The color of the BitmapCheckBox. Default is white.
         */
        BitmapCheckBox(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color = sf::Color::White);

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
        void SetChecked(bool state) override;

        /**
         * @brief Sets the bitmap for the checkbox.
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
         * @param away A boolean indicating whether the release event occurred away from the checkbox. Default is false.
         */
        void OnReleased(bool away = false) override;

    private:
        sf::Texture m_CheckedTexture; ///< Texture for the checked state of the checkbox.
        sf::Texture m_CheckedMouseOverTexture; ///< Texture for the checked state when mouse is over the checkbox.
        sf::Texture m_UncheckedTexture; ///< Texture for the unchecked state of the checkbox.
        sf::Texture m_UncheckedMouseOverTexture; ///< Texture for the unchecked state when mouse is over the checkbox.
        sf::Sprite m_sprite; ///< The sprite for displaying the checkbox.
    };
}