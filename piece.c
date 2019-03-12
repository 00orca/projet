#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "piece.h"

/**
* \file piece.c
* \brief Fonctions operants sur les pieces.
*\author Willhem Liban
*\version 0.5
*\date 01 mars 2019
*/


piece_t * init_piece(classe_t classe,int id_joueur){
    piece_t * piece=malloc(sizeof(piece_t));
    switch (classe){
        case knight:
            piece->classe = knight;
            piece->pdv=50;
            piece->puissance = 22;
            piece->armure=25;
            piece->block=80;
            piece->portee=1;
            piece->deplacement=2;
            piece->select=0;
            piece->joueur=id_joueur;
            break;
        case scout:
            piece->classe = scout;
            piece->pdv=40;
            piece->puissance = 18;
            piece->armure=8;
            piece->block=60;
            piece->portee=6;
            piece->deplacement=4;
            piece->select=0;
            piece->joueur=id_joueur;
            break;
        case priest:
            piece->classe = priest;
            piece->pdv=24;
            piece->puissance = 12;
            piece->armure=0;
            piece->block=0;
            piece->portee=3;
            piece->deplacement=3;
            piece->select=0;
            piece->joueur=id_joueur;
            break;
        case magician:
            piece->classe = magician;
            piece->pdv=28;
            piece->puissance = 24;
            piece->armure=0;
            piece->block=20;
            piece->portee=4;
            piece->deplacement=4;
            piece->select=0;
            piece->joueur=id_joueur;
            break;
        default: printf("Cette classe n'existe pas.\n");
    }
    return (piece);
}

int piece_existe(piece_t * piece){
    return(!(piece==NULL));
}

void afficher_piece(piece_t * piece){
    if (piece_existe(piece)){
        printf("classe :");
        switch(piece->classe){
            case knight:
                printf("Knight\n");
                break;
            case scout:
                printf("Scout\n");
                break;
            case priest:
                printf("Priest\n");
                break;
            case magician:
                printf("Magician\n");
                break;
        }
        printf("lp : %d\n", piece->pdv);
        printf("pui : %d\n", piece->puissance);
        printf("armure : %d\n", piece->armure);
        printf("block : %d\n", piece->block);
        printf("portee : %d\n",piece->portee);
        printf("deplacement : %d\n", piece->deplacement);
    }
    else
        printf("Pas de piece a afficher.\n");
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




int move(case_t terrain[N][M],int x,int y,piece_t *piece){
  if(terrain[x][y].deplacement==1){
    terrain[x][y].piece=piece;
    destruction_piece(piece);
    return 1;
  }
  return 0;
}
