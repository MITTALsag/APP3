#ifndef _LISTES_H
#define _LISTES_H


typedef struct liste liste_t;
/* Type de liste à compléter selon votre besoin. */

typedef char* string;

struct cellule {
	string val;
	struct cellule* suivant;
};



typedef struct cellule cellule_t;

struct liste {
	cellule_t *tete;
};

typedef struct liste liste_t;

/* cree une nouvelle cellule */
cellule_t* nouvelle_cellule(string c);

/* cree une nouvelle liste, initialement vide */
void init_liste_vide(liste_t* L);

int est_vide(liste_t* L);

/* libère une cellule */
void liberer_cel(cellule_t* cel);

/* libère toutes les cellules de la liste */
void liberer_liste(liste_t *L);

/* Ajouter une nouvelle cellule contenant c
 * en tête de la liste L.
 * Si l'ajout est réussi, le résultat est 0,
 * et 1 sinon (échec de l'ajout)
 */
int ajouter_tete(liste_t *L, string c);

void ajouter_fin(liste_t* L, string c);

cellule_t* supprimmer_tete(liste_t* L);

int longeur_seq(cellule_t* seq);

int recherche_dans_seq(cellule_t *seq, string nom);


#endif /* _LISTES_H */


