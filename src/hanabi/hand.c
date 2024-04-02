#include <string.h>
#include "hand.h"

#include "../lib/lab.h"

hand_t new_hand(const card_t cards[HAND_LEN], const char *const name) {
    hand_t hand;
    vec_init(&hand.cards);
    for (int i = 0; i < HAND_LEN; i++) {
        vec_push(&hand.cards, cards[i]);
    }
    strncpy(hand.name, name, NAME);
    return hand;
}

void free_hand(hand_t *const hand) {
    vec_deinit(&hand->cards);
}

int hand_len(const hand_t *const hand) {
    return hand->cards.length;
}

int lowest_unknown_number(const hand_t *const hand) {
    int i, min = 6;
    card_t *card;
    vec_foreach_ptr(&hand->cards, card, i) {
        if (card->number < min && !card->number_known) {
            min = card->number;
        }
    }
    if (min == 6) {
        return -1;
    }
    return min;
}

color_t random_unknown_color(const hand_t *const hand) {
    color_vec_t unknown_colors;
    vec_init(&unknown_colors);
    int i;
    card_t *card;
    vec_foreach_ptr(&hand->cards, card, i) {
        if (!card->color_known) {
            vec_push(&unknown_colors, card->color);
        }
    }

    if (unknown_colors.length == 0) {
        vec_deinit(&unknown_colors);
        return -1;
    }
    color_t color = vec_random(&unknown_colors);
    vec_deinit(&unknown_colors);
    return color;
}

int cards_with_color(const hand_t *const hand, const color_t color) {
    int i, counter = 0;
    card_t *card;
    vec_foreach_ptr(&hand->cards, card, i) {
        if (card->color == color) {
            counter++;
        }
    }
    return counter;
}

int cards_with_number(const hand_t *const hand, const int number) {
    int i, counter = 0;
    card_t *card;
    vec_foreach_ptr(&hand->cards, card, i) {
        if (card->number == number) {
            counter++;
        }
    }
    return counter;
}

void give_number_clue(const hand_t *from, hand_t *to, int number) {
    int i;
    card_t *card;
    vec_foreach_ptr(&to->cards, card, i) {
        if (card->number == number) {
            card->number_known = true;
        }
    }
    printfAt(120, 6, "%s gave hints about the number %d to %s.", from->name, number, to->name);
}

void give_color_clue(const hand_t *from, hand_t *to, color_t color) {
    int i;
    card_t *card;
    vec_foreach_ptr(&to->cards, card, i) {
        if (card->color == color) {
            card->color_known = true;
        }
    }
    printfAt(120, 6, "%s gave hints about the color %s to %s.", from->name, colors[color], to->name);
}

cJSON *get_hand_json(const hand_t *const hand) {
    // Create a cJSON object for the hand
    cJSON *hand_json = cJSON_CreateObject();
    // Add the hand properties to the cJSON object
    cJSON_AddStringToObject(hand_json, "name", hand->name);
    cJSON *cards_json = get_card_vec_json(&hand->cards);
    cJSON_AddItemToObject(hand_json, "cards", cards_json);
    return hand_json;
}

hand_t load_hand(cJSON *const hand_json) {
    // Create a hand object
    hand_t hand;
    // Extract hand properties from the parsed JSON object
    cJSON *name = cJSON_GetObjectItem(hand_json, "name");
    strcpy(hand.name, name->valuestring);
    // Load the cards from the cJSON array
    cJSON *cards = cJSON_GetObjectItem(hand_json, "cards");
    hand.cards = load_card_vec(cards);
    return hand;
}