#ifndef TP04_MAMMIFERE_H
#define TP04_MAMMIFERE_H

#include <iostream>
#include <random>

typedef unsigned int uint;

enum Deplacement { rien, marche, nage, vole };

class Mammifere {
protected:
  uint age;
  uint poids;
  Deplacement deplacement;

  Mammifere(uint age, uint poids) : age(age), poids(poids) {
    deplacement = rien;
  }

public:
  inline uint getAge() const {
    return age;
  }
  inline uint getPoids() const {
    return poids;
  }
  inline Deplacement getDeplacement() const {
    return deplacement;
  }
  virtual void crier() const = 0;

  virtual ~Mammifere() = default;
};

class Baleine : public Mammifere {
  constexpr static uint ageMax = 200;
  constexpr static uint poidsMax = 150000;
public:
  Baleine(uint age, uint poids) : Mammifere(age, poids) {
    deplacement = nage;
  }
  Baleine() : Baleine(rand() % ageMax, rand() % poidsMax) {}
  virtual void crier() const {
    std::cout << "Baleine: Whouuuuu" << std::endl;
  }
};

class Ratel : public Mammifere {
  constexpr static uint ageMax = 20;
  constexpr static uint poidsMax = 30;
public:
  Ratel(uint age, uint poids) : Mammifere(age, poids) {
    deplacement = marche;
  }
  Ratel() : Ratel(rand() % ageMax, rand() % poidsMax) {}
  virtual void crier() const {
    std::cout << "Ratel: Barrrrr" << std::endl;
  }
};


#endif //TP04_MAMMIFERE_H
