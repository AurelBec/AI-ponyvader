///
/// \file Squad.hpp
///

#ifndef SQUAD_HPP
#define SQUAD_HPP

#include "../hdr/texture/TextureInvader.hpp"

class Invader : public sf::Drawable, public sf::Transformable {
  public:
    Invader(const sf::Vector2f& center, sf::Texture* texture)
      : m_texture(center, texture){};
    ~Invader() {}

    inline const int getX() const {
        return m_texture.getPosition().x;
    }
    inline const int getY() const {
        return m_texture.getPosition().y;
    }
    inline const sf::FloatRect getGlobalBounds() const {
        return m_texture.getGlobalBounds();
    }
    inline void move(const float offsetX, const float offsetY) {
        m_texture.move(offsetX, offsetY);
    }

  private:
    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_texture);
    }

    TextureInvader m_texture;
};

class Squad : public sf::Drawable, public sf::Transformable {
  public:
    Squad();
    inline ~Squad() {
        for (Invader* invader : m_squad)
            delete invader;
    }

    void update(const float dt);
    void restart(const uint wave);
    void setTextures(const std::vector<sf::Texture*>* const textures) {
        m_textures = textures;
    }
    inline void clear() {
        while (m_squad.size() != 0) {
            delete m_squad.front();
            m_squad.erase(m_squad.begin());
        }
    }
    inline void speedUp() {
        m_speedX += SQUAD_ACCX;
    }
    inline void setSquadSize(const uint row, const uint col) {
        m_row = row;
        m_col = col;
    }
    inline std::vector<Invader*>* const invaders() {
        return &m_squad;
    }
    inline const bool isEmpty() const {
        return m_squad.empty();
    }
    inline const bool isOnTop() const {
        return m_isOnTop;
    }
    inline const int getLowerY() const {
        return m_ymax;
    }
    inline const int getLowerX() const {
        return m_xmax;
    }
    inline const int getDir() const {
        return m_dir;
    }

  private:
    inline void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        for (Invader* invader : m_squad)
            target.draw(*invader);
    }

    const uint                       m_size;
    const uint                       m_space;
    uint                             m_row;
    uint                             m_col;
    int                              m_speedX;
    int                              m_speedY;
    int                              m_dir;
    int                              m_xmax;
    int                              m_xmin;
    int                              m_ymax;
    bool                             m_isOnTop;
    std::vector<Invader*>            m_squad;
    const std::vector<sf::Texture*>* m_textures;
};

#endif