#include "interfaceListView.hpp"
#include "../components/ui/ethernetAdapterList.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>  // Added for MenuOption
#include <ftxui/component/screen_interactive.hpp> // Added for Screen
#include <ftxui/dom/elements.hpp>  // for text

std::string create_interface_list_component() {
    auto networkInterfaces = get_network_interfaces();
    int selectedIndex = 0;  // Variable to store the selected index
    auto interactiveScreen = ftxui::ScreenInteractive::TerminalOutput();
    ftxui::MenuOption menuOptions;  // Menu options
    auto interfaceMenu = ftxui::Menu(&networkInterfaces, &selectedIndex, menuOptions);
    
    auto interfaceRenderer = ftxui::Renderer(interfaceMenu, [&] {
        return ftxui::vbox({
            ftxui::hbox(ftxui::text("Wybrany interfejs: "), ftxui::text(networkInterfaces[selectedIndex])),
            ftxui::separator(),
            interfaceMenu->Render() | ftxui::frame,
        }) | ftxui::border;
    });

    interactiveScreen.Loop(interfaceRenderer | ftxui::CatchEvent([&](const ftxui::Event& event) {
        if (event == ftxui::Event::Return) {
            interactiveScreen.ExitLoopClosure()();
            capture_packets(networkInterfaces[selectedIndex]);
            return true;
        }
        return false;
    }));
    
    return networkInterfaces[selectedIndex];
}