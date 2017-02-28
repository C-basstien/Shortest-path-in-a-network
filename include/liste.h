#ifndef ____liste__
#define ____liste__

typedef struct Maillon Maillon;
struct Maillon
{
	int num;
    double cout;
    Maillon* suiv;
};
typedef Maillon* Liste;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture.h"


/////définition d'un type Liste pour les graphes


Liste creer_liste(void);

int est_vide(Liste l);

void visualiser_liste(Liste l);

void visualiser_chemin(Liste l,Sommet* S);

Liste ajout_tete(Liste l ,int num ,double cout);

Liste ajout_queue(Liste l ,int num ,double cout);

Liste supprimer_tete(Liste l);

void supprimer_liste(Liste l);


#endif
