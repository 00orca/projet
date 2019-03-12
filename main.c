#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>


#include "piece.h"
#include "interface.h"


//=======STRUCT========//




//=====================================MAIN=============================//

int main(int argc, char** argv)
{
	SDL_Window* pWindow = NULL;
	SDL_Renderer *renderer=NULL;
  SDL_Rect  imgDestRect;

	int preset=1;
  int alea;
  int var1;
	int scroll_speed=20;
	case_t terrain[N][M];
	srand(time(NULL));
	FILE * fp;
	joueurs_t tab[J];
	int nb_joueur_restant;
	int joueur_actu=0;




    /* Initialisation SDL*/
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ) {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }
	/* Initialisation TTF */
	if(TTF_Init() == -1) {
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	/* Création de la fenêtre */
	pWindow = SDL_CreateWindow("Tactic Arena Upgraded V1.0",SDL_WINDOWPOS_UNDEFINED,
												  SDL_WINDOWPOS_UNDEFINED,
												  1200,
												  900,
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

	// CREATION TEXTURE CASE DE BASE  TYPE=1
	SDL_Texture* image_case_normale = load_image("images/case_normalv2.png",renderer);
	// CREATION TEXTURE CASE D'eau  TYPE=5
	SDL_Texture* image_case_eau = load_image("images/case_eauv2.png",renderer);
	// CREATION TEXTURE CASE DE foret TYPE=6
	SDL_Texture* image_case_foret = load_image("images/case_foretv2.png",renderer);
	// CREATION TEXTURE CASE DE montagne  TYPE=7
	SDL_Texture* image_case_montagne = load_image("images/case_montagnev2.png",renderer);
	// CREATION TEXTURE CASE DE BASE COIN  TYPE=2
	SDL_Texture* image_case_coin = load_image("images/case_normal_coinv2.png",renderer);
	// CREATION TEXTURE de bordure gauche  TYPE=3
	SDL_Texture* image_case_normal_bordure_gauche = load_image("images/case_normal_bordure_gauchev2.png",renderer);
	// CREATION TEXTURE de bordure droite  TYPE=4
	SDL_Texture* image_case_normal_bordure_droite = load_image("images/case_normal_bordure_droitev2.png",renderer);

//===IMAGES POUR EVENEMENTS==//
	SDL_Texture* image_deplacement = load_image("images/deplacement.png",renderer);

	SDL_Texture* image_attaque = load_image("images/attaque.png",renderer);

	SDL_Texture* image_inter = load_image("images/inter.png",renderer);

	SDL_Texture* image_knight = load_image("images/image_knight.png",renderer);

	SDL_Texture* image_scout = load_image("images/image_scout.png",renderer);

	SDL_Texture* image_priest = load_image("images/image_priest.png",renderer);

	SDL_Texture* image_magician = load_image("images/image_magician.png",renderer);


//==================================INITIALISATION GRILLE============================//
    //choix du mode de génération
//	printf("1 POUR CARTE ALEATOIRE, AUTRE CHIFFRE POUR UNE DES CARTES PRESET : ");
//	scanf("%d",&preset);


  if(preset>1){
    fp = fopen ("fichiers/preset1.txt", "r"); //preset en 7x7
  }
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){

			if(preset==1){			//======aleatoire=======//

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
				else{
					alea=rand()%6;
					if(alea==0){
						terrain[i][j].type=5;
					}
					else if(alea==1){
						terrain[i][j].type=7;
					}
					else if(alea==2){
						terrain[i][j].type=6;
					}
					else if(alea>=3){
						terrain[i][j].type=1;
					}
				}

			}else{						//=====preset de carte chargé par fichiers=====//

				fscanf(fp, "%i", &var1);
        terrain[i][j].type=var1;
			}

		}

	}
	if(preset>1){
		fclose(fp);
	}



	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			if(terrain[i][j].type==1){
				terrain[i][j].type_case=(image_case_normale);
			}
			else if(terrain[i][j].type==2){
				terrain[i][j].type_case=(image_case_coin);
			}
			else if(terrain[i][j].type==3){
				terrain[i][j].type_case=(image_case_normal_bordure_gauche);
			}
			else if(terrain[i][j].type==4){
				terrain[i][j].type_case=(image_case_normal_bordure_droite);
			}
			else if(terrain[i][j].type==5){
				terrain[i][j].type_case=(image_case_eau);
			}
			else if(terrain[i][j].type==6){
				terrain[i][j].type_case=(image_case_foret);
			}
			else if(terrain[i][j].type==7){
				terrain[i][j].type_case=(image_case_montagne);
			}
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

		}
	}

	//initialisation de la grille//

	(imgDestRect.w)=100;
	(imgDestRect.h)=100;
	int bordure=50;                                                                                                                    //les coef ci dessous permettent d'aligner les images car elle ne sont pas totalement droite dans le sprite
	for(int compteur=0, indice = bordure + (imgDestRect.h) *N + N, indice2=bordure + (imgDestRect.w) *N/1.5; compteur<N; compteur++,indice-=(bordure+(imgDestRect.h)/2)/2.1,indice2-=(bordure+(imgDestRect.w)/2)/1.5){
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
			tab[i].nb_unite=3;
		}


//=========================================================INITIALISATION DES UNITEES===========================================//
	for(int i=0;i<J;i++){
		int unit_gen=0;
		while(unit_gen<tab[i].nb_unite){
			for(int compteur=0;compteur<N; compteur++){
				for(int compteur2=0;compteur2<M; compteur2++){
					if(terrain[compteur][compteur2].piece==NULL && terrain[compteur][compteur2].type != 5){
						if(rand()%100 ==1 && unit_gen<tab[i].nb_unite){
							terrain[compteur][compteur2].piece=init_piece(((rand()%5)+1),i); //
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
		int running = 1;
		while(running) {
			SDL_Event e;

			while(SDL_PollEvent(&e)) {
				switch(e.type) {
					case SDL_QUIT:	//cas ou l'on souhaite quitter
						running = 0;
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
									fprintf(stderr,"x : %d \n",e.motion.x);
									fprintf(stderr,"x : %d \n",e.motion.y);

									//int a,b,a2,b2,a3,b3,a4,b4,res1,res2,res3,res4;
									for(int compteur=0;compteur<N;compteur++){
										for(int compteur2=0;compteur2<M; compteur2++){
											/* VERSION AVANCER NE FONCTIONNANT PAS ENCORE
											fprintf(stderr,"POUR  %d | %d : \n",compteur,compteur2);
											//Y
											a=((terrain[compteur][compteur2].y1-terrain[compteur][compteur2].y4)/(terrain[compteur][compteur2].x1-terrain[compteur][compteur2].x4));
											b= (terrain[compteur][compteur2].y4-a*terrain[compteur][compteur2].x4);
											res1=a*e.motion.x+b;
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
												if(terrain[compteur][compteur2].piece){
													for(int indice=0;indice<N;indice++){
														for(int indice2=0;indice2<M; indice2++){
															if(terrain[indice][indice2].piece && terrain[indice][indice2].piece->select==1){
																terrain[indice][indice2].piece->select=0;
															}
														}
													}
													terrain[compteur][compteur2].piece->select=1;

												}
											}
										}
									}
					      break;
					   	}
					 break;

				}
			}
							//======================================AFFICHAGE=========================================//


			SDL_SetRenderDrawColor(renderer,50, 50, 50, 0);
			SDL_RenderClear(renderer);

			for (int compteur=0;compteur<N;compteur++){
				for (int compteur2=0;compteur2<M;compteur2++){
					imgDestRect.x = terrain[compteur][compteur2].xImg;
					imgDestRect.y = terrain[compteur][compteur2].yImg;
					imgDestRect.w=100;
					imgDestRect.h=100;
					SDL_QueryTexture(terrain[compteur][compteur2].type_case, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
					SDL_RenderCopy(renderer, terrain[compteur][compteur2].type_case, NULL, &imgDestRect);

					if(terrain[compteur][compteur2].piece){ 		//AFFICHAGE DES UNITEES

						switch (terrain[compteur][compteur2].piece->classe){
								case 1:
								SDL_QueryTexture(image_knight, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								SDL_RenderCopy(renderer, image_knight, NULL, &imgDestRect);
								break;
								case 2:
								SDL_QueryTexture(image_scout, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								SDL_RenderCopy(renderer, image_scout, NULL, &imgDestRect);
								break;
								case 3:
								SDL_QueryTexture(image_priest, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								SDL_RenderCopy(renderer, image_priest, NULL, &imgDestRect);
								break;
								case 4:
								SDL_QueryTexture(image_magician, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
								SDL_RenderCopy(renderer, image_magician, NULL, &imgDestRect);
								break;
							}
					}


					if(terrain[compteur][compteur2].climat != 0){
						//afficher l'effet climatique sur la case

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
											imgDestRect.x = terrain[ind][ind2].xImg-bordure/6;
											imgDestRect.y = terrain[ind][ind2].yImg-bordure/6;
											SDL_QueryTexture(image_deplacement, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
											SDL_RenderCopy(renderer, image_deplacement, NULL, &imgDestRect);

										}
									}
								}
													//attaque
													/*
													for(int i=compteur-terrain[compteur][compteur2].piece->portee;i<=compteur+terrain[compteur][compteur2].piece->portee;i++){
														for(int j=compteur2-terrain[compteur][compteur2].piece->portee;j<=compteur2+terrain[compteur][compteur2].piece->portee;j++){
															if(terrain[i][j].piece){
																if(terrain[i][j].piece->joueur!=joueur_actu){
																	imgDestRect.x = terrain[i][j].xImg-bordure-10;
																	imgDestRect.y = terrain[i][j].yImg-bordure-10;
																	SDL_QueryTexture(image_attaque, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
																	SDL_RenderCopy(renderer, image_attaque, NULL, &imgDestRect);
																}
															}
														}
													}*/
							}
							else{
													//affiche dans un cadre les stats de l'ennemi + une fleche montrant le sens d'arret de l'ennemi


							}

										//autre affichages :
						}
										//
					}
				}
			}
			imgDestRect.w=150;			//affichage de l'interface et des stats + image de l'unité selectionné
			imgDestRect.h=200;
			imgDestRect.x = 0;
			imgDestRect.y = 0;
			SDL_QueryTexture(image_inter, NULL, NULL, &(imgDestRect.w), &(imgDestRect.h));
			SDL_RenderCopy(renderer,image_inter , NULL, &imgDestRect);

			SDL_RenderPresent(renderer);
							//===================================DEROULEMENT DU JEU==========================================//
							/*

							0) choix mode de jeu,premiere affichage au début du match juste avant avec carte de base et l'interface puis selection des unitées et mise a jours de la matrice
							puis affichage de nouveau avec les pieces affichées

							1)apparition de potentiel élements climatiques et changement des valeur dans la matrice pour les afficher dans la boucle d'affichage

							2)choix d'un perso ennemi a examiner ou d'un de ses perso pour déplacement ou attaque ennemi a porté + mise a jour des stats en fonction du terrain actuel
							 (mise a 1 d'une variable pour afficher dans la boucle d'affichage les cases de potentiel deplacement et attaques)

							 3)deplacement / combat (changement de place d'un personnage, calcule des dégats etc puis boucle d'affichage pour deplacer le perso, suprimmer les morts etc)
							 et verification de vitoire ou non pour afficher une message de victoire et retourner au menu

							 4)repetition des etapes 2 et 3 selon les points d'actions restants

							 5)changement d'une variable pour changement de joueur puis étapes de 1 a 5 de nouveau


							*/

							//3
							//move()




			nb_joueur_restant=0;
			for(int i=0;i<J;i++){		//fermeture de la fenetre qd il reste un joueur en vie seulement (a modifié pour retourner au menu qd le joueur gagne)
				if(tab[i].nb_unite>0){
					nb_joueur_restant++;
				}
			}
			if(nb_joueur_restant==1){
				running=0;
			}

			if(tab[joueur_actu].pts_action_actu==0){
				tab[joueur_actu].pts_action_actu=tab[joueur_actu].pts_action_max;
				joueur_actu++;
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
