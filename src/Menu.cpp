///
/// \file Menu.cpp
///

#include "../hdr/Menu.hpp"

using namespace sf;
using namespace std;

Menu::Menu()
  : m_sMenu(MENU_PRINCIPAL)
  , m_sOption({0}) {
    m_menus.push_back(new TextureMenu({NAME, "Human Player", "RLMC Agent", "Options", "QUIT"}));
    m_menus.push_back(new TextureMenu({"You loose", "BYE BYE"}));
    m_menus.push_back(new TextureMenu({"OPTIONS", "Null", "Null", "BACK"}));
    m_agentDemo.setPolicy(new RandomPolicy());
    m_agentDemo.setSpeed(120);
}

Menu::~Menu() {
    for (TextureMenu* menu : m_menus)
        delete menu;
}

const uint Menu::prevMenu() {
    switch (m_sMenu) {
        case MENU_OPTION:
            m_sMenu = MENU_PRINCIPAL;
            break;

        default:
            return OPTION_QUIT;
            break;
    }

    m_sOption.pop_back();

    return 3;
}

const uint Menu::nextMenu() {
    switch (m_sMenu) {
        case MENU_END:
            m_sMenu = MENU_PRINCIPAL;
            break;

        case MENU_PRINCIPAL:
            switch (m_sOption.back()) {
                case 0:
                    return OPTION_GAME_HUMAN;
                    break;

                case 1:
                    return OPTION_GAME_AI;
                    break;

                case 2:
                    m_sMenu = MENU_OPTION;
                    break;

                default:
                    return OPTION_QUIT;
                    break;
            }
            break;

        case MENU_OPTION:
            switch (m_sOption.back()) {
                default:
                    return prevMenu();
                    break;
            }
            break;

        default:
            break;
    }

    m_sOption.push_back(0);

    return 3;
}
