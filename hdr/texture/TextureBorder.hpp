///
/// \file TextureBorder.hpp
///

#ifndef TEXTBORDER_HPP
#define TEXTBORDER_HPP

#include "../define.hpp"
#include <SFML/Graphics.hpp>

class TextureBorder : public sf::Drawable, public sf::Transformable {
  public:
    TextureBorder()
      : m_dim(WIN_W - 3 * WIN_H / 50 + 2 * WIN_BORD, WIN_H - 3 * WIN_H / 50 + 2 * WIN_BORD) {
        uint x(WIN_W / 2 - m_dim.x / 2), y(WIN_H / 2 - m_dim.y / 2), w(m_dim.x), h(m_dim.y);

        for (uint i(0); i < 4; ++i) {
            m_border[i]             = sf::VertexArray(sf::Quads, 4);
            m_border[i][0].position = sf::Vector2f(x + (w - WIN_BORD) * (i == 1), y + (h - WIN_BORD) * (i == 2));
            m_border[i][1].position = sf::Vector2f(x - (w - WIN_BORD) * (i == 3) + w, y + (h - WIN_BORD) * (i == 2));
            m_border[i][2].position =
                sf::Vector2f(x - (w - WIN_BORD) * (i == 3) + w, y - (h - WIN_BORD) * (i == 0) + h);
            m_border[i][3].position = sf::Vector2f(x + (w - WIN_BORD) * (i == 1), y + h - (h - WIN_BORD) * (i == 0));

            for (uint j(0); j < 4; ++j)
                m_border[i][j].color = COLOR2;
        }
    }

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (uint i(0); i < 4; ++i)
            target.draw(m_border[i]);
    }

    const sf::Vector2f m_dim;
    sf::VertexArray    m_border[4];
};

#endif