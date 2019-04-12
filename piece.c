#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "piece.h"



//=NB JOUEURS,JOUEUR TOTAUX=====//
int J= 4 ; //nb de joueur total
int J_HUMAIN= 1 ;//nb de joueur humain parmis les joueurs totales
//==============================//

//==UNITEES=====================//
int NB_CLASSE= 6 ; //nb de classe actuelement dans le jeu !!!!!A ne pas modifier!!!!!!
int NB_UNITE= 7 ; //nb unité pour chaque joueurs au debut de la partie
int ESPACE_GEN= 2; //espace (nb de case de chaque coté au minimum) entre deux équipes d'unitée
int NB_MAX_PRIEST=2;
//==============================//

//===========VITESSE DU JEU=====//
int PTS_ACTION_MAX= 5 ; //pts d'action max pour chaque tours de chaque joueur
int VITESSE_JEU_BOT= 1 ; //nb de boucle d'affichage entre chaque action d'un bot (vitesse max=1)
int VITESSE_ANIM=15;
//==============================//

//========AFFICHAGE/GRILLE======//
int AFF_DEG= 10 ; //nombre d'affichage max a la fois par boucle d'affichage d'info texte de dégats, morts et soins
int TAILLE_TAB_BASH=1000; //taille max de ligne de bash sauvegardé
int BASH_SCROLL_SPEED=2;
int DURE_JOUR_NUIT=4000;
int PRESET=1 ; //1 pour generation alea, autre pour preset de carte via fichier
int PRESET_U=1; //1 pour gene aleatoire et autre pour preset d'unité

int N= 10 ; //taille de la grille (ne peux pas eccéder 200x200 actuelement (mettre en place des fichier ou enregistrer et reouvrir pour chargement dynamique de la map et grandeur infini))
int M= 10 ;
//==============================//



piece_t * init_piece(classe_t classe,int id_joueur){
    int pos=((rand()%(4)) + 1);
    piece_t * piece=malloc(sizeof(piece_t));
    int frame=((rand()%2)+1);
    int frame2=((rand()%10)+1);
    int start_anim=((rand()%VITESSE_ANIM));
    switch (classe){
        case knight:
            piece->classe = knight;
            piece->pdv=35;
            piece->puissance = 22;
            piece->armure=40;
            piece->block=80;
            piece->portee=1;
            piece->deplacement=2;
            piece->select=0;
            piece->joueur=id_joueur;
            piece->direction=pos;
            piece->kil=0;
            piece->frame=frame;
            piece->frame_interface=frame;
            piece->start_anim=start_anim;
        break;
        case scout:
            piece->classe = scout;
            piece->pdv=32;
            piece->puissance = 24;
            piece->armure=15;
            piece->block=30;
            piece->portee=5;
            piece->deplacement=4;
            piece->select=0;
            piece->joueur=id_joueur;
            piece->direction=pos;
            piece->kil=0;
            piece->frame=frame;
            piece->frame_interface=frame;
            piece->start_anim=start_anim;
        break;
        case priest:
            piece->classe = priest;
            piece->pdv=34;
            piece->puissance = 14;
            piece->armure=15;
            piece->block=10;
            piece->portee=3;
            piece->deplacement=3;
            piece->select=0;
            piece->joueur=id_joueur;
            piece->direction=pos;
            piece->kil=0;
            piece->frame=frame;
            piece->frame_interface=frame;
            piece->start_anim=start_anim;
        break;
        case magician:
            piece->classe = magician;
            piece->pdv=30;
            piece->puissance = 28;
            piece->armure=10;
            piece->block=40;
            piece->portee=4;
            piece->deplacement=3;
            piece->select=0;
            piece->joueur=id_joueur;
            piece->direction=pos;
            piece->kil=0;
            piece->frame=frame;
            piece->frame_interface=frame;
            piece->start_anim=start_anim;
        break;
        case faucheuse:
            piece->classe = faucheuse;
            piece->pdv=25;
            piece->puissance = 35;
            piece->armure=10;
            piece->block=30;
            piece->portee=2;
            piece->deplacement=5;
            piece->select=0;
            piece->joueur=id_joueur;
            piece->direction=pos;
            piece->kil=0;
            piece->frame=frame;
            piece->frame_interface=frame;
            piece->start_anim=start_anim;
        break;
        case ange:
            piece->classe = ange;
            piece->pdv=40;
            piece->puissance = 22;
            piece->armure=5;
            piece->block=30;
            piece->portee=1;
            piece->deplacement=4;
            piece->select=0;
            piece->joueur=id_joueur;
            piece->direction=pos;
            piece->kil=0;
            piece->frame=frame2;
            piece->frame_interface=frame2;
            piece->start_anim=start_anim;
        break;
        default: printf("Cette classe n'existe pas.\n");
    }
    return (piece);
}

int piece_existe(piece_t * piece){
    return(!(piece==NULL));
}


int destruction_piece(piece_t * piece){
    if(piece_existe(piece)){
        free(piece);
        (piece)=NULL;
        return 1;
    }
    return 0;
}



SDL_Rect afficher_anim(int compteur_anim,classe_t classe,case_t terrain[N][M],int compteur,int compteur2,int inter){
  SDL_Rect img_anim;
  img_anim.h=100;
  img_anim.w=100;
    //anim a 2 images
  if(inter==0){
    if(classe==knight || classe==scout || classe==magician || classe==priest){
      if(compteur_anim%VITESSE_ANIM==terrain[compteur][compteur2].piece->start_anim){
        if(terrain[compteur][compteur2].piece->frame==2){
          terrain[compteur][compteur2].piece->frame=1;
        }else{
          terrain[compteur][compteur2].piece->frame++;
        }
      }
      if(terrain[compteur][compteur2].piece->frame==1){
          img_anim.x=0;
          img_anim.y=0;
      }else if(terrain[compteur][compteur2].piece->frame==2){
          img_anim.x=100;
          img_anim.y=0;
      }
    }
    //ANIM DE L'ANGE
    else if(classe==ange){
      if(compteur_anim%VITESSE_ANIM==terrain[compteur][compteur2].piece->start_anim){
        if(terrain[compteur][compteur2].piece->frame==10){
          terrain[compteur][compteur2].piece->frame=1;
        }else{
          terrain[compteur][compteur2].piece->frame++;
        }
      }
      if(terrain[compteur][compteur2].piece->frame==1 || terrain[compteur][compteur2].piece->frame>9){
          img_anim.x=0;
          img_anim.y=0;
      }else if(terrain[compteur][compteur2].piece->frame%2==0){
          img_anim.x=100;
          img_anim.y=0;
      }else{
          img_anim.x=0;
          img_anim.y=100;
      }
    }
  }else{ //anim de l'interface en haut a gauche
    if(classe==knight || classe==scout || classe==magician || classe==priest){
      if(compteur_anim%VITESSE_ANIM==terrain[compteur][compteur2].piece->start_anim){
        if(terrain[compteur][compteur2].piece->frame_interface==2){
          terrain[compteur][compteur2].piece->frame_interface=1;
        }else{
          terrain[compteur][compteur2].piece->frame_interface++;
        }
      }
      if(terrain[compteur][compteur2].piece->frame_interface==1){
          img_anim.x=0;
          img_anim.y=0;
      }else if(terrain[compteur][compteur2].piece->frame_interface==2){
          img_anim.x=100;
          img_anim.y=0;
      }
    }
    else if(classe==ange){
      if(compteur_anim%VITESSE_ANIM==terrain[compteur][compteur2].piece->start_anim){
        if(terrain[compteur][compteur2].piece->frame_interface==10){
          terrain[compteur][compteur2].piece->frame_interface=1;
        }else{
          terrain[compteur][compteur2].piece->frame_interface++;
        }
      }
      if(terrain[compteur][compteur2].piece->frame_interface==1 || terrain[compteur][compteur2].piece->frame_interface>9){
          img_anim.x=0;
          img_anim.y=0;
      }else if(terrain[compteur][compteur2].piece->frame_interface%2==0){
          img_anim.x=100;
          img_anim.y=0;
      }else{
          img_anim.x=0;
          img_anim.y=100;
      }
    }

  }



  return img_anim;
}



int nombre_classe(case_t terrain[N][M],int joueur_actu,classe_t classe){
  int nb=0;
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(terrain[i][j].piece && terrain[i][j].piece->classe==classe && terrain[i][j].piece->joueur==joueur_actu){
        nb++;
      }
    }
  }
  return nb;
}


void rem_piece_joueur(case_t terrain[N][M],int joueur_actu){
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(terrain[i][j].piece && terrain[i][j].piece->joueur==joueur_actu){
        free(terrain[i][j].piece);
        terrain[i][j].piece=NULL;
      }
    }
  }
  return;
}






int reste_ennemi(case_t terrain[N][M],int joueur_actu){
  int nb=0;
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(terrain[i][j].piece && terrain[i][j].piece->joueur != joueur_actu){
        nb++;
      }
    }
  }
  return nb;
}

int reste_allie(case_t terrain[N][M],int joueur_actu){
  int nb=0;
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(terrain[i][j].piece && terrain[i][j].piece->joueur == joueur_actu){
        nb++;
      }
    }
  }
  return nb;
}





int allie_adjacent(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu){
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(i+1<N && terrain[i+1][j].piece && terrain[i+1][j].piece->joueur==joueur_actu){
        return 1;
      }
      if(j+1<N && terrain[i][j+1].piece && terrain[i][j+1].piece->joueur==joueur_actu){
        return 1;
      }
      if(i-1>=0 && terrain[i-1][j].piece && terrain[i-1][j].piece->joueur==joueur_actu){
        return 1;
      }
      if(j-1>=0 && terrain[i][j-1].piece && terrain[i][j-1].piece->joueur==joueur_actu){
        return 1;
      }
    }
  }
  return 0;

}



void carte_valide(case_t terrain[N][M]){
   int cases[N][M];
   for(int i=0;i<N;i++){
     for(int j=0;j<M;j++){
       if(terrain[i][j].type==5){
         cases[i][j]=-1;
       }else{
         cases[i][j]=0;
       }
     }
   }
   //coin =1
   cases[0][0]=1;
   cases[N-1][M-1]=1;
   cases[0][M-1]=1;
   cases[N-1][0]=1;

   for(int a=0;a<N*M;a++){
    for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
        if (cases[i][j]==1){
          if(i+1<N && cases[i+1][j]==0)
              cases[i+1][j]=1;
          if(i-1>=0 && cases[i-1][j]==0)
             cases[i-1][j]=1;
          if(j+1<M && cases[i][j+1]==0)
             cases[i][j+1]=1;
          if(j-1>=0 && cases[i][j-1]==0)
             cases[i][j-1]=1;
         }
       }
     }
   }
   //verification de la map
   for(int i=0;i<N;i++){
     for(int j=0;j<M;j++){
       if(cases[i][j]==0){
         cases[i][j]=2;
       }
     }
   }
   //correction de la map
   for(int i=0;i<N;i++){
     for(int j=0;j<M;j++){
       if(cases[i][j]==2){
         terrain[i][j].type=5;
       }
     }
   }
   return;
 }



 void initialisation_principale(int bordure,SDL_Window * pWindow,int * largeur, int * hauteur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],case_t terrain[N][M],char variable2[80]){
    int alea;
    SDL_Rect imgDestRect;
    int var1;
    FILE * fp;

    time_t secondes;
    struct tm instant;

    time(&secondes);
    instant=*localtime(&secondes);

    sprintf(variable2,"fichiers/log_%d-%d_%dh%dm%ds.txt", instant.tm_mday, instant.tm_mon+1, instant.tm_hour, instant.tm_min, instant.tm_sec);

  SDL_GetWindowSize(pWindow,largeur,hauteur);
  for(int i=0;i<TAILLE_TAB_BASH;i++){ //ini du tab bash
    tab_info_bash[i].pos_y=265-25*i;
    tab_info_bash[i].couleur=info;
    strcpy(tab_info_bash[i].txt,"PARTIE INITIALISE");
  }


  if(PRESET>1){
    fp = fopen ("fichiers/preset1.txt", "r"); //preset en 7x7
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){

      if(PRESET==1){			//======preset=======//

        if(i==0 && j==0){
          terrain[i][j].type=2;
        }
        else if(i==0 && j>0){
          terrain[i][j].type=4;
        }
        else if(i>0 && j==0){
          terrain[i][j].type=3;
        }
        else if((j==N-1 && i!=0 )||( i==M-1 && j!=0)){
          terrain[i][j].type=1;
        }
        else{												//ALEA "INTELLIGENTE"//
          alea=rand()%(N*M);
          if((alea<(0.05*N*M) )||( (i-1<N && terrain[i-1][j].type==5 && alea<(0.4*N*M)) || (j-1<N && terrain[i][j-1].type==5 && alea<(0.4*N*M)) || (i+1<N && terrain[i+1][j].type==5 && alea<(0.4*N*M)) || (i<N && terrain[i][j+1].type==5 && alea<(0.4*N*M)) )){
            terrain[i][j].type=5;

          }
          else if(((alea<(0.15*N*M) && alea>(0.05*N*M) )|| (i-1<N && terrain[i-1][j].type==7 && alea<(0.45*N*M)) || (j-1<N && terrain[i][j-1].type==7 && alea<(0.45*N*M)) || (i+1<N && terrain[i+1][j].type==7 && alea<(0.45*N*M)) || (i<N && terrain[i][j+1].type==7 && alea<(0.45*N*M)) )){
            terrain[i][j].type=7;
          }
          else if(((alea<(0.25*N*M) && alea>(0.15*N*M) )|| (i-1<N && terrain[i-1][j].type==6 && alea<(0.55*N*M)) || (j-1<N && terrain[i][j-1].type==6 && alea<(0.55*N*M)) || (i+1<N && terrain[i+1][j].type==6 && alea<(0.55*N*M)) || (i<N && terrain[i][j+1].type==6 && alea<(0.55*N*M)) )){
            terrain[i][j].type=6;
          }
          else{
            terrain[i][j].type=1;
          }
        }

      }else{						//=====preset de carte chargé par fichiers=====//

        fscanf(fp, "%i", &var1);
        terrain[i][j].type=var1;
      }

    }

  }
  carte_valide(terrain);
  if(PRESET>1){
    fclose(fp);
  }

  //initialisation de la matrice terrain,variables d'affichages;

    for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
        terrain[i][j].climat=0;
        terrain[i][j].xImg=0;
        terrain[i][j].yImg=0;
        terrain[i][j].x1=0;
        terrain[i][j].y1=0;
        terrain[i][j].x2=0;
        terrain[i][j].y2=0;
        terrain[i][j].x3=0;
        terrain[i][j].y3=0;
        terrain[i][j].x4=0;
        terrain[i][j].y4=0;
        terrain[i][j].piece=NULL;
        terrain[i][j].deplacement=0;
        terrain[i][j].attaque=0;

      }
    }

  //initialisation tableau d'affichage des degats morts et soins

    for(int i=0;i<(N*M);i++){
      aff_deg[i].time=-1;
      aff_deg[i].pos_x=0;
      aff_deg[i].pos_y=0;
      aff_deg[i].c=0;
      strcpy(aff_deg[i].txt,"");
    }

    //initialisation de la grille//

    (imgDestRect.w)=100;
    (imgDestRect.h)=100;                                                                                                                   //les coef ci dessous permettent d'aligner les images car elle ne sont pas totalement droite dans le sprite
    for(int compteur=0, indice = (*hauteur)/2, indice2=(*largeur)/2; compteur<N; compteur++,indice-=(bordure+(imgDestRect.h)/2)/2.1,indice2-=(bordure+(imgDestRect.w)/2)/1.5){
      for(int compteur2=0, indice3= indice , indice4 = indice2; compteur2<M; compteur2++,indice3-=(bordure+(imgDestRect.h)/2)/1.5,indice4+=(bordure+(imgDestRect.w)/2)/1.98){

          imgDestRect.x = indice4;
          imgDestRect.y = indice3;
          imgDestRect.w=100;
          imgDestRect.h=100;

          if(!terrain[compteur][compteur2].x1 || !terrain[compteur][compteur2].x2 || !terrain[compteur][compteur2].y1 || !terrain[compteur][compteur2].y2){

            terrain[compteur][compteur2].xImg=indice4;
            terrain[compteur][compteur2].yImg=indice3;
              //point en haut du losange puis les trois points suivant sont les sommet dans le sens des aiguille d'une montre.



            terrain[compteur][compteur2].x1=imgDestRect.x+imgDestRect.w/2;
            terrain[compteur][compteur2].y1=imgDestRect.y;

            terrain[compteur][compteur2].x2=imgDestRect.x+imgDestRect.w;
            terrain[compteur][compteur2].y2=imgDestRect.y+imgDestRect.h/2;

            terrain[compteur][compteur2].x3=imgDestRect.x+imgDestRect.w/2;
            terrain[compteur][compteur2].y3=imgDestRect.y+imgDestRect.h;

            terrain[compteur][compteur2].x4=imgDestRect.x;
            terrain[compteur][compteur2].y4=imgDestRect.y+imgDestRect.h/2;

          }
        }
      }


  //=========================================================INITIALISATION DES JOUEURS=============================================//

      for(int i=0;i<J;i++){
        if(i<J_HUMAIN){
            tab[i].humain=1;
        }else{
          tab[i].humain=0;
        }
        tab[i].id_joueur=i;
        tab[i].pts_action_max=PTS_ACTION_MAX;
        tab[i].pts_action_actu=tab[i].pts_action_max;
        tab[i].nb_unite=NB_UNITE;
      }


  //=========================================================INITIALISATION DES UNITEES===========================================//

  //alea
  /*
      int unit_gen;
      for(int i=0;i<J;i++){
        unit_gen=0;
        while(unit_gen<tab[i].nb_unite){
          for(int compteur=0;compteur<N; compteur++){
            for(int compteur2=0;compteur2<M; compteur2++){
              if(terrain[compteur][compteur2].piece==NULL && terrain[compteur][compteur2].type != 5){
                if(rand()%(N*M) ==1 && unit_gen<tab[i].nb_unite){
                  terrain[compteur][compteur2].piece=init_piece(((rand()%NB_CLASSE)+1),i); //(((rand()%NB_CLASSE)+1),i)
                  unit_gen++;
                }
              }
            }
          }
        }
      }
*/
  //intelligente

    if(PRESET_U==1){
      int nb_place=0;
      int porte=0;
      int unit_gen;
      for(int i=0;i<J;i++){
        do{
          rem_piece_joueur(terrain,i);
          nb_place=tab[i].nb_unite;
          unit_gen=0;
          while(unit_gen==0){
            for(int compteur=0;compteur<N; compteur++){
              for(int compteur2=0;compteur2<M; compteur2++){
                if(zone_libre(terrain,compteur,compteur2,nb_place)){
                  if(rand()%(N*M) ==1){
                    if(nb_place==1)porte=0;
                    else if(nb_place>=2 && nb_place<=9)porte=1;
                    else if(nb_place>=10 && nb_place<=25)porte=2;
                    else if(nb_place>=26 && nb_place<=49)porte=3;
                    for(int a=compteur-porte;a<=compteur+porte;a++){
                      for(int b=compteur2-porte;b<=compteur2+porte;b++){
                        if(a<N && a>=0 && b<M && b>=0 && case_libre(terrain,a,b) && unit_gen<nb_place){
                          terrain[a][b].piece=init_piece(((rand()%NB_CLASSE)+1),i);
                          unit_gen++;
                        }
                      }
                    }

                  }
                }
              }
            }
          }
        }while(nombre_classe(terrain,i,priest)>NB_MAX_PRIEST);
      }
    }else{
      int var_classe,var_joueur;
      fp = fopen ("fichiers/preset1_U.txt", "r"); //preset d'unité en 7x7
      for(int a=0;a<N;a++){
        for(int b=0;b<M;b++){
          fscanf(fp, "%i", &var_classe);
          fscanf(fp, "%i", &var_joueur);
          if(var_classe!=0 && var_joueur!= -1){
            terrain[a][b].piece=init_piece(var_classe,var_joueur);
          }
        }
      }
      fclose(fp);


    }



}






void affichage_principale(SDL_Renderer *renderer,SDL_Window* pWindow,int bordure,int * largeur,int * hauteur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],case_t terrain[N][M],int joueur_actu,image_t image[Z],int compteur_anim,int nb_joueur_restant,int compteur_tour,int frame_anim_montre,int jour_nuit,char variable2[80]){
  //=================================================================================================================================//
						//=================================================================================================================================//
						//====================================================AFFICHAGE====================================================================//
						//=================================================================================================================================//
						//=================================================================================================================================//
	SDL_Color c = {0,0,0,0};
	SDL_Color c_rouge = {255,0,0,0};
	SDL_Color c_verte = {125,255,125,0};
	SDL_Color c_verte2 = {15,109,15,0};
	SDL_Color b = {255,255,255,255};
	SDL_Color c_bash = {255,0,255,0};
	SDL_Color c_bash_degat = {150,15,15,0};
	SDL_Color c_bash_soin = {15,150,15,0};
	SDL_Color c_bash_ineficace = {175,175,175,0};
	SDL_Color c_bash_deplacement = {255,255,255,0};
	SDL_Color c_bash_kil = {255,0,0,0};

  	int test_bash=0,varBash;
    float coefZoom=1;
    SDL_Rect img_anim;
	  char variable[80];


									SDL_RenderClear(renderer);

									SDL_GetWindowSize(pWindow,largeur,hauteur);
									afficher_img(0,0,*hauteur,*largeur,"images/fond.png",image,renderer,1,0,img_anim);

									for (int compteur=0;compteur<N;compteur++){
										for (int compteur2=0;compteur2<M;compteur2++){

											if(terrain[compteur][compteur2].type==1){
												afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_normalv2.png",image,renderer,coefZoom,0,img_anim);
											}
											else if(terrain[compteur][compteur2].type==2){
												afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_normal_coinv2.png",image,renderer,coefZoom,0,img_anim);
											}
											else if(terrain[compteur][compteur2].type==3){
												afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_normal_bordure_gauchev2.png",image,renderer,coefZoom,0,img_anim);
											}
											else if(terrain[compteur][compteur2].type==4){
												afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_normal_bordure_droitev2.png",image,renderer,coefZoom,0,img_anim);
											}
											else if(terrain[compteur][compteur2].type==5){
												afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_eauv2.png",image,renderer,coefZoom,0,img_anim);
											}
											else if(terrain[compteur][compteur2].type==6){
												afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_foretv2.png",image,renderer,coefZoom,0,img_anim);
											}
											else if(terrain[compteur][compteur2].type==7){
												afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_montagnev2.png",image,renderer,coefZoom,0,img_anim);
											}
										}
									}

									for (int compteur=0;compteur<N;compteur++){
										for (int compteur2=0;compteur2<M;compteur2++){
											if(terrain[compteur][compteur2].piece){
												if(terrain[compteur][compteur2].piece->select){		//affichage case possible déplacement ou attaque si allié, sinon affiche le stats de la cible et sa direction d'arret;
													if(terrain[compteur][compteur2].piece->joueur==joueur_actu){
																			//deplacement
														pathfinding(terrain,compteur,compteur2);

														for (int ind=0;ind<N;ind++){
															for (int ind2=0;ind2<M;ind2++){
																if(terrain[ind][ind2].deplacement==1 && (compteur_anim%(VITESSE_ANIM*2))<(VITESSE_ANIM/2)*2){

																	afficher_img(terrain[ind][ind2].xImg-bordure/15+8,terrain[ind][ind2].yImg-bordure/8+3,100,100,"images/deplacement.png",image,renderer,coefZoom,0,img_anim);

																}else if(terrain[ind][ind2].deplacement==1 && (compteur_anim%(VITESSE_ANIM*2))>=(VITESSE_ANIM/2)*2){

																	afficher_img(terrain[ind][ind2].xImg-bordure/15+8,terrain[ind][ind2].yImg-bordure/8+3,100,100,"images/deplacement2.png",image,renderer,coefZoom,0,img_anim);

																}
															}
														}
															//attaque
														pathfinding_combat(terrain,compteur,compteur2,joueur_actu);

														for (int ind=0;ind<N;ind++){
															for (int ind2=0;ind2<M;ind2++){
																if(terrain[ind][ind2].attaque==1 && ((compteur_anim%VITESSE_ANIM)<(VITESSE_ANIM/2) || (compteur_anim%VITESSE_ANIM)>((VITESSE_ANIM/4)*3)) ){

																	afficher_img(terrain[ind][ind2].xImg-bordure/15+8,terrain[ind][ind2].yImg-bordure/8+3,100,100,"images/attaque.png",image,renderer,coefZoom,0,img_anim);

																}else if(terrain[ind][ind2].attaque==1 && ((compteur_anim%VITESSE_ANIM)>(VITESSE_ANIM/2) || (compteur_anim%VITESSE_ANIM)<=((VITESSE_ANIM/4)*3)) ){

																	afficher_img(terrain[ind][ind2].xImg-bordure/15+8,terrain[ind][ind2].yImg-bordure/8+3,100,100,"images/attaque2.png",image,renderer,coefZoom,0,img_anim);

																}
															}
														}
													}
												}
											}
										}
									}

									for (int compteur=0;compteur<N;compteur++){
										for (int compteur2=0;compteur2<M;compteur2++){
											if(terrain[compteur][compteur2].piece){ 		//AFFICHAGE DES CERCLE UNITES ALLIEES ET UNITES SELECTIONNEES

												if(terrain[compteur][compteur2].piece->joueur==joueur_actu && terrain[compteur][compteur2].piece->select==0){ //cercle des unité du joueur_actu affichage
													afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg+5,100,100,"images/image_allie.png",image,renderer,coefZoom,0,img_anim);
												}else if(terrain[compteur][compteur2].piece->joueur==joueur_actu && terrain[compteur][compteur2].piece->select==1){ //cercle de l'unité selectionné du joueur_actu
													afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg+5,100,100,"images/image_select_allie.png",image,renderer,coefZoom,0,img_anim);
												}
											}
										}
									}


									for (int compteur=0;compteur<N;compteur++){
										for (int compteur2=0;compteur2<M;compteur2++){
											if(terrain[compteur][compteur2].piece){ 		//AFFICHAGE DES UNITEES
												switch (terrain[compteur][compteur2].piece->classe){
													case 1:

													img_anim=afficher_anim(compteur_anim,terrain[compteur][compteur2].piece->classe,terrain,compteur,compteur2,0);
													afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg-10,100,100,"images/knight_anim.png",image,renderer,coefZoom,1,img_anim);

													break;
													case 2:

													img_anim=afficher_anim(compteur_anim,terrain[compteur][compteur2].piece->classe,terrain,compteur,compteur2,0);
													afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg-10,100,100,"images/scout_anim.png",image,renderer,coefZoom,1,img_anim);

													break;
													case 3:

													img_anim=afficher_anim(compteur_anim,terrain[compteur][compteur2].piece->classe,terrain,compteur,compteur2,0);
													afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg-10,100,100,"images/priest_anim.png",image,renderer,coefZoom,1,img_anim);

													break;
													case 4:

													img_anim=afficher_anim(compteur_anim,terrain[compteur][compteur2].piece->classe,terrain,compteur,compteur2,0);
													afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg-10,100,100,"images/magician_anim.png",image,renderer,coefZoom,1,img_anim);

													break;
													case 5:

													afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg-10,100,100,"images/faucheuse.png",image,renderer,coefZoom,0,img_anim);

													break;
													case 6:

													img_anim=afficher_anim(compteur_anim,terrain[compteur][compteur2].piece->classe,terrain,compteur,compteur2,0);
													afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg-10,100,100,"images/ange_anim.png",image,renderer,coefZoom,1,img_anim);

													break;
												}
											}
										}
									}

									//affichage des fleche de deplacement transparentes sur les ennemis a portee de l'allie selectionné si il y en a un
									for (int compteur=0;compteur<N;compteur++){
										for (int compteur2=0;compteur2<M;compteur2++){
											if(terrain[compteur][compteur2].piece && terrain[compteur][compteur2].piece->select == 1 && terrain[compteur][compteur2].piece->joueur==joueur_actu && terrain[compteur][compteur2].piece->classe!=priest){
												for (int i=0;i<N;i++){
													for (int j=0;j<M;j++){
														if(terrain[i][j].attaque==1){
															switch(terrain[i][j].piece->direction){
																case 1:
																	afficher_img(terrain[i][j].xImg+10,terrain[i][j].yImg+10,80,80,"images/fleche_nord_trans.png",image,renderer,1,0,img_anim);
																break;
																case 2:
																	afficher_img(terrain[i][j].xImg+10,terrain[i][j].yImg+10,80,80,"images/fleche_sud_trans.png",image,renderer,1,0,img_anim);
																break;
																case 3:
																	afficher_img(terrain[i][j].xImg+10,terrain[i][j].yImg+10,80,80,"images/fleche_ouest_trans.png",image,renderer,1,0,img_anim);
																break;
																case 4:
																	afficher_img(terrain[i][j].xImg+10,terrain[i][j].yImg+10,80,80,"images/fleche_est_trans.png",image,renderer,1,0,img_anim);
																break;
															}
														}
													}
												}
											}
										}
									}


                  //nuit et jour//
                  if((jour_nuit>=((DURE_JOUR_NUIT/24)*22) && jour_nuit<=(DURE_JOUR_NUIT)+50) || (jour_nuit>=0 && jour_nuit<=((DURE_JOUR_NUIT/24)*2) )){
                    afficher_img(0,0,*hauteur,*largeur,"images/nuit-3.png",image,renderer,1,0,img_anim);
                  }else if((jour_nuit>=((DURE_JOUR_NUIT/24)*21) && jour_nuit<((DURE_JOUR_NUIT/24)*22) )|| (jour_nuit>((DURE_JOUR_NUIT/24)*2) && jour_nuit<=((DURE_JOUR_NUIT/24)*3) )){
                    afficher_img(0,0,*hauteur,*largeur,"images/nuit-2.png",image,renderer,1,0,img_anim);
                  }else if((jour_nuit>=((DURE_JOUR_NUIT/24)*20) && jour_nuit<((DURE_JOUR_NUIT/24)*21) )|| (jour_nuit>((DURE_JOUR_NUIT/24)*3) && jour_nuit<=((DURE_JOUR_NUIT/24)*4) )){
                    afficher_img(0,0,*hauteur,*largeur,"images/nuit-1.png",image,renderer,1,0,img_anim);
                  }

                  //===========//


									//drap rouge en haut
									afficher_img(0,0,*hauteur,*largeur,"images/drap_rouge.png",image,renderer,1,0,img_anim);

									//fin du tour bouton

									afficher_img((*largeur)/3+420,15,50,150,"images/fin_du_tour.png",image,renderer,1,0,img_anim);

									//menu nord

									afficher_img((*largeur)/3,0,75,400,"images/menu_nord.png",image,renderer,1,0,img_anim);

									AfficherText("ACTION RESTANTE:","arial.ttf",c,12,renderer,(*largeur)/3+200,30);

									AfficherText("TOUR DU JOUEUR ","arial.ttf",c,12,renderer,(*largeur)/3+50,30);

									sprintf(variable, "%d",  tab[joueur_actu].pts_action_actu);

									AfficherText(variable,"arial.ttf",c,30,renderer,(*largeur)/3+325,18);

									sprintf(variable, "%d",  joueur_actu);

									AfficherText(variable,"arial.ttf",c,30,renderer,(*largeur)/3+165,18);
									//stats


									afficher_img(0,0,400,150,"images/inter.png",image,renderer,1,0,img_anim);

									AfficherText("PDV        :","arial.ttf",c,12,renderer,30,155);

									AfficherText("ATK        :","arial.ttf",c,12,renderer,30,175);

									AfficherText("DEF        :","arial.ttf",c,12,renderer,30,195);

									AfficherText("BLOCK  :","arial.ttf",c,12,renderer,30,215);

									AfficherText("RANGE  :","arial.ttf",c,12,renderer,30,235);

									AfficherText("MS          :","arial.ttf",c,12,renderer,30,255);

									AfficherText("MENU", "arial.ttf",b,15,renderer,gpScreen->w - 60,gpScreen->h - 30);



									//infos générales de la partie
									afficher_img(150,0,200,300,"images/menu_nord.png",image,renderer,1,0,img_anim);

									AfficherText("Joueurs Restants :        ","arial.ttf",c,20,renderer,185,30);
									sprintf(variable, "%d",  nb_joueur_restant);
									AfficherText(variable,"arial.ttf",c,30,renderer,365,26);

									AfficherText("Unit Allies :        ","arial.ttf",c,20,renderer,185,80);
									sprintf(variable, "%d",  reste_allie(terrain,joueur_actu));
									AfficherText(variable,"arial.ttf",c,30,renderer,365,72);

									AfficherText("Unit Ennemis:        ","arial.ttf",c,20,renderer,185,130);
									sprintf(variable, "%d",  reste_ennemi(terrain,joueur_actu));
									AfficherText(variable,"arial.ttf",c,30,renderer,365,122);


						//==============BASH=======================//

									afficher_img(((*largeur)-450),0,300,450,"images/bash.png",image,renderer,1,0,img_anim);
									test_bash=0;
									for(int i=0;i<J;i++){
										if(tab[i].id_joueur==-2){
											varBash=i;
											test_bash=1;
										}
									}
									if(test_bash==1){
										sprintf(variable, "| Le Joueur %d a ete elimine.",varBash);
										ajouter_ligne_bash(variable,tab_info_bash,info,variable2);
									}

									for(int i=0;i<TAILLE_TAB_BASH;i++){   //AFFICHAGE DU BASH
										if(tab_info_bash[i].pos_y<=265 && tab_info_bash[i].pos_y>=5){
											switch(tab_info_bash[i].couleur){
												case 1: AfficherText(tab_info_bash[i].txt,"arial.ttf",c_bash,15,renderer,((*largeur)-450+25),tab_info_bash[i].pos_y);break;
												case 2: AfficherText(tab_info_bash[i].txt,"arial.ttf",c_bash_degat,15,renderer,((*largeur)-450+25),tab_info_bash[i].pos_y);break;
												case 3: AfficherText(tab_info_bash[i].txt,"arial.ttf",c_bash_soin,15,renderer,((*largeur)-450+25),tab_info_bash[i].pos_y);break;
												case 4: AfficherText(tab_info_bash[i].txt,"arial.ttf",c_bash_ineficace,15,renderer,((*largeur)-450+25),tab_info_bash[i].pos_y);break;
												case 5: AfficherText(tab_info_bash[i].txt,"arial.ttf",c_bash_deplacement,15,renderer,((*largeur)-450+25),tab_info_bash[i].pos_y);break;
												case 6: AfficherText(tab_info_bash[i].txt,"arial.ttf",c_bash_kil,15,renderer,((*largeur)-450+25),tab_info_bash[i].pos_y);break;
											}
										}
									}


				//==============BASH=======================//

				//=======COMPTEUR JOUR======//



									img_anim.x=150*frame_anim_montre;
									img_anim.y=0;
									img_anim.w=150;
									img_anim.h=150;
									afficher_img(((*largeur)-160),410,150,150,"images/montre_anim.png",image,renderer,coefZoom,1,img_anim);
									AfficherText("JOUR","arial.ttf",c,20,renderer,((*largeur)-110),445);
									sprintf(variable, "%d",compteur_tour);
									AfficherText(variable,"arial.ttf",c,30,renderer,((*largeur)-102),490);



				//=======COMPTEUR JOUR======//


									for(int i=0;i<N;i++){
										for(int j=0;j<M;j++){
											if(terrain[i][j].piece && terrain[i][j].piece->select==1){
												//affichage des infos de l'unité en haut a gauche.

												switch (terrain[i][j].piece->classe){
													case 1:

													img_anim=afficher_anim(compteur_anim,terrain[i][j].piece->classe,terrain,i,j,1);
													afficher_img(20,20,100,100,"images/knight_anim.png",image,renderer,coefZoom,1,img_anim);

												break;
												case 2:

													img_anim=afficher_anim(compteur_anim,terrain[i][j].piece->classe,terrain,i,j,1);
													afficher_img(20,20,100,100,"images/scout_anim.png",image,renderer,coefZoom,1,img_anim);

												break;
												case 3:

													img_anim=afficher_anim(compteur_anim,terrain[i][j].piece->classe,terrain,i,j,1);
													afficher_img(20,20,100,100,"images/priest_anim.png",image,renderer,coefZoom,1,img_anim);

												break;
												case 4:

												img_anim=afficher_anim(compteur_anim,terrain[i][j].piece->classe,terrain,i,j,1);
												afficher_img(20,20,100,100,"images/magician_anim.png",image,renderer,coefZoom,1,img_anim);

												break;
												case 5:

												afficher_img(20,20,100,100,"images/faucheuse.png",image,renderer,1,0,img_anim);
												break;
												case 6:

													img_anim=afficher_anim(compteur_anim,terrain[i][j].piece->classe,terrain,i,j,1);
													afficher_img(20,20,100,100,"images/ange_anim.png",image,renderer,coefZoom,1,img_anim);

												break;
												}
												//text


															//affichage des stats de l'unité selectionné en fonction du terrain
												sprintf(variable, "%d",  terrain[i][j].piece->joueur);
												AfficherText(variable,"arial.ttf",c,25,renderer,65,110);

												sprintf(variable, "%d", terrain[i][j].piece->pdv);
												AfficherText(variable,"arial.ttf",c,12,renderer,90,155);

												sprintf(variable, "%d", terrain[i][j].piece->puissance);
												AfficherText(variable,"arial.ttf",c,12,renderer,90,175);

												if(terrain[i][j].type==6){
													sprintf(variable, "%d", (terrain[i][j].piece->armure+3));
													AfficherText(variable,"arial.ttf",c_verte2,12,renderer,90,195);
												}else{
													sprintf(variable, "%d", terrain[i][j].piece->armure);
													AfficherText(variable,"arial.ttf",c,12,renderer,90,195);
												}


												if(terrain[i][j].type==6){
													sprintf(variable, "%d", (terrain[i][j].piece->block+10));
													AfficherText(variable,"arial.ttf",c_verte2,12,renderer,90,215);
												}else{
													sprintf(variable, "%d", terrain[i][j].piece->block);
													AfficherText(variable,"arial.ttf",c,12,renderer,90,215);
												}

												if(terrain[i][j].type==7){
													sprintf(variable, "%d", (terrain[i][j].piece->portee+1));
													AfficherText(variable,"arial.ttf",c_verte2,12,renderer,90,235);
												}else{
													sprintf(variable, "%d", terrain[i][j].piece->portee);
													AfficherText(variable,"arial.ttf",c,12,renderer,90,235);
												}

												if(terrain[i][j].type==6 || terrain[i][j].type==7){
													sprintf(variable, "%d", (terrain[i][j].piece->deplacement-1));
													AfficherText(variable,"arial.ttf",c_rouge,12,renderer,90,255);
												}else{
													sprintf(variable, "%d", terrain[i][j].piece->deplacement);
													AfficherText(variable,"arial.ttf",c,12,renderer,90,255);
												}



												//affichage de nombre de kils actuel de l'unité si ce n'est pas un pretre
												if(terrain[i][j].piece->classe!=priest){
													afficher_img(106,48,30,30,"images/kils.png",image,renderer,1,0,img_anim);
													sprintf(variable, "%d", terrain[i][j].piece->kil);
													AfficherText(variable,"arial.ttf",c_rouge,24,renderer,114,75);
												}
												//DIRECTION affichage


												switch(terrain[i][j].piece->direction){
													case 1:
														afficher_img(25,275,100,100,"images/fleche_nord.png",image,renderer,1,0,img_anim);
													break;
													case 2:
														afficher_img(25,275,100,100,"images/fleche_sud.png",image,renderer,1,0,img_anim);
													break;
													case 3:
														afficher_img(25,275,100,100,"images/fleche_ouest.png",image,renderer,1,0,img_anim);
													break;
													case 4:
														afficher_img(25,275,100,100,"images/fleche_est.png",image,renderer,1,0,img_anim);
													break;
												}


											}
										}
									}

									for(int i=0;i<AFF_DEG;i++){ //affichage des dégats, morts soins etc
										if(aff_deg[i].time>0){
											if(aff_deg[i].c==1){//couleur degat
												AfficherText(aff_deg[i].txt,"arial.ttf",c_rouge,30,renderer,aff_deg[i].pos_x,aff_deg[i].pos_y);
											}else if(aff_deg[i].c==2){//couleur soin
												AfficherText(aff_deg[i].txt,"arial.ttf",c_verte,30,renderer,aff_deg[i].pos_x,aff_deg[i].pos_y);
                      }else if(aff_deg[i].c==3){//couleur kil
												AfficherText(aff_deg[i].txt,"arial.ttf",c_bash,30,renderer,aff_deg[i].pos_x,aff_deg[i].pos_y);
											}else{//couleur grise
												AfficherText(aff_deg[i].txt,"arial.ttf",c_bash_deplacement,30,renderer,aff_deg[i].pos_x,aff_deg[i].pos_y);
											}
										}
									}

									clean_degat_txt(aff_deg);



									SDL_RenderPresent(renderer);
									SDL_Delay(16);



						//=================================================================================================================================//
						//=======================================================FIN=======================================================================//
						//====================================================AFFICHAGE====================================================================//
						//=======================================================...=======================================================================//
						//=================================================================================================================================//


}


int zone_libre(case_t terrain[N][M],int x, int y,int nb_place){
  int porte=0,place_dispo=0;
  if(nb_place==1)porte=0;
  if(nb_place>=2 && nb_place<=9)porte=1;
  if(nb_place>=10 && nb_place<=25)porte=2;
  if(nb_place>=26 && nb_place<=49)porte=3;

  int porte_gen=porte+ESPACE_GEN;


  if(case_libre(terrain,x,y)){
    for(int a=x-porte_gen;a<=x+porte_gen;a++){
      for(int b=y-porte_gen;b<=y+porte_gen;b++){
        if(a<N && a>=0 && b<M && b>=0 && terrain[a][b].piece!=NULL){
          return 0;
        }
      }
    }
  }

  if(case_libre(terrain,x,y)){
    for(int a=x-porte;a<=x+porte;a++){
      for(int b=y-porte;b<=y+porte;b++){
        if(a<N && a>=0 && b<M && b>=0 && case_libre(terrain,a,b)){
          place_dispo++;
        }
      }
    }
  }
  if(place_dispo>=nb_place){
    return 1;
  }
  return 0;
}


int case_libre(case_t terrain[N][M],int x,int y){
  if(terrain[x][y].type!=5 && terrain[x][y].piece==NULL){
    return 1;
  }
  return 0;
}



void pathfinding_combat(case_t terrain[N][M], int x, int y,int joueur_actu){
  int attaque[N][M];
  int i,j;
  int cpt;
  //initialisation des attaques possibles
  for (i=0;i<N;i++){//parcours du terrain
      for(j=0;j<M;j++){
        terrain[i][j].attaque=0;
      }
  }

  for (i=0;i<N;i++){//parcours du terrain
      for(j=0;j<M;j++){
        attaque[i][j]=0;
      }
  }

    attaque[x][y]=1;//case ou se trouve la piece
    //gestion du terrain
    int portee_attaquant;
    if(terrain[x][y].type!=7){
      portee_attaquant=terrain[x][y].piece->portee;
    }else{
      portee_attaquant=terrain[x][y].piece->portee+1;
    }

    for(cpt=1;cpt<=portee_attaquant;cpt++){//tant qu'il y a des point de la portée
        for (i=0;i<N;i++){//parcours du terrain
            for(j=0;j<M;j++){
                if (attaque[i][j]==cpt){
                  if(i+1<N && attaque[i+1][j]==0)
                    attaque[i+1][j]=cpt+1;//ICI
                  if(i-1>=0 && attaque[i-1][j]==0)
                    attaque[i-1][j]=cpt+1;
                  if(j+1<N && attaque[i][j+1]==0)
                    attaque[i][j+1]=cpt+1;
                  if(j-1>=0 && attaque[i][j-1]==0)
                    attaque[i][j-1]=cpt+1;
                }

            }
        }
    }
    for (i=0;i<N;i++){
      for(j=0;j<M;j++){
        if(terrain[i][j].piece && terrain[i][j].piece->joueur==joueur_actu && attaque[i][j]!=0)
          attaque[i][j]=-2;
      }
    }

    for (i=0;i<N;i++){//parcours du terrain
        for(j=0;j<M;j++){
            if(attaque[i][j]>1 && terrain[i][j].piece && terrain[i][j].piece->joueur!=joueur_actu && terrain[x][y].piece->classe!=priest)
              terrain[i][j].attaque=1;
            if(attaque[i][j]==-2 && terrain[i][j].piece && terrain[i][j].piece->joueur==joueur_actu && terrain[x][y].piece->classe==priest)
              terrain[i][j].attaque=1;
        }
    }
}

int calc_block(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def){
    int pos_block[N][M];
    int cpt=1;
    int block=0;
    //init matrice a 0
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
          pos_block[i][j]=-2;
        }
    }
    pos_block[x_def][y_def]=0;
    //diagonales a -1
    while (x_def-cpt>=0 && y_def+cpt<M){
        pos_block[x_def-cpt][y_def+cpt]=-1;
        cpt++;
    }
    cpt=1;
    while (x_def+cpt<N && y_def+cpt<N){
        pos_block[x_def+cpt][y_def+cpt]=-1;
        cpt++;
    }
    cpt=1;
    while (x_def+cpt<N && y_def-cpt>=0){
        pos_block[x_def+cpt][y_def-cpt]=-1;
        cpt++;
    }
    cpt=1;
    while (x_def-cpt>=0 && y_def-cpt>=0){
        pos_block[x_def-cpt][y_def-cpt]=-1;
        cpt++;
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if ((pos_block[i][j-1]==-1 || pos_block[i][j-1]==0 || pos_block[i][j-1]==1) && j>y_def)
                pos_block[i][j]=1;
        }
    }
    for(int i=0;i<N;i++){
        for(int j=M-1;j>=0;j--){
            if ((pos_block[i][j+1]==-1 || pos_block[i][j+1]==0 || pos_block[i][j+1]==2) && j<y_def)
              pos_block[i][j]=2;
        }
    }
    for(int j=0;j<M;j++){
        for(int i=0;i<N;i++){
            if ((pos_block[i-1][j]==-1 || pos_block[i-1][j]==0 || pos_block[i-1][j]==3) && i>x_def)
                pos_block[i][j]=3;
        }
    }
    for(int j=0;j<M;j++){
        for(int i=0;i<N;i++){
            if (pos_block[i][j]==-2)
                pos_block[i][j]=4;
        }
    }


    if(terrain[x_def][y_def].piece->direction==haut){
        if (pos_block[x_att][y_att]==2){
            block= 0;
        }
        else if (pos_block[x_att][y_att]==3 || pos_block[x_att][y_att]==4 || pos_block[x_att][y_att]==(-1)){
            block=((terrain[x_def][y_def].piece->block)/2);
        }
        else{
            block= (terrain[x_def][y_def].piece->block);
        }
    }
    else if(terrain[x_def][y_def].piece->direction==bas){
        if (pos_block[x_att][y_att]==1){
            block= 0;
        }
        else if (pos_block[x_att][y_att]==3 || pos_block[x_att][y_att]==4 || pos_block[x_att][y_att]==-1){
            block= ((terrain[x_def][y_def].piece->block)/2);
        }
        else{
            block= (terrain[x_def][y_def].piece->block);
        }
    }
    else if(terrain[x_def][y_def].piece->direction==gauche){
        if (pos_block[x_att][y_att]==4){
            block= 0;
        }
        else if (pos_block[x_att][y_att]==1 || pos_block[x_att][y_att]==2 || pos_block[x_att][y_att]==-1){
            block= ((terrain[x_def][y_def].piece->block)/2);
        }
        else{
            block= (terrain[x_def][y_def].piece->block);
        }
    }
    else if(terrain[x_def][y_def].piece->direction==droite){
        if (pos_block[x_att][y_att]==3){
            block= 0;
        }
        else if (pos_block[x_att][y_att]==1 || pos_block[x_att][y_att]==2 || pos_block[x_att][y_att]==-1){
            block= ((terrain[x_def][y_def].piece->block)/2);
        }
        else{
            block= (terrain[x_def][y_def].piece->block);
        }
    }
    return block;
}




void combat(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]){
  if(tab[joueur].pts_action_actu>0){
      if(terrain[x_att][y_att].piece->classe==priest){//soin si la piece selectionné est un pretre
          soin(terrain,x_att,y_att,x_def,y_def,joueur,tab,aff_deg,tab_info_bash,variable2);
          return;
      }
      if(terrain[x_def][y_def].attaque==1){//si la piece attaquée est sur une case a portée
        int blockd=((rand()%(100)) + 1);//att bloquée ou non
        int blockage;
        char variable[80];
        int armure;
        //avantages du terrain de foret
        if(terrain[x_def][y_def].type==6){
          blockage = calc_block(terrain,x_att,y_att,x_def,y_def) + 10;
          armure = terrain[x_def][y_def].piece->armure + 3;
        }else{
          blockage = calc_block(terrain,x_att,y_att,x_def,y_def);
          armure = terrain[x_def][y_def].piece->armure;
        }

        if(blockd>=blockage){

          int deg=((terrain[x_att][y_att].piece->puissance)*(100-armure)/100);

          if(deg>=0){
            terrain[x_def][y_def].piece->pdv-=deg;//armure=absorption de dégats //application des dégats ici

            sprintf(variable, "| Unite de Joueur %d en %d/%d attaque pour %d en %d/%d",joueur,x_att,y_att,deg,x_def,y_def);
			    	ajouter_ligne_bash(variable,tab_info_bash,degat,variable2);

            sprintf(variable, "%d", deg);//sauvegarde des dégat pour affichage
            ajouter_degat_txt(variable,aff_deg,(terrain[x_def][y_def].xImg+50),(terrain[x_def][y_def].yImg),1);


          }else{
            sprintf(variable, "| Unite de Joueur %d en %d/%d attaque pour 0 en %d/%d",joueur,x_att,y_att,x_def,y_def);
			    	ajouter_ligne_bash(variable,tab_info_bash,ineficace,variable2);
            ajouter_degat_txt("0",aff_deg,(terrain[x_def][y_def].xImg+50),(terrain[x_def][y_def].yImg),0);
          }
          if(terrain[x_def][y_def].piece->pdv<=0){   //mort ou non de la piece ennemi

            sprintf(variable, "| Unite de Joueur %d en %d/%d tue Unite de %d en %d/%d",joueur,x_att,y_att,terrain[x_def][y_def].piece->joueur,x_def,y_def);
			    	ajouter_ligne_bash(variable,tab_info_bash,kil,variable2);

            tab[terrain[x_def][y_def].piece->joueur].nb_unite--;
            terrain[x_att][y_att].piece->kil+=1;
            ajouter_degat_txt("kil",aff_deg,(terrain[x_def][y_def].xImg),(terrain[x_def][y_def].yImg+20),3);
            free(terrain[x_def][y_def].piece);
            terrain[x_def][y_def].piece=NULL;
            update_stats(terrain,x_att,y_att,joueur,tab);
          }
        }else{

          sprintf(variable, "| Unite de Joueur %d en %d/%d block Unite de %d en %d/%d ",terrain[x_def][y_def].piece->joueur,x_def,y_def,joueur,x_att,y_att);
			    ajouter_ligne_bash(variable,tab_info_bash,4,variable2);


          ajouter_degat_txt("BLOCK",aff_deg,(terrain[x_def][y_def].xImg+50),(terrain[x_def][y_def].yImg),0);
        }
        tab[joueur].pts_action_actu--;
      }
    }
}

void soin(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]){
    char variable[80];
    if(terrain[x_def][y_def].attaque==1){
        terrain[x_def][y_def].piece->pdv+=terrain[x_att][y_att].piece->puissance;

        sprintf(variable, "| Unite de Joueur %d en %d/%d soigne de %d en %d/%d",joueur,x_att,y_att,terrain[x_att][y_att].piece->puissance,x_def,y_def);
				ajouter_ligne_bash(variable,tab_info_bash,soins,variable2);

        tab[joueur].pts_action_actu--;
        sprintf(variable, "%d", terrain[x_att][y_att].piece->puissance);
        ajouter_degat_txt(variable,aff_deg,(terrain[x_def][y_def].xImg+50),(terrain[x_def][y_def].yImg),2);
    }
}



int a_portee(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu){
  pathfinding_combat(terrain,x_bot,y_bot,joueur_actu);
  int nb=0;
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(terrain[i][j].attaque==1){
        nb++;
      }
    }
  }
  return nb;
}




void update_stats(case_t terrain[N][M],int x,int y,int joueur_actu,joueurs_t tab[J]){



        //++++++KNIGHT++++++++//
  if(terrain[x][y].piece->classe==knight){
    //===bonus a chaque kil=====//
    terrain[x][y].piece->puissance+=terrain[x][y].piece->kil;
    if(terrain[x][y].piece->armure<90){
      terrain[x][y].piece->armure+=1;
    }
    //===bonus tous les 3 kils=====//
    if(terrain[x][y].piece->kil % 3==0){
      terrain[x][y].piece->pdv+=30;
    }
    //===bonus tous les 7 kils=====//
    if(terrain[x][y].piece->kil % 7==0){
      terrain[x][y].piece->deplacement+=1;
    }
    //===bonus de vétérant de la guerre(10 kils)===//
    if(terrain[x][y].piece->kil==10){
      terrain[x][y].piece->deplacement+=1;
      terrain[x][y].piece->portee+=1;
      terrain[x][y].piece->puissance+=10;
      terrain[x][y].piece->armure+=5;
      terrain[x][y].piece->block+=10;
    }



        //++++++SCOUT++++++++//
  }else if(terrain[x][y].piece->classe==scout){
    //===bonus a chaque kil=====//
    terrain[x][y].piece->puissance+=terrain[x][y].piece->kil;
    //===bonus tous les 2 kils=====//
    if(terrain[x][y].piece->kil % 2==0){
      terrain[x][y].piece->pdv+=10;
    }
    //===bonus tous les 3 kils=====//
    if(terrain[x][y].piece->kil % 3==0){
      terrain[x][y].piece->deplacement+=1;
    }
    //===bonus de vétérant de la guerre(10 kils)===//
    if(terrain[x][y].piece->kil==10){
      terrain[x][y].piece->puissance+=13;
      terrain[x][y].piece->armure+=10;
      terrain[x][y].piece->block+=20;
      terrain[x][y].piece->portee+=1;
    }





        //++++++MAGICIAN++++++++//
  }else if(terrain[x][y].piece->classe==magician){
    //===bonus a chaque kil=====//
    terrain[x][y].piece->puissance+=terrain[x][y].piece->kil;
    terrain[x][y].piece->pdv+=terrain[x][y].piece->kil;
    //===bonus tous les 5 kils=====//
    if(terrain[x][y].piece->kil % 5==0){
      terrain[x][y].piece->pdv+=15;
    }
    //===bonus tous les 10 kils=====//
    if(terrain[x][y].piece->kil % 10==0){
      terrain[x][y].piece->portee+=1;
    }

    //===bonus de vétérant de la guerre(10 kils)===//
    if(terrain[x][y].piece->kil==10){
      terrain[x][y].piece->puissance+=14;
      terrain[x][y].piece->armure+=5;
      terrain[x][y].piece->block+=5;
      terrain[x][y].piece->deplacement+=1;
    }





       //++++++FAUCHEUSE++++++++//
  }else if(terrain[x][y].piece->classe==faucheuse){
      //===bonus a chaque kil=====//
    terrain[x][y].piece->puissance+=terrain[x][y].piece->kil;
    //===bonus tous les 5 kils=====//
    if(terrain[x][y].piece->kil % 5==0){
      if(terrain[x][y].piece->block<90){
        terrain[x][y].piece->block+=10;
      }
    }
    //===bonus de vétérant de la guerre(10 kils)===//
    if(terrain[x][y].piece->kil==10){
      terrain[x][y].piece->deplacement+=1;
      terrain[x][y].piece->puissance+=15;
      terrain[x][y].piece->portee+=1;
      terrain[x][y].piece->block+=10;
    }




     //++++++ANGE++++++++//
  }else if(terrain[x][y].piece->classe==ange){
      //===bonus a chaque kil=====//
    terrain[x][y].piece->puissance+=terrain[x][y].piece->kil;
    tab[joueur_actu].pts_action_actu+=1;
    terrain[x][y].piece->pdv+=(terrain[x][y].piece->kil)*3;
    //===bonus tous les 5 kils=====//
    if(terrain[x][y].piece->kil % 5==0){
      terrain[x][y].piece->puissance+=terrain[x][y].piece->kil;
      terrain[x][y].piece->deplacement+=1;
    }
    //===bonus de vétérant de la guerre(10 kils)===//
    if(terrain[x][y].piece->kil==10){
      terrain[x][y].piece->puissance+=15;
      terrain[x][y].piece->armure+=15;
      terrain[x][y].piece->deplacement+=1;
    }



      //++++++AUTRE++++++++//
  }else if(terrain[x][y].piece->classe==priest){ //autre unité

  }

}




void depla_atk_mov(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu,joueurs_t tab[J],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]){
  //V2
  //addition de la difference des pos x et y de l'unité par rapport a ses allié,
  //prendre la piece la plus proche et se rapprocher au max des ses coordonné x et y tt en restant dans la range de déplacement
  //int var4=rand()%2; //choix vers ennemi ou allie

  if(terrain[x_bot][y_bot].piece && a_portee(terrain,x_bot,y_bot,joueur_actu)==0 ){
    fprintf(stderr,"VERS ennemi\n");
    depla_ennem_plus_proche(terrain,x_bot,y_bot,joueur_actu,tab,tab_info_bash,variable2);
  }else if(terrain[x_bot][y_bot].piece && reste_allie(terrain,joueur_actu)>1 && (allie_adjacent(terrain,x_bot,y_bot,joueur_actu))==0){
    fprintf(stderr,"VERS allie\n");
    depla_allie_plus_proche(terrain,x_bot,y_bot,joueur_actu,tab,tab_info_bash,variable2);
  }else{
    fprintf(stderr,"RIEN A FAIRE\n");
    move_alea(terrain,x_bot,y_bot,joueur_actu,tab,tab_info_bash,variable2);
  }
}

void centrer_camera(case_t terrain[N][M],int x,int y,int largeur,int hauteur){
	int x_centre,y_centre,diff_x,diff_y;
	x_centre=largeur/2;
	y_centre=hauteur/2;
	diff_x=abs(x_centre-x);
	diff_y=abs(y_centre-y);

	if(x<=x_centre){
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				terrain[i][j].xImg+=diff_x;
				terrain[i][j].x1+=diff_x;
				terrain[i][j].x2+=diff_x;
				terrain[i][j].x3+=diff_x;
				terrain[i][j].x4+=diff_x;
			}
		}
	}else{
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				terrain[i][j].xImg-=diff_x;
				terrain[i][j].x1-=diff_x;
				terrain[i][j].x2-=diff_x;
				terrain[i][j].x3-=diff_x;
				terrain[i][j].x4-=diff_x;
			}
		}
	}

	if(y<=y_centre){
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				terrain[i][j].yImg+=diff_y;
				terrain[i][j].y1+=diff_y;
				terrain[i][j].y2+=diff_y;
				terrain[i][j].y3+=diff_y;
				terrain[i][j].y4+=diff_y;
			}
		}
	}else{
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				terrain[i][j].yImg-=diff_y;
				terrain[i][j].y1-=diff_y;
				terrain[i][j].y2-=diff_y;
				terrain[i][j].y3-=diff_y;
				terrain[i][j].y4-=diff_y;
			}
		}
	}
}








void attaquer_meilleur_cible(case_t terrain[N][M],int x_bot,int y_bot,int nb_ennemies_portee,int joueur_actu,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]){
  pathfinding_combat(terrain,x_bot,y_bot,joueur_actu);
  if(terrain[x_bot][y_bot].piece->classe==priest){//on heal l'allié avec le moin de pv si on est soigneur ou celui qui a le plus d'ennemi adjacent si tt les points de vie sont supérieur 25
    int x_low,y_low,pv_low=-1;
    int tab_ennemi_ont_portee[N][M];
    for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
        tab_ennemi_ont_portee[i][j]=0;
      }
    }
    for(int i=0;i<N;i++){ //minimum de pv des alliés
      for(int j=0;j<M;j++){
        if(terrain[i][j].attaque==1 && pv_low==-1){
          x_low=i;
          y_low=j;
          pv_low=terrain[i][j].piece->pdv;
        }else if(terrain[i][j].attaque==1 && pv_low>terrain[i][j].piece->pdv){
          x_low=i;
          y_low=j;
          pv_low=terrain[i][j].piece->pdv;
        }
      }
    }
    if(pv_low<=25){//soin si pv <= a 25

      combat(terrain,x_bot,y_bot,x_low,y_low,joueur_actu,tab,aff_deg,tab_info_bash,variable2);

    }else{ //sinon on heal l'allié avec le plus d'ennemi adjacent


//version OPTIMISE
      int max_portee_ennemi=1;
      for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
          if(terrain[i][j].piece && terrain[i][j].piece->joueur!=joueur_actu && terrain[i][j].piece->portee>max_portee_ennemi){
            max_portee_ennemi=terrain[i][j].piece->portee+1; //+ 1 au cas ou la piece serais sur un montagne
          }
        }
      }
      for(int a=x_bot-max_portee_ennemi-terrain[x_bot][y_bot].piece->portee-1;a<x_bot-max_portee_ennemi+terrain[x_bot][y_bot].piece->portee+1 && a<N;a++){
        for(int b=y_bot-max_portee_ennemi-terrain[x_bot][y_bot].piece->portee-1;b<y_bot-max_portee_ennemi+terrain[x_bot][y_bot].piece->portee+1 && b<M;b++){
          if(a>=0 && b>=0 && terrain[a][b].piece && terrain[a][b].piece->joueur!=joueur_actu){
            pathfinding_combat(terrain,a,b,terrain[a][b].piece->joueur);
            for(int compteur=a-terrain[a][b].piece->portee-1; compteur<a+terrain[a][b].piece->portee+1 && compteur<N;compteur++){
              for(int compteur2=b-terrain[a][b].piece->portee-1; compteur2<b+terrain[a][b].piece->portee+1 && compteur2<M;compteur2++){
                if(compteur>=0 && compteur2>=0 && terrain[compteur][compteur2].attaque==1){
                  tab_ennemi_ont_portee[compteur][compteur2]+=1;
                }
              }
            }
          }
        }
      }
      int max_atk=0,x=x_bot,y=y_bot;
      pathfinding_combat(terrain,x_bot,y_bot,joueur_actu);
      for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
          if(terrain[i][j].attaque==1 && tab_ennemi_ont_portee[i][j]>max_atk){
            max_atk=tab_ennemi_ont_portee[i][j];
            x=i;
            y=j;
          }
        }
      }
      combat(terrain,x_bot,y_bot,x,y,joueur_actu,tab,aff_deg,tab_info_bash,variable2);
    }

//FIN VERSION OPTIMISE

      //version NON OPTIMISE
      /*for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
          if(terrain[i][j].piece && terrain[i][j].piece->joueur!=joueur_actu){
            pathfinding_combat(terrain,i,j,terrain[i][j].piece->joueur);  //xbot ou i j ?
            for(int compteur=0;compteur<N;compteur++){  //a optimiser pour grille plus grande
              for(int compteur2=0;compteur2<M;compteur2++){
                if(terrain[compteur][compteur2].attaque==1){
                  tab_ennemi_ont_portee[compteur][compteur2]+=1;
                }
              }
            }
          }
        }
      }
      int max_atk=0,x=x_bot,y=y_bot;
      pathfinding_combat(terrain,x_bot,y_bot,joueur_actu);
      for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
          if(terrain[i][j].attaque==1 && tab_ennemi_ont_portee[i][j]>max_atk){
            max_atk=tab_ennemi_ont_portee[i][j];
            x=i;
            y=j;
          }
        }
      }
      combat(terrain,x_bot,y_bot,x,y,joueur_actu,tab,aff_deg,tab_info_bash,variable2);
    }*/

  }else{ //cas ou ce n'est pas un soigneur
    int x_low,y_low,pv_low=-1;
    for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
        if(terrain[i][j].attaque==1 && pv_low==-1){
          x_low=i;
          y_low=j;
          pv_low=terrain[i][j].piece->pdv;
        }else if(terrain[i][j].attaque==1 && pv_low>terrain[i][j].piece->pdv){
          x_low=i;
          y_low=j;
          pv_low=terrain[i][j].piece->pdv;
        }
      }
    }
    combat(terrain,x_bot,y_bot,x_low,y_low,joueur_actu,tab,aff_deg,tab_info_bash,variable2); //attaque l'ennemi avec le moin de pv
  }

}





void depla_allie_plus_proche(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu,joueurs_t tab[J],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]){
  //calcule de l'allie le plus proche et sauvegarde de ses position x et y
  int x_allie,y_allie;
  int distance_allie=-1;
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(terrain[i][j].piece && terrain[i][j].piece->joueur==joueur_actu && distance_allie==-1 && (x_bot!=i || y_bot!=j)){
        x_allie=i;
        y_allie=j;
        distance_allie=(abs(x_bot-x_allie)+abs(y_bot-y_allie));
      }else if(terrain[i][j].piece && terrain[i][j].piece->joueur==joueur_actu && distance_allie>(abs(x_bot-i)+abs(y_bot-j)) && (x_bot!=i || y_bot!=j)){
        x_allie=i;
        y_allie=j;
        distance_allie=(abs(x_bot-x_allie)+abs(y_bot-y_allie));
      }
    }
  }

  //deplacement au plus pret
  move_longue_range(terrain,x_bot,y_bot,x_allie,y_allie,joueur_actu,tab,tab_info_bash,variable2);
}




void depla_ennem_plus_proche(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu,joueurs_t tab[J],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]){
  //calcule de l'ennemi le plus proche et sauvegarde de ses position x et y
  int x_allie,y_allie;
  int distance_allie=-1;
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(terrain[i][j].piece && terrain[i][j].piece->joueur!=joueur_actu && distance_allie==-1 && (x_bot!=i || y_bot!=j)){
        x_allie=i;
        y_allie=j;
        distance_allie=(abs(x_bot-x_allie)+abs(y_bot-y_allie));
      }else if(terrain[i][j].piece && terrain[i][j].piece->joueur!=joueur_actu && distance_allie>(abs(x_bot-i)+abs(y_bot-j))&& (x_bot!=i || y_bot!=j)){
        x_allie=i;
        y_allie=j;
        distance_allie=(abs(x_bot-x_allie)+abs(y_bot-y_allie));
      }
    }
  }

  //deplacement au plus pret
  move_longue_range(terrain,x_bot,y_bot,x_allie,y_allie,joueur_actu,tab,tab_info_bash,variable2);

}




void move_longue_range(case_t terrain[N][M], int x, int y,int x_dest,int y_dest,int joueur_actu,joueurs_t tab[J],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]){
  int deplacement[N][M];
  int i,j;
  int cpt;
    //initialisation des deplacements possibles

  for (i=0;i<N;i++){//parcours du terrain
      for(j=0;j<M;j++){
          if ((terrain[i][j].type==5) || terrain[i][j].piece!=NULL){
              deplacement[i][j]=-1;
          }//case d'eau deplacement impossible
          else{
            deplacement[i][j]=0;
          }
      }


  }
  deplacement[x][y]=1;//case ou se trouve la piece
  deplacement[x_dest][y_dest]=0;//case ou se trouve la piece a rejoindre

  int possible=1;
  for(cpt=1;deplacement[x_dest][y_dest]==0 && possible!=0;cpt++){
      possible=0;
      for (i=0;i<N;i++){//parcours du terrain
          for(j=0;j<M;j++){
              if (deplacement[i][j]==cpt){
                  if(i+1<N && deplacement[i+1][j]==0){
                      deplacement[i+1][j]=cpt+1;
                      possible++;
                  }
                  if(i-1>=0 && deplacement[i-1][j]==0){
                      deplacement[i-1][j]=cpt+1;
                      possible++;
                  }
                  if(j+1<M && deplacement[i][j+1]==0){
                      deplacement[i][j+1]=cpt+1;
                      possible++;
                  }
                  if(j-1>=0 && deplacement[i][j-1]==0){
                      deplacement[i][j-1]=cpt+1;
                      possible++;
                  }

              }

          }
      }
  }

  fprintf(stderr,"avant alea valeur dest = %d\n",deplacement[x_dest][y_dest]);
  int a=x_dest;
  int b=y_dest;
  int var=deplacement[x_dest][y_dest];
  pathfinding(terrain,x,y);
  while(terrain[a][b].deplacement!=1){
    if(a+1<N && deplacement[a+1][b]==var-1){
      a++;
      var--;
    }
    else if(a-1>=0 && deplacement[a-1][b]==var-1){
      a--;
      var--;
    }
    else if(b+1<M && deplacement[a][b+1]==var-1){
      b++;
      var--;
    }
    else if(b-1>=0 && deplacement[a][b-1]==var-1){
      b--;
      var--;
    }else{
      move_alea(terrain,x,y,joueur_actu,tab,tab_info_bash,variable2);
      return;
    }
  }

  move(terrain,a,b,joueur_actu,tab,tab_info_bash,variable2);

}

void move_alea(case_t terrain[N][M],int x,int y, int joueur,joueurs_t tab[J],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]){
  pathfinding(terrain,x,y);
  int ini=0,x_dest,y_dest;
  for (int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(terrain[i][j].deplacement==1 && ini==0){
        x_dest=i;
        y_dest=j;
        ini=1;
      }else if(terrain[i][j].deplacement==1 && rand()%((N+M)/2)){
        x_dest=i;
        y_dest=j;
      }
    }
  }
  if(ini!=0){
    move(terrain,x_dest,y_dest,joueur,tab,tab_info_bash,variable2);
  }else{
    fprintf(stderr,"AUCUNE ACTION POSSIBLE");
  }
}




void IA_blockage_direction(case_t terrain[N][M],int x_def,int y_def,int joueur_actu){
  int pos_block[N][M];
  int cpt=1;
  //init matrice a 0
  for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
        pos_block[i][j]=-2;
      }
  }
  pos_block[x_def][y_def]=0;
  //diagonales a -1
  while (x_def-cpt>=0 && y_def+cpt<M){
      pos_block[x_def-cpt][y_def+cpt]=-1;
      cpt++;
  }
  cpt=1;
  while (x_def+cpt<N && y_def+cpt<N){
      pos_block[x_def+cpt][y_def+cpt]=-1;
      cpt++;
  }
  cpt=1;
  while (x_def+cpt<N && y_def-cpt>=0){
      pos_block[x_def+cpt][y_def-cpt]=-1;
      cpt++;
  }
  cpt=1;
  while (x_def-cpt>=0 && y_def-cpt>=0){
      pos_block[x_def-cpt][y_def-cpt]=-1;
      cpt++;
  }
  for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
          if ((pos_block[i][j-1]==-1 || pos_block[i][j-1]==0 || pos_block[i][j-1]==1) && j>y_def)
              pos_block[i][j]=1;
      }
  }
  for(int i=0;i<N;i++){
      for(int j=M-1;j>=0;j--){
          if ((pos_block[i][j+1]==-1 || pos_block[i][j+1]==0 || pos_block[i][j+1]==2) && j<y_def)
            pos_block[i][j]=2;
      }
  }
  for(int j=0;j<M;j++){
      for(int i=0;i<N;i++){
          if ((pos_block[i-1][j]==-1 || pos_block[i-1][j]==0 || pos_block[i-1][j]==3) && i>x_def)
              pos_block[i][j]=3;
      }
  }
  for(int j=0;j<M;j++){
      for(int i=0;i<N;i++){
          if (pos_block[i][j]==-2)
              pos_block[i][j]=4;
      }
  }
  //on compte le nb d'unité dans chaque direction, on ignore les diagonnales car une unité sur n'ipmporte quel diagonnale fera toujours 50% du block
  int nb_nord=0,nb_sud=0,nb_ouest=0,nb_est=0;

  for (int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(terrain[i][j].piece && terrain[i][j].piece->joueur != joueur_actu){
        if(pos_block[i][j]==1){
          nb_nord++;
        }else if(pos_block[i][j]==2){
          nb_sud++;
        }else if(pos_block[i][j]==3){
          nb_ouest++;
        }else if(pos_block[i][j]==4){
          nb_est++;
        }
      }
    }
  }

  //on se tourne vers la meilleur direction
  if(nb_nord>=nb_sud && nb_nord>=nb_ouest && nb_nord>=nb_est){
    terrain[x_def][y_def].piece->direction=haut;

  }else if(nb_sud>=nb_nord && nb_sud>=nb_ouest && nb_sud>=nb_est){
    terrain[x_def][y_def].piece->direction=bas;

  }else if(nb_ouest>=nb_sud && nb_ouest>=nb_nord && nb_ouest>=nb_est){
    terrain[x_def][y_def].piece->direction=gauche;

  }else{
    terrain[x_def][y_def].piece->direction=droite;
  }

}


void pathfinding(case_t terrain[N][M], int x, int y){
  int deplacement[N][M];
  int i,j;
  int cpt;
    //initialisation des deplacements possibles
    for (i=0;i<N;i++){//parcours du terrain
      for(j=0;j<M;j++){
        terrain[i][j].deplacement=0;
      }
    }


    for (i=0;i<N;i++){//parcours du terrain
        for(j=0;j<M;j++){
            if (terrain[i][j].type==5 || terrain[i][j].piece!=NULL){
                deplacement[i][j]=-1;
            }//case d'eau deplacement impossible
            else{
              deplacement[i][j]=0;
            }
        }


    }
    deplacement[x][y]=1;//case ou se trouve la piece

    int depla;
    //désavantage de deplacement qd le deplacement commence sur une case foret ou montagne.
    if(terrain[x][y].type==6 || terrain[x][y].type==7){
      depla=terrain[x][y].piece->deplacement -1;
    }else{
      depla=terrain[x][y].piece->deplacement;
    }


    for(cpt=1;cpt<=depla;cpt++){//tant qu'il y a des point de deplacement
        for (i=0;i<N;i++){//parcours du terrain
            for(j=0;j<M;j++){
                if (deplacement[i][j]==cpt){
                    if(i+1<N && deplacement[i+1][j]==0)
                        deplacement[i+1][j]=cpt+1;
                    if(i-1>=0 && deplacement[i-1][j]==0)
                        deplacement[i-1][j]=cpt+1;
                    if(j+1<M && deplacement[i][j+1]==0)
                        deplacement[i][j+1]=cpt+1;
                    if(j-1>=0 && deplacement[i][j-1]==0)
                        deplacement[i][j-1]=cpt+1;

                }

            }
        }
    }

    for (i=0;i<N;i++){//parcours du terrain
        for(j=0;j<M;j++){
            if(deplacement[i][j]>1){
              terrain[i][j].deplacement=1;
            }
        }
    }

}






void move(case_t terrain[N][M],int x,int y,int joueur,joueurs_t tab[J],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]){
  char variable[80];
  if(tab[joueur].pts_action_actu>0){
    if(terrain[x][y].deplacement==1){
      for(int compteur=0;compteur<N;compteur++){
        for(int compteur2=0;compteur2<M; compteur2++){
          if(terrain[compteur][compteur2].piece && terrain[compteur][compteur2].piece->select==1 && terrain[compteur][compteur2].piece->joueur==joueur){

            sprintf(variable, "| Unite de Joueur %d en %d/%d se deplace vers %d/%d",joueur,compteur,compteur2,x,y);
				    ajouter_ligne_bash(variable,tab_info_bash,deplacement,variable2);


            terrain[x][y].piece=malloc(sizeof(piece_t));
            terrain[x][y].piece->classe = terrain[compteur][compteur2].piece->classe;
            terrain[x][y].piece->pdv = terrain[compteur][compteur2].piece->pdv;
            terrain[x][y].piece->puissance = terrain[compteur][compteur2].piece->puissance;
            terrain[x][y].piece->armure = terrain[compteur][compteur2].piece->armure;
            terrain[x][y].piece->block = terrain[compteur][compteur2].piece->block;
            terrain[x][y].piece->portee = terrain[compteur][compteur2].piece->portee;
            terrain[x][y].piece->deplacement = terrain[compteur][compteur2].piece->deplacement;
            terrain[x][y].piece->select = terrain[compteur][compteur2].piece->select;
            terrain[x][y].piece->joueur = terrain[compteur][compteur2].piece->joueur;
            terrain[x][y].piece->direction = terrain[compteur][compteur2].piece->direction;
            terrain[x][y].piece->kil = terrain[compteur][compteur2].piece->kil;
            terrain[x][y].piece->frame = terrain[compteur][compteur2].piece->frame;
            terrain[x][y].piece->frame_interface = terrain[compteur][compteur2].piece->frame_interface;
            terrain[x][y].piece->start_anim = terrain[compteur][compteur2].piece->start_anim;


            free(terrain[compteur][compteur2].piece);
            terrain[compteur][compteur2].piece=NULL;

            terrain[x][y].piece->select=1;

            tab[joueur].pts_action_actu--;

            return;
          }
        }
      }

    }
  }
}




void ajouter_ligne_bash(char * variable,bash_t tab_info_bash[TAILLE_TAB_BASH],typeTxt_t c,char variable2[80]){
  if(!strcmp(tab_info_bash[0].txt,"PARTIE INITIALISE")){
    FILE * fp=fopen(variable2,"w");
    fprintf(fp,"MAP : %d x %d || Joueurs : %d || UNITEE : %d par joueurs\n",N,M,J,NB_UNITE);
    fclose(fp);
  }
  FILE * fp=fopen(variable2,"a");
  fprintf(fp,variable);
  fprintf(fp,"\n");
  fclose(fp);


  for(int j=TAILLE_TAB_BASH-1;j>0;j--){
    if(tab_info_bash[j-1].pos_y!=0){
      tab_info_bash[j].pos_y=tab_info_bash[j-1].pos_y-25; ///ICI POUR PLACE ENTRE LES LIGNE DE BASH (-TAILLE ENTRE LES LIGNES).
      tab_info_bash[j].couleur=tab_info_bash[j-1].couleur;
      strcpy(tab_info_bash[j].txt,tab_info_bash[j-1].txt);
    }
  }
  tab_info_bash[0].pos_y=265;
  tab_info_bash[0].couleur=c;
  strcpy(tab_info_bash[0].txt,variable);
  return;
}



void ajouter_degat_txt(char txt[20],degatx_t aff_deg[AFF_DEG],int x,int y,int c){
	for(int i=0;i<AFF_DEG;i++){
		if(aff_deg[i].time<=0){
      strcpy(aff_deg[i].txt,txt);
      aff_deg[i].pos_x=x;
      aff_deg[i].pos_y=y;
      aff_deg[i].c=c;
      aff_deg[i].time=100;
      return;
    }
	}
}



void clean_degat_txt(degatx_t aff_deg[AFF_DEG]){
  for(int i=0;i<AFF_DEG;i++){
		if(aff_deg[i].time<=0 && !vide(aff_deg)){
      for(int j=i;j<(AFF_DEG)-1;j++){
        aff_deg[j].time=aff_deg[j+1].time;
        aff_deg[j].pos_x=aff_deg[j+1].pos_x;
        aff_deg[j].pos_y=aff_deg[j+1].pos_y;
        aff_deg[j].c=aff_deg[j+1].c;
        strcpy(aff_deg[j].txt,aff_deg[j+1].txt);
      }
    }else{
      if(strcmp(aff_deg[i].txt,"MORT")){
        aff_deg[i].time-=10;
        aff_deg[i].pos_x+=(aff_deg[i].time/10);
        aff_deg[i].pos_y-=(aff_deg[i].time/10);
      }else{
        aff_deg[i].time-=10;
        aff_deg[i].pos_y-=(aff_deg[i].time/15);
      }
    }
  }
}

int vide(degatx_t aff_deg[AFF_DEG]){
  for(int i=0;i<AFF_DEG;i++){
    if(aff_deg[i].time>0)
      return 0;
  }
  return 1;
}


/*A FAIRE

void camera_sur_allie(){



}

*/
