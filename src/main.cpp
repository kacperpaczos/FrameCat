#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "../include/components/ui/viewManager.hpp"
#include "../include/views/mainMenuView.hpp"
#include "../include/views/interfaceListView.hpp"

int main() {
    ViewManager viewManager;

    // Dodajemy widoki do ViewManagera
    viewManager.addView("main_menu", []() { return mainMenuView(); });
    viewManager.addView("interface_list", []() { return interfaceListView(); });

    // Tworzymy interaktywny ekran
    auto screen = ftxui::ScreenInteractive::TerminalOutput();

    // Rozpoczynamy od widoku głównego menu
    screen.Loop(viewManager.switchToView("main_menu"));

    return 0;
}