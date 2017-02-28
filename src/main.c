#include "fonction.h"
#include "liste.h"
#include "lecture.h"
#include "file.h"
#include "dico.h"
#include "visuel.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    /*
    info utile:
    argc nombre de chaines de caracrtères saisie dans la console : en générale 2 mais on n'est pas limité./mon_de_prog et mon fichier à ouvrir
    argv tableau de chaines de caracrtères contenant les textes saisie dans  la console :./mon_de_prog et mon fichier à ouvrir  (un/une espace/tabulation indique la nouvelle chaine)
    mais ce n'est pas utile ici on choisi le fichier avec un menu dans la fonction lire
    */
	int nbre_sommets,nbre_arcs;Sommet* tab_sommets;Arc* tab_arcs;Graphe graphe;Ldico* dico;Liste chemin;
	lire (&tab_sommets,&tab_arcs,&nbre_sommets,&nbre_arcs,&graphe,&dico);
	//puts("");
	int reset=1;int rchconsole=1;
	while(reset)
	{
	    Ldico depart,arrivee;
        if(rchconsole)
        {
        puts("saisisez la station de depart");depart=recherche(tab_sommets,dico,nbre_sommets);//visualiser_liste_dico(depart);
        puts("saisisez la station d'arrivée");arrivee=recherche(tab_sommets,dico,nbre_sommets);//visualiser_liste_dico(arrivee);
        }

        chemin=optimisation(graphe,nbre_sommets, tab_sommets, depart->num,arrivee->num);
        visualiser_chemin(chemin,tab_sommets);
        printf("\n");
        reset=gestion_ecran(tab_sommets,graphe,nbre_sommets,chemin,&rchconsole,&(depart->num),&(arrivee->num));
    }
}
