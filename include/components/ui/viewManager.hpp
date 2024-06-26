#ifndef VIEW_MANAGER_HPP
#define VIEW_MANAGER_HPP

#include <ftxui/component/component.hpp>
#include <functional>
#include <map>
#include <string>

class ViewManager {
public:
    void addView(const std::string& name, std::function<ftxui::Component()> createView);
    ftxui::Component switchToView(const std::string& name);
    void switchView(const std::string& name, ftxui::ScreenInteractive& screen);
    
private:
    std::map<std::string, std::function<ftxui::Component()>> views;
    ftxui::Component currentView;
};

#endif // VIEW_MANAGER_HPP