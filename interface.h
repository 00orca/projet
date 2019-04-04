#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

extern int J_HUMAIN;
extern int J_BOT;
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
extern int VITESSE_INCREMENTATION;
extern int NB_BLOCK;



//define booleen
typedef int bool;
#define TRUE  1
#define FALSE 0
#define Z 150 //nb images

typedef enum {Menu,Menu2,Play,Load,About,Quit,In_menu,Help,Play_load,option}menu_e;
//typedef enum {None,Reculer,Save,Help,Quitg,Ok}ingame_menu_e;

menu_e running;

//Declaration de surface et fenetre
extern SDL_Surface *gpScreen;

extern SDL_Renderer *renderer;
//Declaration de l'evenement
extern SDL_Event myEvent;

//Declaration de police
extern TTF_Font *font;

typedef struct image_s{
  SDL_Texture * texture;
  char loc_image[50];
}image_t;

/*Declarer les couleurs communes*/
extern const SDL_Color RGB_Black;
extern const SDL_Color RGB_Red;
extern const SDL_Color RGB_Green;
extern const SDL_Color RGB_Blue;
extern const SDL_Color RGB_Yellow;
extern const SDL_Color RGB_White;

/*Declaration les fonctions*/
void afficher_img(int x,int y,int h,int w,char img[50],image_t image[Z],SDL_Renderer *renderer,float coefZoom,int anim,SDL_Rect imgDestRect);
void loadImage(image_t image[Z],SDL_Renderer *renderer);
void AfficherText(char* message, char* fontFile, SDL_Color color, int fontSize,SDL_Renderer *renderer,int x,int y);

int draw_menu(SDL_Renderer *renderer,SDL_Window* pWindow);
void about();
void ingame_menu(SDL_Renderer *renderer,SDL_Window* pWindow);
void help(SDL_Renderer *renderer,SDL_Window* pWindow);
void mod_menu(SDL_Renderer *renderer,SDL_Window* pWindow,image_t image[Z]);
void mod_option(SDL_Renderer *renderer,SDL_Window* pWindow,image_t *image);


#endif