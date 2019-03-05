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


piece_t * init_piece(classe_t classe){
    piece_t * piece=malloc(sizeof(piece_t));
    switch (classe){
        case 0:
            piece->nom_classe=malloc(sizeof(char)*strlen("knight")+1);
            piece->nom_classe = "knight";
            piece->pdv=50;
            piece->puissance = 22;
            piece->armure=25;
            piece->block=80;
            piece->portee=1;
            piece->deplacement=3;
            break;
        case 1:
            piece->nom_classe=malloc(sizeof(char)*strlen("scout")+1);
            piece->nom_classe = "scout";
            piece->pdv=40;
            piece->puissance = 18;
            piece->armure=8;
            piece->block=60;
            piece->portee=6;
            piece->deplacement=4;
            break;
        case 2:
            piece->nom_classe=malloc(sizeof(char)*strlen("priest")+1);
            piece->nom_classe = "priest";
            piece->pdv=24;
            piece->puissance = 12;
            piece->armure=0;
            piece->block=0;
            piece->portee=3;
            piece->deplacement=3;
            break;
        case 3:
            piece->nom_classe=malloc(sizeof(char)*strlen("magician")+1);
            piece->nom_classe = "magician";
            piece->pdv=28;
            piece->puissance = 24;
            piece->armure=0;
            piece->block=20;
            piece->portee=4;
            piece->deplacement=4;
        default: printf("erreur dans la création d'une piece\n");
    }
    return (piece);
}

int piece_existe(piece_t * piece){
    return(!(piece==NULL));
}

void afficher_piece(piece_t * piece){
    if (piece_existe(piece)){
        printf("classe : %s\n", piece->nom_classe);
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

int destruction_piece(piece_t ** piece){
    if(piece_existe(*piece)){
        //free((*piece)->nom_classe);
        free(*piece);
        (*piece)=NULL;
        return 1;
    }
    return 0;
}


int main(int argc, char const *argv[]) {
    piece_t * knight1 = NULL;
    printf("création.............\n");
    knight1=init_piece(0);
    printf("affichage............\n");
    afficher_piece(knight1);
    printf("destruction..........\n");
    destruction_piece(&knight1);
    printf("affichage............\n");
    afficher_piece(knight1);
    printf("fin\n");
    return 0;
}
