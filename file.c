#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "file.h"


/* cree une nouvelle cellule */
cellule_f* nouvelle_cellule_f(){
    cellule_f* nouv_cel = (cellule_f*) malloc(sizeof(cellule_f));
    nouv_cel->ar = NULL;
    nouv_cel->suivant = NULL;
    nouv_cel->niveau = -1; //val impossible
    return nouv_cel;
}


/* libère une cellule */
void liberer_cel_f(cellule_f* cel){
    free(cel);
}

/* libère toutes les cellules de la liste */
void liberer_liste_f(liste_f *F){
    cellule_f* cel = F->tete;
    while(cel){
        cellule_f* suiv = cel->suivant;
        liberer_cel_f(cel);
        cel = suiv;
    }
    F->tete = NULL;
}


void init_file_vide(liste_f* F){
    F->tete = NULL;
}

//renvoie 1 si vide 0 sinon
int est_vide_f(liste_f* F){
    return F->tete == NULL;
}

arbre defiler(liste_f* F){
    if (est_vide_f(F))
        return NULL;

    cellule_f *cel = F->tete;
    F->tete = cel->suivant;
    arbre ar = cel->ar;
    liberer_cel_f(cel);    
    return ar;
}

void enfiler(liste_f* F, cellule_f* cel){
    if (est_vide_f(F)){
        F->tete = cel;
        return;
    }

    cellule_f* queue = F->tete;

    while (queue->suivant){ 
        queue = queue->suivant;
    }

    queue->suivant = cel;

}
