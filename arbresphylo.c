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

void ajouter_list_car(arbre a, char* esp, cellule_t* seq){

   while(seq){
      a->valeur = seq->val;

      a->droit = nouveau_noeud();
      a = a->droit;

      seq = seq->suivant;
   }

   a->valeur = esp;
}


int ajouter_espece (arbre* a, char *espece, cellule_t* seq) {

   noeud* noeud;

   if (!seq){

      if (!(*a)){
         //arbre vide et pas de car a mettre
         noeud = nouveau_noeud();
         noeud->valeur = espece;
         (*a) = noeud;
         return 0;
      }

      if (!((*a)->gauche) && !((*a)->droit)){
         //on est sur une feuille avec exactement les meme caracteristique qu'une autre espece
         printf("Ne peut pas ajouter %s: possède les mêmes caractères que %s.\n", espece, (*a)->valeur);
			return 1;
      }
      return ajouter_espece(&((*a)->gauche), espece, NULL);

   }     

   if (!(*a)){
      //si arbre vide on ajoute toutes les caracteristique puis l'espece
      noeud = nouveau_noeud();
      *a = noeud;
      ajouter_list_car(*a, espece, seq);
      return 0;
   }

   if (!((*a)->gauche) && !((*a)->droit)){
      //place la feuille initial de l'arbre a gauche d'une carc de seq puis met toutes les carac de seq et ensuite l'espece a rajouter

      (*a)->gauche = nouveau_noeud();
		(*a)->gauche->valeur = (*a)->valeur;

		(*a)->valeur = seq->val;
		(*a)->droit = nouveau_noeud();

		ajouter_list_car(((*a)->droit), espece, seq->suivant);

		return 0;
   }

   if (!strcmp(seq->val, (*a)->valeur)){
      //si les carac sont égales on continue de chercher a droite avec les carac suivantes

      return ajouter_espece(&(*a)->droit, espece, seq->suivant);
   }

   //sinon on cherche a gauche avec la meme carac
   return ajouter_espece(&(*a)->gauche, espece, seq);

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
