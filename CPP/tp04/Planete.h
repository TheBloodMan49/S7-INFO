#ifndef TP04_PLANETE_H
#define TP04_PLANETE_H

#include <vector>
#include <memory>
#include "Mammifere.h"

class Planete {
private:
    std::vector<std::shared_ptr<Mammifere>> _population;
public:
  Planete(uint nb) {
    for (uint i = 0; i < nb; ++i) {
      if (rand() % 2 == 0) {
        _population.push_back(std::make_shared<Baleine>());
      } else {
        _population.push_back(std::make_shared<Ratel>());
      }
    }
  }

  uint population() const {
    return _population.size();
  }

  uint ageMoyen() const {
    uint ageTotal = 0;
    for (const auto & a : _population) {
      ageTotal += a->getAge();
    }
    return ageTotal / _population.size();
  }

  uint poidsMoyenBaleine() const {
    uint poidsTotal = 0;
    uint nbBaleines = 0;
    for (const auto & a : _population) {
      // If the animal is not a Baleine, skip it
      if (std::dynamic_pointer_cast<Baleine>(a) == nullptr)
        continue;
      poidsTotal += a->getPoids();
      nbBaleines++;
    }
    return poidsTotal / nbBaleines;
  }

  void tue_le_doyen() {
    if (_population.empty()) {
      throw std::runtime_error("La planète est déjà déserte");
    }
    auto doyen = _population.begin();
    for (auto it = _population.begin(); it != _population.end(); ++it) {
      if ((*it)->getAge() > (*doyen)->getAge()) {
        doyen = it;
      }
    }
    _population.erase(doyen);
  }
};

#endif //TP04_PLANETE_H
