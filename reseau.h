#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<strings.h>

#include "piece.h"
//#define SERVEURNAME "192.168.1.106" // adresse IP de mon serveur
#define SERVEURNAME "127.0.0.1" // adresse IP de mon serveur

#define QUITTER "QUITTER"

char buffer[512];

void fin(int sig);
int hostname_to_ip(char * hostname , char* ip);
void view_ip();
void send_game_state(int client_socket,case_t terrain[N][M]);
int setup_serv ();
int connection_serv ();
