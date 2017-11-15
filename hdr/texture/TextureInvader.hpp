///
/// \file TextureInvader.hpp
///

#ifndef TEXTINVADER_HPP
#define TEXTINVADER_HPP

#include "../define.hpp"
#include <SFML/Graphics.hpp>

class TextureInvader : public sf::Drawable, public sf::Transformable {
  public:
    TextureInvader(const sf::Vector2f& center, const sf::Texture* const texture)
      : m_texture(texture) {
        m_sprite.setTexture(*m_texture);
        m_sprite.setOrigin(m_texture->getSize().x / 2, m_texture->getSize().y / 2);
        m_sprite.setPosition(center);
    }
    ~TextureInvader() {}

    inline const sf::Vector2f getPosition() const {
        return m_sprite.getPosition();
    }
    inline const sf::FloatRect getGlobalBounds() const {
        return m_sprite.getGlobalBounds();
    }
    inline void move(const float offsetX, const float offsetY) {
        m_sprite.move(offsetX, offsetY);
    }

  private:
    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_sprite);
    }

    const sf::Texture* const m_texture;
    sf::Sprite               m_sprite;
};

#endif