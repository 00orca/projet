#ifndef GRILLE_H
#define GRILLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "piece.h"
#include "logs.h"
#include "interface.h"


extern int J_HUMAIN;
extern int NB_UNITE;
extern int ESPACE_GEN;
extern int PTS_ACTION_MAX;

extern int VITESSE_JEU_BOT;
extern int VITESSE_ANIM;

extern int AFF_DEG;
extern int TAILLE_TAB_BASH;

extern int PRESET;
extern int PRESET_U;
extern int NB_CLASSE;
extern int N;
extern int M;
extern int J;
extern int BASH_SCROLL_SPEED;
extern int DURE_JOUR_NUIT;
extern int NB_MAX_PRIEST;
extern int ISO;
extern int NB_BLOCK;
extern int PDV_BLOCK;
extern float COEF_AFFICHAGE;



typedef struct case_s{
	int type;				//type d'une case
	int climat;
	int est_block;
	int pdv_block;
	int block_allie;
	int block_sel;
	piece_t *piece;		//piece sur cette case
	int deplacement;  // 1 -> droit de se deplacer , 0pas le droit de se deplacer
	int attaque;    // 1 -> droit d'attaquer , 0 -> pas le droit d'attaquer
	int block;
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
	int nb_block;
}joueurs_t;





void initialisation_principale_iso(int bordure,SDL_Window * pWindow,int * largeur, int * hauteur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],case_t terrain[N][M],char variable2[80]);
void affichage_principale_iso(SDL_Renderer *renderer,SDL_Window* pWindow,int bordure,int * largeur,int * hauteur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],case_t terrain[N][M],int joueur_actu,image_t image[Z],int compteur_anim,int nb_joueur_restant,int compteur_tour,int frame_anim_montre,int jour_nuit,char variable2[80],int compteur_bouton_cam);
void initialisation_principale(int bordure,SDL_Window * pWindow,int * largeur, int * hauteur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],case_t terrain[N][M],char variable2[80]);
void affichage_principale(SDL_Renderer *renderer,SDL_Window* pWindow,int bordure,int * largeur,int * hauteur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],case_t terrain[N][M],int joueur_actu,image_t image[Z],int compteur_anim,int nb_joueur_restant,int compteur_tour,int frame_anim_montre,int jour_nuit,char variable2[80],int compteur_bouton_cam);


void carte_valide(case_t terrain[N][M]); //corrige la map pour qu'elle ne possède pas de zone inaccessible.

int zone_libre(case_t terrain[N][M],int x, int y,int nb_place);
int case_libre(case_t terrain[N][M],int x,int y);

int reste_ennemi(case_t terrain[N][M],int joueur_actu); //retourne le nb d'ennemi restant en jeu
int reste_allie(case_t terrain[N][M],int joueur_actu); //retourne le nb d'allié restant en jeu

int allie_adjacent(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu); //revoie 1 si un allié est directement dans une des 4 cases adjacentes


int nombre_classe(case_t terrain[N][M],int joueur_actu,classe_t classe);
void rem_piece_joueur(case_t terrain[N][M],int joueur_actu);


void save(case_t terrain[N][M],int compteur_tour,int joueur_actu,joueurs_t tab[J]);
SDL_Rect afficher_anim(int compteur_anim,classe_t classe,case_t terrain[N][M],int compteur,int compteur2,int inter); //return un rectangle pour afficher la bonne frame d'animation

void pathfinding_block(case_t terrain[N][M],int joueur_actu);
void reset_block(case_t terrain[N][M]);
void poser_block(case_t terrain[N][M],int compteur,int compteur2,int joueur_actu,joueurs_t tab[J],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]);


#endif
