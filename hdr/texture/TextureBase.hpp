///
/// \file TextureBase.hpp
///

#ifndef TEXTBASE_HPP
#define TEXTBASE_HPP

#include "../define.hpp"
#include <SFML/Graphics.hpp>

class TextureBase : public sf::Drawable, public sf::Transformable {
  public:
    TextureBase(const sf::Color& color, const sf::Vector2f& center, const uint size)
      : m_y(center.y)
      , m_color(color) {
        const uint unit(size / 8);
        m_rects.push_back(new sf::RectangleShape(sf::Vector2f(13 * unit, 4 * unit)));
        m_rects.push_back(new sf::RectangleShape(sf::Vector2f(11 * unit, 5 * unit)));
        m_rects.push_back(new sf::RectangleShape(sf::Vector2f(3 * unit, 7 * unit)));
        m_rects.push_back(new sf::RectangleShape(sf::Vector2f(unit, 8 * unit)));

        for (sf::RectangleShape* rect : m_rects) {
            rect->setOrigin(rect->getSize().x / 2, rect->getSize().y);
            rect->setFillColor(color);
            rect->setPosition(center.x, m_y);
        }
    }

    inline ~TextureBase() {
        for (sf::RectangleShape* rect : m_rects)
            delete rect;
    }

    void setX(const uint x) {
        for (sf::RectangleShape* rect : m_rects)
            rect->setPosition(x, m_y);
    }

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (sf::RectangleShape* rect : m_rects)
            target.draw(*rect);
    }

    const uint                       m_y;
    const sf::Color                  m_color;
    std::vector<sf::RectangleShape*> m_rects;
};

#endif