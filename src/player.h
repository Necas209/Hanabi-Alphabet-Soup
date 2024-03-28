#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

// Player related functions

int get_player_playable(const hand_t *player_hand, const deck_t *deck);

bool player_turn(game_t *game);

bool give_bot_clue(const hand_t *player_hand, hand_t *bot_hand);

bool player_play(game_t *game);

bool player_discard(game_t *game);

#endif //PLAYER_H
