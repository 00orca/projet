#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "piece.h"

/**
* \file piece.c
* \brief Fonctions operants sur les pieces.
*\author Willhem Liban, Eliot Lepoittevin
*\version 3.0
*\date 20 mars 2019
*/


piece_t * init_piece(classe_t classe,int id_joueur){
    int pos=((rand()%(4)) + 1);
    piece_t * piece=malloc(sizeof(piece_t));
    switch (classe){
        case knight:
            piece->classe = knight;
            piece->pdv=50;
            piece->puissance = 12;
            piece->armure=15;
            piece->block=60;
            piece->portee=1;
            piece->deplacement=2;
            piece->select=0;
            piece->joueur=id_joueur;
            piece->direction=pos;
            break;
        case scout:
            piece->classe = scout;
            piece->pdv=30;
            piece->puissance = 18;
            piece->armure=8;
            piece->block=30;
            piece->portee=6;
            piece->deplacement=4;
            piece->select=0;
            piece->joueur=id_joueur;
            piece->direction=pos;
            break;
        case priest:
            piece->classe = priest;
            piece->pdv=24;
            piece->puissance = 12;
            piece->armure=2;
            piece->block=10;
            piece->portee=3;
            piece->deplacement=3;
            piece->select=0;
            piece->joueur=id_joueur;
            piece->direction=pos;
            break;
        case magician:
            piece->classe = magician;
            piece->pdv=28;
            piece->puissance = 24;
            piece->armure=3;
            piece->block=20;
            piece->portee=4;
            piece->deplacement=4;
            piece->select=0;
            piece->joueur=id_joueur;
            piece->direction=pos;
            break;
        case faucheuse:
            piece->classe = faucheuse;
            piece->pdv=100;
            piece->puissance = 100;
            piece->armure=15;
            piece->block=40;
            piece->portee=4;
            piece->deplacement=10;
            piece->select=0;
            piece->joueur=id_joueur;
            piece->direction=pos;
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


    for(cpt=1;cpt<=terrain[x][y].piece->deplacement;cpt++){//tant qu'il y a des point de deplacement
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




void move(case_t terrain[N][M],int x,int y,int joueur,joueurs_t tab[J]){
  if(terrain[x][y].deplacement==1){
    for(int compteur=0;compteur<N;compteur++){
      for(int compteur2=0;compteur2<M; compteur2++){
        if(terrain[compteur][compteur2].piece && terrain[compteur][compteur2].piece->select==1 && terrain[compteur][compteur2].piece->joueur==joueur){


          terrain[x][y].piece=malloc(sizeof(piece_t));
          fprintf(stderr,"compteur compteur2 = %d\n",terrain[compteur][compteur2].piece->classe);
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


          //destruction_piece(terrain[compteur][compteur2].piece);
          free(terrain[compteur][compteur2].piece);
          terrain[compteur][compteur2].piece=NULL;

          terrain[x][y].piece->select=1;
          //pathfinding(terrain,x,y);

          tab[joueur].pts_action_actu--;

          return;
        }
      }
    }

  }
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

    for(cpt=1;cpt<=terrain[x][y].piece->portee;cpt++){//tant qu'il y a des point de la portée
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
    int i,j;
    int cpt=1;
    //init matrice a 0
    for(i=0;i<N;i++){
        for(j=0;j<M;j++)
            pos_block[i][j]=-2;
    }
    pos_block[x_def][y_def]=0;
    //diagonales a -1
    while (x_def-cpt>=0 && y_def+cpt<M){
        pos_block[x_def-cpt][y_def+cpt]=-1;
        cpt++;
    }
    cpt=1;
    while (x_def+cpt-1<N && y_def+cpt<N){
        pos_block[x_def+cpt][y_def+cpt]=-1;
        cpt++;
    }
    while (x_def+cpt<N && y_def-cpt>=0){
        pos_block[x_def+cpt][y_def-cpt]=-1;
        cpt++;
    }
    cpt=1;
    while (x_def-cpt>=0 && y_def-cpt>=0){
        pos_block[x_def-cpt][y_def-cpt]=-1;
        cpt++;
    }
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            if ((pos_block[i][j-1]==-1 || pos_block[i][j-1]==0 || pos_block[i][j-1]==1) && j>y_def)
                pos_block[i][j]=1;
        }
    }
    for(i=0;i<N;i++){
        for(j=M-1;j>=0;j--){
            if ((pos_block[i][j+1]==-1 || pos_block[i][j+1]==0 || pos_block[i][j-1]==2) && j<y_def)
            pos_block[i][j]=2;
        }
    }
    for(j=0;j<M;j++){
        for(i=0;i<N;i++){
            if ((pos_block[i-1][j]==-1 || pos_block[i-1][j]==0 || pos_block[i-1][j]==3) && i>x_def)
                pos_block[i][j]=3;
        }
    }
    for(j=0;j<M;j++){
        for(i=0;i<N;i++){
            if (pos_block[i][j]==-2)
                pos_block[i][j]=4;
        }
    }
    if(terrain[x_def][y_def].piece->direction==haut){
        if (pos_block[x_att][y_att]==2)
            return 0;
        else if (pos_block[x_att][y_att]==3||pos_block[x_att][y_att]==4||pos_block[x_att][y_att]==-1)
            return (terrain[x_def][y_def].piece->block/2);
        else
            return (terrain[x_def][y_def].piece->block);
    }
    else if(terrain[x_def][y_def].piece->direction==bas){
        if (pos_block[x_att][y_att]==1)
            return 0;
        else if (pos_block[x_att][y_att]==3||pos_block[x_att][y_att]==4||pos_block[x_att][y_att]==-1)
            return (terrain[x_def][y_def].piece->block/2);
        else
            return (terrain[x_def][y_def].piece->block);
    }
    else if(terrain[x_def][y_def].piece->direction==gauche){
        if (pos_block[x_att][y_att]==4)
            return 0;
        else if (pos_block[x_att][y_att]==1||pos_block[x_att][y_att]==2||pos_block[x_att][y_att]==-1)
            return (terrain[x_def][y_def].piece->block/2);
        else
            return (terrain[x_def][y_def].piece->block);
    }
    else if(terrain[x_def][y_def].piece->direction==droite){
        if (pos_block[x_att][y_att]==3)
            return 0;
        else if (pos_block[x_att][y_att]==1||pos_block[x_att][y_att]==2||pos_block[x_att][y_att]==-1)
            return (terrain[x_def][y_def].piece->block/2);
        else
            return (terrain[x_def][y_def].piece->block);
    }
    return -1;
}

void combat(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J]){
    if(terrain[x_att][y_att].piece->classe==priest){//soin si la piece selectionné est un pretre
        soin(terrain,x_att,y_att,x_def,y_def,joueur,tab);
        return;
    }
    srand(time(NULL));
    if(terrain[x_def][y_def].attaque==1){//si la piece attaquée est sur une case a portée !!!DOUTE!!!
      int blockd=(rand()%(100) + 1);//att bloquée ou non
      int blockage=calc_block(terrain,x_att,y_att,x_def,y_def);
      fprintf(stderr,"blockage : %d\n",blockage);
      if(blockd>blockage){
        terrain[x_def][y_def].piece->pdv-=terrain[x_att][y_att].piece->puissance-(terrain[x_def][y_def].piece->armure);//armure=absorption de dégats
        if(terrain[x_def][y_def].piece->pdv<=0){   //mort ou non de la piece ennemi
          tab[terrain[x_def][y_def].piece->joueur].nb_unite--;
          free(terrain[x_def][y_def].piece);
          terrain[x_def][y_def].piece=NULL;
        }
      }
      fprintf(stderr,"attaque reussie\n");
      tab[joueur].pts_action_actu--;
    }
    else
        printf("echec de l'attaque (hors de portée).\n");
}

void soin(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J]){
    if(terrain[x_def][y_def].attaque==1){
        terrain[x_def][y_def].piece->pdv+=terrain[x_att][y_att].piece->puissance;
        tab[joueur].pts_action_actu--;
      }
    else
        printf("echec du soin (hors de portée).\n");
}
