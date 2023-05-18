#pragma once

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

namespace GUICPP
{
    class Widget;

    class Group
    {
    public:
        Group();

        bool HandleEvents(sf::Event& e);
        void Draw(sf::RenderStates& states);

        void AddWidgetToGroup(std::shared_ptr<Widget> widget);
        void RemoveWidgetFromGroup(const Widget* widget);
        void AddChildGroup(std::shared_ptr<Group> child);
        void SetGroupVisibility(bool visibility);
        bool GetGroupVisibility() const;
        void RemoveChildFromGroup();

        // setters
        void SetGroupGlobalPosition(const sf::Vector2f& position);
        void SetGroupRelativePosition(const sf::Vector2f& position);

        // getters
        std::shared_ptr<Group> GetChild() const;
        const std::vector<std::shared_ptr<Widget>>& GetWidgetList() const;
        int GetWidgetListSize() const;

    private:
        std::vector< std::shared_ptr<Group>> m_child;
        std::vector<std::shared_ptr<Widget>> m_widgetList;
        sf::Vector2f m_relativePosition;
        sf::Vector2f m_globalPosition;
        bool m_isVisible;
        sf::RenderWindow* m_window = nullptr;
        
        friend class GUI;
        friend class Widget;
    };
}