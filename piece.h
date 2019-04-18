/**
* \file piece.h
* \brief Fonctions priitives sur les piece_t et structure de donnée.
*\author Willhem Liban
*\version 1
*\date 12 avril 2019
*/
#ifndef PIECE_H
#define PIECE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


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
extern float COEF_AFFICHAGE;
extern int TOUR_EVOL_FORET;
extern int CHANCE_EVOL;
extern int PTS_ACTION_UNI;



typedef enum {
    knight=1,scout,priest,magician,faucheuse,ange
}classe_t;

typedef enum{
    haut=1,bas,gauche,droite
}dir_t;
/**
* \struct piece_s
* \brief représente une unité et contient ses statistiques.
*/
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
    int pts_action_max;		//point d'action maximal de l'unité
    int pts_action_actu;	//point d'action actuel de l'unité
}piece_t;

/**
* \fn piece_t * init_piece(classe_t classe,int id_joueur)
* \brief Fonction pour creer les pieces.
*/
/**
* \fn int piece_existe(piece_t * piece)
* \brief Renvoi 1 si la piece passée en parametre existe.
*/
/**
* \fn int destruction_piece(piece_t * piece)
* \brief detruit la pièce passée en paramètre.
*/
piece_t * init_piece(classe_t classe,int id_joueur);
/*Renvoi 1 si la piece passée en parametre existe*/
int piece_existe(piece_t * piece);
/*Detruit une piece*/
int destruction_piece(piece_t * piece);




#endif
