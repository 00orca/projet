#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "piece.h"
#define M 2
#define N 2

int a_portee(piece_t * terrain [M][N],int x_att, int y_att, int x_def,int y_def){//coordonnees de la piece sur le terrain
    if ((x_def<=x_att+terrain[x_att][y_att]->portee) && (y_def<=y_att+terrain[x_att][y_att]->portee)&&(x_def>=x_att-terrain[x_att][y_att]->portee)&&(y_def>=y_att-terrain[x_att][y_att]->portee)){
            return 1;
    }
    return 0;
}

void combat(piece_t * terrain [M][N],int x_att, int y_att, int x_def,int y_def){
    if(a_portee(terrain,x_att, y_att, x_def, y_def)){
        terrain[x_def][y_def]->pdv-=terrain[x_att][y_att]->puissance;
    }
    else
        printf("echec de l'attaque (horsde portée).\n");
}

int main(){
    piece_t * terrain[M][N];
    terrain[0][0]=init_piece(0);
    terrain[0][1]=init_piece(0);
    combat(terrain,0,0,0,1);
    printf("fin du test de combat\n");
}
