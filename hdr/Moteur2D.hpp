///
/// \file Moteur2D.hpp
///

#ifndef MOTEUR2D_HPP
#define MOTEUR2D_HPP

#include "../hdr/Game.hpp"
#include "../hdr/Menu.hpp"
#include "../hdr/Settings.hpp"
#include <SFML/Window.hpp>
#include <thread>

enum State { QUIT = 0, IN_GAME_HUMAN = 1, IN_GAME_AI = 2, IN_MENU = 3 };

class Moteur2D {
  public:
    Moteur2D(Settings& s);
    ~Moteur2D() {}

    void run();

    static const bool collision(Laser* const laser, std::vector<Invader*>* const squad);

  private:
    void updateGameClassic();
    void updateGameLearning();
    void updateMenu();

    uint             m_state;
    const Settings   m_settings;
    sf::RenderWindow m_window;
    sf::Clock        m_clock;

    Menu        m_menu;
    Game        m_game;
    TextureText m_affFPS;
    TextureText m_guiOff;
};

#endif