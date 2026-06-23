/**
 ******************************************************************************
 * NOM DU PROJET : Gestion du parc informatique SD+C
 * FICHIER       : main_parc.c
 * DESCRIPTION   : Programme principal — menu interactif, point d'entree.
 * GROUPE        : 11
 * DATE          : 05/05/2026
 * VERSION       : finale corrigee
 * PROFESSEUR    : M. AKAKPO
 ******************************************************************************
 */

#include "parc.h"  /* suffit — parc.h inclut deja stdio, stdlib, string */

int main(void)
{
    /* Allocation dynamique du tableau de pointeurs */
    P_ordinateur *parc = malloc(MAX_ORDINATEURS * sizeof(*parc));
    if (parc == NULL) {
        printf("Erreur fatale : Impossible d'allouer le parc !\n");
        return 1;
    }

    /* Initialisation de toutes les cases a NULL */
    for (int i = 0; i < MAX_ORDINATEURS; i++) {
        parc[i] = NULL;
    }

    int nbOrdi = 0;
    int choix  = 0;

    printf("\n=======================================================\n");
    printf("  BIENVENUE DANS LE SYSTEME DE GESTION DU PARC SD+C  \n");
    printf("=======================================================\n");
    printf("  Capacite maximale : %d ordinateurs\n", MAX_ORDINATEURS);
    printf("=======================================================\n");

    do {
        afficherMenu();

        if (scanf("%d", &choix) != 1) {
            viderBuffer();
            printf("Entree invalide. Veuillez entrer un nombre entre 0 et 9.\n");
            continue;
        }
        viderBuffer();

        switch (choix) {
            case 1:
                ajouterOrdinateur(parc, &nbOrdi);
                break;
            case 2:
                listerOrdinateurs(parc, nbOrdi);
                break;
            case 3:
                afficherDetails(parc, nbOrdi);
                break;
            case 4:
                supprimerOrdinateur(parc, &nbOrdi);
                break;
            case 5:
                repartirParSpecialite(parc, nbOrdi);
                break;
            case 6:
                repartirParMarque(parc, nbOrdi);
                break;
            case 7:
                repartirParRAM(parc, nbOrdi);
                break;
            case 8:
                classerParVitesseCPU(parc, nbOrdi);
                break;
            case 9: {
                long total = calculerValeurTotale(parc, nbOrdi);
                printf("\n===== VALEUR TOTALE DU PARC =====\n");
                printf("  Nombre d'ordinateurs : %d\n",     nbOrdi);
                printf("  Valeur totale        : %ld F CFA\n", total);
                if (nbOrdi > 0) {
                    printf("  Valeur moyenne       : %ld F CFA\n", total / nbOrdi);
                }
                printf("==================================\n");
                break;
            }
            case 0:
                printf("Au revoir ! Liberation de la memoire...\n");
                break;
            default:
                printf("Choix invalide. Entrez un nombre entre 0 et 9.\n");
                break;
        }

    } while (choix != 0);

    /* Liberation finale de toute la memoire */
    libererParc(parc, &nbOrdi);  /* libere chaque struct Ordinateur */
    free(parc);                   /* libere le tableau de pointeurs */
    parc = NULL;

    printf("Memoire entierement liberee.\n");
    printf("Programme termine avec succes.\n\n");
    return 0;
}
