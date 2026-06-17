/**
 ******************************************************************************
 * NOM DU PROJET : programme_calcul_polynome
 * FICHIER       : calcul_polynome.h
 * DESCRIPTION   : Definition des structures de donnees de gestion des  polynomes 
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


#include <stdio.h>
#include <stdlib.h>
#include "calcul_polynome.h"


void menu() {
    printf("\n=================== MENU POLYNOMES ===================\n");
    printf(" 1. Saisir/Remplacer le Polynome 1\n");
    printf(" 2. Saisir/Remplacer le Polynome 2\n");
    printf(" 3. Afficher les polynomes actuels\n");
    printf(" 4. Calculer la SOMME (P1 + P2)\n");
    printf(" 5. Calculer la SOUSTRACTION (P1 - P2)\n");
    printf(" 6. Calculer la MULTIPLICATION (P1 * P2)\n");
    printf(" 7. Quitter le programme\n");
    printf("======================================================\n");
    printf("Votre choix : ");
}

int main() {
    CPolynome* P1 = NULL;
    CPolynome* P2 = NULL;
    CPolynome* resultat = NULL;
    int choix = 0;

    do {
        menu();
        
        // Lecture sécurisée du choix de l'utilisateur
        if (scanf("%d", &choix) != 1) {
            printf("Saisie invalide. Veuillez entrer un nombre.\n");
            vider_buffer(); // Nettoie le tampon pour éviter une boucle infinie
            continue;
        }
        vider_buffer();

        switch (choix) {
            case 1:
                if (P1 != NULL) detruire_polynome(P1); // Libère l'ancien P1 si existant
                P1 = creer_polynome();
                printf("Polynome 1 enregistre avec succes.\n");
                break;

            case 2:
                if (P2 != NULL) detruire_polynome(P2); // Libère l'ancien P2 si existant
                P2 = creer_polynome();
                printf("Polynome 2 enregistre avec succes.\n");
                break;

            case 3:
                printf("\n--- Affichage des polynomes ---\n");
                printf("P1 ="); affichage(P1);
                printf("P2 ="); affichage(P2);
                break;

            case 4:
                if (P1 == NULL || P2 == NULL) {
                    printf("Erreur : Veuillez d'abord saisir les deux polynomes (Options 1 et 2).\n");
                } else {
                    if (resultat != NULL) detruire_polynome(resultat);
                    resultat = somme_polynome(P1, P2);
                    printf("\nResultat de la somme :\n");
                    affichage(resultat);
                }
                break;

            case 5:
                if (P1 == NULL || P2 == NULL) {
                    printf("Erreur : Veuillez d'abord saisir les deux polynomes (Options 1 et 2).\n");
                } else {
                    if (resultat != NULL) detruire_polynome(resultat);
                    resultat = soustraction_polynome(P1, P2);
                    printf("\nResultat de la soustraction :\n");
                    affichage(resultat);
                }
                break;

            case 6:
                if (P1 == NULL || P2 == NULL) {
                    printf("Erreur : Veuillez d'abord saisir les deux polynomes (Options 1 et 2).\n");
                } else {
                    if (resultat != NULL) detruire_polynome(resultat);
                    resultat = produit_polynome(P1, P2);
                    printf("\nResultat de la multiplication :\n");
                    affichage(resultat);
                }
                break;

            case 7:
                printf("Fermeture du programme. Liberation de la memoire...\n");
                break;

            default:
                printf("Option inconnue. Veuillez choisir un nombre entre 1 et 7.\n");
                break;
        }
        
    } while (choix != 7);

    // Libération finale de toute la mémoire dynamique avant de quitter
    if (P1 != NULL) detruire_polynome(P1);
    if (P2 != NULL) detruire_polynome(P2);
    if (resultat != NULL) detruire_polynome(resultat);

    printf("Fin du programme. Au revoir !\n");
    return 0;
}
