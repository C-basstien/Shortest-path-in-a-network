#include "lecture.h"

void affiche_sommets(Sommet *S,int n)//Affiche les données contenu dans le tableau de n strucures Sommet,utile pour faire des tests seulement
{
	int i;//L'indice du sommmet i
	puts("\nSommets:");
	for(i=0;i<n;i++)
	{
		printf("\n%d %lf %lf %s %s", S[i].num,S[i].coordX,S[i].coordY,S[i].ligne,S[i].nom);
	}
	puts("\n");
}

void affiche_arcs(Arc *A,int n)//Affiche les données contenu dans le tableau de n strucure Arc,utile pour faire des tests seulement
{
	int i;
	puts("\nArc:");
	for(i=0;i<n;i++)
	{
		printf("\n%d %d %lf",A[i].depa,A[i].ariv,A[i].cout);
	}
	puts("\n");
}

void affiche_graphe(Graphe G,int n)//Affiche le Graphe:c'est un tableaux de liste ,utile pour faire des tests seulement
{
	int i;
	puts("\nGraphe");
	for(i=0;i<n;i++)
	{
		printf("sommet n°%d ->",i);
		visualiser_liste(G[i]);
		puts("\n");
	}
}

Graphe creer_graphe(Arc *A,int nbre_arcs,int nbre_sommets)//creer un graphe à partir de notre tableau d'arc A et du nombre de sommet n:le resultat est un tableau de n listes
{
	int i,k;k=0;i=0;
	Graphe G=calloc(nbre_sommets, sizeof(Liste));
	for(i=0;i<nbre_sommets;i++)//on parcours nos n indice i en les comparants à chaque sommets de départ d'arc
	{
		while((k<nbre_arcs)&&(A[k].depa==i))//tant que l'arc d'indice k à son indice de sommet de depart egale à i ,la premiere conditions préviens des dépassements mémoire
		{
			G[i]=ajout_queue(G[i],A[k].ariv,A[k].cout);//on ajout en queue les nouvelles donées
			k++;//k est l'indice parcourant le tableau de structure Arc
		}
	}
	return G;
}

void simplifie_chaine(char* m,char* mot)//fonction qui prends 2 paramètre source (mot) et destination  (m),mais est utilisé avec m=mot (source=destination),on pourrait la réecrire en prenant qu'un paramètre char* m ,mais c'est plus simple de faire comme ca pour l'instant
{
//Les fichier csv séparent leurs données avec des tabulations(début) et retour chariot(fin) pour éviter  que cela se retrouve dans le nom des sommets on doit supprimer ces caractères puis décaler la chaine de carartère,si le mot est deja simplifié alors il reste inchangé
	int i;int t=1;

	if(mot[0]=='	'){for (i=0;mot[i+1]!=0;i++){m[i]=mot[i+1];t=2;}}
	if (mot[strlen(mot)-1]=='\n'){m[strlen(mot)-t]=0;}
}

void lire(Sommet** adr_tab_sommets,Arc** adr_tab_arcs,int* adr_nbre_sommets,int* adr_nbre_arcs,Graphe* adr_graphe,Ldico** adr_dico)//fonction qui lit le fichier .csv et retourne les données utiles dans l'adresse de nos paramètres
{
	FILE* fichier = NULL;char num_fichier[3];
	printf("\nEntrer le numéro du fichier que vous voulez ouvrir:\nmetro.csv:0\ngraphe1.csv:1\ngraphe3.csv:2\n");
	fgets(num_fichier,3,stdin);simplifie_chaine(num_fichier,num_fichier);
	if (num_fichier[0]=='1'){fichier = fopen("resource/graphe1.csv", "r");}
	else if (num_fichier[0]=='2'){fichier = fopen("resource/graphe3.csv", "r");}
	else {fichier = fopen("resource/metro.csv", "r");}
	if (fichier==NULL){puts("erreur d'ouverture du fichier"); exit(1);}

	fscanf(fichier,"%d	%d", (adr_nbre_sommets), (adr_nbre_arcs));
	*adr_tab_sommets=calloc(*adr_nbre_sommets, sizeof(Sommet));
	*adr_tab_arcs=calloc(*adr_nbre_arcs, sizeof(Arc));

	int i;
	char buff[511]; fgets(buff,511,fichier);fgets(buff,511,fichier);//creation d'un buffer et affectation du résultat de la lecture des lignes inutiles du fichier,permet de placer le pointeur de lecture du fichier au endroits pertinents
	for(i=0;i<*(adr_nbre_sommets);i++)
	{
		fscanf(fichier,"%d	%lf	%lf	%s", &((*adr_tab_sommets)[i].num), &((*adr_tab_sommets)[i].coordX), &((*adr_tab_sommets)[i].coordY),((*adr_tab_sommets)[i].ligne));
		fgets(((*adr_tab_sommets)[i].nom),511,fichier);simplifie_chaine((*adr_tab_sommets)[i].nom,(*adr_tab_sommets)[i].nom);
	}
	fgets(buff,511,fichier);
	for(i=0;i<*(adr_nbre_arcs);i++){fscanf(fichier,"%d	%d	%lf", &((*adr_tab_arcs)[i].depa), &((*adr_tab_arcs)[i].ariv), &((*adr_tab_arcs)[i].cout));}
	fclose(fichier);
	*adr_graphe=creer_graphe(*adr_tab_arcs,*adr_nbre_arcs,*adr_nbre_sommets);
	*adr_dico= creer_dico(*adr_tab_sommets,*adr_nbre_sommets);
}
