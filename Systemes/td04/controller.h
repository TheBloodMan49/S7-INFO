#ifndef TD04_CONTROLLER_H
#define TD04_CONTROLLER_H

void lire(char* c);
void ecrire(char c);
char etat_sortie;
char etat_entree;
void demander_it_s();
void demander_it_e();
void supprimer_it_e();
void supprimer_it_s();
void initialiser();

// Instructions processeur
void masquer(int niveau);
void demasquer(int niveau);

#endif //TD04_CONTROLLER_H
