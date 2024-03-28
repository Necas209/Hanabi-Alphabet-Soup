#ifndef BOT_H

#define BOT_H

#include "game.h"

// Function Prototypes

// Bot related functions

int get_bot_discardable(const hand_t *hand, int number, const deck_t *deck);

int get_bot_playable(const hand_t *hand, const deck_t *deck);

void bot_turn(game_t *game);

void give_player_clue(const hand_t *bot_hand, hand_t *player_hand, int idx);

#endif //BOT_H
