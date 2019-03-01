#include <stdio.h>
#include <stdlib.h>

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

void init_piece(classe_t classe, piece_t * piece){
    switch (classe){
        case 0:
            piece->nom_classe = "soldat";
            piece->pdv=100;
            piece->puissance = 50;
            piece->armure=40;
            piece->block=50;
            piece->portee=1;
            piece->deplacement=2;
            break;
        case 1:
            piece->nom_classe = "archer";
            piece->pdv=60;
            piece->puissance = 20;
            piece->armure=20;
            piece->block=20;
            piece->portee=3;
            piece->deplacement=2;
            break;
        case 2:
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
}

void afficher_piece(piece_t * piece){
    printf("%s\n", piece->nom_classe);
    printf("lp : %d\n", piece->pdv);
    printf("pui : %d\n", piece->puissance);
    printf("armure : %d\n", piece->armure);
    printf("block : %d\n", piece->block);
    printf("portee : %d\n",piece->portee);
    printf("deplacement : %d\n", piece->deplacement);
}

void destruction_piece(piece_t ** piece){
    //free((*piece)->nom_classe);
    free(*piece);
}

void affrontement(piece_t * attaquant, piece_t * defenseur){

}

int main(int argc, char const *argv[]) {
    piece_t * knight1;
    init_piece(0,knight1);
    afficher_piece(knight1);
    destruction_piece(&knight1);
    return 0;
}
