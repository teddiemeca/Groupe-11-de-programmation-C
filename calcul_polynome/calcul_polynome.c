# include "calcul_polynome.h"


void vider_buffer(){
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}


void test_polynome(CPolynome* polynome)
{
    if (polynome ==NULL){
        printf("erreur d allocation.");
        exit(1);
    }
}


void op_polynome(CPolynome* polynome){
    CPolynome* courant =polynome;
    while(courant != NULL){
        courant->coefficient *=-1;
        courant = courant->suivant;
    }
}


void affichage(CPolynome* polynome)
{
     if(polynome == NULL){
        printf(("aucun polynome enregistrer ."));
        return;
    }

    CPolynome *courant = polynome;
    while(courant!=NULL)
    {
        if(courant->suivant!=NULL){
            printf(" %dx^%d +",courant->coefficient,courant->exposant);
        }
        else{
            printf(" %dx^%d ",courant->coefficient,courant->exposant);
        }
        courant = courant->suivant;
    }
    printf("\n");
}



CPolynome * creer_polynome()
{
    char chaine_p[250];
    int char_lu,coef,exp;
    static int i=1;


    printf("-------- veuillez saisir le polynome ----------\n");
    printf("\nNB: respecter cette structure : aX^n + bX^(n-1) + .... + kX^0 ,a,b,..,k appartient a N\n");
    printf("polynome %d :",i);

    while(scanf("%249[^\n]",chaine_p)!=1){
        vider_buffer();
        return NULL;
    }
    
    vider_buffer();

    i++;
    char* cursor = chaine_p;
    CPolynome* tete = NULL;
    CPolynome* courant_P  = NULL;


    while(sscanf(cursor," %dX^%d %n",&coef,&exp,&char_lu)==2 || sscanf(cursor,"%dX^%d%n",&coef,&exp,&char_lu) == 2)
    {
        cursor+=char_lu;
        while(*cursor == ' ' || *cursor == '+'){
            cursor++;
        }

        CPolynome* nouveau= (CPolynome*)malloc(sizeof(CPolynome));
        test_polynome(nouveau);


        nouveau->coefficient = coef;
        nouveau->exposant = exp;
        nouveau->suivant = NULL;

        if(tete == NULL)
        {
            tete = nouveau;
        }
        else{
            courant_P->suivant= nouveau;
        }
        courant_P=nouveau;
    }


    return tete;
}





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















