//
// Created by William on 26/09/2022.
//

#ifndef COURSC_GAME_H
#define COURSC_GAME_H

struct Player init_player();

void display_players(struct Player *players, int nbPlayers);

int what_action();

void perform_action(int action, int index_current_player, struct Player *players, int nbPlayer);

int update_dead(struct Player *players, int nbPlayers);

#endif // COURSC_GAME_H
