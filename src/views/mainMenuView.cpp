#include "ftxui/component/component.hpp" // Dla komponentów FTXUI
#include "ftxui/screen/screen.hpp"       // Dla wyjścia terminala
#include <ftxui/component/screen_interactive.hpp> // Added for Screen
#include "./interfaceListView.hpp"
#include "../components/ui/mainMenu.hpp"           // Import nowego komponentu mainMenu
bool mainMenuView()
{
    std::vector<std::wstring> menu_entries = {L"Zarządzaj interfejsami", L"Wyjście"};
    int selected_index = 0;

    auto mainMenuComponent = mainMenu(menu_entries, selected_index);
    auto mainMenuRenderer = ftxui::Renderer(mainMenuComponent, [&]
                                            { return ftxui::vbox({ftxui::text(L"Główne Menu"),
                                                                  ftxui::separator(),
                                                                  mainMenuComponent->Render() | ftxui::border}); });

    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    screen.Loop(mainMenuRenderer | ftxui::CatchEvent([&](const ftxui::Event& event) {
        if (event == ftxui::Event::Return) {
            screen.ExitLoopClosure()();
            switch (selected_index)
            {
            case 0:
                create_interface_list_component(); // Zakładamy, że ta funkcja jest zdefiniowana gdzie indziej
                break;
            case 1:
                break;
            }
            return true;
        }
        return false;
    }));

    return true;
}
