#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


#include "piece.h"
#include "interface.h"

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


//=====================================MAIN=============================//

int main(int argc, char** argv)
{


	SDL_Window* pWindow = NULL;
	SDL_Renderer *renderer=NULL;

	int *largeur=0,*hauteur=0;
	largeur=malloc(sizeof(*largeur));
	hauteur=malloc(sizeof(*hauteur));

	int bordure=43;

	int sel=0;
	int fin_tour=0;


	bash_t tab_info_bash[TAILLE_TAB_BASH];
	int nb_tour=0;
	int compteur_anim=VITESSE_ANIM;
	int scroll_speed=20;
	int x_bot,y_bot;
	srand(time(NULL));
	int souris=0;
	int nb_joueur_restant;
	int joueur_actu=0;
	int frame_anim_montre=0;
	int compteur_tour=1;
	int clicout;
	long int jour_nuit;
	image_t image[Z];
	char variable[80];
	char variable2[80];
	int role_reseau = atoi(argv[1]) ; //0 = server 1 =client


    /* Initialisation SDL*/
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
		SDL_DisplayMode dm;
		SDL_GetCurrentDisplayMode(0,&dm);

		int SCREEN_HEIGHT = dm.h;
		int SCREEN_WIDTH = dm.w;
	/* Initialisation TTF */
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	/* Création de la fenêtre */
	pWindow = SDL_CreateWindow("Tactic Arena Upgraded V1.0",SDL_WINDOWPOS_UNDEFINED,
												  SDL_WINDOWPOS_UNDEFINED,
												  SCREEN_WIDTH,
												  SCREEN_HEIGHT,
												  SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);


	SDL_GetWindowSize(pWindow,largeur,hauteur); //initialisation des pointeur largeur et hauteur sur la taille de la fenetre

	if(!pWindow){
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		fprintf(stderr, "Erreur à la création du renderer\n");
		exit(EXIT_FAILURE);
	}

/* a tester, ne fonctionne pas sur windows (l'icone reste le meme)
	SDL_Surface* iconSurface;
	iconSurface = SDL_LoadBMP("images/icon.bmp");
	SDL_SetWindowIcon(pWindow, iconSurface);
*/

//===================================TEXTURES==========================================//

loadImage(image,renderer);

/*initialisation du reseau*/
int client_socket;
struct sockaddr_in serveur_address, client_address;
int server_socket;
if (role_reseau == 0){
	struct sockaddr_in serveur_address, client_address;
	unsigned int mon_address_longueur, lg;
	bzero(&serveur_address,sizeof(serveur_address));
	serveur_address.sin_port = htons(30000);
	serveur_address.sin_family = AF_INET;
	serveur_address.sin_addr.s_addr = htonl(INADDR_ANY);

	char *hostname = "localhost";
    char ip[100];
    hostname_to_ip(hostname , ip);
	fprintf(stderr, "%s resolved to %s" , hostname , ip);
	view_ip();

	/* creation de socket */
	if ((server_socket = socket(AF_INET,SOCK_STREAM,0))== -1) {
		printf("Impossible de créer la socket\n");
		exit(0);
	}

	/* bind serveur - socket */
	bind(server_socket,(struct sockaddr *)&serveur_address,sizeof(serveur_address));
	/* ecoute sur la socket */
	listen(server_socket,5);
	/* accept la connexion */
	mon_address_longueur = sizeof(client_address);

    /* on attend que le client se connecte */
	client_socket = accept(server_socket,
                         (struct sockaddr *)&client_address,
                         &mon_address_longueur);
}
else if (role_reseau == 1){
	struct hostent *serveur_info;
	long hostAddr;
	int server_socket;
	bzero(&serveur_address,sizeof(serveur_address));
	hostAddr = inet_addr(SERVEURNAME);
	if ( (long)hostAddr != (long)-1 ){
		bcopy(&hostAddr,&serveur_address.sin_addr,sizeof(hostAddr));
	} else {
		serveur_info = gethostbyname(SERVEURNAME);
		if (serveur_info == NULL) {
			printf("Impossible de récupérer les infos du serveur\n");
			exit(0);
		}
		bcopy(serveur_info->h_addr,&serveur_address.sin_addr,serveur_info->h_length);
	}
	serveur_address.sin_port = htons(30000);
	serveur_address.sin_family = AF_INET;
	/* creation de la socket */
	if ( (server_socket = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		printf("Impossible de créer la socket client\n");
		exit(0);
	}
	/* requete de connexion */
	if(connect( server_socket, (struct sockaddr *)&serveur_address, sizeof(serveur_address)) < 0 ) {
		printf("Impossible de se connecter au serveur\n");
		exit(0);
	}else printf("connecté!\n");

}

//========================================FENETRE=====================================//

if( pWindow )
{
	running = Menu;
	SDL_Event e;
	if(role_reseau==0){
	while(running != Quit) {
		//================================================================================================================================================//
		//================================================================================================================================================//
		//=============================================================MENU PRINCIPALE====================================================================//
		//================================================================================================================================================//
		//================================================================================================================================================//
			if(running == Menu){
				int longeur = draw_menu(renderer,pWindow);
				while(SDL_PollEvent(&e)) {
					switch(e.type) {
						case SDL_QUIT:	//cas ou l'on souhaite quitter
							running = Quit;
						break;
						case SDL_MOUSEBUTTONDOWN:
							if(e.button.button == SDL_BUTTON_LEFT){
								if (e.button.y > longeur && e.button.y < longeur*2)running = Menu2;
								if (e.button.y > longeur*2 && e.button.y < longeur*3)running = Load;
								if (e.button.y > longeur*3 && e.button.y < longeur*4)running = About;
								if (e.button.y > longeur*4 && e.button.y < longeur*5)running = Quit;
							}
						break;
					}
				}
				//================================================================================================================================================//
				//================================================================================================================================================//
				//=============================================================CHOIX DES PROPRIÉTÉ PARTIE=========================================================//
				//===================================================================ET===========================================================================//
				//=================================================================DEBUT DE PARTIE================================================================//
			}else if(running == Menu2){
				int nb_j=0,nb_o=2,nb_unit=4,taille=N;
				int x1 = gpScreen->w - gpScreen->w/5;
				int x2 = gpScreen->w - gpScreen->w/10;
				int fontsize = gpScreen->h/10;
				int y = fontsize/2;
				int delay_clic=0;
				while((SDL_PollEvent(&e)||running == Menu2) || running == Play) {
					mod_menu(renderer,pWindow,nb_j,nb_o,taille,nb_unit);
					switch(e.type) {
						case SDL_QUIT:	//cas ou l'on souhaite quitter
							running = Quit;
						break;
						case SDL_MOUSEBUTTONDOWN:
							if(e.button.button == SDL_BUTTON_LEFT){
								if(delay_clic%10==0){
									if((nb_j+nb_o)<50){
										if(e.button.x>x1&&e.button.x<x1+fontsize){
											if(e.button.y>y && e.button.y<y+fontsize)nb_j++;
											if(e.button.y>y*5 && e.button.y<y*5+fontsize)nb_o++;
										}
									}
									if((nb_j+nb_o)>2){
										if(e.button.x>x2&&e.button.x<x2+fontsize){
											if(e.button.y>y && e.button.y<y+fontsize&&nb_j>0)nb_j--;
											if(e.button.y>y*5 && e.button.y<y*5+fontsize&&nb_o>0)nb_o--;
										}
									}
									if(taille>=10&&taille<=100){
										if(e.button.x>x1&&e.button.x<x1+fontsize&&e.button.y>y*9&&e.button.y<y*9+fontsize&&taille<100)taille++;
										if(e.button.x>x2&&e.button.x<x2+fontsize&&e.button.y>y*9&&e.button.y<y*9+fontsize&&taille>10)taille--;
									}
									if(nb_unit>=1&&nb_unit<=30){
										if(e.button.x>x1&&e.button.x<x1+fontsize&&e.button.y>y*13&&e.button.y<y*13+fontsize&&nb_unit<30)nb_unit++;
										if(e.button.x>x2&&e.button.x<x2+fontsize&&e.button.y>y*13&&e.button.y<y*13+fontsize&&nb_unit>1)nb_unit--;
									}
									delay_clic=0;
								delay_clic=(delay_clic+1)%51;
							}
							if(e.button.y > gpScreen->h/5*4 && e.button.y < gpScreen->h){
								//==================================INITIALISATION GRILLE============================//
								    //choix du mode de génération
								//	printf("1 POUR CARTE ALEATOIRE, AUTRE CHIFFRE POUR UNE DES CARTES PRESET : ");
								//	scanf("%d",&preset);
								J_HUMAIN = nb_j;
								J = nb_j + nb_o;
								NB_UNITE = nb_unit;
								N = taille;
								M = N;

								degatx_t aff_deg[N*M];
								joueurs_t tab[J];
								case_t terrain[N][M];

								joueur_actu=0;
								frame_anim_montre=4;
								compteur_tour=1;
								jour_nuit=((DURE_JOUR_NUIT/24)*7);
								initialisation_principale(bordure,pWindow,largeur,hauteur,tab,aff_deg,tab_info_bash,terrain,variable2);
								int i,j;
								int test;
								printf("sending\n");
								for (i=0;i<N;i++){
									for(j=0;j<M;j++){
										test=sendto(client_socket,&terrain[i][j],sizeof(case_t),0,&client_address,sizeof(client_address));
									}
								}
						/////a copier
								while(running == Play){ //boucle de jeu
									while(SDL_PollEvent(&e)) {
										switch(e.type) {
											case SDL_QUIT:	//cas ou l'on souhaite quitter
												running = Quit;
											break;

											case SDL_KEYDOWN: //cas ou une touche est pressé
												switch (e.key.keysym.sym)  //switch qui gere les touches
												{
													case SDLK_LEFT:
														for (int compteur=0;compteur<N;compteur++){
															for (int compteur2=0;compteur2<M;compteur2++){
																terrain[compteur][compteur2].xImg+=scroll_speed;
																terrain[compteur][compteur2].x1+=scroll_speed;
																terrain[compteur][compteur2].x2+=scroll_speed;
																terrain[compteur][compteur2].x3+=scroll_speed;
																terrain[compteur][compteur2].x4+=scroll_speed;
															}
														}
														break;
													case SDLK_RIGHT:
														for (int compteur=0;compteur<N;compteur++){
															for (int compteur2=0;compteur2<M;compteur2++){
																terrain[compteur][compteur2].xImg-=scroll_speed;
																terrain[compteur][compteur2].x1-=scroll_speed;
																terrain[compteur][compteur2].x2-=scroll_speed;
																terrain[compteur][compteur2].x3-=scroll_speed;
																terrain[compteur][compteur2].x4-=scroll_speed;
															}
														}
														break;
													case SDLK_UP:
														for (int compteur=0;compteur<N;compteur++){
															for (int compteur2=0;compteur2<M;compteur2++){
																terrain[compteur][compteur2].yImg+=scroll_speed;
																terrain[compteur][compteur2].y1+=scroll_speed;
																terrain[compteur][compteur2].y2+=scroll_speed;
																terrain[compteur][compteur2].y3+=scroll_speed;
																terrain[compteur][compteur2].y4+=scroll_speed;
															}
														}
														break;
													case SDLK_DOWN:
														for (int compteur=0;compteur<N;compteur++){
															for (int compteur2=0;compteur2<M;compteur2++){
																terrain[compteur][compteur2].yImg-=scroll_speed;
																terrain[compteur][compteur2].y1-=scroll_speed;
																terrain[compteur][compteur2].y2-=scroll_speed;
																terrain[compteur][compteur2].y3-=scroll_speed;
																terrain[compteur][compteur2].y4-=scroll_speed;
															}
														}
														break;
													case SDLK_SPACE:
														ingame_menu(renderer,pWindow);
														running = In_menu;
														while(running == In_menu){
															while(SDL_PollEvent(&e)){
																	switch(e.type) {
																	case SDL_QUIT:	//cas ou l'on souhaite quitter
																		running = Quit;
																	break;
																	case SDL_MOUSEBUTTONDOWN:
																		if(e.button.button == SDL_BUTTON_LEFT){
																			if(e.button.x > gpScreen->w - 260 && e.button.x < gpScreen->w - 60){
																				if(e.button.y>gpScreen->h - 330 && e.button.y<gpScreen->h - 330+75)running = Play;
																				if(e.button.y>gpScreen->h - 330+75 && e.button.y<gpScreen->h - 330+75*2)running = Play;
																				if(e.button.y>gpScreen->h - 330+75*2 && e.button.y<gpScreen->h - 330+75*3)running = Help;
																				if(e.button.y>gpScreen->h - 330+75*3 && e.button.y<gpScreen->h - 330+75*4)running = Menu;
																			}else{
																				running = Play;
																			}
																		}
																	break;
																	case SDL_KEYDOWN:
																		if(e.key.keysym.sym == SDLK_SPACE){
																			running = Play;
																		}
																	break;
																}
															}
														}
														break;
												}
												break;

												case SDL_MOUSEBUTTONDOWN:
													switch (e.button.button)
													{
														case SDL_BUTTON_LEFT:
															if(e.button.x > gpScreen->w - 60 && e.button.y >  gpScreen->h - 30){
																ingame_menu(renderer,pWindow);
																running = In_menu;
																while(running == In_menu){
																	while(SDL_PollEvent(&e)){
																			switch(e.type) {
																			case SDL_QUIT:	//cas ou l'on souhaite quitter
																				running = Quit;
																			break;
																			case SDL_MOUSEBUTTONDOWN:
																				if(e.button.button == SDL_BUTTON_LEFT ){
																					if(e.button.x > gpScreen->w - 260 && e.button.x < gpScreen->w - 60){
																						if(e.button.y>gpScreen->h - 330 && e.button.y<gpScreen->h - 330+75)running = Play;
																						if(e.button.y>gpScreen->h - 330+75 && e.button.y<gpScreen->h - 330+75*2)running = Play;
																						if(e.button.y>gpScreen->h - 330+75*2 && e.button.y<gpScreen->h - 330+75*3)running = Help;
																						if(e.button.y>gpScreen->h - 330+75*3 && e.button.y<gpScreen->h - 330+75*4)running = Menu;
																					}else
																						running = Play;
																				}
																			break;
																		}
																	}
																}
															}
															if(tab[joueur_actu].humain==1){
															clicout=0;
															//int a,b,a2,b2,a3,b3,a4,b4,res1,res2,res3,res4;
															for(int compteur=0;compteur<N;compteur++){
																for(int compteur2=0;compteur2<M; compteur2++){
																		/* VERSION AVANCER NE FONCTIONNANT PAS ENCORE
																		fprintf(stderr,"POUR  %d | %d : \n",compteur,compteur2);
																		//Y
																		a=((terrain[compteur][compteur2].y1-terrain[compteur][compteur2].y4)/(terrain[compteur][compteur2].x1-terrain[compteur][compteur2].x4));
																		b= (terrain[compteur][compteur2].y4-a*terrain[compteur][compteur2].x4);
																		res1=a*e.motion.x+b;j
																		fprintf(stderr,"a = %d et b = %d pour x= %d et y = %d , doit dépasser %d en y \n",a,b,e.motion.x,e.motion.y,res1);
																		//X
																		a2=((terrain[compteur][compteur2].y2-terrain[compteur][compteur2].y1)/(terrain[compteur][compteur2].x2-terrain[compteur][compteur2].x1));
																		b2= (terrain[compteur][compteur2].y1-a*terrain[compteur][compteur2].x1);
																		res2=-1*(e.motion.y-b2)/a2;
																		fprintf(stderr,"a2 = %d et b2= %d pour x= %d et y = %d ,doit dépasser %d en x \n",a2,b2,e.motion.x,e.motion.y,res2);
																		//Y
																		a3=((terrain[compteur][compteur2].y2-terrain[compteur][compteur2].y3)/(terrain[compteur][compteur2].x2-terrain[compteur][compteur2].x3));
																		b3= (terrain[compteur][compteur2].y3-a*terrain[compteur][compteur2].x3);
																		res3 = a3*e.motion.x+b3;
																		fprintf(stderr,"a3 = %d et b3= %d pour x= %d et y = %d , ne doit pas dépasser %d en y \n",a3,b3,e.motion.x,e.motion.y,res3);
																		//X
																		a4=((terrain[compteur][compteur2].y3-terrain[compteur][compteur2].y4)/(terrain[compteur][compteur2].x3-terrain[compteur][compteur2].x4));
																		b4= (terrain[compteur][compteur2].y4-a*terrain[compteur][compteur2].x4);
																		res4 = -1*(e.motion.y-b4)/a4;
																		fprintf(stderr,"a4 = %d et b4= %d pour x= %d et y = %d , ne doit pas dépasser %d en x \n",a4,b4,e.motion.x,e.motion.y,res4);

																		if(e.motion.y >  res1 && e.motion.x > res2  && e.motion.y <  res3 && e.motion.x <  res4 ){
																			fprintf(stderr,"la case %d | %d a été selectionné. \n",compteur,compteur2);
																		}
																		*/

																		//VERSION BASIQUE QUI FONCTIONNE MAL
																		if(e.motion.y > terrain[compteur][compteur2].y1+10 && e.motion.y < terrain[compteur][compteur2].y3-10 && e.motion.x > terrain[compteur][compteur2].x4+10 && e.motion.x < terrain[compteur][compteur2].x2-10 &&!(e.motion.x>(*largeur)/2+175 && e.motion.x<(*largeur)/2+175+150 && e.motion.y>15 && e.motion.y<15+50)&&!(e.motion.x>10 && e.motion.x<240 && e.motion.y>300 && e.motion.y<500)){
																			//=================SELECTION D'UNE PIECE====================//
																			if(terrain[compteur][compteur2].piece){
																				clicout=1;

																				for(int x=0;x<N;x++){
																					for(int y=0;y<M;y++){
																						if(terrain[x][y].piece && terrain[x][y].piece->joueur==joueur_actu && terrain[x][y].piece->select==1){
																							combat(terrain,x,y,compteur,compteur2,joueur_actu,tab,aff_deg,tab_info_bash,variable2);
																						}
																					}
																				}
																				for(int indice=0;indice<N;indice++){
																					for(int indice2=0;indice2<M; indice2++){
																						if(terrain[indice][indice2].piece && terrain[indice][indice2].piece->select==1){
																							terrain[indice][indice2].piece->select=0;
																						}
																					}
																				}

																				if(terrain[compteur][compteur2].piece)
																					terrain[compteur][compteur2].piece->select=1;


																			}else{
																			//=================DEPLACEMENT et ATTAQUE D'UNE PIECE====================//

																			move(terrain,compteur,compteur2,joueur_actu,tab,tab_info_bash,variable2);
																			}

																		}
																		else if(e.motion.x>(*largeur)/3+420 && e.motion.x<(*largeur)/2+175+150 && e.motion.y>15 && e.motion.y<15+50){
																			fin_tour=1;
																		}
																	}
																}
																if(e.motion.x>10 && e.motion.x<240 && e.motion.y>300 && e.motion.y<500){
																	clicout=1;
																	for(int indice=0;indice<N;indice++){
																		for(int indice2=0;indice2<M; indice2++){
																			if(terrain[indice][indice2].piece && terrain[indice][indice2].piece->select==1 && terrain[indice][indice2].piece->joueur==joueur_actu){
																				if(terrain[indice][indice2].piece->direction==1)
																					terrain[indice][indice2].piece->direction=4;
																				else if(terrain[indice][indice2].piece->direction==4)
																					terrain[indice][indice2].piece->direction=2;
																				else if(terrain[indice][indice2].piece->direction==2)
																					terrain[indice][indice2].piece->direction=3;
																				else if(terrain[indice][indice2].piece->direction==3)
																					terrain[indice][indice2].piece->direction=1;
																			}
																		}
																	}
																}
																if(clicout==0){
																	for(int indice=0;indice<N;indice++){
																		for(int indice2=0;indice2<M; indice2++){
																			if(terrain[indice][indice2].piece && terrain[indice][indice2].piece->select==1)
																				terrain[indice][indice2].piece->select=0;
																		}

																}
															}
															}
														break;
													}
										break;
										case SDL_MOUSEWHEEL:  //SCROLLING BASH
											if(e.wheel.y==1){
												souris=BASH_SCROLL_SPEED;
											}else if (e.wheel.y==-1){
												souris=-BASH_SCROLL_SPEED;
											}
										break;

											}
										}
										if(tab[joueur_actu].humain==1){
									//if(e.motion.x>((*largeur)-450+25) && e.motion.x<(*largeur) && e.motion.y>0 && e.motion.y<300){
										if(souris>0 && tab_info_bash[TAILLE_TAB_BASH-1].pos_y<=0){
											for(int a=0;a<TAILLE_TAB_BASH;a++){
												//VERS LE HAUT
												tab_info_bash[a].pos_y+=25;
											}
											souris-=1;
										}
										else if (souris<0 && tab_info_bash[0].pos_y>265){
											for(int a=0;a<TAILLE_TAB_BASH;a++){
												//VERS LE BAS
												tab_info_bash[a].pos_y-=25;
											}
											souris+=1;
										}
									//	}


										gpScreen = SDL_GetWindowSurface(pWindow);
										if( e.motion.x >=0 && e.motion.x <=30 && e.type==SDL_MOUSEMOTION){
											for (int compteur=0;compteur<N;compteur++){
												for (int compteur2=0;compteur2<M;compteur2++){
													terrain[compteur][compteur2].xImg+=scroll_speed;
													terrain[compteur][compteur2].x1+=scroll_speed;
													terrain[compteur][compteur2].x2+=scroll_speed;
													terrain[compteur][compteur2].x3+=scroll_speed;
													terrain[compteur][compteur2].x4+=scroll_speed;
												}
											}
										}
										if(e.motion.x >= gpScreen->w - 30 && e.motion.x <= gpScreen->w && e.type==SDL_MOUSEMOTION){
											for (int compteur=0;compteur<N;compteur++){
												for (int compteur2=0;compteur2<M;compteur2++){
													terrain[compteur][compteur2].xImg-=scroll_speed;
													terrain[compteur][compteur2].x1-=scroll_speed;
													terrain[compteur][compteur2].x2-=scroll_speed;
													terrain[compteur][compteur2].x3-=scroll_speed;
													terrain[compteur][compteur2].x4-=scroll_speed;
												}
											}
										}
										if( e.motion.y >=0 && e.motion.y <=30 && e.type==SDL_MOUSEMOTION){
											for (int compteur=0;compteur<N;compteur++){
												for (int compteur2=0;compteur2<M;compteur2++){
													terrain[compteur][compteur2].yImg+=scroll_speed;
													terrain[compteur][compteur2].y1+=scroll_speed;
													terrain[compteur][compteur2].y2+=scroll_speed;
													terrain[compteur][compteur2].y3+=scroll_speed;
													terrain[compteur][compteur2].y4+=scroll_speed;
												}
											}
										}
										if(e.motion.y >= gpScreen->h - 30 && e.motion.y <= gpScreen->h && e.type==SDL_MOUSEMOTION){
											for (int compteur=0;compteur<N;compteur++){
												for (int compteur2=0;compteur2<M;compteur2++){
													terrain[compteur][compteur2].yImg-=scroll_speed;
													terrain[compteur][compteur2].y1-=scroll_speed;
													terrain[compteur][compteur2].y2-=scroll_speed;
													terrain[compteur][compteur2].y3-=scroll_speed;
													terrain[compteur][compteur2].y4-=scroll_speed;
												}
											}
										}
										}

									//fin action du joueur

									if(tab[joueur_actu].humain==0){ 	//===================================================TOUR DU BOT===================================================//
										if(nb_tour>=VITESSE_JEU_BOT){
											if(sel==0){ //SELECTION
												fprintf(stderr,"TOUR DU BOT %d : PTS D'ACTION = %d\n",joueur_actu,tab[joueur_actu].pts_action_actu);
												for (int i=0;i<N;i++){ //deselectionne toutes les pieces
													for (int j=0;j<M;j++){
														if(terrain[i][j].piece && terrain[i][j].piece->select==1){
																terrain[i][j].piece->select=0;
														}
													}
												}
												int var5=0;
												int var6=(rand()%tab[joueur_actu].nb_unite);
												for (int i=0;i<N;i++){ //selection d'une piece
													for (int j=0;j<M;j++){
														if(terrain[i][j].piece && terrain[i][j].piece->select==0 && terrain[i][j].piece->joueur==joueur_actu && var5==var6){
															terrain[i][j].piece->select=1;
															x_bot=i;
															y_bot=j;
														}
														if(terrain[i][j].piece && terrain[i][j].piece->joueur==joueur_actu)
															var5++;
													}
												}

												centrer_camera(terrain,terrain[x_bot][y_bot].xImg,terrain[x_bot][y_bot].yImg,*largeur,*hauteur);
												sel=1;
											}else{ //ACTION
												int nb_ennemies_portee=a_portee(terrain,x_bot,y_bot,joueur_actu);
												if((nb_ennemies_portee>=1 && terrain[x_bot][y_bot].piece->classe!=priest)|| (nb_ennemies_portee>=2 && terrain[x_bot][y_bot].piece->classe==priest) || (reste_allie(terrain,joueur_actu)==1 && terrain[x_bot][y_bot].piece->classe==priest)){
													fprintf(stderr,"ATTAQUE\n");
													attaquer_meilleur_cible(terrain,x_bot,y_bot,nb_ennemies_portee,joueur_actu,tab,aff_deg,tab_info_bash,variable2);
												}else{
													fprintf(stderr,"DEPLACEMENT\n");
													depla_atk_mov(terrain,x_bot,y_bot,joueur_actu,tab,tab_info_bash,variable2);
												}


												sel=0;
											}
											nb_tour=0;
											if(tab[joueur_actu].pts_action_actu<=0){ //direction blockage
												for (int i=0;i<N;i++){
													for (int j=0;j<M;j++){
														if(terrain[i][j].piece && terrain[i][j].piece->joueur==joueur_actu){
															IA_blockage_direction(terrain,i,j,joueur_actu);//tourne le perso selon la direction la plus intéressante
														}
													}
												}
											}

										}


									}


									for(int i=0;i<J;i++){
										if(tab[i].nb_unite<=0 && tab[i].id_joueur!=-1){
											tab[i].id_joueur=-2;
										}
									}


									nb_joueur_restant=0;
									for(int i=0;i<J;i++){		//fermeture de la fenetre qd il reste un joueur en vie seulement (a modifié pour retourner au menu qd le joueur gagne)
										if(tab[i].id_joueur!=-1 && tab[i].id_joueur!=-2){
											nb_joueur_restant++;
										}
									}

									if((jour_nuit%((DURE_JOUR_NUIT/24)*3))>=-20 && (jour_nuit%((DURE_JOUR_NUIT/24)*3))<=20){
										jour_nuit+=40;
										frame_anim_montre++;
									}
									if(frame_anim_montre>=8 && (jour_nuit%((DURE_JOUR_NUIT/24)*3))>=20 && (jour_nuit%((DURE_JOUR_NUIT/24)*3))<=60){
										frame_anim_montre=0;
									}






									if(nb_joueur_restant==1){
										for(int i=0;i<J;i++){
											if(tab[i].id_joueur!=-1 && tab[i].id_joueur!=-2){
													sprintf(variable,"LE JOUEUR %d GAGNE EN %d TOURS !\n",i,compteur_tour);
				    							ajouter_ligne_bash(variable,tab_info_bash,info,variable2);
											}
										}
										//ecran de victoire/defaite

										running=Menu;
									}


									affichage_principale(renderer,pWindow,bordure,largeur,hauteur,tab,aff_deg,tab_info_bash,terrain,joueur_actu,image,compteur_anim,nb_joueur_restant,compteur_tour,frame_anim_montre,jour_nuit,variable2);


									for(int i=0;i<J;i++){
										if(tab[i].id_joueur==-2){
											tab[i].id_joueur=-1;
										}
									}

									if((tab[joueur_actu].pts_action_actu<=0 && tab[joueur_actu].humain==0 )|| (tab[joueur_actu].pts_action_actu<=0 && fin_tour==1) || (fin_tour==1)){				//gestion des tours de jeu
										tab[joueur_actu].pts_action_actu=tab[joueur_actu].pts_action_max;
										do{
											joueur_actu=(joueur_actu+1)%J;
											if(joueur_actu==0){
												compteur_tour++;
											}
										}while(tab[joueur_actu].id_joueur==-1);
										fin_tour=0;
									}

									//incrémentation a chaque tours
									nb_tour=(nb_tour+1)%(VITESSE_JEU_BOT*2);
									compteur_anim=compteur_anim%(VITESSE_ANIM*4);
									compteur_anim++;
									jour_nuit=(jour_nuit+1)%DURE_JOUR_NUIT;



								//===================================ACTUALISATION DES TOURS==========================================//

								}//fin boucle de jeu
							}
						}
					break;
				}
			}


			//================================================================================================================================================//
			//================================================================================================================================================//
			//=============================================================CHARGEMENT DE PARTIE===============================================================//
			//================================================================================================================================================//
			//================================================================================================================================================//

		}else if(running == Load){

			running = Menu2;

			//================================================================================================================================================//
			//================================================================================================================================================//
			//=============================================================HELP===============================================================================//
			//================================================================================================================================================//
			//================================================================================================================================================//
		}else if(running == Help){
			help(renderer,pWindow);
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT:	//cas ou l'on souhaite quitter
						running = Quit;
					break;
					case SDL_MOUSEBUTTONDOWN:
						if(e.button.button == SDL_BUTTON_LEFT){
							if(e.button.x > gpScreen->w - 60 && e.button.y >  gpScreen->h - 30){
								running = Play;
							}
						}
					break;
				}
			}
			//================================================================================================================================================//
			//================================================================================================================================================//
			//=============================================================ABOUT==============================================================================//
			//================================================================================================================================================//
			//================================================================================================================================================//
		}else if(running == About){
			about(renderer,pWindow);
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT:	//cas ou l'on souhaite quitter
						running = Quit;
					break;
					case SDL_MOUSEBUTTONDOWN:
						if(e.button.button == SDL_BUTTON_LEFT){
							if(e.button.x > gpScreen->w - 60 && e.button.y >  gpScreen->h - 30){
								running = Menu;
							}
						}
					break;
				}
			}
		}
		}
	}else {
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}
	}
	if(role_reseau==1){
		int i,j;
		int test;

		J_HUMAIN = nb_j;
		J = nb_j + nb_o;
		NB_UNITE = nb_unit;
		N = taille;
		M = N;

		degatx_t aff_deg[N*M];
		joueurs_t tab[J];
		case_t terrain[N][M];

		joueur_actu=0;
		frame_anim_montre=4;
		compteur_tour=1;
		jour_nuit=((DURE_JOUR_NUIT/24)*7);
		initialisation_principale(bordure,pWindow,largeur,hauteur,tab,aff_deg,tab_info_bash,terrain,variable2);
		printf("receiving\n");
		for (i=0;i<N;i++){
			for(j=0;j<M;j++){
				test=recvfrom(server_socket,&terrain[i][j],sizeof(case_t),0,&serveur_address,sizeof(serveur_address));
			}
		}
		while(running == Play){ //boucle de jeu
			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT:	//cas ou l'on souhaite quitter
						running = Quit;
					break;

					case SDL_KEYDOWN: //cas ou une touche est pressé
						switch (e.key.keysym.sym)  //switch qui gere les touches
						{
							case SDLK_LEFT:
								for (int compteur=0;compteur<N;compteur++){
									for (int compteur2=0;compteur2<M;compteur2++){
										terrain[compteur][compteur2].xImg+=scroll_speed;
										terrain[compteur][compteur2].x1+=scroll_speed;
										terrain[compteur][compteur2].x2+=scroll_speed;
										terrain[compteur][compteur2].x3+=scroll_speed;
										terrain[compteur][compteur2].x4+=scroll_speed;
									}
								}
								break;
							case SDLK_RIGHT:
								for (int compteur=0;compteur<N;compteur++){
									for (int compteur2=0;compteur2<M;compteur2++){
										terrain[compteur][compteur2].xImg-=scroll_speed;
										terrain[compteur][compteur2].x1-=scroll_speed;
										terrain[compteur][compteur2].x2-=scroll_speed;
										terrain[compteur][compteur2].x3-=scroll_speed;
										terrain[compteur][compteur2].x4-=scroll_speed;
									}
								}
								break;
							case SDLK_UP:
								for (int compteur=0;compteur<N;compteur++){
									for (int compteur2=0;compteur2<M;compteur2++){
										terrain[compteur][compteur2].yImg+=scroll_speed;
										terrain[compteur][compteur2].y1+=scroll_speed;
										terrain[compteur][compteur2].y2+=scroll_speed;
										terrain[compteur][compteur2].y3+=scroll_speed;
										terrain[compteur][compteur2].y4+=scroll_speed;
									}
								}
								break;
							case SDLK_DOWN:
								for (int compteur=0;compteur<N;compteur++){
									for (int compteur2=0;compteur2<M;compteur2++){
										terrain[compteur][compteur2].yImg-=scroll_speed;
										terrain[compteur][compteur2].y1-=scroll_speed;
										terrain[compteur][compteur2].y2-=scroll_speed;
										terrain[compteur][compteur2].y3-=scroll_speed;
										terrain[compteur][compteur2].y4-=scroll_speed;
									}
								}
								break;
							case SDLK_SPACE:
								ingame_menu(renderer,pWindow);
								running = In_menu;
								while(running == In_menu){
									while(SDL_PollEvent(&e)){
											switch(e.type) {
											case SDL_QUIT:	//cas ou l'on souhaite quitter
												running = Quit;
											break;
											case SDL_MOUSEBUTTONDOWN:
												if(e.button.button == SDL_BUTTON_LEFT){
													if(e.button.x > gpScreen->w - 260 && e.button.x < gpScreen->w - 60){
														if(e.button.y>gpScreen->h - 330 && e.button.y<gpScreen->h - 330+75)running = Play;
														if(e.button.y>gpScreen->h - 330+75 && e.button.y<gpScreen->h - 330+75*2)running = Play;
														if(e.button.y>gpScreen->h - 330+75*2 && e.button.y<gpScreen->h - 330+75*3)running = Help;
														if(e.button.y>gpScreen->h - 330+75*3 && e.button.y<gpScreen->h - 330+75*4)running = Menu;
													}else{
														running = Play;
													}
												}
											break;
											case SDL_KEYDOWN:
												if(e.key.keysym.sym == SDLK_SPACE){
													running = Play;
												}
											break;
										}
									}
								}
								break;
						}
						break;

						case SDL_MOUSEBUTTONDOWN:
							switch (e.button.button)
							{
								case SDL_BUTTON_LEFT:
									if(e.button.x > gpScreen->w - 60 && e.button.y >  gpScreen->h - 30){
										ingame_menu(renderer,pWindow);
										running = In_menu;
										while(running == In_menu){
											while(SDL_PollEvent(&e)){
													switch(e.type) {
													case SDL_QUIT:	//cas ou l'on souhaite quitter
														running = Quit;
													break;
													case SDL_MOUSEBUTTONDOWN:
														if(e.button.button == SDL_BUTTON_LEFT ){
															if(e.button.x > gpScreen->w - 260 && e.button.x < gpScreen->w - 60){
																if(e.button.y>gpScreen->h - 330 && e.button.y<gpScreen->h - 330+75)running = Play;
																if(e.button.y>gpScreen->h - 330+75 && e.button.y<gpScreen->h - 330+75*2)running = Play;
																if(e.button.y>gpScreen->h - 330+75*2 && e.button.y<gpScreen->h - 330+75*3)running = Help;
																if(e.button.y>gpScreen->h - 330+75*3 && e.button.y<gpScreen->h - 330+75*4)running = Menu;
															}else
																running = Play;
														}
													break;
												}
											}
										}
									}
									if(tab[joueur_actu].humain==1){
									clicout=0;
									//int a,b,a2,b2,a3,b3,a4,b4,res1,res2,res3,res4;
									for(int compteur=0;compteur<N;compteur++){
										for(int compteur2=0;compteur2<M; compteur2++){
												/* VERSION AVANCER NE FONCTIONNANT PAS ENCORE
												fprintf(stderr,"POUR  %d | %d : \n",compteur,compteur2);
												//Y
												a=((terrain[compteur][compteur2].y1-terrain[compteur][compteur2].y4)/(terrain[compteur][compteur2].x1-terrain[compteur][compteur2].x4));
												b= (terrain[compteur][compteur2].y4-a*terrain[compteur][compteur2].x4);
												res1=a*e.motion.x+b;j
												fprintf(stderr,"a = %d et b = %d pour x= %d et y = %d , doit dépasser %d en y \n",a,b,e.motion.x,e.motion.y,res1);
												//X
												a2=((terrain[compteur][compteur2].y2-terrain[compteur][compteur2].y1)/(terrain[compteur][compteur2].x2-terrain[compteur][compteur2].x1));
												b2= (terrain[compteur][compteur2].y1-a*terrain[compteur][compteur2].x1);
												res2=-1*(e.motion.y-b2)/a2;
												fprintf(stderr,"a2 = %d et b2= %d pour x= %d et y = %d ,doit dépasser %d en x \n",a2,b2,e.motion.x,e.motion.y,res2);
												//Y
												a3=((terrain[compteur][compteur2].y2-terrain[compteur][compteur2].y3)/(terrain[compteur][compteur2].x2-terrain[compteur][compteur2].x3));
												b3= (terrain[compteur][compteur2].y3-a*terrain[compteur][compteur2].x3);
												res3 = a3*e.motion.x+b3;
												fprintf(stderr,"a3 = %d et b3= %d pour x= %d et y = %d , ne doit pas dépasser %d en y \n",a3,b3,e.motion.x,e.motion.y,res3);
												//X
												a4=((terrain[compteur][compteur2].y3-terrain[compteur][compteur2].y4)/(terrain[compteur][compteur2].x3-terrain[compteur][compteur2].x4));
												b4= (terrain[compteur][compteur2].y4-a*terrain[compteur][compteur2].x4);
												res4 = -1*(e.motion.y-b4)/a4;
												fprintf(stderr,"a4 = %d et b4= %d pour x= %d et y = %d , ne doit pas dépasser %d en x \n",a4,b4,e.motion.x,e.motion.y,res4);

												if(e.motion.y >  res1 && e.motion.x > res2  && e.motion.y <  res3 && e.motion.x <  res4 ){
													fprintf(stderr,"la case %d | %d a été selectionné. \n",compteur,compteur2);
												}
												*/

												//VERSION BASIQUE QUI FONCTIONNE MAL
												if(e.motion.y > terrain[compteur][compteur2].y1+10 && e.motion.y < terrain[compteur][compteur2].y3-10 && e.motion.x > terrain[compteur][compteur2].x4+10 && e.motion.x < terrain[compteur][compteur2].x2-10 &&!(e.motion.x>(*largeur)/2+175 && e.motion.x<(*largeur)/2+175+150 && e.motion.y>15 && e.motion.y<15+50)&&!(e.motion.x>10 && e.motion.x<240 && e.motion.y>300 && e.motion.y<500)){
													//=================SELECTION D'UNE PIECE====================//
													if(terrain[compteur][compteur2].piece){
														clicout=1;

														for(int x=0;x<N;x++){
															for(int y=0;y<M;y++){
																if(terrain[x][y].piece && terrain[x][y].piece->joueur==joueur_actu && terrain[x][y].piece->select==1){
																	combat(terrain,x,y,compteur,compteur2,joueur_actu,tab,aff_deg,tab_info_bash,variable2);
																}
															}
														}
														for(int indice=0;indice<N;indice++){
															for(int indice2=0;indice2<M; indice2++){
																if(terrain[indice][indice2].piece && terrain[indice][indice2].piece->select==1){
																	terrain[indice][indice2].piece->select=0;
																}
															}
														}

														if(terrain[compteur][compteur2].piece)
															terrain[compteur][compteur2].piece->select=1;


													}else{
													//=================DEPLACEMENT et ATTAQUE D'UNE PIECE====================//

													move(terrain,compteur,compteur2,joueur_actu,tab,tab_info_bash,variable2);
													}

												}
												else if(e.motion.x>(*largeur)/3+420 && e.motion.x<(*largeur)/2+175+150 && e.motion.y>15 && e.motion.y<15+50){
													fin_tour=1;
												}
											}
										}
										if(e.motion.x>10 && e.motion.x<240 && e.motion.y>300 && e.motion.y<500){
											clicout=1;
											for(int indice=0;indice<N;indice++){
												for(int indice2=0;indice2<M; indice2++){
													if(terrain[indice][indice2].piece && terrain[indice][indice2].piece->select==1 && terrain[indice][indice2].piece->joueur==joueur_actu){
														if(terrain[indice][indice2].piece->direction==1)
															terrain[indice][indice2].piece->direction=4;
														else if(terrain[indice][indice2].piece->direction==4)
															terrain[indice][indice2].piece->direction=2;
														else if(terrain[indice][indice2].piece->direction==2)
															terrain[indice][indice2].piece->direction=3;
														else if(terrain[indice][indice2].piece->direction==3)
															terrain[indice][indice2].piece->direction=1;
													}
												}
											}
										}
										if(clicout==0){
											for(int indice=0;indice<N;indice++){
												for(int indice2=0;indice2<M; indice2++){
													if(terrain[indice][indice2].piece && terrain[indice][indice2].piece->select==1)
														terrain[indice][indice2].piece->select=0;
												}

										}
									}
									}
								break;
							}
				break;
				case SDL_MOUSEWHEEL:  //SCROLLING BASH
					if(e.wheel.y==1){
						souris=BASH_SCROLL_SPEED;
					}else if (e.wheel.y==-1){
						souris=-BASH_SCROLL_SPEED;
					}
				break;

					}
				}
				if(tab[joueur_actu].humain==1){
			//if(e.motion.x>((*largeur)-450+25) && e.motion.x<(*largeur) && e.motion.y>0 && e.motion.y<300){
				if(souris>0 && tab_info_bash[TAILLE_TAB_BASH-1].pos_y<=0){
					for(int a=0;a<TAILLE_TAB_BASH;a++){
						//VERS LE HAUT
						tab_info_bash[a].pos_y+=25;
					}
					souris-=1;
				}
				else if (souris<0 && tab_info_bash[0].pos_y>265){
					for(int a=0;a<TAILLE_TAB_BASH;a++){
						//VERS LE BAS
						tab_info_bash[a].pos_y-=25;
					}
					souris+=1;
				}
			//	}


				gpScreen = SDL_GetWindowSurface(pWindow);
				if( e.motion.x >=0 && e.motion.x <=30 && e.type==SDL_MOUSEMOTION){
					for (int compteur=0;compteur<N;compteur++){
						for (int compteur2=0;compteur2<M;compteur2++){
							terrain[compteur][compteur2].xImg+=scroll_speed;
							terrain[compteur][compteur2].x1+=scroll_speed;
							terrain[compteur][compteur2].x2+=scroll_speed;
							terrain[compteur][compteur2].x3+=scroll_speed;
							terrain[compteur][compteur2].x4+=scroll_speed;
						}
					}
				}
				if(e.motion.x >= gpScreen->w - 30 && e.motion.x <= gpScreen->w && e.type==SDL_MOUSEMOTION){
					for (int compteur=0;compteur<N;compteur++){
						for (int compteur2=0;compteur2<M;compteur2++){
							terrain[compteur][compteur2].xImg-=scroll_speed;
							terrain[compteur][compteur2].x1-=scroll_speed;
							terrain[compteur][compteur2].x2-=scroll_speed;
							terrain[compteur][compteur2].x3-=scroll_speed;
							terrain[compteur][compteur2].x4-=scroll_speed;
						}
					}
				}
				if( e.motion.y >=0 && e.motion.y <=30 && e.type==SDL_MOUSEMOTION){
					for (int compteur=0;compteur<N;compteur++){
						for (int compteur2=0;compteur2<M;compteur2++){
							terrain[compteur][compteur2].yImg+=scroll_speed;
							terrain[compteur][compteur2].y1+=scroll_speed;
							terrain[compteur][compteur2].y2+=scroll_speed;
							terrain[compteur][compteur2].y3+=scroll_speed;
							terrain[compteur][compteur2].y4+=scroll_speed;
						}
					}
				}
				if(e.motion.y >= gpScreen->h - 30 && e.motion.y <= gpScreen->h && e.type==SDL_MOUSEMOTION){
					for (int compteur=0;compteur<N;compteur++){
						for (int compteur2=0;compteur2<M;compteur2++){
							terrain[compteur][compteur2].yImg-=scroll_speed;
							terrain[compteur][compteur2].y1-=scroll_speed;
							terrain[compteur][compteur2].y2-=scroll_speed;
							terrain[compteur][compteur2].y3-=scroll_speed;
							terrain[compteur][compteur2].y4-=scroll_speed;
						}
					}
				}
				}

			//fin action du joueur

			if(tab[joueur_actu].humain==0){ 	//===================================================TOUR DU BOT===================================================//
				if(nb_tour>=VITESSE_JEU_BOT){
					if(sel==0){ //SELECTION
						fprintf(stderr,"TOUR DU BOT %d : PTS D'ACTION = %d\n",joueur_actu,tab[joueur_actu].pts_action_actu);
						for (int i=0;i<N;i++){ //deselectionne toutes les pieces
							for (int j=0;j<M;j++){
								if(terrain[i][j].piece && terrain[i][j].piece->select==1){
										terrain[i][j].piece->select=0;
								}
							}
						}
						int var5=0;
						int var6=(rand()%tab[joueur_actu].nb_unite);
						for (int i=0;i<N;i++){ //selection d'une piece
							for (int j=0;j<M;j++){
								if(terrain[i][j].piece && terrain[i][j].piece->select==0 && terrain[i][j].piece->joueur==joueur_actu && var5==var6){
									terrain[i][j].piece->select=1;
									x_bot=i;
									y_bot=j;
								}
								if(terrain[i][j].piece && terrain[i][j].piece->joueur==joueur_actu)
									var5++;
							}
						}

						centrer_camera(terrain,terrain[x_bot][y_bot].xImg,terrain[x_bot][y_bot].yImg,*largeur,*hauteur);
						sel=1;
					}else{ //ACTION
						int nb_ennemies_portee=a_portee(terrain,x_bot,y_bot,joueur_actu);
						if((nb_ennemies_portee>=1 && terrain[x_bot][y_bot].piece->classe!=priest)|| (nb_ennemies_portee>=2 && terrain[x_bot][y_bot].piece->classe==priest) || (reste_allie(terrain,joueur_actu)==1 && terrain[x_bot][y_bot].piece->classe==priest)){
							fprintf(stderr,"ATTAQUE\n");
							attaquer_meilleur_cible(terrain,x_bot,y_bot,nb_ennemies_portee,joueur_actu,tab,aff_deg,tab_info_bash,variable2);
						}else{
							fprintf(stderr,"DEPLACEMENT\n");
							depla_atk_mov(terrain,x_bot,y_bot,joueur_actu,tab,tab_info_bash,variable2);
						}


						sel=0;
					}
					nb_tour=0;
					if(tab[joueur_actu].pts_action_actu<=0){ //direction blockage
						for (int i=0;i<N;i++){
							for (int j=0;j<M;j++){
								if(terrain[i][j].piece && terrain[i][j].piece->joueur==joueur_actu){
									IA_blockage_direction(terrain,i,j,joueur_actu);//tourne le perso selon la direction la plus intéressante
								}
							}
						}
					}

				}


			}


			for(int i=0;i<J;i++){
				if(tab[i].nb_unite<=0 && tab[i].id_joueur!=-1){
					tab[i].id_joueur=-2;
				}
			}


			nb_joueur_restant=0;
			for(int i=0;i<J;i++){		//fermeture de la fenetre qd il reste un joueur en vie seulement (a modifié pour retourner au menu qd le joueur gagne)
				if(tab[i].id_joueur!=-1 && tab[i].id_joueur!=-2){
					nb_joueur_restant++;
				}
			}

			if((jour_nuit%((DURE_JOUR_NUIT/24)*3))>=-20 && (jour_nuit%((DURE_JOUR_NUIT/24)*3))<=20){
				jour_nuit+=40;
				frame_anim_montre++;
			}
			if(frame_anim_montre>=8 && (jour_nuit%((DURE_JOUR_NUIT/24)*3))>=20 && (jour_nuit%((DURE_JOUR_NUIT/24)*3))<=60){
				frame_anim_montre=0;
			}






			if(nb_joueur_restant==1){
				for(int i=0;i<J;i++){
					if(tab[i].id_joueur!=-1 && tab[i].id_joueur!=-2){
							sprintf(variable,"LE JOUEUR %d GAGNE EN %d TOURS !\n",i,compteur_tour);
						ajouter_ligne_bash(variable,tab_info_bash,info,variable2);
					}
				}
				//ecran de victoire/defaite

				running=Menu;
			}


			affichage_principale(renderer,pWindow,bordure,largeur,hauteur,tab,aff_deg,tab_info_bash,terrain,joueur_actu,image,compteur_anim,nb_joueur_restant,compteur_tour,frame_anim_montre,jour_nuit,variable2);


			for(int i=0;i<J;i++){
				if(tab[i].id_joueur==-2){
					tab[i].id_joueur=-1;
				}
			}

			if((tab[joueur_actu].pts_action_actu<=0 && tab[joueur_actu].humain==0 )|| (tab[joueur_actu].pts_action_actu<=0 && fin_tour==1) || (fin_tour==1)){				//gestion des tours de jeu
				tab[joueur_actu].pts_action_actu=tab[joueur_actu].pts_action_max;
				do{
					joueur_actu=(joueur_actu+1)%J;
					if(joueur_actu==0){
						compteur_tour++;
					}
				}while(tab[joueur_actu].id_joueur==-1);
				fin_tour=0;
			}

			//incrémentation a chaque tours
			nb_tour=(nb_tour+1)%(VITESSE_JEU_BOT*2);
			compteur_anim=compteur_anim%(VITESSE_ANIM*4);
			compteur_anim++;
			jour_nuit=(jour_nuit+1)%DURE_JOUR_NUIT;



		//===================================ACTUALISATION DES TOURS==========================================//

		}//fin boucle de jeu
	}
	/*fin reseau*/
	if(role_reseau==0)
		fin_connexion(server_socket);
	else if(role_reseau==1)
		fin_connexion(server_socket);
	//Destruction de la fenetre
	SDL_DestroyWindow(pWindow);

//	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	TTF_Quit();
  SDL_Quit();
	return 0;
}
