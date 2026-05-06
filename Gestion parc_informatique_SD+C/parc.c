/**
 ******************************************************************************
 * NOM DU PROJET : Gestion du parc informatique SD+C
 * FICHIER       : parc.c
 * DESCRIPTION   : Implementation de toutes les fonctions de gestion du parc :
 *                 ajout, suppression, listage, recherche, repartition,
 *                 tri et calcul.
 *                 Formalisme pointeur au maximum + tri bulle optimise.
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
 * VERSION       : finale
 * PROFESSEUR    : M. AKAKPO
 ******************************************************************************
 */

#include "parc.h"

/* ============================================================
   FONCTION : afficherMenu
   ============================================================ */
void afficherMenu(void)
{
    printf("\n");
    printf("=====================================\n");
    printf(" GESTION DU PARC INFORMATIQUE SD+C  \n");
    printf("=====================================\n");
    printf(" 1. Ajouter un ordinateur            \n");
    printf(" 2. Lister les ordinateurs           \n");
    printf(" 3. Afficher les details             \n");
    printf(" 4. Supprimer un ordinateur          \n");
    printf(" 5. Repartir par specialite          \n");
    printf(" 6. Repartir par marque              \n");
    printf(" 7. Repartir par RAM                 \n");
    printf(" 8. Classer par vitesse CPU          \n");
    printf(" 9. Calculer la valeur totale        \n");
    printf(" 0. Quitter                          \n");
    printf("=====================================\n");
    printf("Votre choix : ");
}

/* ============================================================
   FONCTION : creerOrdinateur
   ============================================================ */
P_ordinateur creerOrdinateur(void)
{
    P_ordinateur nouvelOrdi = malloc(sizeof(struct Ordinateur));
    if (nouvelOrdi == NULL) {
        printf("Erreur : Allocation memoire impossible !\n");
        return NULL;
    }
    nouvelOrdi->numeroCarte    = 0;
    nouvelOrdi->vitesseCPU     = 0.0f;
    nouvelOrdi->ram            = 0;
    nouvelOrdi->tailleDisque   = 0;
    nouvelOrdi->prix           = 0L;
    *(nouvelOrdi->specialite)  = '\0';
    *(nouvelOrdi->numeroSerie) = '\0';
    *(nouvelOrdi->marque)      = '\0';
    return nouvelOrdi;
}

/* ============================================================
   FONCTION : libererOrdinateur.
   ============================================================ */
void libererOrdinateur(P_ordinateur *ordi)
{
    if (ordi != NULL && *ordi != NULL) {
        free(*ordi);
        *ordi = NULL;
    }
}

/* ============================================================
   FONCTION : libererParc
   ============================================================ */
void libererParc(P_ordinateur *parc, int *nbOrdi)
{
    if (parc == NULL || *nbOrdi == 0) {
        printf("Parc deja vide, rien a liberer.\n");
        return;
    }
    for (P_ordinateur *p = parc; p < parc + *nbOrdi; p++) {
        if (*p != NULL) {
            free(*p);
            *p = NULL;
        }
    }
    *nbOrdi = 0;
    printf("Parc entierement libere. Memoire nettoyee.\n");
}

/* ============================================================
   FONCTION : ajouterOrdinateur
   ============================================================ */
int ajouterOrdinateur(P_ordinateur *parc, int *nbOrdi)
{
    if (*nbOrdi >= MAX_ORDINATEURS) {
        printf("Erreur : Parc plein (max %d ordinateurs) !\n", MAX_ORDINATEURS);
        return 0;
    }

    P_ordinateur nouvelOrdi = creerOrdinateur();
    if (nouvelOrdi == NULL) return 0;

    printf("\n| AJOUT D'UN ORDINATEUR |\n");

    printf("Numero de carte du detenteur : ");
    scanf("%d", &(nouvelOrdi->numeroCarte));
    viderBuffer();

    printf("Specialite du detenteur : ");
    fgets(nouvelOrdi->specialite, TAILLE_CHAINE, stdin);
    *(nouvelOrdi->specialite + strcspn(nouvelOrdi->specialite, "\n")) = '\0';

    printf("Numero de serie : ");
    fgets(nouvelOrdi->numeroSerie, TAILLE_CHAINE, stdin);
    *(nouvelOrdi->numeroSerie + strcspn(nouvelOrdi->numeroSerie, "\n")) = '\0';

    if (rechercherParNumeroSerie(parc, *nbOrdi, nouvelOrdi->numeroSerie) != -1) {
        printf("Erreur : Numero de serie deja existant.\n");
        free(nouvelOrdi);
        return 0;
    }

    printf("Marque : ");
    fgets(nouvelOrdi->marque, TAILLE_CHAINE, stdin);
    *(nouvelOrdi->marque + strcspn(nouvelOrdi->marque, "\n")) = '\0';

    printf("Vitesse du CPU (GHz) : ");
    scanf("%f", &(nouvelOrdi->vitesseCPU));
    viderBuffer();

    printf("RAM (Go) : ");
    scanf("%d", &(nouvelOrdi->ram));
    viderBuffer();

    printf("Taille disque (Go) : ");
    scanf("%d", &(nouvelOrdi->tailleDisque));
    viderBuffer();

    printf("Prix estime (F CFA) : ");
    scanf("%ld", &(nouvelOrdi->prix));
    viderBuffer();

    *(parc + *nbOrdi) = nouvelOrdi;
    (*nbOrdi)++;

    printf("Ordinateur ajoute avec succes !\n");
    printf("Total dans le parc : %d / %d\n", *nbOrdi, MAX_ORDINATEURS);
    return 1;
}

/* ============================================================
   FONCTION : listerOrdinateurs
   Affiche tous les ordinateurs du parc sur une ligne chacun,
   avec les informations essentielles.
   ============================================================ */
void listerOrdinateurs(P_ordinateur *parc, int nbOrdi)
{
    if (nbOrdi == 0) {
        printf("Le parc est vide. Aucun ordinateur enregistre.\n");
        return;
    }
    printf("\nLISTE DES ORDINATEURS (%d)\n", nbOrdi);
    printf("%-5s | %-6s | %-15s | %-15s | %-12s | %-8s | %-7s | %-8s | %-12s\n",
           "N", "Carte", "Specialite", "Serie", "Marque",
           "CPU(GHz)", "RAM(Go)", "Disque", "Prix(FCFA)");
    printf("----------------------------------------------------------------------"
           "------------------------------------------\n");
    for (P_ordinateur *p = parc; p < parc + nbOrdi; p++) {
        printf("%-5d |", (int)(p - parc) + 1);
        afficherLigne(*p);
    }
    printf("----------------------------------------------------------------------"
           "------------------------------------------\n");
}

/* ============================================================
   FONCTION : afficherDetails
   ============================================================ */
void afficherDetails(P_ordinateur *parc, int nbOrdi)
{
    if (nbOrdi == 0) {
        printf("Le parc est vide. Aucun ordinateur a afficher.\n");
        return;
    }

    char serie[TAILLE_CHAINE];
    printf("Entrez le numero de serie a rechercher : ");
    fgets(serie, TAILLE_CHAINE, stdin);
    *(serie + strcspn(serie, "\n")) = '\0';

    int index = rechercherParNumeroSerie(parc, nbOrdi, serie);
    if (index == -1) {
        printf("Ordinateur non trouve.\n");
        return;
    }

    P_ordinateur o = *(parc + index);

    printf("\n====== DETAILS DE L'ORDINATEUR ======\n");
    printf("--- INFORMATIONS DU DETENTEUR ---\n");
    printf("  Numero de carte : %d\n",       o->numeroCarte);
    printf("  Specialite      : %s\n",       o->specialite);
    printf("--- CARACTERISTIQUES TECHNIQUES ---\n");
    printf("  Numero de serie : %s\n",       o->numeroSerie);
    printf("  Marque          : %s\n",       o->marque);
    printf("  Vitesse CPU     : %.2f GHz\n", o->vitesseCPU);
    printf("  RAM             : %d Go\n",    o->ram);
    printf("  Taille disque   : %d Go\n",    o->tailleDisque);
    printf("--- VALEUR ---\n");
    printf("  Prix estime     : %ld F CFA\n", o->prix);
    printf("=====================================\n");
}

/* ============================================================
   FONCTION : supprimerOrdinateur
   ============================================================ */
int supprimerOrdinateur(P_ordinateur *parc, int *nbOrdi)
{
    if (*nbOrdi == 0) {
        printf("Le parc est deja vide. Rien a supprimer.\n");
        return 0;
    }

    char serie[TAILLE_CHAINE];
    printf("Entrez le numero de serie de l'ordinateur a supprimer : ");
    fgets(serie, TAILLE_CHAINE, stdin);
    *(serie + strcspn(serie, "\n")) = '\0';

    int index = rechercherParNumeroSerie(parc, *nbOrdi, serie);
    if (index == -1) {
        printf("Ordinateur non trouve avec ce numero de serie.\n");
        return 0;
    }

    printf("\nOrdinateur trouve :\n");
    printf("  Marque : %s\n", (*(parc + index))->marque);
    printf("  Serie  : %s\n", (*(parc + index))->numeroSerie);

    char confirmation[4];
    printf("Confirmer la suppression ? (oui/non) : ");
    fgets(confirmation, sizeof(confirmation), stdin);
    *(confirmation + strcspn(confirmation, "\n")) = '\0';

    if (strcmp(confirmation, "oui") != 0) {
        printf("Suppression annulee.\n");
        return 0;
    }

    libererOrdinateur(parc + index);

    for (P_ordinateur *p = parc + index; p < parc + *nbOrdi - 1; p++) {
        *p = *(p + 1);
    }

    (*nbOrdi)--;
    *(parc + *nbOrdi) = NULL;

    printf("Ordinateur supprime avec succes !\n");
    printf("Restants dans le parc : %d / %d\n", *nbOrdi, MAX_ORDINATEURS);
    return 1;
}

/* ============================================================
   FONCTION : rechercherParNumeroSerie.
   ============================================================ */
int rechercherParNumeroSerie(P_ordinateur *parc, int nbOrdi, const char *serie)
{
    for (P_ordinateur *p = parc; p < parc + nbOrdi; p++) {
        if (strcmp((*p)->numeroSerie, serie) == 0) {
            return (int)(p - parc);
        }
    }
    return -1;
}

/* ============================================================
   FONCTION : repartirParSpecialite
   ============================================================ */
void repartirParSpecialite(P_ordinateur *parc, int nbOrdi)
{
    if (nbOrdi == 0) {
        printf("Le parc est vide. Aucune repartition possible.\n");
        return;
    }

    int *dejaVu = (int *)calloc(nbOrdi, sizeof(int));
    if (dejaVu == NULL) { printf("Erreur memoire.\n"); return; }

    printf("\nREPARTITION PAR SPECIALITE\n");
    printf("---------------------------\n");

    int *d = dejaVu;
    for (P_ordinateur *p = parc; p < parc + nbOrdi; p++, d++) {
        if (*d) continue;
        int compte = 0;
        for (P_ordinateur *q = p; q < parc + nbOrdi; q++) {
            if (strcmp((*p)->specialite, (*q)->specialite) == 0) compte++;
        }
        printf("\nSpecialite : %-20s (%d ordi(s))\n", (*p)->specialite, compte);
        printf("Ordinateurs : ");
        int *d2 = d;
        for (P_ordinateur *q = p; q < parc + nbOrdi; q++, d2++) {
            if (strcmp((*p)->specialite, (*q)->specialite) == 0) {
                printf("[%s] ", (*q)->numeroSerie);
                *d2 = 1;
            }
        }
        printf("\n");
    }
    free(dejaVu);
}

/* ============================================================
   FONCTION : repartirParMarque
   ============================================================ */
void repartirParMarque(P_ordinateur *parc, int nbOrdi)
{
    if (nbOrdi == 0) {
        printf("Le parc est vide. Aucune repartition possible.\n");
        return;
    }

    int *dejaVu = (int *)calloc(nbOrdi, sizeof(int));
    if (dejaVu == NULL) { printf("Erreur memoire.\n"); return; }

    printf("\nREPARTITION PAR MARQUE\n");
    printf("-----------------------\n");

    int *d = dejaVu;
    for (P_ordinateur *p = parc; p < parc + nbOrdi; p++, d++) {
        if (*d) continue;
        int compte = 0;
        for (P_ordinateur *q = p; q < parc + nbOrdi; q++) {
            if (strcmp((*p)->marque, (*q)->marque) == 0) compte++;
        }
        printf("\nMarque : %-20s (%d ordi(s))\n", (*p)->marque, compte);
        printf("Ordinateurs : ");
        int *d2 = d;
        for (P_ordinateur *q = p; q < parc + nbOrdi; q++, d2++) {
            if (strcmp((*p)->marque, (*q)->marque) == 0) {
                printf("[%s] ", (*q)->numeroSerie);
                *d2 = 1;
            }
        }
        printf("\n");
    }
    free(dejaVu);
}

/* ============================================================
   FONCTION : repartirParRAM
   ============================================================ */
void repartirParRAM(P_ordinateur *parc, int nbOrdi)
{
    if (nbOrdi == 0) {
        printf("Le parc est vide. Aucune repartition possible.\n");
        return;
    }

    P_ordinateur *temp = malloc(nbOrdi * sizeof(*temp));
    if (temp == NULL) { printf("Erreur memoire.\n");
    return; }

    /* Copie via formalisme pointeur */
    P_ordinateur *src = parc;
    P_ordinateur *dst = temp;
    for (; src < parc + nbOrdi; src++, dst++) {
        *dst = *src;
    }

    /* Tri bulle optimise : desordre + n-- */
    int n = nbOrdi;
    bool desordre;
    do {
        desordre = false;
        for (P_ordinateur *j = temp; j < temp + n - 1; j++) {
            if ((*j)->ram > (*(j + 1))->ram) {
                P_ordinateur swap = *j;
                *j       = *(j + 1);
                *(j + 1) = swap;
                desordre = true;
            }
        }
        n--;
    } while (desordre);

    printf("\nREPARTITION PAR RAM\n");
    printf("--------------------\n");

    int ramActuelle = -1;
    for (P_ordinateur *p = temp; p < temp + nbOrdi; p++) {
        if ((*p)->ram != ramActuelle) {
            if (ramActuelle != -1) printf("\n");
            ramActuelle = (*p)->ram;
            printf("\nRAM : %d Go\nOrdinateurs : ", ramActuelle);
        }
        printf("[%s] ", (*p)->numeroSerie);
    }
    printf("\n");
    free(temp);
}

/* ============================================================
   FONCTION : classerParVitesseCPU
   ============================================================ */
void classerParVitesseCPU(P_ordinateur *parc, int nbOrdi)
{
    if (nbOrdi <= 1) {
        printf("Pas assez d'ordinateurs pour trier (minimum 2).\n");
        return;
    }

    P_ordinateur *temp = malloc(nbOrdi * sizeof(*temp));
    if (temp == NULL) { printf("Erreur memoire.\n"); return; }

    /* Copie via formalisme pointeur */
    P_ordinateur *src = parc;
    P_ordinateur *dst = temp;
    for (; src < parc + nbOrdi; src++, dst++) {
        *dst = *src;
    }

    /* Tri bulle optimise : desordre + n-- */
    int n = nbOrdi;
    bool desordre;
    do {
        desordre = false;
        for (P_ordinateur *j = temp; j < temp + n - 1; j++) {
            if ((*j)->vitesseCPU > (*(j + 1))->vitesseCPU) {
                P_ordinateur swap = *j;
                *j       = *(j + 1);
                *(j + 1) = swap;
                desordre = true;
            }
        }
        n--;
    } while (desordre);

    printf("\nCLASSEMENT PAR VITESSE CPU (croissant)\n");
    printf("----------------------------------------\n");
    printf("%-5s | %-15s | %-12s | %-10s\n",
           "Rang", "Serie", "Marque", "CPU(GHz)");
    printf("------------------------------------------\n");

    int rang = 1;
    for (P_ordinateur *p = temp; p < temp + nbOrdi; p++, rang++) {
        printf("%-5d | %-15s | %-12s | %.2f GHz\n",
               rang,
               (*p)->numeroSerie,
               (*p)->marque,
               (*p)->vitesseCPU);
    }
    free(temp);
}

/* ============================================================
   FONCTION : calculerValeurTotale
   ============================================================ */
long calculerValeurTotale(P_ordinateur *parc, int nbOrdi)
{
    long total = 0L;
    for (P_ordinateur *p = parc; p < parc + nbOrdi; p++) {
        total += (*p)->prix;
    }
    return total;
}

/* ============================================================
   FONCTION : viderBuffer
   ============================================================ */
void viderBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ============================================================
   FONCTION : afficherLigne
  ============================================================ */
void afficherLigne(P_ordinateur ordi)
{
    printf(" %-6d | %-15s | %-15s | %-12s | %-8.2f | %-7d | %-8d | %-12ld\n",
           ordi->numeroCarte,
           ordi->specialite,
           ordi->numeroSerie,
           ordi->marque,
           ordi->vitesseCPU,
           ordi->ram,
           ordi->tailleDisque,
           ordi->prix);
}
