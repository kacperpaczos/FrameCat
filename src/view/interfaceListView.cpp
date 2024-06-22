#include "interfaceListView.hpp"
#include "../components/ui/ethernetAdapterList.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>  // Added for MenuOption
#include <ftxui/component/screen_interactive.hpp> // Added for Screen

ftxui::Component create_interface_list_component() {
    auto interfaces = get_network_interfaces();
    int selected = 0;  // Variable to store the selected index
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    ftxui::MenuOption options;  // Menu options
    auto list = ftxui::Menu(&interfaces, &selected, options);
    screen.Loop(list);
    return list;
}