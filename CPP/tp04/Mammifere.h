#ifndef TP04_MAMMIFERE_H
#define TP04_MAMMIFERE_H

#include <iostream>
#include <random>

typedef unsigned int uint;

enum Deplacement {
    marche, nage, vole
};

class Mammifere {
protected:
    uint age;
    uint poids;

    Mammifere(uint age, uint poids) : age(age), poids(poids) {}

public:
    [[nodiscard]] inline uint getAge() const {
        return age;
    }

    [[nodiscard]] inline uint getPoids() const {
        return poids;
    }

    [[nodiscard]] virtual inline Deplacement getDeplacement() const {
        return Deplacement::marche;
    }

    virtual void crier() const = 0;

    virtual ~Mammifere() = default;
};

class Baleine : public Mammifere {
public:
    Baleine(uint age, uint poids) : Mammifere(age, poids) {}

    void crier() const override {
        std::cout << "Baleine: Whouuuuu" << std::endl;
    }

    [[nodiscard]] inline Deplacement getDeplacement() const override {
        return Deplacement::nage;
    }
};

class Ratel : public Mammifere {
public:
    Ratel(uint age, uint poids) : Mammifere(age, poids) {}

    void crier() const override {
        std::cout << "Ratel: Barrrrr" << std::endl;
    }
};


#endif //TP04_MAMMIFERE_H
