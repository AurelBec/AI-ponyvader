///
/// \file Game.hpp
///

#ifndef GAME_HPP
#define GAME_HPP

#include "Agent.hpp"
#include "Squad.hpp"
#include "texture/TextureBorder.hpp"
#include "texture/TextureText.hpp"
#include <fstream>
#include <iostream>

class Game : public sf::Drawable, public sf::Transformable {
  public:
    Game();
    inline ~Game() {
        for (sf::Texture* texture : m_texturesInvader)
            delete texture;
        m_fileNbIter.close();
    }

    inline const bool isFinish() const {
        return m_isFinish;
    }
    inline const uint getScore() const {
        return m_score;
    }
    inline const uint getWave() const {
        return m_wave;
    }
    void setEnvironment(const bool type);

    void        restart();
    void        update(const float dt);
    inline void clear() {
        m_squad.clear();
    }
    inline void updateAction(const sf::Keyboard::Key key, const bool type) {
        m_agent.updateAction(key, type);
    }

  private:
    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_textureWave);
        target.draw(m_textureScore);
        target.draw(m_border);
        target.draw(m_agent);
        target.draw(m_squad);
    }
    inline const uint getActualState(const uint dxA, const uint dxM, const uint dyM, const int dir) const {
        return ((dir > 0) ? (N_STATES / 2) : 0) + (dyM * 2 * dW + dxA - dxM) / DISCRET_DIM + dW;
    }

    const sf::Vector2f m_dim;
    bool               m_environment;
    bool               m_isFinish;
    uint               m_wave;
    uint               m_score;
    uint               m_steps;
    uint               m_totalSteps;

    std::vector<sf::Texture*> m_texturesInvader;
    TextureText               m_textureWave;
    TextureText               m_textureScore;
    TextureBorder             m_border;

    std::ofstream m_fileNbIter;

    Agent m_agent;
    Squad m_squad;
};

#endif
