//
// Created by William on 26/09/2022.
//

#ifndef COURSC_PLAYER_H
#define COURSC_PLAYER_H

typedef struct Player Player;
struct Player{
  char name[255];
  int life;
  int defense;
  int attack;
  int is_dead;
};

#endif // COURSC_PLAYER_H
