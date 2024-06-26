#include "../../include/views/interfaceListView.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>  // Added for MenuOption
#include <ftxui/component/screen_interactive.hpp> // Added for Screen
#include <ftxui/dom/elements.hpp>  // for text
#include "../../../include/components/backend/networkInterfaces.hpp"

ftxui::Component interfaceListView() {
    auto ethernetAdapters = getEthernetAdapters();
    // return ftxui::Renderer([&] {
    //     return ftxui::vbox({
    //         ftxui::text(L"Lista interfejsów"),
    //         ftxui::separator(),
    //         ethernetAdapterList(ethernetAdapters) | ftxui::border
    //     });
    // });
}
