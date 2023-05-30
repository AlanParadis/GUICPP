#pragma once

#include <SFML/Graphics.hpp>

namespace GUICPP
{
    /**
     * @brief Widget class is the base class for all GUI widgets.
     */
    class Widget
    {
    public:
        /**
         * @brief Construct a new Widget object.
         * 
         * @param m_position Initial position of the Widget.
         * @param m_size Initial size of the Widget.
         * @param m_color Initial color of the Widget.
         */
        Widget(const sf::Vector2f& m_position, const sf::Vector2f& m_size,
               const sf::Color& m_color) : m_position(m_position),
                                           m_size(m_size),
                                           m_color(m_color){}
        
        /**
         * @brief Virtual destructor for the Widget.
         */
        virtual ~Widget() = default;
    
        /**
         * @brief Move the Widget to a new position.
         *
         * @param position New position for the Widget.
         */
        virtual void Move(const sf::Vector2f& position) = 0;
        
        /**
         * @brief Set a new color for the Widget.
         *
         * @param color New color for the Widget.
         */
        virtual void SetColor(const sf::Color& color) = 0;
        
        /**
         * @brief Set a new size for the Widget.
         *
         * @param size New size for the Widget.
         */
        virtual void SetSize(const sf::Vector2f& size) = 0;

        /**
         * @brief Set a new position for the Widget.
         *
         * @param position New position for the Widget.
         */
        virtual void SetPosition(sf::Vector2f position) = 0;
        
        /**
         * @brief Get the current position of the Widget.
         *
         * @return Current position of the Widget.
         */
        sf::Vector2f GetPosition();

        /**
         * @brief Get the position of the Widget relative to a group.
         *
         * @param Group The group to get the relative position to.
         * @return The position of the Widget relative to the group.
         */
        sf::Vector2f GetRelativePosition(class Group& Group);

    protected:
        sf::Vector2f m_position = sf::Vector2f(0, 0); /**< Position of the Widget */
        sf::Vector2f m_size; /**< Size of the Widget */
        sf::Color m_color = sf::Color::White; /**< Color of the Widget */
    
        sf::RenderWindow* m_window = nullptr; /**< Window in which the Widget is rendered */

        /**
         * @brief Handle events for the Widget. This must be implemented in a derived class.
         *
         * @param e Event to handle.
         * @return true if the event was handled, false otherwise.
         */
        virtual bool HandleEvents(const sf::Event& e) = 0;

        /**
         * @brief Draw the Widget. This must be implemented in a derived class.
         *
         * @param states Render states to use when drawing.
         */
        virtual void Draw(sf::RenderStates& states) = 0;
    
    private:
        /**
         * @brief Set the Window for the Widget.
         *
         * @param window Window in which the Widget is to be rendered.
         */
        void SetWindow(sf::RenderWindow* window);
    
        /**
         * @brief Friend classes.
         */
        friend class GUI;
        friend class Group;
    };
}
