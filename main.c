#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


#include "piece.h"
#include "interface.h"


//=======STRUCT========//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//=====================================MAIN=============================//

int main(int argc, char** argv)
{
	SDL_Window* pWindow = NULL;
	SDL_Renderer *renderer=NULL;
  SDL_Rect imgDestRect;
	char variable[50];

	float coefZoom=1;
  int alea;
  int var1;
	int scroll_speed=20;
	case_t terrain[N][M];
	srand(time(NULL));
	FILE * fp;
	joueurs_t tab[J];
	int nb_joueur_restant;
	int joueur_actu=0;
	int clicout;
	image_t image[Z];
	SDL_Color c = {0,0,0,0};
	SDL_Color b = {255,255,255,255};
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



	if(!pWindow){
		fprintf(stderr, "Erreur à la création de la fenetre : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL){
		fprintf(stderr, "Erreur à la création du renderer\n");
		exit(EXIT_FAILURE);
	}





//===================================TEXTURES==========================================//

loadImage(image,renderer);

//==================================INITIALISATION GRILLE============================//
    //choix du mode de génération
//	printf("1 POUR CARTE ALEATOIRE, AUTRE CHIFFRE POUR UNE DES CARTES PRESET : ");
//	scanf("%d",&preset);


  if(PRESET>1){
    fp = fopen ("fichiers/preset1.txt", "r"); //preset en 7x7
  }
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){

			if(PRESET==1){			//======preset=======//

				if(i==0 && j==0){
					terrain[i][j].type=2;
				}
				else if(i==0 && j>0){
					terrain[i][j].type=4;
				}
				else if(i>0 && j==0){
					terrain[i][j].type=3;
				}
        else if((j==N-1 && i!=0 )||( i==M-1 && j!=0)){
          terrain[i][j].type=1;
        }
				else{												//ALEA "INTELLIGENTE"//
					alea=rand()%(N*M);
					if((alea<(0.05*N*M) )||( (i-1<N && terrain[i-1][j].type==5 && alea<(0.4*N*M)) || (j-1<N && terrain[i][j-1].type==5 && alea<(0.4*N*M)) || (i+1<N && terrain[i+1][j].type==5 && alea<(0.4*N*M)) || (i<N && terrain[i][j+1].type==5 && alea<(0.4*N*M)) )){
						terrain[i][j].type=5;

					}
					else if(((alea<(0.15*N*M) && alea>(0.05*N*M) )|| (i-1<N && terrain[i-1][j].type==7 && alea<(0.45*N*M)) || (j-1<N && terrain[i][j-1].type==7 && alea<(0.45*N*M)) || (i+1<N && terrain[i+1][j].type==7 && alea<(0.45*N*M)) || (i<N && terrain[i][j+1].type==7 && alea<(0.45*N*M)) )){
						terrain[i][j].type=7;
					}
					else if(((alea<(0.25*N*M) && alea>(0.15*N*M) )|| (i-1<N && terrain[i-1][j].type==6 && alea<(0.55*N*M)) || (j-1<N && terrain[i][j-1].type==6 && alea<(0.55*N*M)) || (i+1<N && terrain[i+1][j].type==6 && alea<(0.55*N*M)) || (i<N && terrain[i][j+1].type==6 && alea<(0.55*N*M)) )){
						terrain[i][j].type=6;
					}
					else{
						terrain[i][j].type=1;
					}
				}

			}else{						//=====preset de carte chargé par fichiers=====//

				fscanf(fp, "%i", &var1);
        terrain[i][j].type=var1;
			}

		}

	}
	if(PRESET>1){
		fclose(fp);
	}



	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			terrain[i][j].climat=0;
			terrain[i][j].xImg=0;
			terrain[i][j].yImg=0;
			terrain[i][j].x1=0;
			terrain[i][j].y1=0;
			terrain[i][j].x2=0;
			terrain[i][j].y2=0;
			terrain[i][j].x3=0;
			terrain[i][j].y3=0;
			terrain[i][j].x4=0;
			terrain[i][j].y4=0;
			terrain[i][j].piece=NULL;
			terrain[i][j].deplacement=0;
			terrain[i][j].attaque=0;

		}
	}

	//initialisation de la grille//

	(imgDestRect.w)=100;
	(imgDestRect.h)=100;
	int bordure=50;                                                                                                                    //les coef ci dessous permettent d'aligner les images car elle ne sont pas totalement droite dans le sprite
	for(int compteur=0, indice = SCREEN_HEIGHT/2, indice2=SCREEN_WIDTH/2; compteur<N; compteur++,indice-=(bordure+(imgDestRect.h)/2)/2.1,indice2-=(bordure+(imgDestRect.w)/2)/1.5){
		for(int compteur2=0, indice3= indice , indice4 = indice2; compteur2<M; compteur2++,indice3-=(bordure+(imgDestRect.h)/2)/1.5,indice4+=(bordure+(imgDestRect.w)/2)/1.98){

				imgDestRect.x = indice4;
				imgDestRect.y = indice3;
				imgDestRect.w=100;
				imgDestRect.h=100;

				if(!terrain[compteur][compteur2].x1 || !terrain[compteur][compteur2].x2 || !terrain[compteur][compteur2].y1 || !terrain[compteur][compteur2].y2){

					terrain[compteur][compteur2].xImg=indice4;
					terrain[compteur][compteur2].yImg=indice3;
					 //point en haut du losange puis les trois points suivant sont les sommet dans le sens des aiguille d'une montre.



					terrain[compteur][compteur2].x1=imgDestRect.x+imgDestRect.w/2;
					terrain[compteur][compteur2].y1=imgDestRect.y;

					terrain[compteur][compteur2].x2=imgDestRect.x+imgDestRect.w;
					terrain[compteur][compteur2].y2=imgDestRect.y+imgDestRect.h/2;

					terrain[compteur][compteur2].x3=imgDestRect.x+imgDestRect.w/2;
					terrain[compteur][compteur2].y3=imgDestRect.y+imgDestRect.h;

					terrain[compteur][compteur2].x4=imgDestRect.x;
					terrain[compteur][compteur2].y4=imgDestRect.y+imgDestRect.h/2;

				}
			}
		}


//=========================================================INITIALISATION DES JOUEURS=============================================//

		for(int i=0;i<J;i++){
			tab[i].id_joueur=i;
			tab[i].pts_action_max=4;
			tab[i].pts_action_actu=tab[i].pts_action_max;
			tab[i].nb_unite=5;
		}


//=========================================================INITIALISATION DES UNITEES===========================================//
		int unit_gen;
		for(int i=0;i<J;i++){
			unit_gen=0;
			while(unit_gen<tab[i].nb_unite){
				for(int compteur=0;compteur<N; compteur++){
					for(int compteur2=0;compteur2<M; compteur2++){
						if(terrain[compteur][compteur2].piece==NULL && terrain[compteur][compteur2].type != 5){
							if(rand()%(N*M) ==1 && unit_gen<tab[i].nb_unite){
								terrain[compteur][compteur2].piece=init_piece(((rand()%NB_CLASSE)+1),i); //
								unit_gen++;
							}
						}
					}
				}
			}
		}


//========================================FENETRE=====================================//

	if( pWindow )
	{
		menu_e running = Menu;
		while(running != Quit) {
			SDL_Event e;
			if(running == Menu){
				int longeur = draw_menu(renderer,pWindow);
				while(SDL_PollEvent(&e)) {
					switch(e.type) {
						case SDL_QUIT:	//cas ou l'on souhaite quitter
							running = Quit;
						break;
						case SDL_MOUSEBUTTONDOWN:
							if(e.button.button == SDL_BUTTON_LEFT){
								if (e.button.y > longeur && e.button.y < longeur*2)running = HvsH;
								if (e.button.y > longeur*2 && e.button.y < longeur*3)running = HvsO;
								if (e.button.y > longeur*3 && e.button.y < longeur*4)running = About;
								if (e.button.y > longeur*4 && e.button.y < longeur*5)running = Quit;
							}
						break;
					}
				}
			}else if(running == About){
				about(renderer,pWindow);
				gpScreen = SDL_GetWindowSurface(pWindow);
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
			}else if(running == HvsH || running == HvsO){
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
							}
							break;

							case SDL_MOUSEBUTTONDOWN:
						  	switch (e.button.button)
						    {
						    	case SDL_BUTTON_LEFT:
										if(e.button.x > gpScreen->w - 60 && e.button.y >  gpScreen->h - 30){
											running = Menu;
										}
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
												if(e.motion.y > terrain[compteur][compteur2].y1+10 && e.motion.y < terrain[compteur][compteur2].y3-10 && e.motion.x > terrain[compteur][compteur2].x4+10 && e.motion.x < terrain[compteur][compteur2].x2-10){
													fprintf(stderr,"la case %d | %d a été selectionné. \n",compteur,compteur2);
													//=================SELECTION D'UNE PIECE====================//
													if(terrain[compteur][compteur2].piece){
														clicout=1;

														for(int x=0;x<N;x++){
															for(int y=0;y<M;y++){
																if(terrain[x][y].piece && terrain[x][y].piece->joueur==joueur_actu && terrain[x][y].piece->select==1){
																	combat(terrain,x,y,compteur,compteur2,joueur_actu,tab);
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

													move(terrain,compteur,compteur2,joueur_actu,tab);
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
						      break;
						   	}
					break;
					case SDL_MOUSEWHEEL:
						if(e.wheel.y==1){
							coefZoom+=0.01;
							for(int a=0;a<N;a++){
								for(int b=0;b<M;b++){
									terrain[a][b].xImg-=15;
									terrain[a][b].yImg-=15;
									terrain[a][b].x1-=15;
									terrain[a][b].x2-=15;
									terrain[a][b].x3-=15;
									terrain[a][b].x4-=15;
									terrain[a][b].y1-=15;
									terrain[a][b].y2-=15;
									terrain[a][b].y3-=15;
									terrain[a][b].y4-=15;
								}
							}

						}
						else{
							coefZoom-=0.01;
							for(int a=0;a<N;a++){
								for(int b=0;b<M;b++){
									terrain[a][b].xImg+=15;
									terrain[a][b].yImg+=15;
									terrain[a][b].x1+=15;
									terrain[a][b].x2+=15;
									terrain[a][b].x3+=15;
									terrain[a][b].x4+=15;
									terrain[a][b].y1+=15;
									terrain[a][b].y2+=15;
									terrain[a][b].y3+=15;
									terrain[a][b].y4+=15;
								}
							}
						}

					break;
					}
				}
				gpScreen = SDL_GetWindowSurface(pWindow);
				if( e.motion.x >0 && e.motion.x <30 && e.type!=SDL_MOUSEWHEEL){
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
				if(e.motion.x > gpScreen->w - 30 && e.motion.x < gpScreen->w && e.type!=SDL_MOUSEWHEEL){
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
				if( e.motion.y >0 && e.motion.y <30 && e.type!=SDL_MOUSEWHEEL){
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
				if(e.motion.y > gpScreen->h - 30 && e.motion.y < gpScreen->h && e.type!=SDL_MOUSEWHEEL){
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



								//======================================AFFICHAGE=========================================//


				SDL_SetRenderDrawColor(renderer,50, 50, 50, 0);
				SDL_RenderClear(renderer);

				for (int compteur=0;compteur<N;compteur++){
					for (int compteur2=0;compteur2<M;compteur2++){

						if(terrain[compteur][compteur2].type==1){
							afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_normalv2.png",image,renderer,coefZoom);
						}
						else if(terrain[compteur][compteur2].type==2){
							afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_normal_coinv2.png",image,renderer,coefZoom);
						}
						else if(terrain[compteur][compteur2].type==3){
							afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_normal_bordure_gauchev2.png",image,renderer,coefZoom);
						}
						else if(terrain[compteur][compteur2].type==4){
							afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_normal_bordure_droitev2.png",image,renderer,coefZoom);
						}
						else if(terrain[compteur][compteur2].type==5){
							afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_eauv2.png",image,renderer,coefZoom);
						}
						else if(terrain[compteur][compteur2].type==6){
							afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_foretv2.png",image,renderer,coefZoom);
						}
						else if(terrain[compteur][compteur2].type==7){
							afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg,100,100,"images/case_montagnev2.png",image,renderer,coefZoom);
						}
					}
				}

				for (int compteur=0;compteur<N;compteur++){
					for (int compteur2=0;compteur2<M;compteur2++){
						if(terrain[compteur][compteur2].piece){
							if(terrain[compteur][compteur2].piece->select){		//affichage case possible déplacement ou attaque si allié, sinon affiche le stats de la cible et sa direction d'arret;
								if(terrain[compteur][compteur2].piece->joueur==joueur_actu){
														//deplacement
									pathfinding(terrain,compteur,compteur2);

									for (int ind=0;ind<N;ind++){
										for (int ind2=0;ind2<M;ind2++){
											if(terrain[ind][ind2].deplacement==1){
												afficher_img(terrain[ind][ind2].xImg-bordure/15+8,terrain[ind][ind2].yImg-bordure/8+3,100,100,"images/deplacement.png",image,renderer,coefZoom);
											}
										}
									}
										//attaque
									pathfinding_combat(terrain,compteur,compteur2,joueur_actu);

									for (int ind=0;ind<N;ind++){
										for (int ind2=0;ind2<M;ind2++){
											if(terrain[ind][ind2].attaque==1){
												afficher_img(terrain[ind][ind2].xImg-bordure/9,terrain[ind][ind2].yImg-bordure/9,100,100,"images/attaque.png",image,renderer,coefZoom);

											}
										}
									}
								}
							}
						}
					}
				}


				for (int compteur=0;compteur<N;compteur++){
					for (int compteur2=0;compteur2<M;compteur2++){
						if(terrain[compteur][compteur2].piece){ 		//AFFICHAGE DES UNITEES

							if(terrain[compteur][compteur2].piece->joueur==joueur_actu){ //cercle des unité du joueur_actu affichage
								afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg+5,100,100,"images/image_allie.png",image,renderer,coefZoom);
							}


							switch (terrain[compteur][compteur2].piece->classe){
								case 1:
									afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg-10,100,100,"images/image_knight.png",image,renderer,coefZoom);
								break;
								case 2:

								afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg-10,100,100,"images/image_scout.png",image,renderer,coefZoom);

								break;
								case 3:

								afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg-10,100,100,"images/image_priest.png",image,renderer,coefZoom);

								break;
								case 4:

								afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg-10,100,100,"images/image_magician.png",image,renderer,coefZoom);

								break;
								case 5:

								afficher_img(terrain[compteur][compteur2].xImg,terrain[compteur][compteur2].yImg-10,100,100,"images/faucheuse.png",image,renderer,coefZoom);

								break;
							}
						}
					}
				}

				//menu nord

				afficher_img(SCREEN_WIDTH/3,0,75,400,"images/menu_nord.png",image,renderer,1);

				AfficherText("ACTION RESTANTE:","arial.ttf",c,12,renderer,SCREEN_WIDTH/3+200,30);

				AfficherText("TOUR DE JOUEUR ","arial.ttf",c,12,renderer,SCREEN_WIDTH/3+50,30);

				sprintf(variable, "%d",  tab[joueur_actu].pts_action_actu);

				AfficherText(variable,"arial.ttf",c,30,renderer,SCREEN_WIDTH/3+325,18);

				sprintf(variable, "%d",  joueur_actu);

				AfficherText(variable,"arial.ttf",c,30,renderer,SCREEN_WIDTH/3+165,18);
				//stats


				afficher_img(0,0,400,150,"images/inter.png",image,renderer,1);

				AfficherText("PDV        :","arial.ttf",c,12,renderer,30,155);

				AfficherText("ATK        :","arial.ttf",c,12,renderer,30,175);

				AfficherText("DEF        :","arial.ttf",c,12,renderer,30,195);

				AfficherText("BLOCK  :","arial.ttf",c,12,renderer,30,215);

				AfficherText("RANGE  :","arial.ttf",c,12,renderer,30,235);

				AfficherText("MS          :","arial.ttf",c,12,renderer,30,255);


				AfficherText("BACK", "arial.ttf",b,15,renderer,gpScreen->w - 60,gpScreen->h - 30);

				for(int i=0;i<N;i++){
					for(int j=0;j<M;j++){
						if(terrain[i][j].piece && terrain[i][j].piece->select==1){
							//affichage des infos de l'unité en haut a gauche.

							switch (terrain[i][j].piece->classe){
								case 1:
								afficher_img(20,20,100,100,"images/image_knight.png",image,renderer,1);
							break;
							case 2:

							afficher_img(20,20,100,100,"images/image_scout.png",image,renderer,1);

							break;
							case 3:

							afficher_img(20,20,100,100,"images/image_priest.png",image,renderer,1);

							break;
							case 4:

							afficher_img(20,20,100,100,"images/image_magician.png",image,renderer,1);

							break;
							case 5:

							afficher_img(20,20,100,100,"images/faucheuse.png",image,renderer,1);
							break;
							}
							//text



							sprintf(variable, "%d",  terrain[i][j].piece->joueur);
							AfficherText(variable,"arial.ttf",c,25,renderer,65,110);

							sprintf(variable, "%d", terrain[i][j].piece->pdv);
							AfficherText(variable,"arial.ttf",c,12,renderer,90,155);

							sprintf(variable, "%d", terrain[i][j].piece->puissance);
							AfficherText(variable,"arial.ttf",c,12,renderer,90,175);

							sprintf(variable, "%d", terrain[i][j].piece->armure);
							AfficherText(variable,"arial.ttf",c,12,renderer,90,195);

							sprintf(variable, "%d", terrain[i][j].piece->block);
							AfficherText(variable,"arial.ttf",c,12,renderer,90,215);

							sprintf(variable, "%d", terrain[i][j].piece->portee);
							AfficherText(variable,"arial.ttf",c,12,renderer,90,235);

							sprintf(variable, "%d", terrain[i][j].piece->deplacement);
							AfficherText(variable,"arial.ttf",c,12,renderer,90,255);

						}
					}
				}






				SDL_RenderPresent(renderer);
				SDL_Delay(16);


			//===================================ACTUALISATION DES TOURS==========================================//
				for(int i=0;i<J;i++){
					if(tab[i].nb_unite<=0){
						tab[i].id_joueur=-1;
					}
				}


				nb_joueur_restant=0;
				for(int i=0;i<J;i++){		//fermeture de la fenetre qd il reste un joueur en vie seulement (a modifié pour retourner au menu qd le joueur gagne)
					if(tab[i].id_joueur!=-1){
						nb_joueur_restant++;
					}
				}
				if(nb_joueur_restant==1){
					for(int i=0;i<J;i++){
						if(tab[i].id_joueur!=-1)
								fprintf(stderr,"LE JOUEUR %d GAGNE\n",i);
					}
					//ecran de victoire/defaite

					running = Quit;
				}

				if(tab[joueur_actu].pts_action_actu==0){				//gestion des tours de jeu
					tab[joueur_actu].pts_action_actu=tab[joueur_actu].pts_action_max;
					do{
						joueur_actu=(joueur_actu+1)%J;
					}while(tab[joueur_actu].id_joueur==-1);
				}


			}
		}

	}
	else {
		fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
	}

	//Destruction de la fenetre
	SDL_DestroyWindow(pWindow);

//	TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
	TTF_Quit();
  SDL_Quit();
	return 0;
}
