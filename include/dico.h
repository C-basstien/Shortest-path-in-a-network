#ifndef dicoH
#define dicoH

typedef struct Maille Maille;
struct Maille
{
	char* nom;//nom du sommet
    int num;//et son numéro
    Maille* suiv;
};
typedef Maille* Ldico;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture.h"

void visualiser_liste_dico(Ldico l);

void affiche_dico(Ldico* l,int dim_tab_hach);

Ldico ajout_tete_dico(Ldico l ,char* mot ,  int num);


unsigned int hachage(unsigned char* mot, int dim_tab_hach);

Ldico* creer_dico(Sommet* S,int nbre_sommets);

Ldico recherche(Sommet* S,Ldico* l,int dim_tab_hach);

void affiche_suggestion(Sommet* S,char* mot,int nbre_sommet);

int test_char(char s , char c);

#endif 
