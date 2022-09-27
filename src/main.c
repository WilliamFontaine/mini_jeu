#include <stdio.h>

#include "player.h"
#include "game.h"

int number_of_player(){
  int nbPlayers = 0;
  do{
    printf("Saisissez un nombre de joueurs (entre 2 et 4):");
    scanf("%d",&nbPlayers);
  } while (nbPlayers < 2 || nbPlayers > 4);
  return nbPlayers;
}

void init_party(Player players[], int nbPlayer){
  for(int i = 0; i < nbPlayer; i++){
    printf("Initialisation du joueur %d:\n",i+1);
    players[i] = init_player();
  }
  display_players(players, nbPlayer);
}

void play_party(Player players[],int nbPlayer){
  int index = 0;
  int alive_player = nbPlayer;
  Action action;

  printf("\n");
  printf("Debut du jeu:\n");
  while (alive_player != 1){
    printf("C'est au tour de %s.\n", players[index].name);
    action = what_action();
    perform_action(action, index, players, nbPlayer);

    alive_player = update_dead(players, nbPlayer);
    display_players(players, nbPlayer);
    index++;
    if(players[index].is_dead == 0)
      index++;
    while (index >= nbPlayer){
      index = 0;
      while (players[index].is_dead == 0)
        index++;
    }
  }
  printf("%s a gagne la partie.\n", players[index].name);
}

int main(int argc, char *argv[]) {
  int nbPlayer = number_of_player();
  struct Player players[nbPlayer];
  init_party(players, nbPlayer);
  play_party(players, nbPlayer);
  return 0;
}

