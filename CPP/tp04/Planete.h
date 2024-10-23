#ifndef TP04_PLANETE_H
#define TP04_PLANETE_H

#include "Mammifere.h"
#include <algorithm>
#include <memory>
#include <numeric>
#include <random>
#include <vector>

class Planete {
private:
    std::vector<std::unique_ptr<Mammifere>> _population;

public:
    explicit Planete(uint nb) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> poids_baleine(3000, 200000);
        std::uniform_int_distribution<> poids_ratel(5, 30);
        std::uniform_int_distribution<> age_baleine(0, 200);
        std::uniform_int_distribution<> age_ratel(0, 20);
        std::bernoulli_distribution dis(0.5);
        for (uint i = 0; i < nb; ++i) {
            if (dis(gen)) {
                _population.push_back(std::make_unique<Baleine>(age_baleine(gen), poids_baleine(gen)));
            } else {
                _population.push_back(std::make_unique<Ratel>(age_ratel(gen), poids_ratel(gen)));
            }
        }
    }

    [[nodiscard]] uint population() const {
        return _population.size();
    }

    [[nodiscard]] uint ageMoyen() const {

        uint ageTotal = std::accumulate(_population.begin(), _population.end(), 0,
                                        [](uint acc, const std::unique_ptr<Mammifere> &a) {
                                            return acc + a->getAge();
                                        });
        return ageTotal / _population.size();
    }

    [[nodiscard]] uint poidsMoyenBaleine() const {
        uint nbBaleines = 0;
        uint poidsTotal = std::accumulate(_population.begin(), _population.end(), 0,
                                          [&nbBaleines](uint acc, const std::unique_ptr<Mammifere> &a) {
                                              if (dynamic_cast<Baleine *>(a.get())) {
                                                  ++nbBaleines;
                                                  return acc + a->getPoids();
                                              }
                                              return acc;
                                          });
        return poidsTotal / nbBaleines;
    }

    void tue_le_doyen() {
        if (_population.empty()) {
            throw std::runtime_error("La planète est déjà déserte");
        }

        auto doyen = std::max_element(_population.begin(), _population.end(),
                                      [](const std::unique_ptr<Mammifere> &a, const std::unique_ptr<Mammifere> &b) {
                                          return a->getAge() < b->getAge();
                                      });
        _population.erase(doyen);
    }
};

#endif//TP04_PLANETE_H
