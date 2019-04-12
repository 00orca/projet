#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "interface.h"


//facteurs changeant la méthode que les bots utilise pour jouer
#define DEFENSIF 3 //nb de piece qui peuvent attaquer le bot a patir duquel il jouera cet piece en mode defensif
#define AGRESSIF 2 //nb de coup (en comptant l'armure) sans prendre en compte le block qui pouraient tuer un ennemi a porter (en comptant les allié a porte aussi)
#define MOVEMENT 2 //nb d'allié qu'une piece essayera de garder a coté d'elle, un pretre vaut pour 2 piece dans le calcule



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



typedef enum {
    knight=1,scout,priest,magician,faucheuse,ange
}classe_t;

typedef enum{
    haut=1,bas,gauche,droite
}dir_t;
#pragma pack(1)
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
    int kil;
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
#pragma pack(0)

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



typedef enum {
    info=1,degat,soins,ineficace,deplacement,kil
}typeTxt_t;



typedef struct bash_s{
  char txt[80];
  int pos_y;
  typeTxt_t couleur;
}bash_t;




/*Fonction pour creer les pieces*/
piece_t * init_piece(classe_t classe,int id_joueur);
/*Renvoi 1 si la piece passée en parametre existe*/
int piece_existe(piece_t * piece);
/*Detruit une piece*/
int destruction_piece(piece_t * piece);

/*Affiche les chemins possible pour la piece selectionnée dont les coordonnées sont passée en param*/


/*effectue le calcul des dommages*/

SDL_Rect afficher_anim(int compteur_anim,classe_t classe,case_t terrain[N][M],int compteur,int compteur2,int inter); //return un rectangle pour afficher la bonne frame d'animation



void initialisation_principale(int bordure,SDL_Window * pWindow,int * largeur, int * hauteur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],case_t terrain[N][M],char variable2[80]);
void affichage_principale(SDL_Renderer *renderer,SDL_Window* pWindow,int bordure,int * largeur,int * hauteur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],case_t terrain[N][M],int joueur_actu,image_t image[Z],int compteur_anim,int nb_joueur_restant,int compteur_tour,int frame_anim_montre,int jour_nuit,char variable2[80]);


void carte_valide(case_t terrain[N][M]); //corrige la map pour qu'elle ne possède pas de zone inaccessible.

int zone_libre(case_t terrain[N][M],int x, int y,int nb_place);
int case_libre(case_t terrain[N][M],int x,int y);

int reste_ennemi(case_t terrain[N][M],int joueur_actu); //retourne le nb d'ennemi restant en jeu
int reste_allie(case_t terrain[N][M],int joueur_actu); //retourne le nb d'allié restant en jeu

int allie_adjacent(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu); //revoie 1 si un allié est directement dans une des 4 cases adjacentes


void pathfinding_combat(case_t terrain[N][M], int x, int y,int joueur_actu); //remplis la grille de jeu (terrain[x][y].attaque= ?) selon si la case est apte a l'attaque d'un allié
int calc_block(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def); //retourne la valeur du block de la cible en fonction de la position de notre unité
void combat(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]); //systeme de combat
void soin(case_t terrain [N][M],int x_att, int y_att, int x_def,int y_def,int joueur,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]); //soigne un allié
void update_stats(case_t terrain[N][M],int x,int y,int joueur_actu,joueurs_t tab[J]); //amélioration des stats apres un kill en fonction de la classe.
int a_portee(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu); //nb ennemis a porte (via pathfinding combat)



void depla_atk_mov(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu,joueurs_t tab[J],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]); //IA de deplacement des bots
void centrer_camera(case_t terrain[N][M],int x,int y,int largeur,int hauteur); //centre la caméra sur une case de la grille
void depla_allie_plus_proche(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu,joueurs_t tab[J],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]); //deplacement au plus proche d'un allié potentiellement en dehors de la zone de deplacement possible de l'unitée se deplaçant(utilise move_longue_range)
void depla_ennem_plus_proche(case_t terrain[N][M],int x_bot,int y_bot,int joueur_actu,joueurs_t tab[J],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]); //deplacement au plus proche d'un ennemi potentiellement en dehors de la zone de deplacement possible de l'unitée se deplaçant(utilise move_longue_range)
void IA_blockage_direction(case_t terrain[N][M],int x_def,int y_def,int joueur_actu); //met le blockage de l'unité en x_def et y_def dans la position la plus intéressante

void move_longue_range(case_t terrain[N][M], int x, int y,int x_dest,int y_dest,int joueur_actu,joueurs_t tab[J],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]); //pathfinding et deplacement utilisé pour faire le déplacement et trouver la coordonné pour se rapprocher au max de la cible
void move_alea(case_t terrain[N][M],int x,int y, int joueur,joueurs_t tab[J],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]); //deplacement aléatoire parmis les choix de déplacement possible
void attaquer_meilleur_cible(case_t terrain[N][M],int x_bot,int y_bot,int nb_ennemies_portee,int joueur_actu,joueurs_t tab[J],degatx_t aff_deg[AFF_DEG],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]); //IA d'attaque des bots

void pathfinding(case_t terrain[N][M], int x, int y); //remplis la grille de jeu (terrain[x][y].deplacement= ?) selon si la case est apte au deplacement d'un allié SELECTIONNE
void move(case_t terrain[N][M],int x,int y, int joueur,joueurs_t tab[J],bash_t tab_info_bash[TAILLE_TAB_BASH],char variable2[80]); //deplacement vers une coordonné x et y de la grille


void ajouter_ligne_bash(char * variable,bash_t tab_info_bash[TAILLE_TAB_BASH],typeTxt_t c,char variable2[80]);

void ajouter_degat_txt(char txt[20],degatx_t aff_deg[AFF_DEG],int x,int y,int c); //ajoute un texte dans le tableau d'anim des dégats, blocks et kills
void clean_degat_txt(degatx_t aff_deg[AFF_DEG]); //nettoie le tableau d'anim de texte des degats,blocks, kills etc
int vide(degatx_t aff_deg[AFF_DEG]); //regarde si le tableau d'affichage des dégats sous forme d'animation est vide ou non

int nombre_classe(case_t terrain[N][M],int joueur_actu,classe_t classe);
void rem_piece_joueur(case_t terrain[N][M],int joueur_actu);


/////////////PARTIE RESEAU////////////
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
//#define SERVEURNAME "192.168.1.106" // adresse IP de mon serveur
#define SERVEURNAME "127.0.0.1" // adresse IP de mon serveur

void quitter(int to_server_socket);
void fin(int sig);
int hostname_to_ip(char * hostname , char* ip);
void fin_connexion(int server_sock);
void view_ip();
