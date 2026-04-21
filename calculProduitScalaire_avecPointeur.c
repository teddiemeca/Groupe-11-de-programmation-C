#include    <stdio.h>
#include    <stdlib.h>



/******************************************************************************
NOM DU FICHIER : programme_C2

DESCRIPTION    : Ce Programme permet de calculer le produit scalaire de deux vecteurs
                 entrés par l utilisateur . Il fait appelle a plusieurs fonctions et procedures
                 chacun jouant un role specifique.

GROUPE          :   N°11

MEMBRES DE GROUPE:    David PASSAH GC
                      Marcel AFANGNIBO IABD
                      Pierrette ATCHIKITI IABD
                      Eddie CHILI GM
                      Imenne TCHALIM GM
                      Jason AGNAVE IABD
                      Charles SEGBEDZI GC
                      Abdoul-Raouf BARBOZA GC
                      Godwin HONKU IABD

DATE           : 21/04/2026

VERSION        : finale ameliorée totalement avec les pointeurs

COMPILATION    : gcc -Wall -o programme programme_C2
*****************************************************************************
*/


//  Prototype des fonctions
void lire_taille(int* N);   //    Procedure permettant de recuperer le nombre de vecteur dont l'utilisateur dispose
float* pointeur_vect(int* N);   //    Creation des vecteurs .
void lire_coordonnees_vecteur(float*tab,int* N,char nom);     //     Procedure de recuperation des coordonnees des vecteurs
void calcul_produit_scalaire(float*tab1,float*tab2,int* N,float* produit_scalaire);     //  Procedure de calcul du produit scalaire
void afficher_vecteur(float* tab1,float* tab2,int* N);      //      Procedure d affichage des vecteurs
void afficher_produit_scalaire(float* produit_scalaire);       //      Procedure d affichage du produit scalaire



// Fonction principale
int main(){
    printf("\n ** Debut du programme  **\n");
    int N;
    float *u=NULL;
    float *v=NULL;
    float produit_scalaire;

    lire_taille(&N);
    u=pointeur_vect(&N);
    v=pointeur_vect(&N);


    lire_coordonnees_vecteur(u,&N,'u');
    lire_coordonnees_vecteur(v,&N,'v');
    afficher_vecteur(u,v,&N);

    calcul_produit_scalaire(u,v,&N,&
                            produit_scalaire);
    afficher_produit_scalaire(&produit_scalaire);

    // on vide les tableaux
    free(u);
    free(v);
    // on remet les pointeurs a NULL
    u=NULL;
    v=NULL;

    return 0;
}

// Fonction de recuperation de la taille des vecteurs saisie par l utilisateur
void lire_taille(int* N){
    printf(" entrez  le  nombre de composante des vecteurs :");
    while (scanf("%d",N)!=1 || *N<=1){
                printf("[!] Erreur. Entrez un nombre superieur ou egale a deux: ");
                while (getchar() != '\n'); }
}

float* pointeur_vect(int* N){

    float *u = (float*)(malloc(*N*sizeof(float)));
    //verification de L ALLOCATION DE LA MEMOIRE
    if(u == NULL){
        printf("Erreur d allocation de la memoire veuillez relancer le programme");
        exit(EXIT_FAILURE);
    }
    return u;
}


// fonction permettant de lire chaque vecteur
void lire_coordonnees_vecteur(float*tab,int* N,char nom){
    int compteur=1;
    for(float* i=tab;i<tab+*N;i++){
        printf(" entrez la composante %d du vecteur %c :",compteur,nom);
        while(scanf("%f",i)!=1){
             printf(" [!] tu dois entrer un reel :");
             while(getchar() !=  '\n');}
        compteur++;
        }
        printf("\n");
}

// Fonction de calcule du produit scalaire
void calcul_produit_scalaire(float* tab1,float* tab2,int* N,float* produit_scalaire){
    float* y = tab2;
    *produit_scalaire=0;
    for(float* i=tab1;i<tab1 + *N;i++)
    {
        *produit_scalaire += *i * *y ;
        y++;
    }
}


// Procedure d affichage des vecteurs
void afficher_vecteur(float*tab1,float*tab2,int* N){
    printf("les deux vecteurs enregistres sont :\n");
    printf("- u(");
    for(float* i=tab1;i<tab1+*N;i++){
        printf("%.2f",*i);
        if(i<tab1+*N-1){printf(",");}
    }
    printf(")\n");
    printf("- v(");
    for(float *i=tab2;i<tab2+*N;i++){
        printf("%.2f",*i);
        if(i<tab2+*N-1){printf(",");}
    }
    printf(")\n");
}



// Procedure d affichage du produit scalaire
void afficher_produit_scalaire(float* produit_scalaire){
    printf("\n le produit scalaire des deux vecteurs u et v est : %.2f \n",*produit_scalaire);
}
