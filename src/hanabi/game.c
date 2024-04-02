#include "game.h"

#include <stdlib.h>

#include "bot.h"
#include "player.h"
#include "interface.h"

game_t new_game(const deck_t deck, const hand_t player_hand, const hand_t bot_hand,
                const bool player_first) {
    return (game_t) {
            .deck = deck,
            .player_hand = player_hand,
            .bot_hand = bot_hand,
            .lives = MAX_LIVES,
            .hints = MAX_HINTS,
            .player_first = player_first,
    };
}

void free_game(game_t *const game) {
    free_deck(&game->deck);
    free_hand(&game->player_hand);
    free_hand(&game->bot_hand);
}

bool is_over(const game_t *const game) {
    return deck_len(&game->deck) == 0
           || game->lives == 0
           || get_score(&game->deck) == MAX_SCORE;
}

void game_loop(game_t *const game) {
    while (!is_over(game)) {
        print_ui(game);
        game_turn(game);
    }
    if (deck_len(&game->deck) == 0) {
        game_turn(game);
    }
    if (game->lives == 0) {
        print_no_lives();
    } else {
        print_score(&game->deck);
    }
    gotoxy(2, 34);
}

void game_turn(game_t *const game) {
    save_game(game, "save.json");

    if (game->player_first) {
        while (player_turn(game) == INVALID_ACTION) {
            clear_menu_screen();
        }
        enter_to_continue();
        print_ui(game);

        bot_turn(game);
        enter_to_continue();
        print_ui(game);
    } else {
        bot_turn(game);
        enter_to_continue();
        print_ui(game);

        while (player_turn(game) == INVALID_ACTION) {
            clear_menu_screen();
        }
        enter_to_continue();
        print_ui(game);
    }
}

cJSON *get_game_json(const game_t *const game) {
    cJSON *game_json = cJSON_CreateObject();

    cJSON_AddItemToObject(game_json, "deck", get_deck_json(&game->deck));
    cJSON_AddItemToObject(game_json, "player_hand", get_hand_json(&game->player_hand));
    cJSON_AddItemToObject(game_json, "bot_hand", get_hand_json(&game->bot_hand));
    cJSON_AddBoolToObject(game_json, "player_first", game->player_first);
    cJSON_AddNumberToObject(game_json, "hints", game->hints);
    cJSON_AddNumberToObject(game_json, "lives", game->lives);

    return game_json;
}

void save_game(const game_t *const game, const char *const filename) {
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

game_t *get_game_from_json(const cJSON *const game_json) {
    // Create a new game
    game_t *game = malloc(sizeof(game_t));
    // Get the properties of the game from the JSON object
    cJSON *deck_json = cJSON_GetObjectItem(game_json, "deck");
    cJSON *player_hand_json = cJSON_GetObjectItem(game_json, "player_hand");
    cJSON *bot_hand_json = cJSON_GetObjectItem(game_json, "bot_hand");
    cJSON *player_first_json = cJSON_GetObjectItem(game_json, "player_first");
    cJSON *hints_json = cJSON_GetObjectItem(game_json, "hints");
    cJSON *lives_json = cJSON_GetObjectItem(game_json, "lives");
    // Load the deck, player hand, bot hand, and other properties
    game->deck = load_deck(deck_json);
    game->player_hand = load_hand(player_hand_json);
    game->bot_hand = load_hand(bot_hand_json);
    game->player_first = cJSON_IsTrue(player_first_json);
    game->hints = hints_json->valueint;
    game->lives = lives_json->valueint;
    return game;
}

game_t *load_game(const char *const filename) {
    FILE *save = fopen(filename, "r");
    if (save == NULL) {
        return NULL;
    }

    fseek(save, 0, SEEK_END);
    const long size = ftell(save);
    fseek(save, 0, SEEK_SET);

    char *game_str = malloc(size + 1);
    size_t read = fread(game_str, 1, size, save);
    if (read != size) {
        puts("Error reading save file.");
        exit(1);
    }
    game_str[size] = '\0';
    fclose(save);

    cJSON *game_json = cJSON_Parse(game_str);
    free(game_str);

    game_t *game = get_game_from_json(game_json);
    cJSON_Delete(game_json);

    return game;
}
