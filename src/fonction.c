#include "fonction.h"
#include <stdio.h>
#include <stdlib.h>

#define INF 10E9


int circuit_neg(Graphe graph, int nbsom, double* poids){	// vérifie l'existence d'un circuit négatif
	int j,k;
	Liste buff;
	
	for (j=0; j<nbsom; j++){
		buff=graph[j];				
		while(buff != NULL) {
			
			k=buff->num;
			if (poids[j] + buff->cout < poids[k]){	
				return 1;		//il y a un circuit négatif
			}
			buff=buff->suiv;
		}
	}
	return 0;
}


Liste bellman (Graphe graph, int nbsom, int in, int out){ //on prend en paramètre le graphe à traiter et son nombre de sommets, puis les points de départ et d'arrivée
	int i,j,k;
	
	//Initialisation
	Liste chemin= creer_liste();
	Liste tmp;
	double * poids = calloc (nbsom, sizeof(*poids));
	int * pere = calloc (nbsom, sizeof(*pere));
	for (i=0; i<nbsom; i++){		// On initialise le poids de tous les sommets à l'infini
		poids[i]=INF;
	}
	poids[in]=0;					// Sauf pour le sommet de départ
	
	//Calcul du coût des différents chemins
	if (in==out){		//si la station de départ est la même que celle d'arrivée, on ne fait rien
		chemin=ajout_tete(chemin, in, 0);
		return chemin;
	} 	
	
	for(i=1; i<nbsom; i++){		 //répétéplusieurs fois pour mettre à jours les poids des sommets précédents en fonction des suivants (pour "remonter une ligne" par exemple)
		for (j=0; j<nbsom; j++){ //parcourt le tableau des sommets
			tmp=graph[j];		 // pour ne pas perdre l'adresse du premier maillon
			while(tmp!= NULL){	 //parcourt la liste chainée
				k=tmp->num;
				if (poids[j] + tmp->cout < poids[k]){
					poids[k]= poids[j] + tmp->cout; //modifie le poids du sommet si le cout est plus faible
					pere[k] = j;	//le champ pere stocke le meilleur père, ie. celui dont le cout est le plus faible
				}
				tmp=tmp->suiv;
			}			
		}		
	}
	// Vérification de l'existence d'un circuit négatif
	if (circuit_neg(graph, nbsom, poids)){
		printf ("Il y a un circuit négatif dans le graphe, solution impossible");
		exit(1);
	}

	
	//Extraction du plus court chemin
	i=0;
	chemin=ajout_tete(chemin, out, 0);	//ajout de la station d'arrivée
	k=out;
	while (pere[k] != in && i<100){// remplit chemin avec les indices des noeuds du chemin calculé (ceux dont le poids est le plus faible) grâce à la liste père
		chemin=ajout_tete(chemin, pere[k], 0);
		k=pere[k];
		i++;
	}
	chemin=ajout_tete(chemin, in, 0);	//ajout de la station de départ

	return chemin;
}

Liste optimisation(Graphe graph, int nbsom, Sommet* tab_sommets, int in, int out){
	int i,j, k,n=0;
	
	//Initialisation
	Sommet u;
	File file = creer_file();
	Liste maillon, chemin =creer_liste();
	file = enfiler(file,tab_sommets[in]);
	
	int * pere = calloc (nbsom, sizeof(*pere));
	double* poids = calloc (nbsom, sizeof(*poids));
	
	for (i=0; i<nbsom; i++){ // On initialise le poids de tous les sommets à l'infini
		poids[i]=INF;
	}
	poids[in]=0;	// Sauf pour le sommet de départ
	
	if (in==out){	//si la station de départ est la même que celle d'arrivée, on ne fait rien
		chemin=ajout_tete(chemin, in, 0);
		return chemin;
	} 
	


	//Algorithme principal
	while(!file_vide(file) && n<1000){ 	//Tant que la file n'est pas vide
		n++;
		u=defiler(&file);	//On regarde le dernier sommet enfilé
		i=u.num;
		maillon = graph[i];
		while(maillon != NULL){		//On teste tous les arcs partant de ce sommet i (vers les sommets j)
			j=maillon->num;	
			int present=0;
			if (poids[i] + maillon->cout < poids[j]){
				poids[j]= poids[i] + maillon->cout; 	//modifie le poids du sommet si le cout est plus faible
				pere[j] = i;							//et stocke le père avec le cout le plus faible 
				
				
				File tmp=file; 	//On parcourt la file pour vérifier si le sommet y est déjà ou pas
				
				File tete= file->suiv;
				
				while((tete!=NULL)&&(tmp!=tete)){
					if(maillon->num==tmp->som.num){
						present=1;
					}
					tmp=tmp->suiv;
				}
				if (!present){		//S'il n'est pas présent, on l'ajoute à la file
					file=enfiler(file,tab_sommets[j]);
				}
			}
			maillon=maillon->suiv;
		}	
	}
	/*if (circuit_neg(graph, nbsom, poids))
	{
		printf ("Il y a un circuit négatif dans le graphe, solution impossible");
		exit(1);
	}*/
	
	//Extraction du plus court chemin
	i=0;
	chemin=ajout_tete(chemin, out, 0);	//ajout de la station d'arrivée
	k=out;
	while (pere[k] != in && i<100){// remplir chemin avec les indices des noeuds du chemin calculé (ceux dont le poids est le plus faible) grâce à la liste père
		chemin=ajout_tete(chemin, pere[k], 0);	
		k=pere[k];
		i++;
	}
	chemin=ajout_tete(chemin, in, 0);	//ajout de la station de départ
	
	return chemin;
}
