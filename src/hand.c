#include <string.h>
#include "hand.h"

#include "lab.h"

int lowest_unknown_number(const hand_t *hand) {
    int min = 6;
    for (int i = 0; i < HAND_LEN; i++) {
        const card_t card = hand->cards[i];
        if (card.number < min && !card.number_known) {
            min = card.number;
        }
    }
    if (min == 6) {
        return -1;
    }
    return min;
}

color_t random_unknown_color(const hand_t *hand) {
    int k = 0;
    color_t unknown_colors[HAND_LEN];
    for (int i = 0; i < HAND_LEN; i++) {
        const card_t card = hand->cards[i];
        if (!card.color_known) {
            unknown_colors[k] = card.color;
            k++;
        }
    }

    if (k == 0) {
        return -1;
    }
    return unknown_colors[generate_random_int(0, k)];
}

int cards_with_color(const hand_t *hand, const color_t color) {
    int counter = 0;
    for (int i = 0; i < HAND_LEN; i++) {
        if (hand->cards[i].color == color) {
            counter++;
        }
    }
    return counter;
}

int cards_with_number(const hand_t *hand, const int number) {
    int counter = 0;
    for (int i = 0; i < HAND_LEN; i++) {
        if (hand->cards[i].number == number) {
            counter++;
        }
    }
    return counter;
}

void give_number_clue(const hand_t *from, hand_t *to, const int number) {
    for (int i = 0; i < HAND_LEN; i++) {
        card_t *card = &to->cards[i];
        if (card->number == number) {
            card->number_known = true;
        }
    }

    printfAt(120, 6, "%s gave clues about the number %d to %s.", from->name, number, to->name);
}

void give_color_clue(const hand_t *from, hand_t *to, const color_t color) {
    for (int i = 0; i < HAND_LEN; i++) {
        card_t *card = &to->cards[i];
        if (card->color == color) {
            card->color_known = true;
        }
    }

    printfAt(120, 6, "%s gave clues about the color %s to %s.", from->name, colors[color], to->name);
}

cJSON *get_hand_json(const hand_t *hand) {
    // Create a cJSON object for the hand
    cJSON *hand_json = cJSON_CreateObject();

    // Add the hand properties to the cJSON object
    cJSON_AddStringToObject(hand_json, "name", hand->name);
    cJSON_AddArrayToObject(hand_json, "cards");

    // Add each card to the cJSON array
    for (int i = 0; i < HAND_LEN; i++) {
        cJSON *card_json = save_card(&hand->cards[i]);
        cJSON_AddItemToArray(cJSON_GetObjectItem(hand_json, "cards"), card_json);
    }

    return hand_json;
}

void load_hand(cJSON *hand_json, hand_t *hand) {
// Extract hand properties from the parsed JSON object
    cJSON *name = cJSON_GetObjectItem(hand_json, "name");
    strcpy(hand->name, name->valuestring);

    cJSON *cards = cJSON_GetObjectItem(hand_json, "cards");
    for (int i = 0; i < HAND_LEN; i++) {
        cJSON *card_json = cJSON_GetArrayItem(cards, i);
        load_card(card_json, &hand->cards[i]);
    }
}