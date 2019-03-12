#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define N 15
#define M 15
#define J 3

/**
* \file piece.c
* \brief Structure pieces.
*\author Willhem Liban
*\version 0.5
*\date 01 mars 2019
*/

typedef enum {
    knight=1,scout,priest,magician
}classe_t;


typedef struct piece_s{
    classe_t classe;
    int pdv; //point de vie
    int puissance;
    int armure;
    int block; //pourcentage de chance de bloquer
    int portee; //portée de l'attaque
    int deplacement; //nombre de case de mouvement
    int select;
    int joueur;
}piece_t;




typedef struct case_s{
	int type;				//type d'une case
	SDL_Texture *type_case;	//texture de cette case
	int climat;
	piece_t *piece;		//piece sur cette case
	int deplacement;  // 1 -> droit de se deplacer , 0pas le droit de se deplacer
	int xImg; // ccordonné reel de l'image
	int yImg;
	int x1; // coordonné du losange représentant une case(pour gerer les coordonnées du clic souris)
	int y1;
	int x2;
	int y2;
  int x3;
	int y3;
	int x4;
	int y4;
}case_t;


typedef struct joueurs_s{
  int pts_action_max;
  int pts_action_actu;
  int nb_unite;
  int id_joueur;

}joueurs_t;

piece_t * init_piece(classe_t classe,int id_joueur);
int piece_existe(piece_t * piece);
int destruction_piece(piece_t * piece);
void pathfinding(case_t terrain[N][M], int x, int y);
void move(case_t terrain[N][M],int x,int y, int joueur,joueurs_t tab[J]);
