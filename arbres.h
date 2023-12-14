#ifndef ARBRES_H
#define ARBRES_H

/* Structure d'un noeud d'arbre */
struct noeud_s;
typedef struct noeud_s noeud;

/* Un arbre binaire est défini comme une référence vers le noeud racine de l'arbre.
 * Un arbre binaire vide est représenté par une référence NULL.
 * Un arbre binaire est une structure de données récursive.
 * Si il n'est pas vide, ses fils sont des arbres.
 */
typedef noeud* arbre;

struct noeud_s {
    char* valeur;
    arbre gauche;
    arbre droit;
};

#define RED   "\x1B[31m" 
#define RESET "\x1B[0m"



/* Crée un nouveau nœud et initialise ses champs à null */
noeud* nouveau_noeud (void);

/* Construit un arbre depuis le fichier ouvert f.
 * Fonction récursive (s'appelle elle-même pour la lecture des fils
 * gauche et droit).
 */
arbre lire_arbre (FILE *f);

/* fonction récursive qui écrit dans un fichier l'arbre qui correspond a ar au format de l'énoncé*/
void ecrire_arbre(arbre ar, char* nom_fich);
void ecrire_arbre_corp(arbre ar, FILE* fich);

//met dans un fichier l'arbre sous format .dot pour pouvoir ensuite l'afficher
//fonction recursive
void fichier_DOT(arbre a, FILE* fich);

void fichier_DOT_corps(arbre a, FILE* fich, char direction);


/* Fonction d'affichage, à remplir */
void affiche_arbre (arbre);


/* Macros pour de l'affichage uniquement si DEBUG est != 0 */
extern int DEBUG;

#define debug(fmt, ...) \
            do { if (DEBUG) fprintf(stderr, fmt, ##__VA_ARGS__); } while (0)

#endif
