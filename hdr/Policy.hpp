///
/// \file Policy.hpp
///

#ifndef POLICY_HPP
#define POLICY_HPP

#include "define.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

enum Action { Action_NOTHING, Action_SHOOT, Action_LEFT, Action_RIGHT };

class Policy {
  public:
    Policy()
      : m_actionState(3, false) {}
    virtual ~Policy(){};

    inline void restart() {
        m_actionState = std::vector<bool>(3, false);
    }
    virtual inline void        notify(const uint x, const uint a, const double r) {}
    virtual inline void        notifyEndOfEpisode(const uint i) {}
    virtual inline const float getMinTopSuccessReward() const {
        return 0.0;
    }
    virtual inline const float getMaxTopSuccessReward() const {
        return 0.0;
    }
    virtual inline const float getSuccessReward() const {
        return 0.0;
    }
    virtual inline const float getFailureReward() const {
        return 0.0;
    }
    virtual inline const std::string getParamToStr() const {
        return "";
    }
    virtual const uint getDecision(const uint X)                         = 0;
    virtual void       updateKey(sf::Keyboard::Key key, const bool type) = 0;

  protected:
    std::vector<bool> m_actionState;
};

class VoidPolicy : public Policy {
  public:
    VoidPolicy(){};
    ~VoidPolicy(){};

    const uint getDecision(const uint X) override {
        return Action_NOTHING;
    }
    void updateKey(sf::Keyboard::Key key, const bool type) override {}
};

class RandomPolicy : public Policy {
  public:
    RandomPolicy(){};
    ~RandomPolicy(){};

    const uint getDecision(const uint X) override;
    void       updateKey(sf::Keyboard::Key key, const bool type) override {}
};

class KeyboardPolicy : public Policy {
  public:
    KeyboardPolicy(){};
    ~KeyboardPolicy(){};

    const uint getDecision(const uint X);
    void       updateKey(sf::Keyboard::Key key, const bool type);

  private:
    std::vector<sf::Keyboard::Key> m_control = {sf::Keyboard::Up, sf::Keyboard::Left, sf::Keyboard::Right};
};

////////////////////////////////////////////////////////////////////////
//                                                                    //
//  //  // ////// //    //  //    ////// ////// ////// ////// //      //
//  //  // //  // //     ////     //  // //  // //  // //  // //      //
//  ////// //  // //      //      //     ////// ////// ////// //      //
//  //  // //  // //      //      // /// // //  //  // //  // //      //
//  //  // ////// //////  //      ////   //  // //  // //  // //////  //
//                                                                    //
////////////////////////////////////////////////////////////////////////

const uint   argmax(const std::vector<double>& v);
const double sum(const std::vector<double>& v);
const uint   max(const uint a, const uint b);

class Episode {
  public:
    Episode(const uint X, const uint A, const double R)
      : x(X)
      , a(A)
      , r(R) {}
    ~Episode(){};

    inline const uint getX() const {
        return x;
    }
    inline const uint getA() const {
        return a;
    }
    inline const double getR() const {
        return r;
    }

    std::ostream& operator<<(std::ostream& out) {
        out << x << " " << a << " " << r;
        return out;
    }

  private:
    const uint   x;
    const uint   a;
    const double r;
};

class MCPolicy : public Policy {
  public:
    MCPolicy(const uint _nstates, const uint _nactions)
      : gamma(1.0)
      , epsilon(0.4)
      , minTopSuccessReward(600.f)
      , maxTopSuccessReward(1000.f)
      , successReward(100.f)
      , failureReward(-50.f)
      , optimal(false)
      , iteration(0)
      , nactions(_nactions)
      , Q(_nstates, std::vector<double>(_nactions, 0.0))
      , pi(_nstates, std::vector<double>(_nactions, 1.0))
      , Rsum(_nstates, std::vector<double>(_nactions, 0.0))
      , Rcnt(_nstates, std::vector<double>(_nactions, 0.0))
      , Rvisit(_nstates, std::vector<bool>(_nactions, false)) {}

    ~MCPolicy() {
        for (Episode* ep : episode)
            delete ep;
    }

    const uint getDecision(const uint X) override;
    void       updateKey(sf::Keyboard::Key key, const bool type) override {}

    inline void restart() {
        m_actionState = std::vector<bool>(3, false);
        while (episode.size()) {
            delete episode.front();
            episode.erase(episode.begin());
        }
    }
    // const truc saveData() const { return [Q, pi, Rsum, Rcnt];}
    // const void loadData(data) { Q = data[0]; pi = data[1]; Rsum = data[2]; Rcnt
    // = data[3];}

    inline void notify(const uint X, const uint A, const double r) override {
        episode.push_back(new Episode(X, A, r));
    }
    void                     notifyEndOfEpisode(const uint i) override;
    void                     updateQ_episode();
    inline const std::string getParamToStr() const override {
        return "gamma: " + std::to_string(static_cast<double>(gamma)) +
               "\nepsilon: " + std::to_string(static_cast<double>(epsilon)) +
               "\nmaxSuccessReward: " + std::to_string(static_cast<float>(maxTopSuccessReward)) +
               "\nminSuccessReward: " + std::to_string(static_cast<float>(minTopSuccessReward)) +
               "\nsuccessReward: " + std::to_string(static_cast<float>(successReward)) +
               "\nfailureReward: " + std::to_string(static_cast<float>(failureReward));
    }
    inline const float getMinTopSuccessReward() const override {
        return minTopSuccessReward;
    }
    inline const float getMaxTopSuccessReward() const override {
        return maxTopSuccessReward;
    }
    inline const float getSuccessReward() const override {
        return successReward;
    }
    inline const float getFailureReward() const override {
        return failureReward;
    }

  private:
    inline const double getRavg(const uint X, const uint A) const {
        return Rsum[X][A] / Rcnt[X][A];
    }
    inline const void addR(const uint X, const uint A, const double r) {
        Rsum[X][A] += r;
        Rcnt[X][A]++;
    }
    const bool   firstVisit(const uint X, const uint A);
    const uint   chooseAction(const uint X) const;
    const double rreturn(uint k) const;

    const double gamma;    // discount factor
    const double epsilon;  // epsilon greedy factor
    const float  minTopSuccessReward;
    const float  maxTopSuccessReward;
    const float  successReward;
    const float  failureReward;
    bool         optimal;
    uint         iteration;
    uint         nactions;

    std::vector<Episode*>            episode;
    std::vector<std::vector<double>> Q;
    std::vector<std::vector<double>> pi;
    std::vector<std::vector<double>> Rsum;
    std::vector<std::vector<double>> Rcnt;
    std::vector<std::vector<bool>>   Rvisit;
};

#endif