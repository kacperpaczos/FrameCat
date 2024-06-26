#include "../../../include/components/ui/viewManager.hpp"
#include <ftxui/component/screen_interactive.hpp> // Added for Screen

void ViewManager::addView(const std::string& name, std::function<ftxui::Component()> createView) {
    views[name] = createView;
}

ftxui::Component ViewManager::switchToView(const std::string& name) {
    auto it = views.find(name);
    if (it != views.end()) {
        currentView = it->second();
    }
    return currentView;
}

void ViewManager::switchView(const std::string& name, ftxui::ScreenInteractive& screen) {
    screen.ExitLoopClosure()();
    screen.Loop(switchToView(name));
}
