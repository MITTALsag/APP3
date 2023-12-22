#ifndef _FILE_H
#define _FILE_H

#include "arbres.h"


typedef struct cellule_file{
    arbre ar;
    int niveau;
    struct cellule_file* suivant;
}cellule_f;


typedef struct liste_file {
	cellule_f *tete;
}liste_f;

/* cree une nouvelle cellule */
cellule_f* nouvelle_cellule_f();


/* libère une cellule */
void liberer_cel_f(cellule_f* cel);

/* libère toutes les cellules de la liste */
void liberer_liste_f(liste_f *F);


void init_file_vide(liste_f* F);

//renvoie 1 si vide 0 sinon
int est_vide_f(liste_f* F);

arbre defiler(liste_f* F);

void enfiler(liste_f* F, cellule_f* cel);

#endif