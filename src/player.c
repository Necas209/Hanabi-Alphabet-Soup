#include "player.h"

#include <stdlib.h>

#include "bot.h"
#include "interface.h"
#include "lab.h"

int get_player_playable(const hand_t *player_hand, const deck_t *deck) {
    for (int i = 0; i < HAND_LEN; i++) {
        const card_t card = player_hand->cards[i];
        if (is_playable(deck, card)) {
            return i;
        }
    }
    return -1;
}

bool player_turn(game_t *game) {
    printfAt(120, 6, "\tYour move:");
    printfAt(120, 8, "\t 1. Give a clue");
    printfAt(120, 10, "\t 2. Discard a card");
    printfAt(120, 12, "\t 3. Play a card");
    if (game->player_first) {
        printfAt(120, 14, "\t 4. Save game and exit");
    }
    printfAt(120, 16, "\t Option: ");
    const int option = read_int(stdin);
    clear_screen();

    switch (option) {
        case 1: {
            if (game->clues == 0) {
                printfAt(120, 6, "Illegal move!");
                return false;
            }
            while (!give_bot_clue(&game->player_hand, &game->bot_hand)) {
                printfAt(120, 6, "Invalid clue.");
                msleep(800);
                clear_screen();
            }
            game->clues--;
        }
        break;
        case 2: {
            if (game->clues == 8) {
                printfAt(120, 6, "Illegal move!");
                return false;
            }
            while (!player_discard(game)) {
                printfAt(120, 6, "Invalid move.");
                msleep(800);
                clear_screen();
            }
            game->clues++;
        }
        break;
        case 3:
            while (!player_play(game)) {
                printfAt(120, 6, "Invalid move.");
                msleep(800);
                clear_screen();
            }
            break;
        case 4:
            save_game(game, "save.json");
            exit(0);
        default:
            return false;
    }
    return true;
}

bool give_bot_clue(const hand_t *player_hand, hand_t *bot_hand) {
    printfAt(120, 6, "Pick the type of clue you want to give:");
    printfAt(120, 8, "\t- Color (C)");
    printfAt(120, 10, "\t- Number (N)");
    printfAt(120, 12, "  Option: ");
    const char option = read_char(stdin);
    switch (option) {
        case 'c':
        case 'C':
            printfAt(120, 14, "Pick a color:");
            printfAt(120, 16, "\t(1) Yellow");
            printfAt(120, 18, "\t(2) Blue");
            printfAt(120, 20, "\t(3) Green");
            printfAt(120, 22, "\t(4) Red");
            printfAt(120, 24, "\t(5) White");
            printfAt(120, 26, "  Option: ");
            const int opt = read_int(stdin);
            if (opt < 1 || opt > 5) {
                return false;
            }

            const color_t color = opt - 1;
            give_color_clue(player_hand, bot_hand, color);
            break;
        case 'n':
        case 'N':
            printfAt(120, 14, "Pick a number between 1 and 5: ");
            const int number = read_int(stdin);
            if (number < 1 || number > 5) {
                return false;
            }

            give_number_clue(player_hand, bot_hand, number);
            break;
        default:
            return false;
    }
    return true;
}

bool player_play(game_t *game) {
    printfAt(120, 6, "Pick the card you want to play (1 - 5):");
    const int card_idx = read_int(stdin) - 1;
    if (card_idx < 0 || card_idx > 4) {
        return false;
    }

    if (!play_card(&game->deck, &game->player_hand, card_idx)) {
        game->lives--;
    }
    return true;
}

bool player_discard(game_t *game) {
    printfAt(120, 6, "Pick the card you want to discard (1 - 5):");
    const int card_idx = read_int(stdin) - 1;
    if (card_idx < 0 || card_idx > 4) {
        return false;
    }

    if (discard_card(&game->deck, &game->player_hand, card_idx)) {
        game->clues++;
    }
    return true;
}
