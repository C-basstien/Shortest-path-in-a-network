#include "dico.h"

unsigned int hachage(unsigned char* mot, int dim_tab_hach)//dans notre cas dim_tab_hach=nbre_sommets pour faire simple
{
	const int a=31;
    unsigned int h = 0;
    int i=0;
    while((mot[i]!='\0')&& (mot[i]!='\n')) {i++;}//compte le nombre de caractère du mot
    while(i>=0)
	{
        h=h*a+mot[i];
        i--;
    }
    h=h%dim_tab_hach;//modulo comme ca tout les h sont compris entre 0 et dim_tab_hach-1
    return h;
}
Ldico* creer_dico(Sommet *S,int nbre_sommets)
{
    int i;
    char* nom;
    unsigned int h;
    Ldico* dico= calloc(nbre_sommets, sizeof(Ldico));
    for (i=0; i<nbre_sommets; i++)
	{
        h= hachage(S[i].nom,nbre_sommets);
        dico[h]=ajout_tete_dico(dico[h],S[i].nom,i);
	}
    return dico;
}

Ldico ajout_tete_dico(Ldico l,char* nom ,int num)
{

    Ldico buff=calloc(1, sizeof(*buff));
   	buff->nom=strdup(nom);
    buff->num =num;
	buff->suiv=l;
    return buff;
}
void visualiser_liste_dico(Ldico l)
{
	Ldico buff;
	for(buff=l;buff!=NULL;buff=buff->suiv)
	{
		printf("sommet n°%d:%s\n",buff->num,buff->nom);
	}
	printf("/");
}
void affiche_dico(Ldico* l,int dim_tab_hach)
{
	int i;puts("\nDico:");
	for(i=0;i<dim_tab_hach;i++){printf("//ligne dico n°%d// \n",i);visualiser_liste_dico(l[i]);puts("");}
}

int test_char(char s , char c)//pour éliminer la prise en compte des majuscules
{
	if (s==c){return 1;}
	if((s>='a') && (s<='z') && (s-32==c)){return 1;}
	if((s>='A') && (s<='Z') && (s+32==c)){return 1;}
	if(((s=='-') && (c==' '))||((s==' ') && (c=='-'))) {return 1;}
	else {return 0;}
}

void affiche_suggestion(Sommet* S,char* mot,int nbre_sommet)//permet d'afficher l'orthographe le "+ probable" de la station demandé
{
	int j,r,i;
	int* k=calloc(nbre_sommet,sizeof(int));
	for(j=0;j<nbre_sommet;j++){for(i=0;i<strlen(mot);i++){if (test_char(mot[i],S[j].nom[i])){k[j]=k[j]+1;}}}
	//on compte le nombre de caractère en commun entre le mot saisie  et pour chaque nom de Sommet
	r=0;i=0;
	for (j=0;j<nbre_sommet;j++){if(k[j]>r){i=j;r=k[j];}}//dans l'idéal il faudrait afficher plusieurs suggestions dans le cas ou on à k[j]==r mais c'est chiant à faire et pas très utile...
	printf("\nSuggestion:%s\n",S[i].nom);
}
Ldico recherche(Sommet* S,Ldico* l,int dim_tab_hach)
{
	do//principe: on creer une boucle qui demande de saisir le nom de la station
	{
	char nom[SLEN];
	fgets(nom,SLEN,stdin);simplifie_chaine(nom,nom);//on simplifie les caratères inutiles tab ou retour chariot
	unsigned int h=hachage(nom,dim_tab_hach);//on appelle la fonction de hachage qui nous retourne h
	Ldico buff=l[h];Ldico sommets=NULL;//on creer une liste copie qui vas parcourir la liste à l'indice h de notre tableau de liste
		if (buff==NULL){puts("\nCette station n'existe pas , vérifiez l'orthographe");affiche_suggestion(S,nom,dim_tab_hach);}
		//cela veut dire que aucune station n'à cette indice h comme résultat de la fonction de hash
		else
		{
			for(buff=l[h];buff!=NULL;buff=buff->suiv)//on parcours la liste
			{
				if (!strcasecmp(buff->nom,nom)){sommets=ajout_tete_dico(sommets,buff->nom,buff->num);}
				//on compare notre chaine de caractère à celle des noms de stations compris dans notre tableau de liste à l'indice h
				//si c'est le cas on ajoute le nom et numéro du sommets correspondant
			}
			if (sommets==NULL){puts("\nCette station n'existe pas ,vérifiez l'orthographe");affiche_suggestion(S,nom,dim_tab_hach);}
			else {return sommets;}
			//tout c'est bien déroulé on retourne donc la liste ldico de sommets possédants le même nom de station on quite la fonction et donc pas de problème de bouche infini do while
		}
	}
	while(1);
}

