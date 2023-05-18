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
    class GUI {
    public:
        GUI(sf::RenderWindow& window);

        void HandleEvents(const sf::Event& e);
        void Draw(sf::RenderStates& states) const;
    
        void AddWidgetToGui(const std::shared_ptr<Widget>& widget);
        void RemoveWidgetFromGui(const std::shared_ptr<Widget>& widget);

        [[nodiscard]] sf::Font* GetFont() const;
        [[nodiscard]] unsigned int GetDefaultSize() const;

    private:
        sf::RenderWindow& m_window;

        std::vector<std::shared_ptr<Group>> m_groupList;
        
        std::vector<std::shared_ptr<Widget>> m_widgetList;
        //std::vector<std::shared_ptr<Group>> groupList;
        std::shared_ptr<sf::Font> m_defaultFont;
        unsigned int m_defaultSize;
        std::shared_ptr<Widget> m_isLockBy;

        bool m_isShowingHandCursor;
        sf::Cursor m_arrowCursor;
        sf::Cursor m_handCursor;

        bool HandleEventsFromWidgetList(const sf::Event& e);
        void DrawFromWidgetList(sf::RenderStates& states) const;

        bool HandleEventsFromGroupList(sf::Event event);
        void DrawFromGroupList(sf::RenderStates& states);
    };
}
