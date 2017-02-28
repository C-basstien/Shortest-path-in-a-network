#include "liste.h"
#include "lecture.h"
#include "file.h"
#include "dico.h"
#include <stdio.h>
#include <stdlib.h>

int circuit_neg(Graphe graph, int nbsom, double* poids);

Liste bellman (Graphe graph, int nbsom, int in, int out);

Liste optimisation(Graphe graph, int nbsom, Sommet* tab_sommets, int in, int out);
