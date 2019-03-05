#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* \file piece.c
* \brief Structure pieces.
*\author Willhem Liban
*\version 0.5
*\date 01 mars 2019
*/

typedef enum {
    knight, scout,priest,magician
}classe_t;
typedef struct piece_s{
    char * nom_classe;
    int pdv; //point de vie
    int puissance;
    int armure;
    int block; //pourcentage de chance de bloquer
    int portee; //portée de l'attaque
    int deplacement; //nombre de case de mouvement
}piece_t;


piece_t * init_piece(classe_t classe);
int piece_existe(piece_t * piece);
int destruction_piece(piece_t ** piece);
