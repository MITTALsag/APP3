#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "arbres.h"

noeud* nouveau_noeud(void)
{
    noeud *n = (noeud*)malloc(sizeof(noeud));
    assert (n!=NULL);
    n->valeur = NULL;
    n->gauche = NULL;
    n->droit  = NULL;
    return n;
}


/* buffer pour lire les caractères des espèces sous forme de "mots" (words) */
#define MAX_WORD_SIZE 255
char buffer[MAX_WORD_SIZE+1];

/* Variable globale qui contient le prochain caractère à traiter */
static char next_char = ' ';

/* Supprime tous les espaces, tabulations, retour à la ligne */
#define GLOB(f) \
    while(isspace(next_char)) { \
        next_char = fgetc(f);\
    }


/* Fonction récursive qui lit un sous-arbre */
/* Appelée une fois à la racine (debut du fichier), puis récursivement
 * pour chaque nœud interne rencontré. */
arbre lire_arbre (FILE *f)
{
    arbre racine;

    GLOB(f); /* lit dans next_char le premier caractère non vide */

    if (next_char == '/') {
        next_char = ' '; /* on ne garde pas '/' en mémoire */
        return NULL;
    }

    if (next_char == ')') {
        return NULL;
    }

    if (next_char != '(') {
        fprintf(stderr, "Error while reading binary tree : '(' or ')' expected at position %ld\n", ftell(f));
        exit (1);
    }

    /* On remplit le buffer tant qu'on lit des caractères alphanumériques */
    char *p = buffer; /* début du buffer */
    next_char = ' '; GLOB(f);

    do {
        *p = next_char;       /* sauvegarde du char courant */
        next_char = fgetc(f);
        p++;
        assert (p < buffer + MAX_WORD_SIZE);
    } while (! isspace (next_char) && next_char != '(' && next_char != ')');
    /* on arrète si le char suivant est un espace ou une parenthèse */
    *p='\0'; /* on ferme la chaîne de caractères dans le buffer */

    racine = nouveau_noeud();
    racine->valeur = strdup(buffer); /* dupliquer le mot lu */

    GLOB(f);

    if (next_char == ')') {
        next_char = ' '; /* on est sur une feuille, on prépare la lecture du prochain nœud */
    }
    else {
        racine->gauche = lire_arbre (f); /* appel récursif pour le fils gauche */
        racine->droit  = lire_arbre (f); /* idem pour le droit */

        GLOB(f); /* lit jusqu'au ')' fermant */

        if (next_char != ')') {
            fprintf(stderr, "Error while reading binary tree: ')' expected\n");
            exit(1);
        }
        next_char = ' '; /* on ne garde pas la parenthèse en mémoire */
    }
    return racine;
}


void ecrire_arbre(arbre ar, char* nom_fich){
    FILE* fich = fopen(nom_fich, "w");

    if (!fich){
        printf("Erreur lors de l'ouverture du fichier %s en écriture.\n", nom_fich);
        exit(1);
    }

    ecrire_arbre_corp(ar, fich);

    fclose(fich);
}


void ecrire_arbre_corp(arbre ar, FILE* fich){

    if (!ar){
        fprintf(fich, "/\n");
        return;
    }

    fprintf(fich, "(%s\n", ar->valeur);

    ecrire_arbre_corp(ar->gauche, fich);
    ecrire_arbre_corp(ar->droit, fich);

    fprintf(fich, ")\n");

}


//affichage de l'arbre
/*----------------------------------------------------------------------------------------------------------------------------------*/


void fichier_DOT(arbre a, FILE* fich){
    
    fprintf(fich, "digraph graph_arbre{\n\t");

    fichier_DOT_corps (a, fich, 'a');
    
    fprintf(fich, "\n}");

}



void fichier_DOT_corps(arbre a, FILE* fich, char direction){

    //arbre vide
    if (!a)
        return;

    //si on est sur une feuille (espece)
    //sert pour mettre "non" ou "oui" (pas obligatoire)
    if (!a->gauche && ! a->droit){
        if (direction == 'g')
            fprintf(fich, "%s [label = \"non\"];\n\t", a->valeur);
        else if (direction == 'd')
            fprintf(fich, "%s [label = \"oui\"];\n\t", a->valeur);
        else 
            fprintf(fich, "%s;\n\t", a->valeur);

        return;
    }
    
    if (a->gauche){
        fprintf(fich, "%s -> ", a->valeur);

        //sert pour le label mais marche bien sans 
        if (a->gauche->gauche)  
            fprintf(fich, "%s [label = \"non\"];\n\t", a->gauche->valeur);

        //appelle recurssif
        fichier_DOT_corps(a->gauche, fich, 'g');
    }

    if (a->droit){
        fprintf(fich, "%s -> ", a->valeur);

        //sert pour le label mais marche bien sans
        if (a->droit->droit)
            fprintf(fich, "%s [label = \"oui\"];\n\t", a->droit->valeur);
        
        //appelle recursif
        fichier_DOT_corps(a->droit, fich, 'd');
    }


}


void affiche_arbre (arbre ar)
{
    //Pour savoir si on veut afficher l'arbre ou pas
    char c;
    printf("Voulez-vous affichez l'arbre dans un fichier .png ? (y pour oui et n pour non)\n");
    printf(RED"PS: les arbre amphibians ou recher_appolab sont trop gros pour graphviz donc il faut mettr n pour eux.\n"RESET);

    scanf("%c", &c);
    while (c != 'y' && c != 'n'){
        printf("Il faut choisir entre y pour afficher ou n pour ne pas l'afficher !!!\n");
        scanf("%c", &c);
    }
    
    if (c == 'y'){

        FILE* fich;
        fich = fopen("fichier_arbres.dot", "w");

        if (!fich) {
            fprintf (stderr, "Erreur à l'ouverture du fichier 'fichier_arbres.dot'\n");
            exit(1);
        }
        fichier_DOT(ar, fich);
        fclose(fich);

        const char* commande = "dot -Tpng fichier_arbres.dot -o graph.png";
        int sys = system(commande);

        if (sys != 0){ 
            fprintf(stderr, "Impossible de lancer la commande : %s\n", commande);
        }
    }
}

