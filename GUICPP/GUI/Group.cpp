#include "Group.h"
#include "Widget.h"

using namespace GUICPP;

Group::Group()
    : m_relativePosition(0.f, 0.f)
    , m_globalPosition(0.f, 0.f)
    , m_isVisible(true)
{
}

bool Group::HandleEvents(sf::Event& event)
{
    bool handled = false;
    if (m_isVisible)
    {
        for (auto& widget : m_widgetList)
        {
            if(widget->HandleEvents(event) && !handled)
            {
                handled = true;
            }
        }
        for (auto& child : m_child)
        {
            if(child->HandleEvents(event) && !handled)
            {
                handled = true;
            }
        }
    }

    return handled;
}

void Group::Draw(sf::RenderStates& states)
{
    if (m_isVisible)
    {
        for (auto& widget : m_widgetList)
        {
            widget->Draw(states);
        }
        for (auto& child : m_child)
        {
            child->Draw(states);
        }
    }
}

void Group::AddWidgetToGroup(std::shared_ptr<Widget> widget)
{
    m_widgetList.push_back(widget);
    sf::Vector2f widgetGlobalPosition = widget->GetPosition();
    widgetGlobalPosition += m_globalPosition;
    widget->SetPosition(widgetGlobalPosition);
}

void Group::RemoveWidgetFromGroup(const Widget* widget)
{
    m_widgetList.erase(
        std::remove_if(
            m_widgetList.begin(),
            m_widgetList.end(),
            [widget](const auto& w) { return w.get() == widget; }),
        m_widgetList.end());
}

void Group::AddChildGroup(std::shared_ptr<Group> child)
{
    m_child.push_back(child);
    sf::Vector2f newPosition = m_globalPosition + child->m_relativePosition;
    child->SetGroupGlobalPosition(newPosition);
}

void Group::SetGroupVisibility(bool visibility)
{
    m_isVisible = visibility;
}

bool Group::GetGroupVisibility() const
{
    return m_isVisible;
}

void Group::RemoveChildFromGroup()
{
    m_child.clear();
}

// setters
void Group::SetGroupGlobalPosition(const sf::Vector2f& position)
{
    m_globalPosition = position;

    for (auto& widget : m_widgetList)
    {
        sf::Vector2f globalPosition = widget->GetPosition();
        sf::Vector2f relativePosition = widget->GetRelativePosition(*this);
        globalPosition = m_globalPosition;
        globalPosition += relativePosition;
        widget->SetPosition(globalPosition);
    }

    for (auto& child : m_child)
    {
        sf::Vector2f globalPosition = child->m_globalPosition;
        sf::Vector2f relativePosition = child->m_relativePosition;
        globalPosition = child->m_globalPosition;
        globalPosition += relativePosition;
        child->SetGroupGlobalPosition(globalPosition);
    }
}

void Group::SetGroupRelativePosition(const sf::Vector2f& position)
{
    m_relativePosition = position;
    sf::Vector2f newPosition = m_globalPosition;

    newPosition -= m_relativePosition;
    m_relativePosition = position;
    newPosition += m_relativePosition;

    SetGroupGlobalPosition(newPosition);
}

// getters
std::shared_ptr<Group> Group::GetChild() const
{
    return m_child.empty() ? nullptr : m_child[0];
}

const std::vector<std::shared_ptr<Widget>>& Group::GetWidgetList() const
{
    return m_widgetList;
}

size_t Group::GetWidgetListSize() const
{
    return m_widgetList.size();
}
