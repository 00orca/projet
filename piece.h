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
extern int VITESSE_ANIM;

extern int AFF_DEG;

extern int PRESET;
extern int NB_CLASSE;
extern int N;
extern int M;
extern int J;





typedef enum {
    knight=1,scout,priest,magician,faucheuse,ange
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
    int kill;
    int frame; //pour les images successive utile a l'animation
    int frame_interface;
    int start_anim;
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
void pathfinding(case_t terrain[N][M], int x, int y); //remplis la grille de jeu (terrain[x][y].deplacement= ?) selon si la case est apte au deplacement d'un allié SELECTIONNE
void pathfinding_combat(case_t terrain[N][M], int x, int y,int joueur_actu); //remplis la grille de jeu (terrain[x][y].attaque= ?) selon si la case est apte a l'attaque d'un allié
/*effectue le calcul des dommages*/
int calc_block(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def); //retourne la valeur du block de la cible en fonction de la position de notre unité
void combat(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG]); //systeme de combat
void soin(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG]); //soigne un allié
void move(case_t terrain[N][M],int x,int y, int joueur,joueurs_t tab[J]); //deplacement vers une coordonné x et y de la grille
void depla_atk_mov(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu,joueurs_t tab[J]); //IA de deplacement des bots
void centrer_camera(case_t terrain[N][M],int x,int y,int largeur,int hauteur); //centre la caméra sur une case de la grille
void ajouter_degat_txt(char txt[20],degatx_t aff_deg[AFF_DEG],int x,int y,int c); //ajoute un texte dans le tableau d'anim des dégats, blocks et kills
void clean_degat_txt(degatx_t aff_deg[AFF_DEG]); //nettoie le tableau d'anim de texte des degats,blocks, kills etc
int vide(degatx_t aff_deg[AFF_DEG]); //regarde si le tableau d'affichage des dégats sous forme d'animation est vide ou non
int a_portee(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu); //nb ennemis a porte (via pathfindçing combat)
void attaquer_meilleur_cible(case_t terrain[N][M],int x_bot,int y_bot,int nb_ennemies_portee,int joueur_actu,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG]); //IA d'attaque des bots
int reste_ennemi(case_t terrain[N][M],int joueur_actu); //retourne le nb d'ennemi restant en jeu
int reste_allie(case_t terrain[N][M],int joueur_actu); //retourne le nb d'allié restant en jeu
void depla_allie_plus_proche(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu,joueurs_t tab[J]); //deplacement au plus proche d'un allié potentiellement en dehors de la zone de deplacement possible de l'unitée se deplaçant(utilise move_longue_range)
void depla_ennem_plus_proche(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu,joueurs_t tab[J]); //deplacement au plus proche d'un ennemi potentiellement en dehors de la zone de deplacement possible de l'unitée se deplaçant(utilise move_longue_range)
int allie_adjacent(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu); //revoie 1 si un allié est directement dans une des 4 cases adjacentes
void move_longue_range(case_t terrain[N][M], int x, int y,int x_dest,int y_dest,int joueur_actu,joueurs_t tab[J]); //pathfinding et deplacement utilisé pour faire le déplacement et trouver la coordonné pour se rapprocher au max de la cible
void move_alea(case_t terrain[N][M],int x,int y, int joueur,joueurs_t tab[J]); //deplacement aléatoire parmis les choix de déplacement possible
void update_stats(case_t terrain[N][M],int x,int y,int joueur_actu,joueurs_t tab[J]); //amélioration des stats apres un kill en fonction de la classe.
void IA_blockage_direction(case_t terrain[N][M],int x_def,int y_def,int joueur_actu); //met le blockage de l'unité en x_def et y_def dans la position la plus intéressante
SDL_Rect afficher_anim(int compteur_anim,classe_t classe,case_t terrain[N][M],int compteur,int compteur2,int inter); //return un rectangle pour afficher la bonne frame d'animation
//void afficher_unitee(int compteur_anim,classe_t classe,case_t terrain[N][M],int compteur,int compteur2,int h,int w,char img[50],image_t image[Z],SDL_Renderer *renderer,float coefZoom,int anim,SDL_Rect imgDestRect); //affichage d'une unité sur la map en x et y de la grille
void carte_valide(case_t terrain[N][M]); //corrige la map pour qu'elle ne possède pas de zone inaccessible.
