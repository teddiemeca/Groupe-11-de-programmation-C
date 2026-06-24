#ifndef CALCUL_POLYNOME_H_INCLUDED
#define CALCUL_POLYNOME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


typedef struct composant_polynome CPolynome;
typedef struct corp_polynome Polynome;

struct composant_polynome{
    int coefficient;
    int exposant;

    CPolynome* suivant;
};

struct corp_polynome{
    CPolynome*first_C;
    CPolynome*last;

    int nb_composant;
};

void vider_buffer();
void test_polynome(CPolynome* polynome);
void supprimer_espace (char * str);
void afficher_polynome(CPolynome* polynome);
void aide_affichage(CPolynome* courant);
void ordonner_polynome(CPolynome* polynome);

CPolynome* creer_polynome();
CPolynome* somme_polynome (CPolynome* polynome1,CPolynome* polynome2);
CPolynome* soustraction_polynome(CPolynome* polynome1,CPolynome* polynome2);
CPolynome* insert_polynome(CPolynome*polynome,int c, int e);
CPolynome* produit_polynome(CPolynome* polynome1,CPolynome* polynome2);

void detruire_polynome(CPolynome* polynome);
#endif
