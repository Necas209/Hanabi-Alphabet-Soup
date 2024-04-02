#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

uint32_t get_player_playable(const hand_t *player_hand, const deck_t *deck);

int player_turn(game_t *game);

int player_hint(game_t *game);

int player_play(game_t *game);

int player_discard(game_t *game);

#endif //PLAYER_H
