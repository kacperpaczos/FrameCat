#ifndef UI_MAIN_MENU_HPP
#define UI_MAIN_MENU_HPP

#include "ftxui/component/component.hpp" // Dla komponentów FTXUI
#include <vector>
#include <string>

ftxui::Component mainMenu(std::vector<std::wstring>& menu_entries, int& selected_index);

#endif // UI_MAIN_MENU_HPP
