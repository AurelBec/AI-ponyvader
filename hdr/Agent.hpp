///
/// \file Agent.hpp
///

#ifndef AGENT_HPP
#define AGENT_HPP

#include "Laser.hpp"
#include "Policy.hpp"
#include "texture/TextureBase.hpp"

class Agent : public sf::Drawable, public sf::Transformable {
  public:
    Agent();
    inline ~Agent() {
        delete m_policy;
    }

    inline const float getX() const {
        return m_center.x;
    }
    inline const float getY() const {
        return m_center.y;
    }
    inline const float getMinTopSuccessReward() const {
        return m_policy->getMinTopSuccessReward();
    }
    inline const float getMaxTopSuccessReward() const {
        return m_policy->getMaxTopSuccessReward();
    }
    inline const float getSuccessReward() const {
        return m_policy->getSuccessReward();
    }
    inline const float getFailureReward() const {
        return m_policy->getFailureReward();
    }
    inline const std::string getParamToStr() const {
        return m_policy->getParamToStr();
    }
    inline Laser* const getLaser() {
        return &m_laser;
    }
    inline void setSpeed(const uint speed) {
        m_speed = speed;
    }
    inline void updateAction(const sf::Keyboard::Key key, const bool type) {
        m_policy->updateKey(key, type);
    }
    inline void notify(const double r) const {
        m_policy->notify(m_state, m_action, r);
    }
    inline void notifyEndOfEpisode(const uint i) const {
        m_policy->notifyEndOfEpisode(i);
    }

    void setPolicy(Policy* const policy) {
        delete m_policy;
        m_policy = policy;
    }

    void restart() {
        m_center.x = WIN_W / 2;
        m_texture.setX(WIN_W / 2);
        m_policy->restart();
        m_laser.disable();
    }

    void update(const float dt, const uint x = -1);

  private:
    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_texture);
        target.draw(m_laser);
    }

    const sf::Color m_color;
    const uint      m_size;
    uint            m_speed;
    sf::Vector2f    m_center;
    TextureBase     m_texture;
    Policy*         m_policy;
    Laser           m_laser;

    uint m_state;
    uint m_action;
};

#endif