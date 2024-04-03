#include "bot.h"

#include <stdlib.h>

#include "../lib/lab.h"
#include "player.h"

uint32_t get_bot_discardable(const hand_t *const hand, const discard_strategy_t strategy, const deck_t *const deck) {
    int i;
    card_t *card;
    switch (strategy) {
        case DISCARD_UNKNOWN:
            vec_foreach_ptr(&hand->cards, card, i) {
                if (!card->color_known && !card->number_known) {
                    return i;
                }
            }
            break;
        case DISCARD_LOWEST_TABLE:
            vec_foreach_ptr(&hand->cards, card, i) {
                if (card->number_known && card->number <= get_lowest_table(deck)) {
                    return i;
                }
            }
            break;
        case DISCARD_KNOWN_FIREWORKS:
            vec_foreach_ptr(&hand->cards, card, i) {
                if (card->color_known && card->number_known && card->number <= deck->fireworks[card->color]) {
                    return i;
                }
            }
            break;
        case DISCARD_HALF_KNOWN: {
            vec_int_t indices;
            vec_init(&indices);

            vec_foreach_ptr(&hand->cards, card, i) {
                if ((!card->color_known && card->number_known) || (card->color_known && !card->number_known)) {
                    vec_push(&indices, i);
                }
            }
            const uint32_t idx = vec_random(&indices);
            vec_deinit(&indices);

            return indices.length == 0 ? INVALID_CARD : idx;
        }
        case DISCARD_RANDOM:
            return vec_random_idx(&hand->cards);
        default:
            break;
    }
    return INVALID_CARD;
}

uint32_t get_bot_playable(const hand_t *const hand, const deck_t *const deck) {
    int i;
    card_t *card;
    vec_foreach_ptr(&hand->cards, card, i) {
        if (!card->number_known) {
            continue;
        }
        const bool playable = is_playable(deck, card);
        const bool fireworks_at_table = is_fireworks_at_table(deck, card->number - 1);
        if (playable && (fireworks_at_table || card->color_known)) {
            return i;
        }
    }
    return INVALID_CARD;
}

void bot_turn(game_t *const game) {
    printfAt(120, 6, "The bot is playing...");
    // Check if it is the first turn. If it is, give a clue about cards with number 1
    bool is_first_turn = !game->player_first
                         && game->hints == MAX_HINTS
                         && game->deck.cards.length == DECK_LEN - 2 * HAND_LEN;
    if (is_first_turn) {
        give_number_clue(&game->bot_hand, &game->player_hand, 1);
        game->hints--;
        return;
    }
    // Check if the bot can play a card. If it can, play the card
    const uint32_t bot_playable = get_bot_playable(&game->bot_hand, &game->deck);
    if (bot_playable != INVALID_CARD) {
        play_card(&game->deck, &game->bot_hand, bot_playable);
        return;
    }
    // Check if the bot can give a hint. If it can, give a hint
    if (game->hints != 0) {
        const uint32_t idx = get_player_playable(&game->player_hand, &game->deck);
        bot_hint(&game->bot_hand, &game->player_hand, idx);
        game->hints--;
        return;
    }
    // Check if the bot can discard a card. If it can, discard the card
    for (discard_strategy_t strategy = DISCARD_UNKNOWN; strategy <= DISCARD_RANDOM; strategy++) {
        const uint32_t idx = get_bot_discardable(&game->bot_hand, strategy, &game->deck);
        if (idx != INVALID_CARD) {
            const card_t card = vec_at(&game->bot_hand.cards, idx);
            discard_card(&game->deck, &game->bot_hand, idx);
            game->hints++;
            return;
        }
    }
}

void bot_hint(const hand_t *bot_hand, hand_t *player_hand, uint32_t idx) {
    if (!vec_valid_idx(&player_hand->cards, idx)) {
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

    card_t *const card = vec_at_ptr(&player_hand->cards, idx);

    if (!card->number_known && cards_with_number(player_hand, card->number) == 1) {
        printfAt(120, 8, "Card #%d is your only '%d' card.", idx + 1, card->number);
        card->number_known = true;
    } else if (!card->color_known && cards_with_color(player_hand, card->color) == 1) {
        printfAt(120, 8, "Card #%d is your only %s card.", idx + 1, colors[card->color]);
        card->color_known = true;
    } else if (!card->number_known && card->color_known) {
        give_number_clue(bot_hand, player_hand, card->number);
    } else if (!card->color_known && card->number_known) {
        give_color_clue(bot_hand, player_hand, card->color);
    } else {
        const uint32_t bit = generate_random_int(0, 2);
        if (bit == 0) {
            give_number_clue(bot_hand, player_hand, card->number);
        } else {
            give_color_clue(bot_hand, player_hand, card->color);
        }
    }
}
