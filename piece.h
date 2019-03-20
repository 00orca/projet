#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#define N 20 //taille de la grille
#define M 20
#define J 5 //nb de joueur
#define PRESET 1 //1 pour generation alea, autre pour preset de carte via fichier
#define NB_CLASSE 5

/**
* \file piece.c
* \brief Fonctions operants sur les pieces.
*\author Willhem Liban, Eliot Lepoittevin
*\version 3.0
*\date 20 mars 2019
*/


/**
*\struct piece_s
*\brief Objet piece qui contient les statistiques d'une piece (unité qui combat)
*contient : les points de vie, la classe, la uissance, armure,block, portee, si oui ou non la piece est selectionnée, la direction dans laquelle est la piece et le joueur a qui la piece appartient
*/
/**
*\struct case_s
*\brief Objet qui represente une case, la piece qui est sur cette case, sa position et l'image qui lui corresond
*/
/**
*\struct joueurs_s
*\brief Objet qui represente un joueur avec ses points d'actions, le nombre d'unités qu'il possede.
*/
typedef enum {
    knight=1,scout,priest,magician,faucheuse
}classe_t;

typedef enum{
    haut=1,bas,gauche,droite
}dir_t;

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
    dir_t direction;
}piece_t;




typedef struct case_s{
	int type;				//type d'une case
	int climat;
	piece_t *piece;		//piece sur cette case
	int deplacement;  // 1 -> droit de se deplacer , 0pas le droit de se deplacer
	int attaque;    // 1 -> droit d'attaquer , 0 -> pas le droit d'attaquer
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

/**
*\fn piece_t * init_piece(classe_t classe,int id_joueur);
*\brief Fonction pour creer les pieces
*
*\fn int piece_existe(piece_t * piece)
*\brief Renvoi 1 si la piece passée en parametre existe
*
*\fn int destruction_piece(piece_t * piece)
*\brief Detruit une piece
*
*\fn void pathfinding(case_t terrain[N][M], int x, int y)
*\brief sert a connaitre les cases ou peut se deplacer une unité
*
*\fn void pathfinding_combat(case_t terrain[N][M], int x, int y,int joueur_actu)
*\brief sert a connaitre les cases ou peut attaquer une unité
*
*\fn int calc_block(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def)
*\brief calcul le block d'une unité en fonction d'ou elle est attaquée
*\fn void combat(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J])
*\brief calcul les dommages en cas de combat
*\fn void soin(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J])
*\brief ajoute les points de vie en cas de soin
*\fn void move(case_t terrain[N][M],int x,int y, int joueur,joueurs_t tab[J])
*\brief permet de deplacer les unités sur le terrain
*/
piece_t * init_piece(classe_t classe,int id_joueur);
int piece_existe(piece_t * piece);
/*Detruit une piece*/
int destruction_piece(piece_t * piece);
/*Affiche les chemins possible pour la piece selectionnée dont les coordonnées sont passée en param*/
void pathfinding(case_t terrain[N][M], int x, int y);
void pathfinding_combat(case_t terrain[N][M], int x, int y,int joueur_actu);
/*effectue le calcul des dommages*/
int calc_block(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def);
void combat(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J]);
void soin(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J]);
void move(case_t terrain[N][M],int x,int y, int joueur,joueurs_t tab[J]);
