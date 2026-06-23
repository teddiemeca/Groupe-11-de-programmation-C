#ifndef CALCUL_POLYNOME_H_INCLUDED
#define CALCUL_POLYNOME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct CPolynome CPolynome;
struct CPolynome
{
    int coefficient;
    int exposant;

    CPolynome* suivant;
};

typedef struct TCorps TCorps;
struct TCorps
{
    CPolynome*tete;
    CPolynome*fin;
};


void vider_buffer();
void test_polynome(CPolynome* polynome);
void supprimer_espace (char * str);// ajout pour corriger erreur de creation des polynomes
void affichage(CPolynome* polynome);

CPolynome* creer_polynome();
CPolynome* somme_polynome (CPolynome* polynome1,CPolynome* polynome2);
CPolynome* soustraction_polynome(CPolynome* polynome1,CPolynome* polynome2);
CPolynome* insert_polynome(CPolynome*polynome,int c, int e);
CPolynome* produit_polynome(CPolynome* polynome1,CPolynome* polynome2);

void detruire_polynome(CPolynome* polynome);
#endif

