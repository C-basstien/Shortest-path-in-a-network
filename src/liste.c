#include "liste.h"

Liste creer_liste(void){return NULL;}

int est_vide(Liste l){return !l;}

void visualiser_liste(Liste l)
{
	Liste buff=l;
	int i=0;
	for(i=0;buff!=NULL;i++)
	{
		printf("n°%d:%lf->",buff->num,buff->cout);
		buff=buff->suiv;
	}
	printf("/");
}

void visualiser_chemin(Liste l,Sommet* S)
{
	Liste buff=l;
	int i=0;char c[4];
	puts("\n");
	printf("Affichez le chemin complet ?Oui:o,Non:n\n");fgets(c,4,stdin);
	puts("\n");
	if (c[0]=='o')
	{

		printf("Partir de la station:");
		for(i=0;buff!=NULL;i++)
		{
			printf("%s (ligne:%s)\n puis \n",S[buff->num].nom,S[buff->num].ligne);
			buff=buff->suiv;
		}
		printf("vous êtes arrivé!!");
	}
	else
	{
		printf("Partir de la station :%s prendre la ligne: %s \n",S[buff->num].nom,S[buff->num].ligne);
		buff=buff->suiv;
		while(buff!=NULL)
		{
			if (buff->suiv!=NULL)
			{
				if(strcasecmp(S[buff->suiv->num].ligne,S[buff->num].ligne))
				{
					if(!strcasecmp(S[buff->suiv->num].nom,S[buff->num].nom)){printf("Puis descendre à la station :%s prendre la ligne :%s \n",S[buff->num].nom,S[buff->suiv->num].ligne);}
					else {printf("Puis descendre à la station :%s aller jusqu'à la station %s puis prendre la ligne :%s \n",S[buff->num].nom,S[buff->suiv->num].nom,S[buff->suiv->num].ligne);}
				}
			}
			else {printf("Puis descendre à la station :%s vous êtes arrivé \n",S[buff->num].nom,S[buff->num].ligne);}
			buff=buff->suiv;
		}
	}
}

Liste ajout_tete(Liste l ,int num ,double cout)
{

    Liste buff=calloc(1, sizeof(*buff));
    buff->num =num;
    buff->cout =cout;
	buff->suiv=l;
    return buff;
}

Liste supprimer_tete(Liste l)
{
    if(est_vide(l)) {return NULL;}
    else
		{
        	Liste buff=l->suiv;
        	free(l);
        	return buff;
		}
}
void supprimer_liste(Liste l)
{
    while(!est_vide(l)){l=supprimer_tete(l);}
}

Liste ajout_queue(Liste l ,int num ,double cout)
{
	Liste nl= calloc(1, sizeof(*nl));
	nl->suiv=NULL;
	nl->num=num;
	nl->cout=cout;
	if(est_vide(l)){return nl;}
	else
	{
		Liste buff=l;
		for(buff=l;buff->suiv!=NULL;buff=buff->suiv){}
		buff->suiv=nl;
		return l;
	}
}
