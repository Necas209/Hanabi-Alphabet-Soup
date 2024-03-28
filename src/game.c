#include "game.h"

#include <stdlib.h>

#include "bot.h"
#include "deck.h"
#include "player.h"
#include "interface.h"
#include "lab.h"

game_t new_game(const deck_t deck, const hand_t player_hand, const hand_t bot_hand,
                const bool player_first) {
    return (game_t){
        .deck = deck,
        .player_hand = player_hand,
        .bot_hand = bot_hand,
        .lives = MAX_LIVES,
        .clues = MAX_CLUES,
        .player_first = player_first,
    };
}

void game_loop(game_t *game) {
    while (game->deck.length > 0 && game->lives != 0 && get_score(&game->deck) < 25) {
        print_ui(game);
        game_turn(game);
    }
    if (get_score(&game->deck) == 25) {
        print_score(&game->deck);
    }
    if (game->deck.length == 0) {
        game_turn(game);
        if (game->lives == 0) {
            print_no_lifes();
        } else {
            print_score(&game->deck);
        }
    } else if (game->lives == 0) {
        print_no_lifes();
    }
    gotoxy(2, 34);
}

void game_turn(game_t *game) {
    save_game(game, "save.json");

    if (game->player_first) {
        while (!player_turn(game)) {
            gotoxy(120, 30);
            enter_to_continue();
        }
        enter_to_continue();
        print_ui(game);

        bot_turn(game);
        print_ui(game);
        enter_to_continue();
    } else {
        bot_turn(game);
        print_ui(game);
        enter_to_continue();

        while (!player_turn(game)) {
            gotoxy(120, 30);
            enter_to_continue();
        }
        enter_to_continue();
        print_ui(game);
    }
}

void save_game(const game_t *game, const char *filename) {
    FILE *save = fopen(filename, "w");
    if (save == NULL) {
        puts("Error opening save file.");
        exit(1);
    }

    fprintf(save, "{\n");
    fprintf(save, "\t\"deck\":\n");
    save_deck(save, &game->deck);
    fprintf(save, ",\n");

    fprintf(save, "\t\"player_hand\":\n");
    save_hand(save, &game->player_hand);
    fprintf(save, ",\n");

    fprintf(save, "\t\"bot_hand\":\n");
    save_hand(save, &game->bot_hand);
    fprintf(save, ",\n");

    fprintf(save, "\t\"player_first\": %d,\n", game->player_first);
    fprintf(save, "\t\"clues\": %d,\n", game->clues);
    fprintf(save, "\t\"lives\": %d\n", game->lives);
    fprintf(save, "}\n");
    fclose(save);
}

game_t *load_game(const char *filename) {
    FILE *save = fopen(filename, "r");
    if (save == NULL) {
        puts("Error opening save file.");
        exit(1);
    }

    game_t *game = malloc(sizeof(game_t));

    fscanf(save, "{\n");
    fscanf(save, "\t\"deck\":\n");
    load_deck(save, &game->deck);
    fscanf(save, ",\n");

    fscanf(save, "\t\"player_hand\":\n");
    load_hand(save, &game->player_hand);
    fscanf(save, ",\n");

    fscanf(save, "\t\"bot_hand\":\n");
    load_hand(save, &game->bot_hand);
    fscanf(save, ",\n");

    int temp;
    fscanf(save, "\t\"player_first\": %d,\n", &temp);
    game->player_first = temp;
    fscanf(save, "\t\"clues\": %d,\n", &game->clues);
    fscanf(save, "\t\"lives\": %d\n", &game->lives);
    fscanf(save, "}\n");

    fclose(save);
    return game;
}
