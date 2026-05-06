/**
 ******************************************************************************
 * NOM DU PROJET : Gestion du parc informatique SD+C
 * FICHIER       : parc.h
 * DESCRIPTION   : Declarations de la structure Ordinateur, constantes et
 *                 prototypes de toutes les fonctions de gestion du parc
 *                 (max 300 machines). Compilation separee.
 * GROUPE        : 11
 * AUTEURS       : AFANGNIBO Dieudonne Marcel   IABD
 *                 AGNAVE Mawusse Jason          IABD
 *                 ATCHIKITI Djidjome Pierrette  IABD
 *                 BARBOZA Abdoul-Raouf          GC
 *                 CHILI Tienpabe Eddie          GM
 *                 HONKU Komi Godwin             IABD
 *                 PASSAH Kwami David            GC
 *                 SEGBEDZI Komi Charles         GC
 *                 TCHALIM Maare Immenne         GM
 * DATE          : 05/05/2026
 * VERSION       : finale corrigee
 * PROFESSEUR    : M. AKAKPO
 ******************************************************************************
 */

#ifndef PARC_H
#define PARC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* ===== CONSTANTES ===== */
#define MAX_ORDINATEURS 300
#define TAILLE_CHAINE   100

/* ===== STRUCTURE ===== */
/* CORRECTION #4 : struct definie AVANT le typedef */
struct Ordinateur {
    int    numeroCarte;
    char   specialite[TAILLE_CHAINE];
    char   numeroSerie[TAILLE_CHAINE];
    char   marque[TAILLE_CHAINE];
    float  vitesseCPU;
    int    ram;
    int    tailleDisque;
    long   prix;          /* CORRECTION #9 : long pour eviter depassement */
};

/* Formalisme pointeur impose par le sujet */
typedef struct Ordinateur *P_ordinateur;

/* ===== PROTOTYPES ===== */

/* Menu */
void afficherMenu(void);

/* Allocation memoire */
P_ordinateur creerOrdinateur(void);
void         libererOrdinateur(P_ordinateur *ordi);
void         libererParc(P_ordinateur *parc, int *nbOrdi);

/* CRUD */
int  ajouterOrdinateur(P_ordinateur *parc, int *nbOrdi);
void listerOrdinateurs(P_ordinateur *parc, int nbOrdi);
void afficherDetails(P_ordinateur *parc, int nbOrdi);
int  supprimerOrdinateur(P_ordinateur *parc, int *nbOrdi);

/* Recherche */
int rechercherParNumeroSerie(P_ordinateur *parc, int nbOrdi, const char *serie);

/* Repartition */
void repartirParSpecialite(P_ordinateur *parc, int nbOrdi);
void repartirParMarque(P_ordinateur *parc, int nbOrdi);
void repartirParRAM(P_ordinateur *parc, int nbOrdi);

/* Tri et calcul */
void classerParVitesseCPU(P_ordinateur *parc, int nbOrdi);
long calculerValeurTotale(P_ordinateur *parc, int nbOrdi);

/* Utilitaires */
void viderBuffer(void);
void afficherLigne(P_ordinateur ordi);

#endif /* PARC_H */
