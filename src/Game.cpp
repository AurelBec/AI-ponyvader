///
/// \file Game.cpp
///

#include "../hdr/Game.hpp"
#include "../hdr/Moteur2D.hpp"

using namespace sf;
using namespace std;

Game::Game()
  : m_dim(WIN_W, WIN_H)
  , m_isFinish(false)
  , m_wave(1)
  , m_score(0)
  , m_steps(0)
  , m_totalSteps(0)
  , m_textureWave(COLOR2, FONT_SIZE * 3 / 4, "", WIN_W - WIN_H / 20, WIN_H / 20, "rightfix")
  , m_textureScore(COLOR2, FONT_SIZE * 3 / 4, "", WIN_H / 20, WIN_H / 20, "leftfix")
  , m_border() {
    for (uint i(0); i < 6; ++i) {
        m_texturesInvader.push_back(new Texture());
        m_texturesInvader.at(i)->loadFromFile("img/sprite_mob_" + to_string(i) + "_36x36.png");
    }

    m_squad.setTextures(&m_texturesInvader);
    m_textureScore.setString("SCORE <0>");
    m_textureWave.setString("WAVE <1>");
}

void Game::setEnvironment(const bool type) {
    m_environment = type;

    if (m_environment == HUMAN)
        m_agent.setPolicy(new KeyboardPolicy());
    else if (m_environment == LEARNING) {
        m_agent.setPolicy(new MCPolicy(N_STATES, 4));

        time_t     rawtime;
        struct tm* timeinfo;
        char       date[128];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(date, sizeof(date), "%F_%H:%M:%S", timeinfo);

        m_fileNbIter.open(string(date) + "_nbiter.csv");

        m_fileNbIter << m_agent.getParamToStr() << endl;

        cout << "Agent will use those parameters:" << endl;
        cout << m_agent.getParamToStr() << endl << endl;
    }
}

void Game::restart() {
    m_isFinish = false;
    m_wave     = 1;
    m_score    = 0;
    m_steps    = 0;
    m_textureScore.setString("SCORE <0>");
    m_textureWave.setString("WAVE <1>");

    if (m_environment == HUMAN)
        m_squad.setSquadSize(SQUAD_H, SQUAD_W);
    else if (m_environment == LEARNING)
        m_squad.setSquadSize(1, 1);

    random_shuffle(begin(m_texturesInvader), end(m_texturesInvader));
    m_agent.restart();
    m_squad.restart(m_wave);
}

void Game::update(const float dt) {
    m_squad.update(dt);

    if (m_environment == HUMAN)
        m_agent.update(dt);
    else if (m_environment == LEARNING)
        m_agent.update(dt, getActualState(m_agent.getX(), m_squad.getLowerX(), m_squad.getLowerY(), m_squad.getDir()));

    if (Moteur2D::collision(m_agent.getLaser(), m_squad.invaders())) {
        m_score++;
        m_textureScore.setString("SCORE <" + to_string(static_cast<uint>(m_score)) + ">");

        if (m_environment == LEARNING) {
            const unsigned int dSteps(100);
            const unsigned int maxMean(600);
            const unsigned int maxWidth(40);
            const float        minTopReward(m_agent.getMinTopSuccessReward());
            const float        maxTopReward(m_agent.getMaxTopSuccessReward());
            const float        dReward(maxTopReward - minTopReward);

            if (m_squad.isOnTop())
                m_agent.notify(dReward * (WIN_W / 2 - abs(WIN_W / 2 - m_agent.getX())) + minTopReward);
            else
                m_agent.notify(m_agent.getSuccessReward());

            // Log the number of iterations
            // m_fileNbIter << m_steps << ";" << endl;
            // m_fileHReward << m_agent.getHReward() << ";" << endl;
            if (m_score % dSteps == 0) {
                const unsigned int meanSteps = m_totalSteps / dSteps;
                m_totalSteps                 = 0;

                m_fileNbIter << meanSteps << endl;

                for (unsigned int i = 0; i < maxWidth; ++i)
                    cout << ((i != meanSteps / (maxMean / maxWidth)) ? " " : "*");
                cout << "| " << meanSteps << endl;
            }
        } else {
            m_squad.speedUp();
        }
    } else {
        m_agent.notify(m_agent.getFailureReward());
    }

    if (m_squad.isEmpty()) {
        m_totalSteps += m_steps;
        m_wave++;
        m_textureWave.setString("WAVE <" + to_string(static_cast<uint>(m_wave)) + ">");
        random_shuffle(begin(m_texturesInvader), end(m_texturesInvader));

        if (m_environment == HUMAN) {
            m_squad.setSquadSize(SQUAD_H + m_wave / 5, SQUAD_W + m_wave / 3);
            m_squad.restart(m_wave);
        } else {
            m_agent.notifyEndOfEpisode(m_steps);
            m_squad.restart(1);
        }

        m_steps = 0;
    } else if (m_squad.getLowerY() > WIN_H * 9 / 10) {
        if (m_environment == HUMAN) {
            m_isFinish = true;
        } else {
            // cout << "Score: " << m_score << endl;
            restart();
        }
    }

    m_steps++;
}
