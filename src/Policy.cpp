///
/// \file Policy.cpp
///

#include "../hdr/Policy.hpp"

using namespace sf;
using namespace std;

const uint RandomPolicy::getDecision(const uint X) {
    uint r(rand() % (8 * m_actionState.size()));
    if (r < m_actionState.size())
        for (uint i(0); i < m_actionState.size(); ++i)
            m_actionState.at(i) = (r == i);

    for (uint i(0); i < m_actionState.size(); ++i)
        if (m_actionState[i])
            return i + 1;

    return Action_NOTHING;
}

const uint KeyboardPolicy::getDecision(const uint X) {
    for (uint i(0); i < m_actionState.size(); ++i)
        if (m_actionState[i])
            return i + 1;

    return Action_NOTHING;
}

void KeyboardPolicy::updateKey(Keyboard::Key key, const bool type) {
    for (uint i(0); i < m_actionState.size(); ++i)
        if (key == m_control[i])
            m_actionState[i] = type;
}

const bool MCPolicy::firstVisit(const uint x, const uint a) {
    bool r(false);
    if (Rvisit[x][a] == false) {
        r            = true;
        Rvisit[x][a] = true;
    }

    return r;
}

const uint MCPolicy::getDecision(const uint x) {
    uint a(chooseAction(x));
    if (DEBUG_ON) {
        const uint xr(x % (N_STATES / 2));
        const int  dir((x > N_STATES / 2) ? 1 : -1), d(60 - xr % (2 * dW)), Ym(xr / (2 * dW));
        cout << "Q: " << x << " = [" << d << "," << Ym << "," << dir << "] -> ";
        for (double a : Q[x])
            cout << Q[x][a] << " ";
        cout << endl << "Decision: " << a << endl;
        cout << endl;
    }

    return a;
}

void MCPolicy::notifyEndOfEpisode(const uint i) {
    iteration = i;
    updateQ_episode();
    // hreward = episode.back()->getR() * pow(alpha, iteration);
    restart();
}

const uint MCPolicy::chooseAction(const uint x) const {
    uint a(Action_NOTHING);

    if (optimal) {
        a = argmax(pi[x]);
    } else {
        double s(sum(pi[x]));
        double r((s * rand()) / RAND_MAX);

        if (DEBUG_ON) {
            cout << "pi(A|X) = ";
            for (double val : pi[x])
                cout << val << " ";
            cout << endl << "sum pi(A|X) " << s << " - random: " << r << endl;
        }

        double c(0);
        while (c < s + 1) {
            c += pi[x][a];
            if (DEBUG_ON) {
                // cout << "  - action " << a << " p(A|X) = " << pi[x][a] << endl;
                // cout << "    - rand " << r << " < c " << c << endl;
            }

            if (r < c || a == pi[x].size() - 1)
                break;

            a++;
        }
    }

    if (DEBUG_ON)
        cout << "Action " << a << endl;

    return a;
}

const double MCPolicy::rreturn(uint k) const {
    double r(0.0), g(1.0);
    while (k < episode.size()) {
        Episode* ep = episode[k];
        r += g * ep->getR();
        g *= gamma;
        k++;
    }

    return r;
}

void MCPolicy::updateQ_episode() {
    if (optimal)
        return;

    double eps((epsilon >= 0) ? epsilon : 0.9 * (1.0 - 1.0 / (1.0 + exp(-0.01 * (iteration - 500)))) + 0.05);

    for (uint x(0); x < Rvisit.size(); ++x)
        for (uint a(0); a < Rvisit[x].size(); ++a)
            Rvisit[x][a] = false;

    int k(0);
    for (Episode* ep : episode) {
        double x(ep->getX()), a(ep->getA());
        if (firstVisit(x, a)) {
            addR(x, a, rreturn(k));
            Q[x][a] = getRavg(x, a);
        }
        k++;
    }

    for (Episode* ep : episode) {
        uint x(ep->getX());
        uint bestAction(argmax(Q[x]));

        for (uint a(0); a < nactions; ++a)
            if (a == bestAction)
                pi[x][a] = 1.0 - eps + eps / nactions;
            else
                pi[x][a] = eps / nactions;

        if (DEBUG_ON) {
            cout << "[D] episode step " << (&ep) << endl;
            cout << "[D] Q(x,:) = ";
            for (double a : Q[x])
                cout << a << " ";
            cout << endl << "[D] best action " << bestAction << endl;
            cout << "[D] pi(a,:) = ";
            for (double a : pi[x])
                cout << a << " ";
            cout << endl;
        }
    }
}

const uint argmax(const vector<double>& v) {
    uint a(0);
    for (uint i(1); i < v.size(); ++i)
        if (v[i] > v[a])
            a = i;

    return a;
}

const double sum(const vector<double>& v) {
    double s(0);
    for (uint i(0); i < v.size(); ++i)
        s += v[i];

    return s;
}

const uint max(const uint a, const uint b) {
    return a > b ? a : b;
}
