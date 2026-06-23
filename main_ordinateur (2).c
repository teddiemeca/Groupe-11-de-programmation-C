/*
 *
 ******************************************************************************\n
 * NOM DU PROJET : Gestion du parc informatique SD+C
 *
 *FICHIER  : main_ordinateur.c
 *
 *\n
 * DESCRIPTION :       Programme principal, menu interactif pour la gestion du parc informatique SD + C ,
 *                     point d'entree du programme
 *
 *
 * GROUPE : 11
 *
 *\n
 * AUTEURS :            AFANGNIBO Dieudonne Marcel IABD\n
 *                      AGNAVE Mawusse Jason IABD\n
 *                      ATCHIKITI Djidjome Pierrette IABD\n
 *                      BARBOZA Abdoul-Raouf GC\n
 *                      CHILIE Tienpabe Eddie GM\n
 *                      HONKU Komi Godwin IABD\n
 *                      PASSAH Kwami David GC\n
 *                      SEGBEDZI Komi Charles GC\n
 *                      TCHALIM Maare Immenne GM\n
 *\n
 * DATE           : 28/04/2026\n
 *\n
 * VERSION        : finale
 * \n *\n
 * PROFESSEUR  : M. AKAKPO
 *
 ****************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "ordinateur.h"



// Fonction principale : main

int main(void)
{
    // Allocation du parc (tableau de 300 pointeurs)
P_ordinateur* parc = (P_ordinateur*)malloc(MAX_ORDINATEURS * sizeof(P_ordinateur));
    if (parc == NULL) {
        printf("Erreur fatale : Impossible d'allouer le parc !\n");
        printf("  Le programme va s'arreter .\n");
        return 1;
    }

// Initialisation
    int nbOrdi = 0;
    int choix = 0;

    // Message de bienvenue
    printf("\n");
    printf("=======================================================\n");
    printf("BIENVENUE DANS LE SYSTEME DE GESTION DU PARC SD+C\n");
    printf("=======================================================\n");
    printf("Capacite maximale : %d ordinateurs\n", MAX_ORDINATEURS);
    printf("=======================================================\n");

    // Boucle principale
    do {
            afficherMenu();
            if (scanf("%d", &choix) != 1) {
                viderBuffer();
                printf("Entree invalide. Veuillez entrer un nombre entre 0 et 9.\n");
                continue;
            }
            viderBuffer();
            switch (choix)
            {

                case 1:
                    // Ajouter un ordinateur
                        ajouterOrdinateur(parc, &nbOrdi);
                        break;

                case 2:
                    // Lister les ordinateurs
                        listerOrdinateurs(parc, nbOrdi);
                        break;

                case 3:
                   // Afficher les details d'un ordinateur
                        afficherDetails(parc, nbOrdi);
                        break;

                case 4:
                    // Supprimer un ordinateur
                        supprimerOrdinateur(parc, &nbOrdi);
                        break;

                case 5:
                    // Repartition par specialite
                    repartirParSpecialite(parc, nbOrdi);
                    break;

                case 6:
                    // Repartition par marque
                    repartirParMarque(parc, nbOrdi);
                    break;

                case 7:
                    // Repartition par RAM
                    repartirParRAM(parc, nbOrdi);
                    break;

                case 8:
                    // Trier par vitesse CPU
                    classerParVitesseCPU(parc, nbOrdi);
                    break;

                case 9:
                // Calculer la valeur totale
                    {
                        long total = calculerValeurTotale(parc, nbOrdi);
                        printf("\nVALEUR TOTALE DU PARC : %ld FCFA\n", total);
                        printf("  Nombre d'ordinateurs : %d\n", nbOrdi);
                        printf("   Valeur totale       : %ld F CFA\n", total);
                        if (nbOrdi > 0) {
                            printf("Valeur moyenne : %ld FCFA\n", total / nbOrdi);
                        }
                    }
                    break;

                case 0:
                    // Quitter le programme
                    printf("\n Au revoir ! Liberation de la memoire...\n");
                    break;

                default:
                    // Choix invalide(nombres hors 0-9)
                     printf("Choix invalide. Entrez un nombre entre 0 et 9.\n");
                     break;

            }
        }while (choix != 0); // continuer tant que choix != 0

    // Liberation finale de TOUTE la memoire
    libererParc(parc, &nbOrdi);
    free(parc); // Libere le tableau de pointeurs lui-meme
    parc = NULL;

    printf(" Memoire entierement liberee.\n");
    printf("=======================================\n");
    printf(" Programme terminee avec succes.\n\n");
    printf("=======================================\n");
    return 0;
}

