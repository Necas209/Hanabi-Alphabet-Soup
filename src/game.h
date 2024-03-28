#ifndef GAME_H

#define GAME_H

#include "deck.h"

#define MAX_LIVES 3
#define MAX_CLUES 8

typedef struct game {
    deck_t deck;
    int lives;
    int clues;
    hand_t player_hand;
    hand_t bot_hand;
    bool player_first;
} game_t;

game_t new_game(deck_t deck, hand_t player_hand, hand_t bot_hand, bool player_first);

void game_loop(game_t *game);

void game_turn(game_t *game);

void save_game(const game_t *game, const char *filename);

game_t *load_game(const char *filename);

#endif //GAME_H
