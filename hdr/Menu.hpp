///
/// \file Menu.hpp
///

#ifndef MENU_HPP
#define MENU_HPP

#include "../hdr/Agent.hpp"
#include "../hdr/texture/TextureMenu.hpp"

enum MENU { MENU_PRINCIPAL = 0, MENU_END = 1, MENU_OPTION = 2 };
enum OPTION { OPTION_QUIT = 0, OPTION_GAME_HUMAN = 1, OPTION_GAME_AI = 2 };

class Menu : public sf::Drawable, public sf::Transformable {
  public:
    Menu();
    ~Menu();

    const uint  prevMenu();
    const uint  nextMenu();
    inline void nextSelection() {
        m_sOption.back() += (m_sOption.back() < m_menus[m_sMenu]->getSize() - 1);
    }
    inline void prevSelection() {
        m_sOption.back() -= (m_sOption.back() > 0);
    }

    inline void ending() {
        m_sMenu = MENU_END;
        m_sOption.push_back(0);
    }
    inline void update(const float dt) {
        m_menus.at(m_sMenu)->updateSelection(m_sOption.back());
        m_agentDemo.update(dt);
    }

  private:
    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(*(m_menus.at(m_sMenu)));
        target.draw(m_agentDemo);
    }

    uint                      m_sMenu;
    std::vector<uint>         m_sOption;
    std::vector<TextureMenu*> m_menus;
    Agent                     m_agentDemo;
};

#endif