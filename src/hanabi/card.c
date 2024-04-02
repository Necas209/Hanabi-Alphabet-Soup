#include "card.h"

const char *colors[] = {"Yellow", "Blue", "Green", "Red", "White"};


cJSON *get_card_vec_json(const card_vec_t *const cards) {
    // Create a cJSON array
    cJSON *cards_json = cJSON_CreateArray();

    // Add each card to the cJSON array
    int i;
    card_t *card;
    vec_foreach_ptr(cards, card, i) {
        cJSON *card_json = get_card_json(card);
        cJSON_AddItemToArray(cards_json, card_json);
    }

    return cards_json;
}

card_vec_t load_card_vec(const cJSON *const cards_json) {
    // Create a card vector
    card_vec_t cards;
    vec_init(&cards);

    // Load each card from the cJSON array
    cJSON *card_json;
    cJSON_ArrayForEach(card_json, cards_json) {
        card_t card = load_card(card_json);
        vec_push(&cards, card);
    }

    return cards;
}

cJSON *get_card_json(const card_t *const card) {
    // Create a cJSON object
    cJSON *card_json = cJSON_CreateObject();

    // Add card properties to the cJSON object
    cJSON_AddNumberToObject(card_json, "number", card->number);
    cJSON_AddNumberToObject(card_json, "color", card->color);
    cJSON_AddBoolToObject(card_json, "number_known", card->number_known);
    cJSON_AddBoolToObject(card_json, "color_known", card->color_known);

    return card_json;
}

#include "../lib/cJSON.h"

card_t load_card(const cJSON *const card_json) {
    // Extract card properties from the parsed JSON object
    card_t card = {
            .number = cJSON_GetObjectItem(card_json, "number")->valueint,
            .color = cJSON_GetObjectItem(card_json, "color")->valueint,
            .number_known = cJSON_GetObjectItem(card_json, "number_known")->valueint,
            .color_known = cJSON_GetObjectItem(card_json, "color_known")->valueint
    };

    return card;
}