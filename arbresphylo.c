#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"

void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac)
{
   //initialisation de variables
   *nb_carac = 0;
   *nb_esp = 0;

   analyse_arbre_corps(racine, nb_esp, nb_carac);

}

void analyse_arbre_corps(arbre racine, int* nb_esp, int* nb_carac){

   //arbre vide
   if (!racine) 
      return;

   //c'est forcément une espece
   if (!racine->gauche && !racine->droit){
      *nb_esp +=1;
      return;
   }

   //si on arrive jusque la on est sur uen caractéristique
   *nb_carac +=1;

   // appelle récursifs
   if (racine->gauche)
      analyse_arbre_corps(racine->gauche, nb_esp, nb_carac);

   if (racine->droit)
      analyse_arbre_corps(racine->droit, nb_esp, nb_carac);
}






/* ACTE II */
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
 * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece (arbre racine, char *espece, liste_t* seq)
{
   int res;

   if (!racine)
      return 1;
   //si on a trouvé l'espece cherché
   if (!strcmp(racine->valeur, espece)) 
      return 0;

   res = rechercher_espece(racine->gauche, espece, seq);
   //si res = 0 cela veux dire que l'espece n'a la carctéristique courante
   if (res == 0){
      return 0;
   }

   res = rechercher_espece(racine->droit, espece, seq);
   //si res = 0 cela signifie que l'espece se trouve a droite et donc que la caractéristique courante doit etre dans la sequence
   if (res == 0){
      ajouter_tete(seq, racine->valeur);
      return 0;
   }

   return 1; //on n'a pas touvé l'espece
}



/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un 
 * message d'erreur.
 */
int ajouter_espece (arbre* a, char *espece, cellule_t* seq) {

    return 1;
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau (arbre racine, FILE* fout) {
   printf ("<<<<< À faire: fonction afficher_par_niveau fichier " __FILE__ "\n >>>>>");
}

// Acte 4


int ajouter_carac(arbre* a, char* carac, cellule_t* seq) {
   printf ("<<<<< À faire: fonction ajouter_carac fichier " __FILE__ "\n >>>>>");
   return 0;
}
