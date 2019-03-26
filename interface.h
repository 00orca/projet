#ifndef SDL_PROJET_H
#define SDL_PROJET_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//define booleen
typedef int bool;
#define TRUE  1
#define FALSE 0#define Z 20 //nb images
#define Z 35 //nb images

typedef enum {Menu,Menu2,Play,Load,About,Quit,In_menu,Help}menu_e;
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
void afficher_img(int x,int y,int h,int w,char img[50],image_t image[Z],SDL_Renderer *renderer,float coefZoom);
void loadImage(image_t image[Z],SDL_Renderer *renderer);
void AfficherText(char* message, char* fontFile, SDL_Color color, int fontSize,SDL_Renderer *renderer,int x,int y);

int draw_menu(SDL_Renderer *renderer,SDL_Window* pWindow);
void about();
void ingame_menu(SDL_Renderer *renderer,SDL_Window* pWindow);
void help(SDL_Renderer *renderer,SDL_Window* pWindow);
void mod_menu(SDL_Renderer *renderer,SDL_Window* pWindow,int nb_j,int nb_o,int taille,int nb_unit);
#endif
