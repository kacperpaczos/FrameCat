#include "mainMenu.hpp"

ftxui::Component mainMenu(std::vector<std::wstring>& menu_entries, int& selected_index) {
    return ftxui::Menu(&menu_entries, &selected_index);
}
