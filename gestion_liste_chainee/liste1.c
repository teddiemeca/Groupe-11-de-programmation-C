/**
 ******************************************************************************
 * NOM DU PROJET : Gestion de liste chainee dynamique
 * FICHIER       : liste1.c
 * DESCRIPTION   : Implementation des fonctions de gestion de la liste :
 * initialisation, insertions (debut, fin, position),
 * affichage structure, enregistrement et chargement binaire.
 * GROUPE        : 11
 * AUTEURS       :
 * AFANGNIBO Dieudonne Marcel    IABD
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

#include "liste1.h"


// Initialisation
void initialisation(TListe *liste)
{
    if (liste != NULL)
    {
        liste->debut = NULL;
        liste->fin = NULL;
        liste->taille = 0;
    }
}

// Insertion au début
int ins_debut_liste(TListe *liste, char *nom)
{
    TMaillon *nouveau = (TMaillon*)malloc(sizeof(TMaillon));
    if (nouveau == NULL)
        return -1;

    strcpy(nouveau->donnee, nom);
    nouveau->next = liste->debut;

    // Si la liste est vide, le nouveau est aussi la fin
    if (liste->taille == 0)
    {
        liste->fin = nouveau;
    }

    liste->debut = nouveau;
    liste->taille++;
    return 0;
}

// Insertion à la fin
int ins_fin_liste(TListe *liste, char *nom)
{
    TMaillon *nouveau = (TMaillon*)malloc(sizeof(TMaillon));
    if (nouveau == NULL)
        return -1;

    strcpy(nouveau->donnee, nom);
    nouveau->next = NULL;

    if (liste->taille == 0)
    {
        // Si la liste est vide, début et fin pointent sur le nouveau
        liste->debut = nouveau;
        liste->fin = nouveau;
    } else {
        // Sinon, on accroche après l'élément de fin actuel
        liste->fin->next = nouveau;
        liste->fin = nouveau;
    }

    liste->taille++;
    return 0;
}

void ins_position(TListe *liste, char *nom, int position)
{
    // 1. Vérification des limites
    if (liste == NULL || position < 1 || position > liste->taille)
    {
        printf("Erreur : position invalide\n");
        return;
    }

    // 2. Allocation du nouveau maillon
    TMaillon *nouveau = (TMaillon*)malloc(sizeof(TMaillon));
    if (nouveau == NULL)
    {
        printf("Erreur d'allocation memoire\n");
        return;
    }

    strcpy(nouveau->donnee, nom);
    nouveau->next = NULL;

    // 3. Cas particulier : Insertion au début (position 1)
    if (position == 1)
    {
        ins_debut_liste(liste,nom);
    }
    // 4. Cas particulier : Insertion à la fin
    else if (position == liste->taille +  1)
    {
       ins_fin_liste(liste,nom);
    }
    // 5. Cas général : Insertion à une position quelconque
    else
    {
        TMaillon *courant = liste->debut;
        int i = 1;

        // On avance jusqu'au maillon juste avant la position voulue
        while (i < position - 1)
        {
            courant = courant->next;
            i++;
        }

        // On ajuste les pointeurs
        nouveau->next = courant->next;
        courant->next = nouveau;
    }
    liste->taille++;
}

// Module d'affichage complet

void affiche(TListe *liste) {
    if (liste == NULL || liste->debut == NULL)
    {
        printf("\nCONTENU DE LA LISTE\n");
        printf("ADRESSE\t\t\tDONNEE\n");
        printf("[Liste vide]\n\n");
        return;
    }
    int numero=1;
    TMaillon *courant = liste->debut;

    printf("\n********CONTENU DE LA LISTE********\n");

    printf("\n%-8s %-18s %-10s %-18s", "Numero", "ADRESSE ELEMENT", "VALEUR", "ADRESSE SUIVANT");
    printf("\n------------------------------------------------------------------");

    while (courant != NULL) {

        printf("\n%-8d %-18p %-10s %-18p", numero, (void*)courant, courant->donnee, (void*)courant->next);
        courant = courant->next;
        numero++;
    }

    printf("\n\n");
    printf("------------------------------------\n");

}


void enregistrer_liste_In_fichier(TListe *liste) {
    if (liste == NULL) {
        printf("Erreur : La liste n'est pas initialisee.\n");
        return;
    }

    if (liste->taille == 0) {
        printf("Votre liste est vide, inutile d'enregistrer.\n");
        return;
    }

    FILE *f = NULL;
    int choix;
    printf("Voulez-vous enregistrer la liste dans un fichier vide (1) ou a la suite (0) ? : ");
    while (scanf("%d", &choix) != 1 || (choix != 1 && choix != 0)) {
        printf("Vous devez entrer soit 1, soit 0.\n");
        while (getchar() != '\n'); // Vider le tampon
    }

    if (choix == 1) {
        f = fopen("data_liste_bin", "wb");
    } else {
        f = fopen("data_liste_bin", "ab");
    }

    if (!f) {
        printf("Erreur au niveau du fichier d'enregistrement.\n");
        return;
    }

    TMaillon *courant = liste->debut;
    while (courant != NULL) {
        // On écrit le tableau de caractères 'donnee' directement dans le fichier binaire
        fwrite(courant->donnee, sizeof(courant->donnee), 1, f);
        courant = courant->next;
    }
    fclose(f);
    printf("Liste enregistree avec succes.\n");
}

void remplir_liste_by_Fichierbin(TListe *liste) {
    if (liste == NULL) {
        printf("Erreur : La liste fournie n'est pas initialisee.\n");
        return;
    }

    FILE *f = fopen("data_liste_bin", "rb");
    if (!f) {
        printf("Erreur lors de l'ouverture du fichier (il n'existe peut-être pas encore).\n");
        return;
    }

    // Variable tampon pour tester si le fichier contient des données
    char tampon[50];
    if (fread(tampon, sizeof(tampon), 1, f) != 1) {
        printf("Le fichier est vide.\n");
        fclose(f);
        return;
    }

    int choix = 1;
    // Si la liste contient déjà des éléments, on demande où insérer
    if (liste->taille > 0) {
        printf("\n      Menu insertion de fichier a liste    \n");
        printf("    1- Inserer au debut de la liste \n");
        printf("    2- Inserer a la fin de la liste \n");
        printf("Votre choix : ");

        while (scanf("%d", &choix) != 1 || (choix != 1 && choix != 2)) {
            printf("Vous devez entrer soit 1, soit 2.\n");
            while (getchar() != '\n');
        }
    }

    // Retour au début du fichier
    rewind(f);

    if (choix == 1) {
        // Mode insertion au début
        while (fread(tampon, sizeof(tampon), 1, f) == 1) {
            TMaillon *nouveau = (TMaillon*)malloc(sizeof(TMaillon));
            if (nouveau == NULL) {
                printf("Erreur d'allocation memoire.\n");
                fclose(f);
                return;
            }
            strcpy(nouveau->donnee, tampon);

            if (liste->taille == 0) {
                liste->debut = nouveau;
                liste->fin = nouveau;
                nouveau->next = NULL;
            } else {
                nouveau->next = liste->debut;
                liste->debut = nouveau;
            }
            liste->taille++;
        }
    } else {
        // Conservervation de  l'ordre du fichier)
        while (fread(tampon, sizeof(tampon), 1, f) == 1) {
            TMaillon *nouveau = (TMaillon*)malloc(sizeof(TMaillon));
            if (nouveau == NULL) {
                printf("Erreur d'allocation memoire.\n");
                fclose(f);
                return;
            }
            strcpy(nouveau->donnee, tampon);
            nouveau->next = NULL;

            if (liste->taille == 0) {
                liste->debut = nouveau;
                liste->fin = nouveau;
            } else {
                liste->fin->next = nouveau;
                liste->fin = nouveau;
            }
            liste->taille++;
        }
    }

    fclose(f);
    affiche(liste);
}


