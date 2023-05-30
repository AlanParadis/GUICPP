#pragma once

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

namespace GUICPP
{
    class Widget;

    /**
     * @brief This class represents a group of widgets. The group can contain child groups.
     * It provides methods to handle events, draw the group and manipulate the widgets and child groups.
     */
    class Group
    {
    public:
        /**
         * @brief Default constructor for the Group.
         */
        Group();

        /**
         * @brief Handle SFML events for this group.
         * 
         * @param e The SFML event to handle.
         * @return bool Returns true if the event is handled.
         */
        bool HandleEvents(sf::Event& e);

        /**
         * @brief Draw this group with the specified render states.
         * 
         * @param states The render states to use when drawing.
         */
        void Draw(sf::RenderStates& states);

        /**
         * @brief Add a widget to this group.
         * 
         * @param widget The widget to add.
         */
        void AddWidgetToGroup(std::shared_ptr<Widget> widget);

        /**
         * @brief Remove a widget from this group.
         * 
         * @param widget The widget to remove.
         */
        void RemoveWidgetFromGroup(const Widget* widget);

        /**
         * @brief Add a child group to this group.
         * 
         * @param child The child group to add.
         */
        void AddChildGroup(std::shared_ptr<Group> child);

        /**
         * @brief Set the visibility of this group.
         * 
         * @param visibility The visibility state to set.
         */
        void SetGroupVisibility(bool visibility);

        /**
         * @brief Get the visibility of this group.
         * 
         * @return bool Returns the visibility state of the group.
         */
        bool GetGroupVisibility() const;

        /**
         * @brief Remove a child group from this group.
         */
        void RemoveChildFromGroup();

        /**
         * @brief Set the global position of this group.
         * 
         * @param position The global position to set.
         */
        void SetGroupGlobalPosition(const sf::Vector2f& position);

        /**
         * @brief Set the relative position of this group.
         * 
         * @param position The relative position to set.
         */
        void SetGroupRelativePosition(const sf::Vector2f& position);

        /**
         * @brief Get a child group from this group.
         * 
         * @return std::shared_ptr<Group> Returns a shared pointer to a child group.
         */
        std::shared_ptr<Group> GetChild() const;

        /**
         * @brief Get the list of widgets in this group.
         * 
         * @return const std::vector<std::shared_ptr<Widget>>& Returns a constant reference to the vector of shared pointers to widgets.
         */
        const std::vector<std::shared_ptr<Widget>>& GetWidgetList() const;

        /**
         * @brief Get the number of widgets in this group.
         * 
         * @return size_t Returns the size of the widget list.
         */
        size_t GetWidgetListSize() const;

    private:
        std::vector< std::shared_ptr<Group>> m_child; ///< The child groups of this group.
        std::vector<std::shared_ptr<Widget>> m_widgetList; ///< The list of widgets in this group.
        sf::Vector2f m_relativePosition; ///< The relative position of this group.
        sf::Vector2f m_globalPosition; ///< The global position of this group.
        bool m_isVisible; ///< The visibility state of this group.
        sf::RenderWindow* m_window = nullptr; ///< The render window to draw this group on.
        
        friend class GUI;
        friend class Widget;
    };
}