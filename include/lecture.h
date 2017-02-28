#ifndef GRAPH
#define GRAPH

#define SLEN 40
typedef struct Sommet Sommet;
struct Sommet
{
	int num;
	double coordX;
	double coordY;
	char ligne[15];
	char nom[SLEN];
    int poids ;
};
typedef struct Arc Arc;
struct Arc
{
	int depa;
	int ariv;
	double cout;
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include "dico.h"

typedef Liste* Graphe;

void affiche_sommets(Sommet *S,int n);//Affiche les données contenu dans le tableau de n strucures Sommet,utile pour faire des tests seulement

void affiche_arcs(Arc *A,int n);//Affiche les données contenu dans le tableau de n strucure Arc,utile pour faire des tests seulement

void affiche_graphe(Graphe G,int n);//Affiche le Graphe:c'est un tableaux de liste ,utile pour faire des tests seulement

Graphe creer_graphe(Arc *A,int nbre_arcs,int nbre_sommets);//creer un graphe à partir de notre tableau d'arc A et du nombre de sommet n:le resultat est un tableau de n listes

void simplifie_chaine(char* m,char* mot);//fonction qui suprimme les tabulations et les retours chariots dans une chaine de caractère , pour qu'elle fonctionne il faut m=mot

void lire(Sommet** adr_tab_sommets,Arc** adr_tab_arcs,int* adr_nbre_sommets,int* adr_nbre_arcs,Graphe* adr_graphe,Ldico** adr_dico);//fonction qui lit le fichier.csv et retourne les données utiles dans l'adresse de nos paramètres

#endif 
