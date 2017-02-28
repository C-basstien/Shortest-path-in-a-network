#include "visuel.h"

int gestion_ecran (Sommet* S,Graphe G ,int nbre_sommet,Liste chemin,int* type_de_rch,int* dep ,int* ariv)
{
    //Init de l'affichage
    SDL_Surface* f=newfenetregraphique(X_LEN,Y_LEN);
    if ( f== NULL){printf("Impossible d'ouvrir la fenetre d'affichage");exit(1);}

    TTF_Init();TTF_Font *police = TTF_OpenFont("resource/police2.ttf",10);//Init de l'affichage des polices
    if(police==NULL){printf("Impossible d'ouvrir la police");exit(1);}
    double moy_xy[2];moyenne(S,nbre_sommet,moy_xy);
    int ctre_xy[2];ctre_xy[0]=X_LEN/2;ctre_xy[1]=Y_LEN/2;
    int c_xy[2];c_xy[0]=ctre_xy[0];c_xy[1]=ctre_xy[1];
    int cmen_xy[2];cmen_xy[0]=ctre_xy[0];cmen_xy[1]=ctre_xy[1];
    double zoom_xy[2];zoom_xy[0]=X_LEN/2;zoom_xy[1]=7*Y_LEN/8;
    int nbre_select=1;
    int t=0;//variable indicatrice si on affiche le nom des stations ou pas dans la fonction affichage_plan,par défaut on affiche pas le nom des stations
    int v=0;//variable indicatrice si on affiche totalement le plan ou seulement le chemin utile dans la fonction affichage_plan,par défaut on affiche tout le plan
    int r=1;//variable indicatrice si l'utilsateur souhaite relancer une nouvelle fenetre ou fermer le programe
    affichage_plan(f,police,S,G ,nbre_sommet,moy_xy,ctre_xy,zoom_xy,t,v,chemin);
    int continuer=1;
    SDL_Event event;
    while (continuer)//tant que l'utilisateur ne ferme pas la fenetre
    {
        SDL_WaitEvent(&event);//attente d'un nouvel evenement
        switch(event.type)
        {
        case SDL_QUIT:r=0;continuer = 0;break;//Appui sur la "croix", on arrête le programme
        case SDL_KEYDOWN:switch (event.key.keysym.sym)
        {
            case SDLK_UP :
            {
                zoom_xy[0]*=2;zoom_xy[1]*=2;
                affichage_plan(f,police,S,G ,nbre_sommet,moy_xy,ctre_xy,zoom_xy,t,v,chemin);
            }
            break;
            case SDLK_DOWN :
            {
                zoom_xy[0]/=2;zoom_xy[1]/=2;
                affichage_plan(f,police,S,G ,nbre_sommet,moy_xy,ctre_xy,zoom_xy,t,v,chemin);
            }
            break;
            case SDLK_t:
            {
                if (t==0){t=1;}else{t=0;}//si l'affichage du texte n'est pas activé on active sinon on désactive
                affichage_plan(f,police,S,G ,nbre_sommet,moy_xy,ctre_xy,zoom_xy,t,v,chemin);
            }
            break;
            case SDLK_v:
            {
                if (v==0){v=1;}else{v=0;}//si l'affichage du plan n'est pas activé on active sinon on affiche le seulment le chemin
                affichage_plan(f,police,S,G ,nbre_sommet,moy_xy,ctre_xy,zoom_xy,t,v,chemin);
            }
            break;
            case SDLK_r:continuer = 0;break;//l'utilisateur demande un reset du chemin
            case SDLK_ESCAPE:r=0;*type_de_rch=1;continuer = 0;break; //Appui sur la touche Echap, on arrête le programme
         }break;
        case SDL_MOUSEBUTTONDOWN:switch (event.button.button)
        {
            case SDL_BUTTON_RIGHT ://Clic droit réstauration de l'affichage d'origine
            {
                ctre_xy[0]=X_LEN/2;ctre_xy[1]=Y_LEN/2;zoom_xy[0]=X_LEN/2; zoom_xy[1]=7*Y_LEN/8;//restauration de zoom et du ctre
                c_xy[0]=ctre_xy[0];c_xy[1]=ctre_xy[1];
                affichage_plan(f,police,S,G ,nbre_sommet,moy_xy,ctre_xy,zoom_xy,t,v,chemin);
            }
            break;

        case SDL_BUTTON_LEFT ://clic gauche :tant que le bouton est enfoncée on modifie les nouvelles coordonées
        {
            int tp=t;
            cmen_xy[0]=event.motion.x;cmen_xy[1]=event.motion.y;
            while((event.type!=SDL_MOUSEBUTTONUP)&&(event.button.button==SDL_BUTTON_LEFT))
            {
                SDL_PollEvent(&event);//attente d'un nouvel evenement
                if(event.type==SDL_MOUSEMOTION)//si la souris bouge
                {
                    ctre_xy[0]=c_xy[0]+event.motion.x-cmen_xy[0];ctre_xy[1]=c_xy[1]+event.motion.y-cmen_xy[1];//on récupère les coords x y de la souris dans la fenetre
                    if (tp==1){t=0;}
                    affichage_plan(f,police,S,G ,nbre_sommet,moy_xy,ctre_xy,zoom_xy,t,v,chemin);
                }
            }
            if (tp==1){t=1;}
            affichage_plan(f,police,S,G ,nbre_sommet,moy_xy,ctre_xy,zoom_xy,t,v,chemin);
            c_xy[0]=ctre_xy[0];c_xy[1]=ctre_xy[1];
            SDL_WaitEvent(&event);
            if((event.type=SDL_MOUSEBUTTONDOWN)&&(event.button.button==SDL_BUTTON_LEFT))
            {
                SDL_WaitEvent(&event);
                if((event.type=SDL_MOUSEBUTTONUP)&&(event.button.button==SDL_BUTTON_LEFT))
                {
                    SDL_PollEvent(&event);
                    if((event.type=SDL_MOUSEBUTTONDOWN)&&(event.button.button==SDL_BUTTON_LEFT))
                    {
                    int s=rch_fntre(event.motion.x,event.motion.y,S,nbre_sommet,moy_xy,ctre_xy,zoom_xy);
                    if(nbre_select<2){*dep=s;nbre_select++;}else{*ariv=s;*type_de_rch=0;continuer = 0;}
                    }
                }
            }

        }break;
        }break;
        }
    }
    TTF_CloseFont(police);
	TTF_Quit();
	SDL_FreeSurface(f);
	SDL_Quit();
	return r;
}
void affichage_plan(SDL_Surface* f ,TTF_Font *police,Sommet* S,Graphe G ,int nbre_sommet,double moy_xy[],int ctre_xy[],double zoom_xy[],int t,int v ,Liste chemin)
{
    Liste buff;
    SDL_FillRect(f, NULL, SDL_MapRGB(f->format, 255,255,255));//réinit d'une surface blanche
    SDL_Surface* texte;
    SDL_Rect position;
    SDL_Color couleurNoire = {0, 0, 0};
    //copie de notre liste pour ne pas "supprimer"(faire pointer sur null la "veritable" liste lorsque on doit parcourir les élements de   S[i]
    //double mx,my;mx=2.344345;my=48.837511;//moyennne de toutes les coordonées en X et Y pour obtenir quelque chose de centré
    double xaff1 ,xaff2 ,yaff1,yaff2;//coordonnées à afficher
    int i;
    for(i=0; i<nbre_sommet; i++) //On parcours notre graphe on affiche ligne pour chaque arcs
    {
        if (v==0)
        {
            buff=G[i];
            xaff1=(ctre_xy[0]+zoom_xy[0]*(-moy_xy[0]+S[i].coordX));
            yaff1=(ctre_xy[1]+zoom_xy[1]*(moy_xy[1]-S[i].coordY));//mise à jour des coords de départs
        }
        else{buff=chemin;}

        while(buff!=NULL)//parcours de notre liste
        {
            xaff2=(ctre_xy[0]+zoom_xy[0]*(-moy_xy[0]+S[buff->num].coordX));
            yaff2=(ctre_xy[1]+zoom_xy[1]*(moy_xy[1]-S[buff->num].coordY));//mise à jour des coords d'arrivées
            if ((v==1)&&(buff->suiv!=NULL))//mise à jour dans le cas de l'affichage du chemin seulement
            {
                xaff1=(ctre_xy[0]+zoom_xy[0]*(-moy_xy[0]+S[buff->suiv->num].coordX));
                yaff1=(ctre_xy[1]+zoom_xy[1]*(moy_xy[1]-S[buff->suiv->num].coordY));//mise à jour des coords de départs
            }
            if ((test_coord(xaff1,yaff1))&&(test_coord(xaff2,yaff2)))// affiche l'arc si les coordonées sont bien dans la fenètre d'affichage
            {
                if (v==0){Draw_Line(f,xaff1,yaff1,xaff2,yaff2,color(S[i],S[buff->num]));}
                else if(buff->suiv!=NULL){Draw_Line(f,xaff1,yaff1,xaff2,yaff2,color(S[buff->suiv->num],S[buff->num]));}
            }
            buff=buff->suiv;//passage au prochain arc
        }
        if (v==1){i=nbre_sommet;}    //permet de sortir  le de la boucle dans le cas d'un affichage du chemin de parcours
    }
    if (v==0)//affichage du plan total
    {
        for(i=0; i<nbre_sommet; i++) //on affiche les points correspondant au sommet après pour un meilleure affichage (cela évite la superposition des arcs par dessus nos points de sommets
        {

            xaff1=ctre_xy[0]+zoom_xy[0]*(-moy_xy[0]+S[i].coordX);//mise à jour des coords du point à afficher
            yaff1=ctre_xy[1]+zoom_xy[1]*(moy_xy[1]-S[i].coordY);
            if(test_coord(xaff1,yaff1))// affiche le sommet si les coordonées sont bien dans la fenètre d'affichage
            {
                Draw_FillCircle(f,xaff1,yaff1,2.5,0x000000);
                if (t)//dans le cas ou l'on souhaite afficher le nom de station sur le graphe
                {
                    texte = TTF_RenderText_Blended(police,S[i].nom, couleurNoire);//transformation de la chaine de caractère en surface
                    position.x=xaff1;position.y=yaff1;//coord ou l'on place notre texte
                    SDL_BlitSurface(texte, NULL,f, &position);// Blit du texte=transfere notre surface dans notre fenetre à la position indiqué
                }
            }

        }
    }
    else//dans le cas ou seul l'affichage de notre chemin nous intéresse
    {
        buff=chemin;
        while(buff!=NULL)
        {
            xaff1=ctre_xy[0]+zoom_xy[0]*(-moy_xy[0]+S[buff->num].coordX);//mise à jour des coords du point à afficher
            yaff1=ctre_xy[1]+zoom_xy[1]*(moy_xy[1]-S[buff->num].coordY);
            if(test_coord(xaff1,yaff1))// affiche le sommet si les coordonées sont bien dans la fenètre d'affichage
            {
                Draw_FillCircle(f,xaff1,yaff1,2.5,0x000000);//dessine notre point en rayon 2,5 pixel couleur au coord xaff,yaff
                if (t)//dans le cas ou l'on souhaite afficher le nom de station sur le graphe
                {
                    texte = TTF_RenderText_Blended(police,S[buff->num].nom, couleurNoire);//transformation de la chaine de caractère en surface
                    position.x=xaff1;position.y=yaff1;//coord ou l'on place notre texte
                    SDL_BlitSurface(texte, NULL,f, &position); // Blit du texte=transfere notre surface dans notre fenetre à la position indiqué
                }
            }
            buff=buff->suiv;
        }


    }
    //affichage d'un menu
    texte = TTF_RenderText_Blended(police,"t pour activer/desactiver l'affichage des nom ", couleurNoire);
    position.x=1100;position.y=600;
    SDL_BlitSurface(texte, NULL,f, &position);
    texte = TTF_RenderText_Blended(police,"v pour visualiser le chemin utile ou tout le plan ", couleurNoire);
    position.x=1100;position.y=620;
    SDL_BlitSurface(texte, NULL,f, &position);
    texte = TTF_RenderText_Blended(police,"fleche haut/bas pour zoomer/dezoomer", couleurNoire);
    position.x=1100;position.y=640;
    SDL_BlitSurface(texte, NULL,f, &position);
    texte = TTF_RenderText_Blended(police,"clic gauche pour se deplacer dans le plan", couleurNoire);
    position.x=1100;position.y=660;
    SDL_BlitSurface(texte, NULL,f, &position);
    texte = TTF_RenderText_Blended(police,"clic droit pour re initialiser l'affichage", couleurNoire);
    position.x=1100;position.y=680;
    SDL_BlitSurface(texte, NULL,f, &position);
    texte = TTF_RenderText_Blended(police,"escp ou croix pour quiter", couleurNoire);
    position.x=1100;position.y=700;
    SDL_BlitSurface(texte, NULL,f, &position);
    texte = TTF_RenderText_Blended(police,"r pour un nouveau calcul de chemin", couleurNoire);
    position.x=1100;position.y=720;
    SDL_BlitSurface(texte, NULL,f, &position);
    texte = TTF_RenderText_Blended(police,"double clic sur les nouvelles stations de départ,", couleurNoire);
    position.x=1100;position.y=740;
    SDL_BlitSurface(texte, NULL,f, &position);
    texte = TTF_RenderText_Blended(police,"et arrivée pour lancer une nouvelle recherche", couleurNoire);
    SDL_Flip(f);//affichage
}
int test_coord(double x ,double y)//test si les coordonées sont bien dans la fenetre
{
    if (((x>19)&&(x<X_LEN-19))&&((y>19)&&(y<Y_LEN-19))){return 1;}
    else{return 0;}
}
void moyenne(Sommet* S,int nbre_sommet,double *m)
{
    int i;for(i=0;i<nbre_sommet;i++){m[0]+=S[i].coordX;m[1]+=S[i].coordY;}m[0]/=nbre_sommet;m[1]/=nbre_sommet;
}
int color(Sommet S1,Sommet S2)//retourne le code hexa d'une couleur noir si les 2 sommets ne sont pas sur la meme ligne et une autre couleur correspondant à la ligne
{
    if (strcasecmp(S1.ligne,S2.ligne)){return 0x000000;}
    if (!strcasecmp(S1.ligne,S2.ligne))
    {
        if(S1.ligne[0]=='M')
        {
            if(!strcasecmp(S1.ligne,"M1")){return 0xC03000;}
            if(!strcasecmp(S1.ligne,"M2")){return 0x01B0F0;}
            if(!strcasecmp(S1.ligne,"M3")){return 0xFF358B;}
            if(!strcasecmp(S1.ligne,"M3bis")){return 0x4A1A2C;}
            if(!strcasecmp(S1.ligne,"M4")){return 0x32331D;}
            if(!strcasecmp(S1.ligne,"M5")){return 0x332DE5;}
            if(!strcasecmp(S1.ligne,"M6")){return 0xD0C204;}
            if(!strcasecmp(S1.ligne,"M7")){return 0xFE01B2;}
            if(!strcasecmp(S1.ligne,"M7bis")){return 0x01F6FE;}
            if(!strcasecmp(S1.ligne,"M8")){return 0x55FE01;}
            if(!strcasecmp(S1.ligne,"M9")){return 0xD55205;}
            if(!strcasecmp(S1.ligne,"M10")){return 0xCB30C1;}
            if(!strcasecmp(S1.ligne,"M11")){return 0x56A9CD;}
            if(!strcasecmp(S1.ligne,"M12")){return 0x00721E;}
            if(!strcasecmp(S1.ligne,"M13")){return 0x002989;}
            if(!strcasecmp(S1.ligne,"M14")){return 0x8880CD;}
        }
        if(!strcasecmp(S1.ligne,"funi")){return 0x000000;}
        if(S1.ligne[0]=='A')
        {
            if(!strcasecmp(S1.ligne,"A")){return 0xFE01BB;}
            if(!strcasecmp(S1.ligne,"A1")){return 0xFE01AB;}
            if(!strcasecmp(S1.ligne,"A2")){return 0xFE01BA;}
            if(!strcasecmp(S1.ligne,"A3")){return 0xF851BB;}
            if(!strcasecmp(S1.ligne,"A4")){return 0xFE015B;}
            if(!strcasecmp(S1.ligne,"A5")){return 0xF2015B;}
        }
        if(S1.ligne[0]=='B')
        {
            if(!strcasecmp(S1.ligne,"B"))
            {
                return 0x01FE23;
            }
            if(!strcasecmp(S1.ligne,"B2")){return 0x01EE23;}
            if(!strcasecmp(S1.ligne,"B3")){return 0x01FE64;}
            if(!strcasecmp(S1.ligne,"B4")){return 0x01FE03;}
            if(!strcasecmp(S1.ligne,"B5")){return 0x014E23;}
        }
        if(S1.ligne[0]=='C')
        {
            if(!strcasecmp(S1.ligne,"C")){return 0x01C3FE;}
            if(!strcasecmp(S1.ligne,"C1")){return 0x01A3FE;}
            if(!strcasecmp(S1.ligne,"C2")){return 0x01C35E;}
            if(!strcasecmp(S1.ligne,"C2")){return 0x01C37E;}
            if(!strcasecmp(S1.ligne,"C4")){return 0x01C3F4;}
            if(!strcasecmp(S1.ligne,"C5")){return 0x09C3FE;}
            if(!strcasecmp(S1.ligne,"C6")){return 0x01C52E;}
            if(!strcasecmp(S1.ligne,"C7")){return 0x01C4EE;}
            if(!strcasecmp(S1.ligne,"C8")){return 0x03C3FE;}
        }
        if(S1.ligne[0]=='D')
        {
            if(!strcasecmp(S1.ligne,"D")){return 0x6F01FE;}
            if(!strcasecmp(S1.ligne,"D2")){return 0x6F51FE;}
            if(!strcasecmp(S1.ligne,"D4")){return 0x6F91FE;}
            if(!strcasecmp(S1.ligne,"D6")){return 0x6F01FA;}
        }
        if(S1.ligne[0]=='E')
        {
            if(!strcasecmp(S1.ligne,"E")){return 0xFE4D01;}
            if(!strcasecmp(S1.ligne,"E2")){return 0xFE4D41;}
            if(!strcasecmp(S1.ligne,"E4")){return 0xF54D01;}
        }
        if(!strcasecmp(S1.ligne,"Val")){return 0xFEAA01;}
        if(S1.ligne[0]=='T')
        {
            if(!strcasecmp(S1.ligne,"T1")){return 0xB2FE01;}
            if(!strcasecmp(S1.ligne,"T2")){return 0xABE2BA;}
            if(!strcasecmp(S1.ligne,"T3")){return 0xD9ABE2;}
        }
        else {return 0x000000;}
    }

}
int rch_fntre(double x ,double y,Sommet* S,int nbre_sommet,double moy_xy[],int ctre_xy[],double zoom_xy[])//test si les coordonées sont bien dans la fenetre
{
    int i=0;double xaff;double yaff;
    for(i=0;i<nbre_sommet;i++)
    {
    xaff=ctre_xy[0]+zoom_xy[0]*(-moy_xy[0]+S[i].coordX);
    yaff=ctre_xy[1]+zoom_xy[1]*(moy_xy[1]-S[i].coordY);
    //printf("\n%d %s", S[i].num,S[i].nom);
    if ((xaff<x+4)&&(xaff>x-4)&&(yaff<y+4)&&(yaff>y-4)){/*printf("\n%d %s", S[i].num,S[i].nom);*/return S[i].num;}
    }
}
