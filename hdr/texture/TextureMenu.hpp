///
/// \file TextureMenu.hpp
///

#ifndef TEXTMENU_HPP
#define TEXTMENU_HPP

#include "TextureBorder.hpp"
#include "TextureText.hpp"

class TextureMenu : public sf::Drawable, public sf::Transformable {
  public:
    TextureMenu(const std::vector<std::string>& names)
      : m_names(names) {
        m_options.push_back(new TextureText(COLOR2, 2.5 * FONT_SIZE, names.front(), WIN_W / 2, WIN_H / 5));
        for (uint i(1); i < names.size() - 1; ++i)
            m_options.push_back(
                new TextureText(COLOR3, 2 * FONT_SIZE, names.at(i), WIN_W / 2, WIN_H / 4 + WIN_H / 10 * i));
        m_options.push_back(new TextureText(COLOR3, 2 * FONT_SIZE, names.back(), WIN_W / 2, 7 * WIN_H / 8));
    }

    inline ~TextureMenu() {
        for (TextureText* option : m_options)
            delete option;
    }

    void updateSelection(const uint option) {
        for (uint i(0); i < m_options.size(); ++i)
            m_options.at(i)->setString(m_names.at(i));

        m_options.at(option + 1)->setString("> " + m_names.at(option + 1) + " <");
    }

    inline const uint getSize() const {
        return m_options.size() - 1;
    }

  private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(m_border);

        for (uint i(0); i < m_options.size(); ++i)
            target.draw(*(m_options[i]));
    }

    const TextureBorder            m_border;
    const std::vector<std::string> m_names;
    std::vector<TextureText*>      m_options;
};

#endif