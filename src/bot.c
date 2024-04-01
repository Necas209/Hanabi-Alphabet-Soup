#include "bot.h"

#include <stdlib.h>

#include "interface.h"
#include "lab.h"
#include "player.h"

// Function Implementation

uint32_t get_bot_discardable(const hand_t *hand, const int number, const deck_t *deck) {
    switch (number) {
        case 1:
            for (int i = 0; i < HAND_LEN; i++) {
                const card_t card = hand->cards[i];
                if (!card.color_known && !card.number_known)
                    return i;
            }
            break;
        case 2:
            for (int i = 0; i < HAND_LEN; i++) {
                const card_t card = hand->cards[i];
                if (card.number_known && card.number <= get_lowest_table(deck))
                    return i;
            }
            break;
        case 3:
            for (int i = 0; i < HAND_LEN; i++) {
                const card_t card = hand->cards[i];
                if (card.color_known && card.number_known && card.number <= deck->fireworks[card.color])
                    return i;
            }
            break;
        case 4: {
            int k = 0;
            int aux[HAND_LEN] = {-1};

            for (int i = 0; i < HAND_LEN; i++) {
                const card_t card = hand->cards[i];
                if ((!card.color_known && card.number_known) || (card.color_known && !card.number_known)) {
                    aux[k] = i;
                    k++;
                }
            }
            if (k == 0)
                break;

            return aux[generate_random_int(0, k)];
        }
        case 5:
            return generate_random_int(0, HAND_LEN);
        default:
            break;
    }
    return UINT32_MAX;
}

int get_bot_playable(const hand_t *hand, const deck_t *deck) {
    for (int i = 0; i < HAND_LEN; i++) {
        const card_t card = hand->cards[i];
        if (!card.number_known) {
            continue;
        }

        const bool playable = is_playable(deck, card);
        if (playable && (is_table(deck) || card.color_known)) {
            return i;
        }
    }
    return -1;
}

void bot_turn(game_t *game) {
    if (!game->player_first) {
        printfAt(120, 6, "Do you want to save the game and exit?");
        printfAt(120, 8, "  (y/n): ");
        const int c = fgetc(stdin);
        if (c == 'y' || c == 'Y') {
            save_game(game, "save.json");
            exit(0);
        }
    }
    clear_screen();
    printfAt(120, 6, "The bot is playing...");

    const int bot_playable = get_bot_playable(&game->bot_hand, &game->deck);

    if (!game->player_first && game->clues == MAX_CLUES && game->deck.length == 40) {
        give_number_clue(&game->bot_hand, &game->player_hand, 1);
        game->clues--;
        return;
    }

    if (bot_playable != -1) {
        play_card(&game->deck, &game->bot_hand, bot_playable);
        return;
    }

    if (game->clues == 0) {
        int number = 1;
        uint32_t idx = get_bot_discardable(&game->bot_hand, number, &game->deck);
        while (idx == UINT32_MAX && number < 6) {
            number++;
            idx = get_bot_discardable(&game->bot_hand, number, &game->deck);
        }
        if (idx != -1) {
            if (discard_card(&game->deck, &game->bot_hand, idx)) {
                game->clues++;
            }
        } else {
            printfAt(120, 8, "The bot decided to discard a random card.");
            const uint32_t card_idx = generate_random_int(0, HAND_LEN);
            if (discard_card(&game->deck, &game->bot_hand, card_idx)) {
                game->clues++;
            }
        }
        return;
    }

    const int card_idx = get_player_playable(&game->player_hand, &game->deck);
    give_player_clue(&game->bot_hand, &game->player_hand, card_idx);
    game->clues--;
}

void give_player_clue(const hand_t *bot_hand, hand_t *player_hand, const int idx) {
    if (idx < 0 || idx >= HAND_LEN) {
        const int number = lowest_unknown_number(player_hand);
        if (number != -1) {
            give_number_clue(bot_hand, player_hand, number);
            return;
        }

        const color_t color = random_unknown_color(player_hand);
        if (color != -1) {
            give_color_clue(bot_hand, player_hand, color);
        }
        return;
    }

    card_t *const card = &player_hand->cards[idx];

    if (!card->number_known && cards_with_number(player_hand, card->number) == 1) {
        printfAt(120, 8, "Card #%d is your only '%d' card.", idx + 1, card->number);
        card->number_known = true;
    } else if (!card->color_known && cards_with_color(player_hand, card->color) == 1) {
        printfAt(120, 8, "Card #%d is your only %s card.", idx + 1, colors[card->color]);
        card->color_known = true;
    } else {
        if (!card->number_known && card->color_known) {
            give_number_clue(bot_hand, player_hand, card->number);
        } else if (!card->color_known && card->number_known) {
            give_color_clue(bot_hand, player_hand, card->color);
        } else {
            const uint32_t random = generate_random_int(0, 2);
            if (random == 0) {
                give_number_clue(bot_hand, player_hand, card->number);
            } else {
                const color_t color = card->color;
                give_color_clue(bot_hand, player_hand, color);
            }
        }
    }
}
