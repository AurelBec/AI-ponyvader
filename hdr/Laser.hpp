///
/// \file Laser.hpp
///

#ifndef LASER_HPP
#define LASER_HPP

#include "define.hpp"
#include <SFML/Graphics.hpp>

class Laser : public sf::Drawable, public sf::Transformable {
  public:
    Laser()
      : m_color(sf::Color::Red)
      , m_texture(sf::Vector2f(5, 12))
      , m_fired(false) {
        m_texture.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y);
        m_texture.setFillColor(m_color);
    }
    ~Laser() {}

    inline const bool isFired() const {
        return m_fired;
    }
    inline void disable() {
        m_fired = false;
    }
    inline const sf::FloatRect getGlobalBounds() const {
        return m_texture.getGlobalBounds();
    }

    void update(const float dt) {
        if (!m_fired)
            return;
        m_texture.move(0, -LASER_SPEED * dt);
        if (m_texture.getPosition().y < 4 * WIN_H / 100 + 6)
            disable();
    }

    void restart(const float x, const float y) {
        m_fired = true;
        m_texture.setPosition(x, y);
    }

  private:
    inline virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        if (m_fired)
            target.draw(m_texture);
    }

    const sf::Color    m_color;
    sf::RectangleShape m_texture;
    bool               m_fired;
};

#endif