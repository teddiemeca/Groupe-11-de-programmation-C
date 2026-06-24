/*
 ******************************************************************************
 * NOM DU PROJET : programme_calcul_polynome
 * FICHIER       : calcul_polynome.h
 * DESCRIPTION   : Definition des structures de donnees de gestion des polynomes 
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


# include "calcul_polynome.h"

// VIDER BUFFER NECESSAIRE POUR EFFACER LE TAMPON APRES UN SCANF
void vider_buffer(){
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}


// UTILE POUR VERIFIER SI LE POLYNOME A ETE BEL ET BIEN CREER 
void test_polynome(CPolynome* polynome)
{
    if (polynome ==NULL){
        printf("erreur d allocation.");
        exit(1);
    }
}


// SOLUTION POUR NE PAS REECRIRE TOUTE LA FONCTION DE SOUSTRACTION DE POLYNOME 
void op_polynome(CPolynome* polynome){
    CPolynome* courant =polynome;
    while(courant != NULL){
        courant->coefficient *=-1;
        courant = courant->suivant;
    }
}


void supprimer_espace(char* str)
{
    char* i = str;
    char* j = str;

    while(*i){
        if(!isspace((unsigned char)*i)){
            *j++ = *i;
        }
        i++;
    }
    *j = '\0';
}


void ordonner_polynome(CPolynome* polynome)
{
    if (polynome == NULL || polynome->suivant == NULL){
        return;
    }

    bool ordre = false;
    
    CPolynome* courant;

    while (!ordre){
        ordre = true;
        courant = polynome;

        while(courant->suivant != NULL ){
            if(courant->exposant < (courant->suivant)->exposant){

                int relai_coef = courant->coefficient;
                courant->coefficient = courant->suivant->coefficient;
                courant->suivant->coefficient = relai_coef;

                int relai_expo = courant->exposant;
                courant->exposant = courant->suivant->exposant;
                courant->suivant->exposant = relai_expo;

                ordre = false;
            }
            courant = courant->suivant;
        }
    }
}



void aide_affichage(CPolynome*courant){

    int coeff = abs(courant->coefficient);

    if(coeff !=0 && courant->exposant !=0){

        if (coeff == 1){
            printf("x^%d",courant->exposant);
        }
        else{
            printf("%dx^%d",courant->coefficient,courant->exposant);
        }
    }

    else if (courant->coefficient != 0 && courant->exposant ==0){
        printf("%d",courant->coefficient);
    }
}


// AFFICHER LE POLYNOME 
void afficher_polynome(CPolynome* polynome)
{
     if(polynome == NULL){
        printf(("aucun polynome enregistrer ."));
        return;
    }

    int premier = 1;
    CPolynome *courant = polynome;

    while(courant!=NULL)
    {
        if (courant->coefficient != 0){

            if (premier){
                if (courant->coefficient < 0){
                    printf("-");
                }
                premier = 0;
            }
            else{
                if (courant->coefficient > 0){
                    printf(" + ");
                }
                else if (courant->coefficient < 0){
                    printf(" - ");
                }
            }
            aide_affichage(courant);

        }
        
        courant = courant->suivant;
    }
    if (premier)
    {
        printf("0");
    }
    printf("\n");
}




// CREER UN POLYNOME 
CPolynome * creer_polynome()
{
    char chaine_p[250];
    int char_lu, coef, exp;
    static int i = 1;

    printf("-------- veuillez saisir le polynome ----------\n");
    printf("\nNB: respecter cette structure : ax^n + bx^(n-1) + .... + kx^0\n");
    printf("polynome %d :", i);

    while(scanf("%249[^\n]", chaine_p) != 1){
        vider_buffer();
        return NULL;
    }
    
    vider_buffer();

    // Suppression de tous les espaces
    supprimer_espace(chaine_p);

    i++;
    char* cursor = chaine_p;
    CPolynome* tete = NULL;
    CPolynome* courant_P = NULL;



    while (*cursor!='\0')
    
    {
        // Saut du signe '+' pour le prochain tour
        if (*cursor == '+') {
            cursor++;
        }

        if(sscanf(cursor, "%dx^%d%n", &coef, &exp, &char_lu) == 2 || sscanf(cursor, "%dX^%d%n", &coef, &exp, &char_lu) == 2 ){
            cursor+=char_lu;
        }

        else if (sscanf(cursor, "x^%d%n", &exp, &char_lu) == 1 || sscanf(cursor, "X^%d%n", &exp, &char_lu) == 1){
            coef = 1;
            cursor+=char_lu;
        }

        else if(sscanf(cursor, "-x^%d%n", &exp, &char_lu) == 1 || sscanf(cursor, "-X^%d%n", &exp, &char_lu) == 1){
            coef = -1;
            cursor +=char_lu;
        }

        else if(sscanf(cursor, "%d%n", &coef, &char_lu) == 1 ){
            exp = 0;
            cursor+=char_lu;
        }
        else{
            printf(" Erreur de synthaxe detectee au niveau de %s",cursor);
            break;
        }
        

        CPolynome* nouveau = (CPolynome*)malloc(sizeof(CPolynome));
        test_polynome(nouveau);

        nouveau->coefficient = coef;
        nouveau->exposant = exp;
        nouveau->suivant = NULL;

        if (tete == NULL) {
            tete = nouveau;
        } else {
            courant_P->suivant = nouveau;
        }
        courant_P = nouveau;
    }
    
    ordonner_polynome(tete);

    return tete;
}




// FONCTION PERMETTANT DEE CALCULER LA SOMME DE DEUX POLYNOMES 
CPolynome * somme_polynome (CPolynome* polynome1,CPolynome* polynome2)
{
    if (polynome1 == NULL) return polynome2;
    if (polynome2 == NULL) return polynome1;

    CPolynome* P1=polynome1;
    CPolynome* P2=polynome2;

    CPolynome* somme_G = NULL;
    CPolynome* courant = NULL;
 

    while(P1!=NULL || P2 !=NULL)
    {
        CPolynome* somme_P =  (CPolynome*)malloc(sizeof(CPolynome));
        test_polynome(somme_P);
        somme_P->suivant = NULL;

        if(P1!=NULL && P2==NULL){

            somme_P->coefficient = P1->coefficient;
            somme_P->exposant = P1->exposant;
            P1 = P1->suivant;

        }
        else if(P1==NULL && P2!=NULL){

            somme_P->coefficient = P2->coefficient;
            somme_P->exposant = P2->exposant;
            P2 = P2->suivant;

        }
        else{
            if (P1->exposant != P2->exposant)
                {
                    if(P1->exposant > P2->exposant)
                    {
                        somme_P->coefficient = P1->coefficient;
                        somme_P->exposant = P1->exposant;
                        P1 = P1->suivant;
                    }
                    else{
                        somme_P->coefficient = P2->coefficient;
                        somme_P->exposant = P2->exposant;
                        P2 = P2->suivant;
                    }
                }
            else
            {
                somme_P->coefficient = P1->coefficient + P2->coefficient;
                somme_P->exposant = P1->exposant;
                P1 = P1->suivant;
                P2 = P2->suivant;
            }
        }

        if (somme_G == NULL){
                somme_G = somme_P;
            }

        else{
            courant->suivant = somme_P;
        }    
        courant = somme_P;
    }

    return somme_G;
}


// FONCTION PERMETTANT DE SOUSTRAIRE DEUX POLYNOMES
CPolynome* soustraction_polynome(CPolynome* polynome1,CPolynome* polynome2)
{
    if (polynome1 == NULL){
        op_polynome(polynome2);
        return polynome2;
    }
    if (polynome2 == NULL) return polynome1;

    op_polynome(polynome2);

    CPolynome* resultat = somme_polynome(polynome1,polynome2);

    op_polynome(polynome2);

    return resultat;

}


// NECESSAIRE POUR GERER LES ADDITIONS EN MULTIPLICATION DE DEUX POLYNOMES 
CPolynome* insert_polynome(CPolynome* tete , int c, int e)
{
    if (c == 0) return tete;

    CPolynome* courant = tete;
    CPolynome* precedent= NULL;

    while (courant!= NULL && courant->exposant > e)
    {
        precedent = courant;
        courant = courant->suivant;
    }

    if (courant != NULL && courant->exposant == e)
    {
        courant->coefficient += c;
        if (courant->coefficient == 0){ 
            if (precedent == NULL) tete = courant->suivant;
            else precedent->suivant = courant->suivant;
            free (courant);
        }
        return tete;
    }

    CPolynome* nouveau = (CPolynome*)malloc(sizeof(CPolynome));
    test_polynome(nouveau);

    nouveau->coefficient = c;
    nouveau->exposant = e ;
    nouveau->suivant = courant;

    if(precedent == NULL) return nouveau;
    precedent->suivant = nouveau;
    return tete;
}


// FONCTION DE PRODUIT DE DEUX POLYNOMES QUI UTILISES LA FONCTION INSERT_POLYNOMES PREDEFINIT
CPolynome* produit_polynome(CPolynome*polynome1,CPolynome* polynome2)
{
    if (polynome1 == NULL || polynome2 == NULL) return NULL;

    CPolynome* prod_G = NULL;
    for (CPolynome* P1 =polynome1 ;P1 != NULL ; P1=P1->suivant){
        for (CPolynome* P2 = polynome2 ;P2 !=NULL ;P2 = P2->suivant)
        {
            int c = P1->coefficient *  P2->coefficient;
            int e = P1->exposant + P2->exposant;

            prod_G=insert_polynome(prod_G,c,e);
        }
    }
    return prod_G;
}



// FONCTION PERMETTANT DE LIBERER L ESPACE MEMOIRE ALLOUE POUR UN POLYNOMES
void detruire_polynome(CPolynome* polynome)
{
    CPolynome* courant = polynome;
    while(courant != NULL)
    {
        CPolynome* assuprimer = courant;
        courant = courant->suivant;
        free(assuprimer);
    }
}














