#include "GUI.h"
#include "Widget.h"
#include "Widgets/button.h"

namespace GUICPP
{
    
    GUI::GUI(sf::RenderWindow& window) : m_window(window), m_defaultSize(30), m_isLockBy(nullptr), m_isShowingHandCursor(false)
    {
        m_defaultFont = std::make_shared<sf::Font>();
        if (!m_defaultFont->loadFromFile("C:/Windows/Fonts/arial.ttf"))
        {
            throw std::runtime_error("Error loading default font");
        }
        m_arrowCursor.loadFromSystem(sf::Cursor::Arrow);
        m_handCursor.loadFromSystem(sf::Cursor::Hand);
    }

    void GUI::HandleEvents(const sf::Event& e) {
        m_isShowingHandCursor = false;
        const bool tmp = HandleEventsFromWidgetList(e) || HandleEventsFromGroupList(e);
        if (!m_isShowingHandCursor) {
            m_isShowingHandCursor = tmp;
        }

        if (m_isShowingHandCursor) {
            m_window.setMouseCursor(m_handCursor);
        } else {
            m_window.setMouseCursor(m_arrowCursor);
        }
    }

    void GUI::Draw(sf::RenderStates& states) const
    {
        DrawFromWidgetList(states);
        DrawFromGroupList(states);
    }

    void GUI::AddWidgetToGui(const std::shared_ptr<Widget>& widget) {
        widget->SetWindow(&m_window);

        // if widget is a button, set the default font
        const auto button = dynamic_cast<Button*>(widget.get());
        if (button != nullptr) {
            button->SetFont(*m_defaultFont);
        }
    
        m_widgetList.push_back(widget);
    }

    void GUI::RemoveWidgetFromGui(const std::shared_ptr<Widget>& widget) {
        std::erase(m_widgetList, widget);
    }

    void GUI::AddGroupToGui(const std::shared_ptr<Group>& group)
    {
        m_groupList.push_back(group);

        for (auto& widget : group->GetWidgetList()) {
            widget->SetWindow(&m_window);
            // if widget is a button, set the default font
            const auto button = dynamic_cast<Button*>(widget.get());
            if (button != nullptr) {
                button->SetFont(*m_defaultFont);
            }
        }
    }

    void GUI::RemoveGroupFromGui(const std::shared_ptr<Group>& group)
    {
        std::erase(m_groupList, group);
    }

    sf::Font* GUI::GetFont() const
    {
        return m_defaultFont.get();
    }

    unsigned int GUI::GetDefaultSize() const
    {
        return m_defaultSize;
    }

    bool GUI::HandleEventsFromWidgetList(const sf::Event& e) {
        if (m_window.isOpen()) {
            for (auto& widget : m_widgetList) {
                bool tmp = false;

                if (m_isLockBy == widget || m_isLockBy == nullptr) {
                    tmp = widget->HandleEvents(e);
                }
                if (!m_isShowingHandCursor) {
                    m_isShowingHandCursor = tmp;
                    if ((tmp && m_isLockBy == nullptr)) {
                        m_isLockBy = widget;
                    } else if (!tmp && m_isLockBy == widget) {
                        m_isLockBy = nullptr;
                    }
                }
            }
            return m_isShowingHandCursor;
        } else {
            return false;
        }
    }

    void GUI::DrawFromWidgetList(sf::RenderStates& states) const
    {
        for (auto& widget : m_widgetList) {
            widget->Draw(states);
        }
    }

    bool GUI::HandleEventsFromGroupList(sf::Event e) const
    {
        for (auto& group : m_groupList) {
            if (group->HandleEvents(e)) {
                return true;
            }
        }
        return false;
    }

    void GUI::DrawFromGroupList(sf::RenderStates& states) const
    {
        for (auto& group : m_groupList) {
            group->Draw(states);
        }
    }

}
