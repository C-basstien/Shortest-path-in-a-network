#include "file.h"

File creer_file(void){return NULL;}

int file_vide(File f){return !f;}

File enfiler(File f, Sommet s){
	Cellule* new =calloc(1, sizeof(*new));
	if (file_vide(f)){
		new->som=s;
		new->suiv= new;
		return new;
	}
	new->som=s;
	new->suiv= f->suiv;
	f->suiv=new;
	return new;
}

Sommet defiler(File* pf){
	if(file_vide(*pf)){
		return;
	}
	Cellule* sup=(*pf)->suiv;
	(*pf)->suiv=sup->suiv;
	Sommet tmp = sup->som;
	//free(sup);/*A revoir le bug vient de la :le free est pas essentielle pour que ca marche,mais c'est mieux de le mettre pour éviter les fuites de mémoires
	return tmp;
}

void affiche_file(File f){
	if (file_vide(f)) return;
	Cellule* tete = f->suiv;
	Cellule* p = tete;
	while (p->suiv != tete){
		printf("%d \n", p->som.num);
		printf("\n");
		p=p->suiv;
	}
	printf("%d \n", p->som.num);
}

