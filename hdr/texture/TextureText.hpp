///
/// \file TextureText.hpp
///

#ifndef TEXTTEXT_HPP
#define TEXTTEXT_HPP

#include "../define.hpp"
#include <SFML/Graphics.hpp>
#include <assert.h>
#include <iostream>

class TextureText : public sf::Drawable, public sf::Transformable {
  public:
    TextureText(const sf::Color&   color,
                const uint         font_size,
                const std::string& str    = "",
                const float        x      = 0,
                const float        y      = 0,
                const std::string& method = "center")
      : m_method(static_cast<char>(method[0])) {
        assert(m_font.loadFromFile(FONT));

        m_text.setFont(m_font);
        m_text.setCharacterSize(font_size);
        m_text.setColor(color);

        setString(str);
        m_text.setPosition(x, y);
    }

    ~TextureText() {}

    void setString(const std::string& str) {
        switch (m_method) {
            case 'r': {  // right
                const sf::Vector2f oldPos(m_text.getPosition());
                const float        oldW(m_text.getLocalBounds().width);
                m_text.setString(str);
                m_text.setOrigin(0, 0);
                m_text.setPosition(oldPos.x - m_text.getLocalBounds().width + oldW, oldPos.y);
                break;
            }
            case 'l': {  // left
                m_text.setString(str);
                m_text.setOrigin(0, 0);
                break;
            }
            case 't': {  // top
                break;
            }
            case 'b': {  // bottom
                break;
            }
            case 'c': {  // center
                m_text.setString(str);
                const sf::FloatRect bound(m_text.getLocalBounds());
                m_text.setOrigin(bound.left + bound.width / 2, bound.top + bound.height / 2);
                break;
            }
        }
    }

  private:
    inline virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_text, states);
    }

    sf::Font   m_font;
    sf::Text   m_text;
    const char m_method;
};

#endif