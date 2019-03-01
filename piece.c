#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    soldat, archer,cavalier
}classe_t;
typedef struct piece_s{
    char * nom_classe;
    int pdv; //point de vie
    int puissance;
    int armure;
    int block; //pourcentage de chance de bloquer
    int portee; //portée de l'attaque
    int deplacement; //nombre de case de mouvement
}piece_t;

piece_t * init_piece(classe_t classe){
    piece_t * piece=malloc(sizeof(piece_t));
    switch (classe){
        case 0:
            piece->nom_classe=malloc(sizeof(char)*strlen("soldat")+1);
            piece->nom_classe = "soldat";
            piece->pdv=100;
            piece->puissance = 50;
            piece->armure=40;
            piece->block=50;
            piece->portee=1;
            piece->deplacement=2;
            break;
        case 1:
            piece->nom_classe=malloc(sizeof(char)*strlen("archer")+1);
            piece->nom_classe = "archer";
            piece->pdv=60;
            piece->puissance = 20;
            piece->armure=20;
            piece->block=20;
            piece->portee=3;
            piece->deplacement=2;
            break;
        case 2:
            piece->nom_classe=malloc(sizeof(char)*strlen("cavalier")+1);
            piece->nom_classe = "cavalier";
            piece->pdv=110;
            piece->puissance = 30;
            piece->armure=20;
            piece->block=30;
            piece->portee=1;
            piece->deplacement=4;
            break;
        default: printf("erreur dans la création d'une piece\n");
    }
    return (piece);
}

int piece_existe(piece_t * piece){
    return(!(piece==NULL));
}

void afficher_piece(piece_t * piece){
    if (piece_existe(piece)){
        printf("classe : %s\n", piece->nom_classe);
        printf("lp : %d\n", piece->pdv);
        printf("pui : %d\n", piece->puissance);
        printf("armure : %d\n", piece->armure);
        printf("block : %d\n", piece->block);
        printf("portee : %d\n",piece->portee);
        printf("deplacement : %d\n", piece->deplacement);
    }
    else
        printf("Pas de piece a afficher.\n");
}

int destruction_piece(piece_t ** piece){
    //free((*piece)->nom_classe);
    free(*piece);
    (*piece)=NULL;
}

void affrontement(piece_t * attaquant, piece_t * defenseur){

}

int main(int argc, char const *argv[]) {
    piece_t * knight1 = NULL;
    printf("création.............\n");
    knight1=init_piece(0);
    printf("affichage............\n");
    afficher_piece(knight1);
    printf("destruction..........\n");
    destruction_piece(&knight1);
    printf("affichage............\n");
    afficher_piece(knight1);
    printf("oui\n");
    return 0;
}
