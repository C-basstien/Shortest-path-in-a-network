#include "lecture.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <SDL.h>
#include <SDL_phelma.h>

#define X_LEN 1400
#define Y_LEN 800
int gestion_ecran (Sommet* S,Graphe G ,int nbre_sommet,Liste chemin,int* type_de_rch,int* dep ,int* ariv);

void affichage_plan(SDL_Surface* f ,TTF_Font *police,Sommet* S,Graphe G ,int nbre_sommet,double moy_xy[],int ctre_xy[],double zoom_xy[],int t,int v ,Liste chemin)
;
int test_coord(double x ,double y);
void moyenne(Sommet* S,int nbre_sommet,double *m);
int color(Sommet S1,Sommet S2);
int rch_fntre(double x ,double y,Sommet* S,int nbre_sommet,double moy_xy[],int ctre_xy[],double zoom_xy[]);
