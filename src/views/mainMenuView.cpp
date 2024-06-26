#include "ftxui/component/component.hpp" // Dla komponentów FTXUI
#include "ftxui/screen/screen.hpp"       // Dla wyjścia terminala
#include <ftxui/component/screen_interactive.hpp> // Added for Screen
#include "../../include/views/interfaceListView.hpp"
#include "./../include/components/ui/mainMenu.hpp"           // Import nowego komponentu mainMenu
#include "./../include/components/ui/viewManager.hpp"

ViewManager viewManager;

ftxui::Component mainMenuView() {
    std::vector<std::wstring> menu_entries = {L"Zarządzaj interfejsami", L"Wyjście"};
    int selected_index = 0;

    auto mainMenuComponent = mainMenu(menu_entries, selected_index);
    return ftxui::Renderer(mainMenuComponent, [&] {
        return ftxui::vbox({
            ftxui::text(L"Główne Menu"),
            ftxui::separator(),
            mainMenuComponent->Render() | ftxui::border
        });
    });
}
