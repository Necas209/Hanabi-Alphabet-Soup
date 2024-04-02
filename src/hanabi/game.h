#ifndef GAME_H

#define GAME_H

#include "deck.h"

#define MAX_LIVES 3
#define MAX_HINTS 8
#define MAX_SCORE 25

typedef struct game {
    deck_t deck;
    int lives;
    int hints;
    hand_t player_hand;
    hand_t bot_hand;
    bool player_first;
} game_t;

game_t new_game(deck_t deck, hand_t player_hand, hand_t bot_hand, bool player_first);

void free_game(game_t *game);

void game_loop(game_t *game);

void game_turn(game_t *game);

bool is_over(const game_t *game);

cJSON *get_game_json(const game_t *game);

void get_game_from_json(game_t *game, const cJSON *game_json);

void save_game(const game_t *game, const char *filename);

game_t *load_game(const char *filename);

#endif //GAME_H
