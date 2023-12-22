#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"


cellule_t* nouvelle_cellule(string c){
    cellule_t* nouv_cel = (cellule_t*) malloc(sizeof(cellule_t));
    nouv_cel->val = c;
    nouv_cel->suivant = NULL;
    return nouv_cel;
}

void init_liste_vide(liste_t* L) {
    L->tete = NULL;
}

//revoie 1 si liste vide et 0 sinon
int est_vide(liste_t* L){
    return L->tete == NULL;
}

void liberer_cel(cellule_t* cel){

    free(cel);
}


void liberer_liste(liste_t* L) {
    cellule_t* cel = L->tete;
    while(cel){
        cellule_t* suiv = cel->suivant;
        liberer_cel(cel);
        cel = suiv;
    }
    L->tete = NULL;
}


int ajouter_tete(liste_t* L, string c) { /* retourne 0 si OK, 1 sinon  */
    cellule_t* cel = nouvelle_cellule(c);
    cel->suivant = L->tete;
    L->tete = cel;

        if (strcmp(L->tete->val, c))
            return 1;
    return 0;
}


int longeur_seq(cellule_t* cel){
    int compteur = 0;
    while (cel != NULL)
    {
        compteur++;
        cel = cel->suivant;
    }
    return compteur;
}

int recherche_dans_seq(cellule_t *seq, string nom)
{
    cellule_t *cel;
    cel = seq;
    while (cel != NULL)
    {
        if (!strcmp(cel->val, nom)){
            //trouvé
            return 1;
        }
        cel = cel->suivant;
    }
    return 0;
}