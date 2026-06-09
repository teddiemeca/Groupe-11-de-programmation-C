/**
 ******************************************************************************
 * NOM DU PROJET : Gestion de liste chainee dynamique
 * FICHIER       : liste1.h
 * DESCRIPTION   : Definition des structures de donnees (TMaillon, TListe)
 * et prototypes de l'ensemble des fonctions du projet.
 * GROUPE        : 11
 * AUTEURS       :
 * AFANGNIBO Dieudonne Marcel   IABD
 * AGNAVE Mawusse Jason          IABD
 * ATCHIKITI Djidjome Pierrette  IABD
 * BARBOZA Abdoul-Raouf          GC
 * CHILI Tienpabe Eddie          GM
 * HONKU Komi Godwin             IABD
 * PASSAH Kwami David            GC
 * SEGBEDZI Komi Charles         GC
 * TCHALIM Maare Imenne         GM
 * DATE          : 09/06/2026
 * VERSION       : finale
 * PROFESSEUR    : M. AKAKPO
 ******************************************************************************
 */

#ifndef LISTE1_H_INCLUDED
#define LISTE1_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure d'un élément (Maillon)
typedef struct TMaillon {
    char donnee[50];
    struct TMaillon *next;
} TMaillon;

// Structure de contrôle de la liste
typedef struct {
    TMaillon *debut;
    TMaillon *fin;
    int taille;
} TListe;

// Uniquement les prototypes nécessaires
void initialisation(TListe *liste);
int ins_debut_liste(TListe *liste, char *nom);
int ins_fin_liste(TListe *liste, char *nom);
void affiche(TListe *liste);
void ins_position(TListe *liste, char *nom, int position);
void enregistrer_liste_In_fichier(TListe *liste);
void remplir_liste_by_Fichierbin(TListe *liste);

#endif
