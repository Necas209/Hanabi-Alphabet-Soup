#include "player.h"

#include <stdlib.h>
#include <ctype.h>

#include "interface.h"
#include "../lib/lab.h"

uint32_t get_player_playable(const hand_t *const player_hand, const deck_t *const deck) {
    int i;
    card_t *card;
    vec_foreach_ptr(&player_hand->cards, card, i) {
        if (is_playable(deck, card)) {
            return i;
        }
    }
    return UINT32_MAX;
}

int player_turn(game_t *const game) {
    printfAt(120, 6, "\tYour move:");
    printfAt(120, 8, "\t 1. Give a hint");
    printfAt(120, 10, "\t 2. Discard a card");
    printfAt(120, 12, "\t 3. Play a card");
    if (game->player_first) {
        printfAt(120, 14, "\t 4. Save game and exit");
    }
    printfAt(120, 16, "\t Option: ");
    const int option = read_int(stdin);
    clear_screen();

    switch (option) {
        case 1:
            return player_hint(game);
        case 2:
            return player_discard(game);
        case 3:
            return player_play(game);
        case 4:
            if (!game->player_first) {
                error_msg("Invalid option");
                return INVALID_ACTION;
            }
            save_game(game, "save.json");
            exit(0);
        default:
            error_msg("Invalid option");
            return INVALID_ACTION;
    }
}

int player_hint(game_t *const game) {
    if (game->hints == 0) {
        error_msg("No more hints available");
        return INVALID_ACTION;
    }
    int ret;
    printfAt(120, 6, "Pick the type of clue you want to give:");
    printfAt(120, 8, "\t- Color (C)");
    printfAt(120, 10, "\t- Number (N)");
    printfAt(120, 12, "  Option: ");
    const char option = read_char(stdin);
    switch (tolower(option)) {
        case 'c':
            printfAt(120, 14, "Pick a color:");
            printfAt(120, 16, "\t(1) Yellow");
            printfAt(120, 18, "\t(2) Blue");
            printfAt(120, 20, "\t(3) Green");
            printfAt(120, 22, "\t(4) Red");
            printfAt(120, 24, "\t(5) White");
            printfAt(120, 26, "  Option: ");
            const color_t color = read_int(stdin) - 1;
            ret = give_color_clue(&game->player_hand, &game->bot_hand, color);
            break;
        case 'n':
            printfAt(120, 14, "Pick a number between 1 and 5: ");
            const int number = read_int(stdin);
            ret = give_number_clue(&game->player_hand, &game->bot_hand, number);
            break;
        default:
            error_msg("Invalid clue option");
            return INVALID_ACTION;
    }
    if (ret == 0) {
        game->hints--;
    }
    return ret;
}

int player_play(game_t *const game) {
    // Get the player's hand
    hand_t *const player_hand = &game->player_hand;
    // Check if the player has cards to play
    if (hand_len(player_hand) == 0) {
        error_msg("No cards to play");
        return INVALID_ACTION;
    }
    // Ask the player to pick a card
    printfAt(120, 6, "Pick the card you want to play (%d - %d):", 1, hand_len(player_hand));
    const int idx = read_int(stdin) - 1;
    // Check if the index is valid
    if (!vec_valid_idx(&player_hand->cards, idx)) {
        error_msg("Invalid card index");
        return INVALID_ACTION;
    }
    // Play the card
    // If the card is not playable, the player loses a life
    if (!play_card(&game->deck, player_hand, idx)) {
        game->lives--;
    }
    return 0;
}

int player_discard(game_t *game) {
    // Check if the player can discard a card
    if (game->hints == 8) {
        error_msg("Maximum number of hints reached");
        return INVALID_ACTION;
    }
    printfAt(120, 6, "Pick the card you want to discard (1 - 5):");
    const int idx = read_int(stdin) - 1;
    if (!vec_valid_idx(&game->player_hand.cards, idx)) {
        error_msg("Invalid card index");
        return INVALID_ACTION;
    }
    const card_t card = vec_at(&game->player_hand.cards, idx);
    discard_card(&game->deck, &game->player_hand, idx);
    game->hints++;
    return 0;
}
