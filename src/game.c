//
// Created by William on 26/09/2022.
//
#include <stdio.h>

#include "game.h"
#include "player.h"
#include "action.h"

void setPlayerName(Player *player) {
  printf("Quel est votre nom ?");
  scanf("%s", player->name);
}

void setSkills(Player *player){
  player->is_dead = 1;
  player->life = -1;
  player->defense = -1;
  player->attack = -1;
  int choice = 0;
  int points = 100;
  int competence = 0;
  int remain_skill = 3;
  do{
    if(remain_skill == 1) {
      if(player->life == -1) player->life = points;
      if(player->defense == -1) player->defense = points;
      if(player->attack == -1)player->attack = points;
      break ;
    }
    printf("Quel statistique voulez vous initialiser ?\n");
    do{
      if(player->life == -1){
        printf("\t- Tappez 1 pour la vie\n");
      }
      if(player->defense == -1){
        printf("\t- Tappez 2 pour la defense\n");
      }
      if(player->attack == -1){
        printf("\t- Tappez 3 pour l'attaque\n");
      }
      scanf("%d", &choice);
    } while (choice < 1 || choice > 3 ||choice == 1 && player->life != -1 ||
             choice == 2 && player->defense != -1 || choice == 3 && player->attack != -1);
    do {

      printf("Points restants : %d.\n", points);
      printf("Combien de points voulez vous attribuer a la competence (entre 0 et %d)?", points);
      scanf("%d", &competence);
    } while (competence > points ||remain_skill == 3 && points - competence < 2 || remain_skill == 2 && points - competence < 1 || competence <= 0);
    switch (choice) {
    case 1:
      player->life = competence;
      points -= competence;
      break ;
    case 2:
      player->defense = competence;
      points -= competence;
      break ;
    case 3:
      player->attack = competence;
      points -= competence;
      break ;
    default:
      printf("Erreur innatendue.");
    }
    remain_skill--;
  } while (player->life == -1 || player->defense == -1 || player->attack == -1);
}

Player init_player(){
  Player player;
  setPlayerName(&player);
  setSkills(&player);
  return player;
}

void display_player(Player players[], int index){
  if(players[index].is_dead != 0) {
    printf("\nAffichage du joueur '%s':\n",players[index].name);
    printf("\t- Points de vie: %d\n", players[index].life);
    printf("\t- Points de defense: %d\n", players[index].defense);
    printf("\t- Points d'attaque: %d\n", players[index].attack);
  }
  else{
    printf("%s est mort.\n", players[index].name);
  }
}

void display_players(Player players[], int nbPlayers){
  for (int i = 0; i < nbPlayers; ++i) {
    display_player(players, i);
  }
}

int what_action() {
  Action action;
  do{
    printf("Voulez-vous attaquer un autre joueur ou vous soigner ?\n");
    printf("\t- 1: attaquer\n");
    printf("\t- 2: se soigner\n");
    scanf("%d", &action);
  } while (action < 1 || action > 2);
  if(action == 1)
    return ATTACK;
  else
    return HEAL;
}

int ask_who_attack(Player players[], int index_player, int nbPlayer){
  int index;
    do{
      printf("Quel joueur voulez-vous attaquer ?\n");
      for(int i = 0; i < nbPlayer; i++) {
        if (i != index_player && players[i].is_dead != 0) {
          printf("\t- Tapper %d pour %s\n", i + 1, players[i].name);
        }
      }
      printf("Qui voulez-vous attaquer ?");
      scanf("%d", &index);
    } while (index-1 == index_player || index <= 0 || index > nbPlayer || players[index].is_dead == 0);
    index--;
    return index;
}

void attack(int index_player, Player players[], int nbPlayer){
  int index_attacked = ask_who_attack(players, index_player, nbPlayer);
  if(players[index_player].attack - (players[index_attacked].defense / 2) < 0)
    players[index_attacked].life += players[index_player].attack - (players[index_attacked].defense / 2);
  else
    players[index_attacked].life -= players[index_player].attack - (players[index_attacked].defense / 2);
}

void heal(int index_player, Player player[]){
  player[index_player].life += player[index_player].defense / 2;
}

void perform_action(Action action, int index_current_player, Player players[], int nbPlayer) {
  switch (action) {
  case ATTACK:
    attack(index_current_player, players, nbPlayer);
    break;
  case HEAL:
    heal(index_current_player, players);
    break;
  default:
    printf("Acton inconnue.\n");
    return;
  }
}

int update_dead(Player players[], int nbPlayers){
  int alive = 0;
  for(int i = 0; i < nbPlayers; i++){
    if(players[i].life <= 0)
      players[i].is_dead = 0;
    else
      alive ++;
  }
  return alive;
}
