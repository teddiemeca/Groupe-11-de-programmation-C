/*
 *
 ******************************************************************************\n
 * NOM DU PROJET : Gestion du parc informatique SD+C
 *
 *FICHIER  : ordinateur.c
 *
 *\n
 * DESCRIPTION :       Implementation de toutes les fonctions de gestion du parc : ajout ,
 *                      suppression, listage , recherche , repartition, tri et calcul.
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

#include "ordinateur.h"

// Fonction afficherMenu
void afficherMenu(void)
{
    printf("\n");
    printf("=====================================\n");
    printf(" GESTION DU PARC INFORMATIQUE SD+C \n");
    printf("=====================================\n");
    printf(" 1. Ajouter un ordinateur       \n");
    printf(" 2. Lister les ordinateurs      \n");
    printf(" 3. Afficher les details        \n");
    printf(" 4. Supprimer un ordinateur     \n");
    printf(" 5. Repartir par specialite     \n");
    printf(" 6. Repartir par marque         \n");
    printf(" 7. Repartir par RAM            \n");
    printf(" 8. Classer par vitesse CPU     \n");
    printf(" 9. Calculer la valeur totale   \n");
    printf(" 0. Quitter                     \n");
    printf("=====================================\n");
    printf("Votre choix : ");
}

// ============================================================
// FONCTIONS D'ALLOCATION MEMOIRE
// ============================================================

P_ordinateur creerOrdinateur(void) {
// malloc alloue la memoire pour UNE structure Ordinateur
P_ordinateur nouvelOrdi = (P_ordinateur)malloc(sizeof(P_ordinateur));
if (nouvelOrdi == NULL) {
printf("Erreur !! : Allocation memoire impossible !\n");
return NULL;
}
// Initialisation des champs numeriques a 0
nouvelOrdi->numeroCarte = 0;
nouvelOrdi->vitesseCPU = 0.0f;
nouvelOrdi->ram = 0;
nouvelOrdi->tailleDisque = 0;
nouvelOrdi->prix = 0;

// Les chaines sont initialisees a chaine vide
nouvelOrdi->specialite[0] = '\0';
nouvelOrdi->numeroSerie[0] = '\0';
nouvelOrdi->marque[0] = '\0';
return nouvelOrdi;
}

// Fonctiion libererOrdinateur
void libererOrdinateur(P_ordinateur* ordi)
{
    if (ordi != NULL && *ordi != NULL)
    {
        free(*ordi); // Libere la memoire allouee
        *ordi = NULL; // Evite le dangling pointer
    }
}

//Liberer Parc
void libererParc(P_ordinateur* parc, int* nbOrdi)
{
    if (parc == NULL) 
    {
        printf("Parc deja vide , rien a liberer.\n");
        return;
    }
    for (int i = 0; i < *nbOrdi; i++) 
    {
        libererOrdinateur(&parc[i]);
    }
    *nbOrdi = 0;
    printf("Parc entierement lib�r�. M�moire nettoy�e. \n");
}

// Fonction AjouterOrdinateur
int ajouterOrdinateur(P_ordinateur* parc, int* nbOrdi)
{
    //Etape 1 : Verfication
    if (*nbOrdi >= MAX_ORDINATEURS) {
        printf("Erreur : Parc plein (max %d ordinateurs) !\n", MAX_ORDINATEURS);
        return 0;
    }

    //Etape 2 : Creation d'un ordi vide
    P_ordinateur nouvelOrdi = creerOrdinateur();
    if (nouvelOrdi == NULL){
        return 0;
    }

    printf("| AJOUT D'UN ORDINATEUR : |\n");
    //---Numero de carte ---
    printf("Numero de carte  du detenteur : ");
    scanf("%d", &nouvelOrdi->numeroCarte);
    viderBuffer();
    //---Specialite---
    printf("Specialite  du detenteur : ");
    fgets(nouvelOrdi->specialite, TAILLE_CHAINE, stdin);
    nouvelOrdi->specialite[strcspn(nouvelOrdi->specialite, "\n")] = '\0';
    //---Numero de serie---
    printf("Numero de serie : ");
    fgets(nouvelOrdi->numeroSerie, TAILLE_CHAINE, stdin);
    nouvelOrdi->numeroSerie[strcspn(nouvelOrdi->numeroSerie, "\n")] = '\0';
    //---Marque---
    printf("Marque : ");
    fgets(nouvelOrdi->marque, TAILLE_CHAINE, stdin);
    nouvelOrdi->marque[strcspn(nouvelOrdi->marque, "\n")] = '\0';
    //---Vitesse CPU---
    printf("Vitesse  du CPU (GHz) : ");
    scanf("%f", &nouvelOrdi->vitesseCPU);
    viderBuffer();
    //---RAM ---
    printf("RAM (Go) : ");
    scanf("%d", &nouvelOrdi->ram);
    viderBuffer();
    //--- Taille disque---
    printf("Taille disque (Go) : ");
    scanf("%d", &nouvelOrdi->tailleDisque);
    viderBuffer();
    //---Prix---
    printf("Prix estime (F CFA) : ");
    scanf("%d", &nouvelOrdi->prix);
    viderBuffer();
    //---stockage dans le parc---
    parc[*nbOrdi] = nouvelOrdi;
    //---incrementation du compteur---
    (*nbOrdi)++;
    printf("\n Ordinateur ajout� avec succes !\n");
    printf("  Total dans le parc : %d / %d\n", *nbOrdi, MAX_ORDINATEURS);
    return 1;
    
}

//Fonction listerOrdinateur
void listerOrdinateurs(P_ordinateur* parc, int nbOrdi)
{
    if (nbOrdi == 0) {
        printf("Le parc est vide. Aucun ordinateur enregistre. \n");
        return;
    }
    printf("LISTE DES ORDINATEURS (%d)\n", nbOrdi);
    printf("%-5s | %-15s | %-15s | %-15s | %-12s | %-8s | %-6s | %-8s | %-10s\n",
    "N", "Carte", "Specialite","Serie", "Marque", "CPU", "RAM", "Disque", "Prix");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < nbOrdi; i++) {
        printf("%-5d |", i + 1);
        afficherLigne(parc[i]);
    }
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

}

// Fonction Details
void afficherDetails(P_ordinateur* parc, int nbOrdi)
{
    if (nbOrdi == 0) {
        printf("Le parc est vide. Aucun ordinateur a afficher. \n");
        return;
    }

    char serie[TAILLE_CHAINE];
    printf("Entrez le numero de serie a rechercher : ");
    fgets(serie, TAILLE_CHAINE, stdin);
    serie[strcspn(serie, "\n")] = '\0';

    int index = rechercherParNumeroSerie(parc, nbOrdi, serie);
    if (index == -1) {
        printf("Ordinateur non trouve.\n");
        return;
    }


    P_ordinateur o = parc[index];

    printf("====DETAILS DE L'ORDINATEUR====\n");

    printf("---INFORMATIONS DU DETENTEUR--- :\n");
    printf("Numero de carte : %d\n", o->numeroCarte);
    printf("Specialite : %s\n", o->specialite);

    printf("\n ---CARACTERISTIQUES TECHNIQUES--- :\n");
    printf("Numero de serie  : %s\n", o->numeroSerie);
    printf("Marque           : %s\n", o->marque);
    printf("Vitesse CPU      : %.2f GHz\n", o->vitesseCPU);
    printf("RAM              : %d Go\n", o->ram);
    printf("Taille disque    : %d Go\n", o->tailleDisque);

    printf("\n Prix estime : %d F CFA\n", o->prix);
    }

    //Fonction supprimerOrdinateur
    int supprimerOrdinateur(P_ordinateur* parc, int* nbOrdi)
    {
    if (*nbOrdi == 0) {
        printf("\nLe parc est deja vide.RIEN  a supprimer. \n");
       return 0;
    }
    char serie[TAILLE_CHAINE];
    printf("Entrez le numero de serie de l'ordi a supprimer .\n ");
    fgets(serie, TAILLE_CHAINE, stdin);
    serie[strcspn(serie, "\n")] = '\0';


    int index = rechercherParNumeroSerie(parc, *nbOrdi, serie);

    if (index == -1) {
        printf("Ordinateur non trouve avec ce numero de serie .\n");
        return 0;
    }
    //confirmation
    printf("\n Ordinateur trouve :\n");
    printf(" Marque  : %s\n", parc[index]->marque);
    printf(" Serie   : %s\n", parc[index]->numeroSerie);

    char confirmation;
    printf("\nConfirmer la suppression ? (o/n) : ");
    scanf("%c", &confirmation);
    viderBuffer();

    if (confirmation != 'o' && confirmation != 'n'){

        printf("Suppression annulee.\n");
        return 0;
    }


    // 1. Libere la memoire de l'ordinateur supprime
    libererOrdinateur(&parc[index]);

    // 2. Decale les elements suivants vers la gauche
    for (int i = index; i < *nbOrdi - 1; i++) {
        parc[i] = parc[i + 1];
    }
    // 3. Decremente le compteur
    (*nbOrdi)--;
    printf("Ordinateur supprime avec succes !\n");
    printf(" Restants dans le parc : %d / %d\n ", *nbOrdi, MAX_ORDINATEURS );

    return 1;

    }

    // Fonction rechercher par numero de serie
    int rechercherParNumeroSerie(P_ordinateur* parc, int nbOrdi, const char* serie)
    {
        for (int i = 0; i < nbOrdi; i++) {
            if (strcmp(parc[i]->numeroSerie, serie) == 0) {
                return i; // Retourne l'index trouve
            }

        }
        return -1; // Non trouve
    }

    // Fonction repartirParSpecialite
    void repartirParSpecialite(P_ordinateur* parc, int nbOrdi)
    {
        if (nbOrdi == 0) {
            printf("Le parc est vide. Aucune repartition possible. \n");
            return;
       }
    // allocation et initialisation avec calloc
    int* dejaVu = (int*)calloc(nbOrdi, sizeof(int));
    if (dejaVu == NULL) {
        printf(" Erreur memoire. \n");
        return;
    }

    printf("REPARTITION PAR SPECIALITE\n");
    for (int i = 0; i < nbOrdi; i++) {
        if (dejaVu[i]) continue;
        printf("\n Specialite : %s\n", parc[i]->specialite);
        printf(" Ordinateurs : ");
        for (int j = i; j < nbOrdi; j++) {
            if (strcmp(parc[i]->specialite, parc[j]->specialite) == 0) {
                printf("[%s] ", parc[j]->numeroSerie);
                dejaVu[j] = 1;
            }
        }
            printf("\n");
    }
    free(dejaVu);
}


// Repartir par marque
void repartirParMarque(P_ordinateur* parc, int nbOrdi)
{
    if (nbOrdi == 0) {
        printf("Le parc est vide. Aucune repartition possible. \n");
        return;
    }

    int* dejaVu = (int*)calloc(nbOrdi, sizeof(int));
    if (dejaVu == NULL){
        printf("\n Erreur memoire lors de la repartition.\n");
        return;
    }

    printf("REPARTITION PAR MARQUE\n");

    for (int i = 0; i < nbOrdi; i++) {
        if (dejaVu[i]) continue;
        printf("\n Marque : %s\n", parc[i]->marque);
        printf(" Ordinateurs : ");

        for (int j = i; j < nbOrdi; j++) {
            if (strcmp(parc[i]->marque, parc[j]->marque) == 0) {
               printf("[%s] ", parc[j]->numeroSerie);
                dejaVu[j] = 1;
            }
        }
        printf("\n");
    }
    free(dejaVu);
}

// Fonction repartirParRAM
void repartirParRAM(P_ordinateur* parc, int nbOrdi)
{
    if (nbOrdi == 0) {
        printf("Le parc est vide. Aucune repartition possible.\n");
        return;
    }

// Copie temporaire des pointeurs pour trier sans modifier l'original
    P_ordinateur* temp = (P_ordinateur*)malloc(nbOrdi * sizeof(P_ordinateur));
    if (temp == NULL){
        printf("Ereur memoire lors de la repartition.\n");
        return;
    }

    for (int i = 0; i < nbOrdi; i++){
        temp[i] = parc[i];
    }
    // Tri bulle par RAM
    for (int i = 0; i < nbOrdi - 1; i++) {
        for (int j = 0; j < nbOrdi - i - 1; j++) {
            if (temp[j]->ram > temp[j + 1]->ram) {
                P_ordinateur swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }   
    printf("REPARTITION PAR RAM\n");

    int ramActuelle = -1;
    for (int i = 0; i < nbOrdi; i++) {
        if (temp[i]->ram != ramActuelle) {
            ramActuelle = temp[i]->ram;
            printf("\n RAM : %d Go\n ", ramActuelle);
            printf("  Ordinateur :");
        }
        printf("[%s] ", temp[i]->numeroSerie);
    }
    printf("\n");
    free(temp); // Libere seulement le tableau de pointeurs
}

// Fonction classerParVitesseCPU
void classerParVitesseCPU(P_ordinateur* parc, int nbOrdi)
{
    if (nbOrdi <= 1) {
        printf("Pas assez d'ordinateurs pour trier (min 2).\n");
        return;
    }

// Tri a bulles sur le tableau de pointeurs
    for (int i = 0; i < nbOrdi - 1; i++) {
        for (int j = 0; j < nbOrdi - i - 1; j++) {
            if (parc[j]->vitesseCPU > parc[j + 1]->vitesseCPU) {
            // Echange les pointeurs (pas les structures !)
                P_ordinateur temp = parc[j];
                parc[j] = parc[j + 1];
                parc[j + 1] = temp;
            }
        }
        }
    printf("Parc trie par vitesse CPU (croissant).\n");
}

// Fonction calculerValeurTotale
long calculerValeurTotale(P_ordinateur* parc, int nbOrdi)
{
    long total = 0;
    for (int i = 0; i < nbOrdi; i++) {
        total += parc[i]->prix;
    }
    return total;
}

// Fonction viderBuffer
void viderBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Fonction afficherLigne
void afficherLigne(P_ordinateur ordi)
{
    printf("%-5d | %-15s | %-15s | %-12s | %-6.1fGHz | %-4dGo | %-6dGo | %-10d FCFA\n",
ordi->numeroCarte,
ordi->specialite,
ordi->numeroSerie,
ordi->marque,
ordi->vitesseCPU,
 ordi->ram,
ordi->tailleDisque,
ordi->prix);
}

