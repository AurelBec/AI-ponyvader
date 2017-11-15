///
/// \file Moteur2D.cpp
///

#include "../hdr/Moteur2D.hpp"

using namespace std;
using namespace sf;

Moteur2D::Moteur2D(Settings& s)
  : m_state(s.isGUIOn() ? IN_MENU : IN_GAME_AI)
  , m_settings(s)
  , m_window(VideoMode(WIN_W, WIN_H), NAME, Style::Default, *(s.getSFMLSettings()))
  , m_affFPS(Color::Red, FONT_SIZE / 2, "", WIN_W, 5, "rightfix")
  , m_guiOff(Color::White, FONT_SIZE, "GUI off, press SPACE", WIN_W / 2, WIN_H / 2, "center") {}

void Moteur2D::run() {
    switch (m_state) {
        case IN_GAME_HUMAN:
            updateGameClassic();
            break;

        case IN_GAME_AI:
            updateGameLearning();
            break;

        case IN_MENU:
            updateMenu();
            break;

        default:
            break;
    }
}

void Moteur2D::updateMenu() {
    float dt(0);
    Time  T(seconds(1.f / m_settings.getIPS()));
    bool  paused(false);
    Event event;

    while (m_window.isOpen()) {
        while (m_window.pollEvent(event)) {
            switch (static_cast<int>(event.type)) {
                case Event::Closed:
                    m_window.close();
                    break;

                case Event::LostFocus:
                    paused = true;
                    break;

                case Event::GainedFocus:
                    paused = false;
                    break;

                case Event::KeyPressed:
                    switch (static_cast<int>(event.key.code)) {
                        case Keyboard::Escape:
                            switch (m_menu.prevMenu()) {
                                case QUIT:
                                    m_window.close();
                                    break;

                                default:
                                    break;
                            }
                            break;

                        case Keyboard::Return:
                            switch (m_menu.nextMenu()) {
                                case IN_GAME_HUMAN:
                                    updateGameClassic();
                                    m_menu.ending();
                                    break;

                                case IN_GAME_AI:
                                    updateGameLearning();
                                    m_menu.ending();
                                    break;

                                case QUIT:
                                    m_window.close();
                                    break;

                                default:
                                    break;
                            }
                            break;

                        case Keyboard::Up:
                            m_menu.prevSelection();
                            break;
                        case Keyboard::Left:
                            m_menu.prevSelection();
                            break;
                        case Keyboard::Down:
                            m_menu.nextSelection();
                            break;
                        case Keyboard::Right:
                            m_menu.nextSelection();
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }

        dt = m_clock.restart().asSeconds();
        if (!paused) {
            m_menu.update(dt);
            m_affFPS.setString(to_string(static_cast<uint>(ceil(1 / dt))));

            m_window.clear(COLOR1);
            m_window.draw(m_menu);
            m_window.draw(m_affFPS);
            m_window.display();
        }

        sleep(T - m_clock.getElapsedTime());
    }
}

void Moteur2D::updateGameClassic() {
    float dt(0);
    Time  T(seconds(1.f / m_settings.getIPS()));
    bool  paused(false);
    Event event;

    m_game.setEnvironment(HUMAN);
    m_game.restart();

    while (m_window.isOpen() && !m_game.isFinish()) {
        while (m_window.pollEvent(event)) {
            switch (static_cast<int>(event.type)) {
                case Event::Closed:
                    m_window.close();
                    break;

                case Event::LostFocus:
                    paused = true;
                    break;

                case Event::GainedFocus:
                    paused = false;
                    break;

                case Event::KeyPressed:
                    if (event.key.code == Keyboard::Escape)
                        updateMenu();  // quit the game if ESC pressed
                    else if (event.key.code == Keyboard::Space)
                        paused = !paused;  // paused the game if SPACE pressed
                    if (!paused)
                        m_game.updateAction(event.key.code, true);
                    break;

                case Event::KeyReleased:
                    if (!paused)
                        m_game.updateAction(event.key.code, false);
                    break;

                default:
                    break;
            }
        }

        dt = m_clock.restart().asSeconds();
        if (!paused) {
            m_game.update(dt * m_settings.getVit());
            m_affFPS.setString(to_string(static_cast<uint>(ceil(1 / dt))));

            m_window.clear(COLOR1);
            m_window.draw(m_game);
            m_window.draw(m_affFPS);
            m_window.display();
        }

        sleep(T - m_clock.getElapsedTime());
    }

    m_game.clear();
}

void Moteur2D::updateGameLearning() {
    float dt(0);
    bool  speedUp(true), guiOn(m_settings.isGUIOn());
    int   state(guiOn ? 1 : 0);
    Event event;

    m_game.setEnvironment(LEARNING);
    m_game.restart();
    m_window.clear(COLOR1);
    m_window.display();

    while (m_window.isOpen() && !m_game.isFinish()) {
        while (m_window.pollEvent(event)) {
            switch (static_cast<int>(event.type)) {
                case Event::Closed:
                    m_window.close();
                    break;

                case Event::KeyPressed:
                    if (event.key.code == Keyboard::Escape)
                        updateMenu();  // quit the game if ESC pressed
                    else if (event.key.code == Keyboard::Space)
                        switch (state) {
                            case 0:
                                guiOn   = true;
                                speedUp = true;
                                state   = 1;
                                break;
                            case 1:
                                guiOn   = true;
                                speedUp = false;
                                state   = 2;
                                break;
                            case 2:
                                guiOn   = false;
                                speedUp = true;
                                state   = 0;
                                m_window.clear(COLOR1);
                                m_window.draw(m_guiOff);
                                m_window.display();
                                break;
                        }
                    break;

                default:
                    break;
            }
        }

        dt = m_clock.restart().asSeconds();
        m_game.update(dt * (speedUp ? SPEED_SIMU : 3));

        if (guiOn) {
            m_affFPS.setString(to_string(static_cast<uint>(ceil(1 / dt))));

            m_window.clear(COLOR1);
            m_window.draw(m_game);
            m_window.draw(m_affFPS);
            m_window.display();
        }

        sleep(seconds(1.f / (IPS * (speedUp ? SPEED_SIMU : 3))) - m_clock.getElapsedTime());
    }

    m_game.clear();
}

const bool Moteur2D::collision(Laser* const laser, std::vector<Invader*>* const squad) {
    if (!laser->isFired())
        return false;

    for (uint i(0); i < squad->size(); ++i) {
        if (laser->getGlobalBounds().intersects(squad->at(i)->getGlobalBounds())) {
            laser->disable();
            delete squad->at(i);
            squad->erase(squad->begin() + i);
            return true;
        }
    }

    return false;
}
