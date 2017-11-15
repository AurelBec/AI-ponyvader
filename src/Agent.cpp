///
/// \file Agent.cpp
///

#include "../hdr/Agent.hpp"

#include <iostream>

using namespace sf;
using namespace std;

Agent::Agent()
  : m_color(COLOR4)
  , m_size(AGENT_SIZE)
  , m_speed(AGENT_SPEED)
  , m_center(WIN_W / 2, 96 * WIN_H / 100)
  , m_texture(m_color, m_center, m_size)
  , m_policy(new VoidPolicy()) {}

void Agent::update(const float dt, const uint x) {
    m_state  = x;
    m_action = m_policy->getDecision(x);

    switch (m_action) {
        case Action_LEFT:
            m_center.x -= m_speed * dt;
            break;
        case Action_RIGHT:
            m_center.x += m_speed * dt;
            break;
        case Action_SHOOT:
            if (!m_laser.isFired())
                m_laser.restart(m_center.x, m_center.y - m_size);
            break;

        default:
            break;
    }

    uint limit(WIN_H - m_center.y + m_size * 13 / 16 + 1);
    if (m_center.x < limit)
        m_center.x = limit;
    else if (m_center.x >= WIN_W - limit)
        m_center.x = WIN_W - limit;

    m_texture.setX(m_center.x);
    m_laser.update(dt);
}
