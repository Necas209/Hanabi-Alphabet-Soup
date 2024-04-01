#include "card.h"

const char *colors[] = {"Yellow", "Blue", "Green", "Red", "White"};

// Function Implementation

cJSON *save_card(const card_t *card) {
    // Create a cJSON object
    cJSON *card_json = cJSON_CreateObject();

    // Add card properties to the cJSON object
    cJSON_AddNumberToObject(card_json, "number", card->number);
    cJSON_AddNumberToObject(card_json, "color", card->color);
    cJSON_AddBoolToObject(card_json, "number_known", card->number_known);
    cJSON_AddBoolToObject(card_json, "color_known", card->color_known);

    return card_json;
}

#include "cJSON.h"

void load_card(cJSON *card_json, card_t *card) {
// Extract card properties from the parsed JSON object
    card->number = cJSON_GetObjectItem(card_json, "number")->valueint;
    card->color = cJSON_GetObjectItem(card_json, "color")->valueint;
    card->number_known = cJSON_GetObjectItem(card_json, "number_known")->valueint;
    card->color_known = cJSON_GetObjectItem(card_json, "color_known")->valueint;
}