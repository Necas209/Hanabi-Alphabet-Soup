#include "game.h"

#include <stdlib.h>

#include "bot.h"
#include "deck.h"
#include "player.h"
#include "interface.h"
#include "lab.h"

game_t new_game(const deck_t deck, const hand_t player_hand, const hand_t bot_hand,
                const bool player_first) {
    return (game_t) {
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
            print_no_lives();
        } else {
            print_score(&game->deck);
        }
    } else if (game->lives == 0) {
        print_no_lives();
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

cJSON *get_game_json(const game_t *game) {
    cJSON *game_json = cJSON_CreateObject();

    cJSON_AddItemToObject(game_json, "deck", get_deck_json(&game->deck));
    cJSON_AddItemToObject(game_json, "player_hand", get_hand_json(&game->player_hand));
    cJSON_AddItemToObject(game_json, "bot_hand", get_hand_json(&game->bot_hand));
    cJSON_AddNumberToObject(game_json, "player_first", game->player_first);
    cJSON_AddNumberToObject(game_json, "clues", game->clues);
    cJSON_AddNumberToObject(game_json, "lives", game->lives);

    return game_json;
}

void save_game(const game_t *game, const char *filename) {
    FILE *save = fopen(filename, "w");
    if (save == NULL) {
        puts("Error opening save file.");
        exit(1);
    }

    cJSON *game_json = get_game_json(game);
#ifdef DEBUG
    char *game_str = cJSON_Print(game_json);
#else
    char *game_str = cJSON_PrintUnformatted(game_json);
#endif
    fprintf(save, "%s", game_str);
    fclose(save);
    cJSON_Delete(game_json);
    free(game_str);
}

game_t *load_game(const char *filename) {
    FILE *save = fopen(filename, "r");
    if (save == NULL) {
        return NULL;
    }

    fseek(save, 0, SEEK_END);
    const long size = ftell(save);
    fseek(save, 0, SEEK_SET);

    char *game_str = malloc(size + 1);
    fread(game_str, 1, size, save);
    game_str[size] = '\0';
    fclose(save);

    cJSON *game_json = cJSON_Parse(game_str);
    free(game_str);

    game_t *game = malloc(sizeof(game_t));
    get_game_from_json(game_json, game);
    cJSON_Delete(game_json);

    return game;
}

void get_game_from_json(cJSON *game_json, game_t *game) {
    cJSON *deck_json = cJSON_GetObjectItem(game_json, "deck");
    cJSON *player_hand_json = cJSON_GetObjectItem(game_json, "player_hand");
    cJSON *bot_hand_json = cJSON_GetObjectItem(game_json, "bot_hand");
    cJSON *player_first_json = cJSON_GetObjectItem(game_json, "player_first");
    cJSON *clues_json = cJSON_GetObjectItem(game_json, "clues");
    cJSON *lives_json = cJSON_GetObjectItem(game_json, "lives");

    load_deck(deck_json, &game->deck);
    load_hand(player_hand_json, &game->player_hand);
    load_hand(bot_hand_json, &game->bot_hand);
    game->player_first = cJSON_IsTrue(player_first_json);
    game->clues = (int) cJSON_GetNumberValue(clues_json);
    game->lives = (int) cJSON_GetNumberValue(lives_json);
}
