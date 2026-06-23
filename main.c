/**
 ******************************************************************************
 * NOM DU PROJET : Gestion de liste chainee dynamique
 * FICHIER       : main.c
 * DESCRIPTION   : Programme principal. Contient le menu interactif utilisateur
 * permettant de piloter toutes les fonctionnalites de la liste
 * et assure la liberation finale de la memoire.
 * GROUPE        : 11
 * AUTEURS       : AFANGNIBO Dieudonne Marcel   IABD
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

#include "liste1.h"


int main(void)
 {
    int choix = -1;
    char *nom;
    int position ;
    TListe *liste;

    // Allocation de la memoire

    if ((liste = (TListe *) malloc(sizeof(TListe))) == NULL)
        return -1;
    if ((nom = (char *) malloc(50)) == NULL)
    {
        free(liste);
        return -1;
    }

    // Initialisation

    initialisation(liste);

    while (choix != 0) {
        printf("================ MENU ================\n");
        printf("1. Ajouter un element au debut\n");
        printf("2. Ajouter un element a la fin\n");
        printf("3. Ajouter à une position specifique\n");
        printf("4. Enregistrer la liste dans le fichier binaire\n");
        printf("5. Charger le fichier binaire dans la liste\n");
        printf("0. Quitter le programme\n");
        printf("======================================\n");
        printf("Entrez votre choix : ");

        if (scanf("%d", &choix) != 1)
        {
            while (getchar() != '\n'); // Nettoyer le tampon
            continue;
        }
        getchar();


        switch (choix)
        {
            case 1:
                printf("Entrez un element : ");
                scanf("%s", nom);
                getchar();

                ins_debut_liste(liste, nom);

                // Affichage direct
                printf("%d elements:deb=%s,fin=%s",
                        liste->taille,
                        liste->debut->donnee,
                        liste->fin->donnee);
                affiche(liste);
                break;

            case 2:
                printf("Entrez un element : ");
                scanf("%s", nom);
                getchar();

                ins_fin_liste(liste, nom);

                // Affichage direct
                if (liste->debut != NULL && liste->fin != NULL) {
                    printf("%d elements: deb=%s, fin=%s\n",
                            liste->taille,
                            liste->debut->donnee,
                            liste->fin->donnee);
                }
                affiche(liste);
                break;

            case 3:
                printf("Entrez la position ");
                scanf("%d", &position);
                getchar();

                printf("Entrez un element : ");
                scanf("%s", nom);
                getchar();

                ins_position(liste, nom, position);

                if (liste->debut != NULL && liste->fin != NULL) {
                    printf("%d elements: deb=%s, fin=%s\n",
                            liste->taille,
                            liste->debut->donnee,
                            liste->fin->donnee);
                }
                affiche(liste);
                break;

            case 4:
                enregistrer_liste_In_fichier(liste);
                break;

            case 5:
                remplir_liste_by_Fichierbin(liste);
                break;

            case 0:
                printf("Fermeture du programme...\n");
                break;

            default:
                printf("Choix invalide. Veuillez choisir entre 0 et 5.\n\n");
                break;
        }
    }

    // Libération de la mémoire
    TMaillon *courant = liste->debut;
    while (courant != NULL) {
        TMaillon *aSupprimer = courant;
        courant = courant->next;
        free(aSupprimer);
    }
    free(nom);
    free(liste);

    return 0;
}
