#ifndef INTERFACE_H
#define INTERFACE_H

#include "card.h"
#include "game.h"
#include "lab.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 30
#define CARD_HEIGHT 6
#define CARD_WIDTH 9

// Function Prototypes

void enter_to_continue();

char read_char(FILE *stream);

int read_int(FILE *stream);

char *read_string(FILE *stream);

void print_game_start();

void clear_screen();

AnsiColor get_card_ui_color(color_t color);

bool is_player_first();

void print_score(const deck_t *deck);

void print_no_lifes();

void print_player_hand(const hand_t *player_hand);

void print_bot_hand(const hand_t *bot_hand);

void print_deck(const deck_t *deck);

void print_clues_lives(int clues, int lives);

void print_ui(const game_t *game);

#endif //INTERFACE_H
