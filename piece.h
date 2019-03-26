#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


//facteurs changeant la méthode que les bots utilise pour jouer
#define DEFENSIF 3 //nb de piece qui peuvent attaquer le bot a patir duquel il jouera cet piece en mode defensif
#define AGRESSIF 2 //nb de coup (en comptant l'armure) sans prendre en compte le block qui pouraient tuer un ennemi a porter (en comptant les allié a porte aussi)
#define MOVEMENT 2 //nb d'allié qu'une piece essayera de garder a coté d'elle, un pretre vaut pour 2 piece dans le calcule


extern int J_HUMAIN;
extern int NB_UNITE;
extern int PTS_ACTION_MAX;

extern int VITESSE_JEU_BOT;

extern int AFF_DEG;

extern int PRESET;
extern int NB_CLASSE;
extern int N;
extern int M;
extern int J;


/*
* \file piece.c
* \brief Structure pieces.
*\author Willhem Liban
*\version 0.5
*\date 01 mars 2019
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
  int humain;
}joueurs_t;


typedef struct degatx_s{
  int pos_x;
  int pos_y;
  int time;
  int c; //noire =0 rouge =1 verte =2
  char txt[20];
}degatx_t;

/*Fonction pour creer les pieces*/
piece_t * init_piece(classe_t classe,int id_joueur);
/*Renvoi 1 si la piece passée en parametre existe*/
int piece_existe(piece_t * piece);
/*Detruit une piece*/
int destruction_piece(piece_t * piece);
/*Affiche les chemins possible pour la piece selectionnée dont les coordonnées sont passée en param*/
void pathfinding(case_t terrain[N][M], int x, int y);
void pathfinding_combat(case_t terrain[N][M], int x, int y,int joueur_actu);
/*effectue le calcul des dommages*/
int calc_block(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def);
void combat(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J],degatx_t aff_deg[N*M]);
void soin(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J],degatx_t aff_deg[N*M]);
void move(case_t terrain[N][M],int x,int y, int joueur,joueurs_t tab[J]);
void depla_atk_mov(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu,joueurs_t tab[J]);
void centrer_camera(case_t terrain[N][M],int x,int y,int largeur,int hauteur);
void ajouter_degat_txt(char txt[20],degatx_t aff_deg[AFF_DEG],int x,int y,int c);
void clean_degat_txt(degatx_t aff_deg[AFF_DEG]);
int vide(degatx_t aff_deg[AFF_DEG]);
