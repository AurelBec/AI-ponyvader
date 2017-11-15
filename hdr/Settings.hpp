///
/// \file Settings.hpp
///

#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "define.hpp"
#include <assert.h>
#include <iostream>
#include <sstream>
#include <unistd.h>

class Settings {
  public:
    Settings(int argc, char* argv[]) {
        using namespace std;

        m_ips                            = IPS;
        m_vit                            = VIT;
        m_gui                            = true;
        m_SFMLsettings.antialiasingLevel = AA;

        while (argc > 0) {
            if (string(argv[argc - 1]) == "-ips") {
                istringstream buffer(argv[argc]);
                assert(buffer >> m_ips);
                cout << "Warning : IPS set at " << m_ips << ". Estimate CPU use : " << min(m_ips / 8, 50) << "~"
                     << min(m_ips / 6, 55) << "%." << endl;
            }

            if (string(argv[argc - 1]) == "-vit") {
                istringstream buffer(argv[argc]);
                assert(buffer >> m_vit);
                cout << "Warning : Game speed set at " << m_vit << ". Colliding errors may appear." << endl;
            }

            if (string(argv[argc - 1]) == "-aa") {
                istringstream buffer(argv[argc]);
                assert(buffer >> m_SFMLsettings.antialiasingLevel);
            }

            if (string(argv[argc - 1]) == "--nogui") {
                cout << "Warning: Window will start and stay grey." << endl;
                cout << "Use ESC key to quit." << endl;
                m_gui = false;
            }

            argc--;
        }
    }

    inline const bool isGUIOn() const {
        return m_gui;
    }
    inline const uint getIPS() const {
        return m_ips;
    }
    inline const float getVit() const {
        return m_vit;
    }
    void setIPS(const uint ips) {
        m_ips = ips;
        m_vit = m_ips / 50.0;
    }
    void setVIT(const float vit) {
        m_vit = vit;
        m_ips = m_vit * 50;
    }
    inline const sf::ContextSettings* const getSFMLSettings() {
        return &m_SFMLsettings;
    }

  private:
    float               m_vit;
    int                 m_ips;
    bool                m_gui;
    sf::ContextSettings m_SFMLsettings;
};

#endif