#ifndef _file_
#define _file_

#include "lecture.h"

typedef struct Cellule Cellule;
struct Cellule
{
	Sommet som;
    Cellule* suiv;
};
typedef Cellule* File;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


File creer_file(void);

int file_vide(File f);

File enfiler(File f, Sommet s);

Sommet defiler(File* pf);

void affiche_file(File f);

#endif