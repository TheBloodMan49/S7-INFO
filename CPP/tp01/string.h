#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <algorithm>

namespace mystring {

	class string
	{

		char* _data; // pointeur sur tableau de char alloué dynamiquement et redimensionné selon les besoins
		unsigned int _physic_size; // mémorise la taille actuelle physique du tableau:
      // la taille logique de la chaine stockée à l'intérieur est géré en compatibilité C: elle se termine par '\0'
    explicit string(unsigned int size); // constructeur privé pour allouer un tableau de taille size
    string(char c); // constructeur privé pour allouer un tableau de taille 2 et y stocker le caractère c

	public:
		string(); // constructeur sans argument: chaine vide: tableau avec un '\0' dans la première case
    string(const char* s); // constructeur à partir d'une chaine C
    string(const string& s); // constructeur par copie
    string(string&& s) noexcept ; // constructeur par déplacement
    ~string(); // destructeur: libère la mémoire allouée dynamiquement

		string operator+ (const string& s) const; // concaténation de deux chaines
    char operator[] (unsigned int i) const; // accesseur en lecture seule à un caractère de la chaine
    char& operator[] (unsigned int i); // accesseur en lecture-écriture à un caractère de la chaine
    bool operator== (const string& s) const; // comparaison de deux chaines
    bool operator== (const char* s) const; // comparaison d'une chaine avec une chaine C
    string& operator= (const string& s); // affectation d'une chaine à une autre
    bool operator< (const string& s) const; // comparaison de deux chaines
    bool operator> (const string& s) const; // comparaison de deux chaines
    string& operator+= (const string& s); // concaténation de deux chaines

    unsigned int size() const {
      return _physic_size - 1;
    }
    char* begin() const {
      return _data;
    }
    char* end() const {
      return _data + _physic_size - 1;
    }

    unsigned int find(const char* s) const; // recherche d'une chaine C dans une chaine
    string substr(unsigned int pos, unsigned int len) const; // extraction d'une sous-chaine

    friend std::ostream& operator<<(std::ostream &os, const string &s); // affichage d'une chaine
    friend std::istream& operator>>(std::istream &is, string &s); // lecture d'une chaine
	};

}
#endif