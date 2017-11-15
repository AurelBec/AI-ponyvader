///
/// \file Squad.cpp
///

#include "../hdr/Squad.hpp"
#include <iostream>

using namespace sf;
using namespace std;

Squad::Squad()
  : m_size(36)
  , m_space(m_size / 3)
  , m_row(0)
  , m_col(0)
  , m_speedX(SQUAD_SPEEDX)
  , m_speedY(SQUAD_SPEEDY)
  , m_dir(rand() % 2 ? -1 : 1)
  , m_isOnTop(true) {}

void Squad::restart(const uint wave) {
    float offset(m_size + m_space);
    uint  x((WIN_W - (m_col - 1) * (m_size + m_space)) / 2), y(2.5 * m_size);

    m_speedY = SQUAD_SPEEDY;
    m_speedX = SQUAD_SPEEDX + SQUAD_ACCX * wave;
    m_dir    = rand() % 2 ? -1 : 1;

    clear();
    for (uint i(0); i < m_row; ++i) {
        for (uint j(0); j < m_col; ++j)
            m_squad.push_back(new Invader({x + j * offset, y + i * offset}, m_textures->at(i % m_textures->size())));
    }
}

void Squad::update(const float dt) {
    int  limit(4 * WIN_H / 100 + m_size / 2);
    bool advance(false);
    m_xmax = 0;
    m_ymax = 0;
    m_xmin = WIN_W;

    for (Invader* invader : m_squad) {
        int x(invader->getX()), y(invader->getY());
        m_xmin = min(x, m_xmin);
        m_xmax = max(x, m_xmax);
        m_ymax = max(y, m_ymax);
    }

    if (m_xmin < limit || m_xmax > WIN_W - limit) {
        m_dir *= -1;
        advance   = true;
        m_isOnTop = false;
    }

    for (Invader* invader : m_squad) {
        if (advance)
            invader->move((m_dir > 0) ? (limit - m_xmin + 1) : (WIN_W - limit - m_xmax - 1), m_speedY);
        else
            invader->move(dt * m_speedX * m_dir, 0);
    }
}