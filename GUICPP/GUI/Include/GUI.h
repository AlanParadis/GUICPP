#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>

#include "Group.h"
#include "Widgets/BitmapButton.h"
#include "Widgets/BitmapCheckBox.h"
#include "Widgets/BitmapSlider.h"

namespace GUICPP
{
    /**
     * @class GUI
     * @brief A graphical user interface manager for widgets and groups.
     */
    class GUI {
    public:
        /**
         * @brief Construct the GUI object, initializing the GUI manager with a provided window.
         * @param window The render window for the GUI to be drawn on.
         */
        GUI(sf::RenderWindow& window);

        /**
         * @brief Handle incoming SFML events.
         * @param e SFML Event to handle.
         */
        void HandleEvents(const sf::Event& e);

        /**
         * @brief Draw the GUI onto the provided render states.
         * @param states The states to draw the GUI onto.
         */
        void Draw(sf::RenderStates& states) const;
    
        /**
         * @brief Add a widget to the GUI.
         * @param widget The widget to add.
         */
        void AddWidgetToGui(const std::shared_ptr<Widget>& widget);
        
        /**
         * @brief Remove a widget from the GUI.
         * @param widget The widget to remove.
         */
        void RemoveWidgetFromGui(const std::shared_ptr<Widget>& widget);

        /**
         * @brief Add a group to the GUI.
         * @param group The group to add.
         */
        void AddGroupToGui(const std::shared_ptr<Group>& group);
        
        /**
         * @brief Remove a group from the GUI.
         * @param group The group to remove.
         */
        void RemoveGroupFromGui(const std::shared_ptr<Group>& group);
        
        /**
         * @brief Get the default font of the GUI.
         * @return Pointer to the default sf::Font object.
         */
        [[nodiscard]] sf::Font* GetFont() const;
        
        /**
         * @brief Get the default size of the GUI.
         * @return The default size as an unsigned integer.
         */
        [[nodiscard]] unsigned int GetDefaultSize() const;
    private:
        sf::RenderWindow& m_window;

        std::vector<std::shared_ptr<Group>> m_groupList;
        
        std::vector<std::shared_ptr<Widget>> m_widgetList;
        std::shared_ptr<sf::Font> m_defaultFont;
        unsigned int m_defaultSize;
        std::shared_ptr<Widget> m_isLockBy;

        bool m_isShowingHandCursor;
        sf::Cursor m_arrowCursor;
        sf::Cursor m_handCursor;
        
        /**
         * @brief Handle events from widget list.
         * @param e SFML Event to handle.
         * @return True if the event has been handled by any widget.
         */
        bool HandleEventsFromWidgetList(const sf::Event& e);
        
        /**
         * @brief Draw widgets from widget list onto provided render states.
         * @param states The states to draw the widgets onto.
         */
        void DrawFromWidgetList(sf::RenderStates& states) const;

        /**
         * @brief Handle events from group list.
         * @param e SFML Event to handle.
         * @return True if the event has been handled by any group.
         */
        bool HandleEventsFromGroupList(sf::Event e) const;
        
        /**
         * @brief Draw groups from group list onto provided render states.
         * @param states The states to draw the groups onto.
         */
        void DrawFromGroupList(sf::RenderStates& states) const;
    };
}
