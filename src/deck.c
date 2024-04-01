#include "deck.h"

#include <string.h>

#include "lab.h"

hand_t new_hand(deck_t *deck, const char *name) {
    hand_t hand;
    strncpy(hand.name, name, NAME);

    for (int i = 0; i < HAND_LEN; i++) {
        hand.cards[i] = draw_card(deck);
    }
    return hand;
}

deck_t new_deck() {
    deck_t deck = {
            .length = DECK_LEN,
            .discard_deck = {0}
    };

    const int numbers[NUMBERS_PER_COLOR] = {1, 1, 1, 2, 2, 3, 3, 4, 4, 5};

    for (int i = 0; i < deck.length; i++) {
        deck.cards[i] = (card_t) {
                .number = numbers[i % NUMBERS_PER_COLOR],
                .color = i / NUMBERS_PER_COLOR,
                .number_known = false,
                .color_known = false
        };
    }
    return deck;
}

void shuffle_deck(deck_t *deck) {
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < deck->length; i++) {
            const uint32_t swapper = generate_random_int(0, deck->length - 1);
            const card_t temp = deck->cards[i];
            deck->cards[i] = deck->cards[swapper];
            deck->cards[swapper] = temp;
        }
    }
}

bool is_playable(const deck_t *deck, const card_t card) {
    return card.number == deck->fireworks[card.color] + 1;
}

bool play_card(deck_t *deck, hand_t *hand, uint32_t idx) {
    const card_t card = hand->cards[idx];
    printfAt(120, 8, "%s played the card #%d %s.", hand->name, card.number, colors[card.color]);

    if (!is_playable(deck, card)) {
        printfAt(120, 10, " The card %s played was illegal.", hand->name);
        discard_card(deck, hand, idx);
        return false;
    }

    deck->fireworks[card.color]++;
    if (deck->fireworks[card.color] == 5) {
        printfAt(120, 10, "Congratulations! %s completed the %s fireworks!", hand->name, colors[card.color]);
    }
    hand->cards[idx] = draw_card(deck);
    return true;
}

bool discard_card(deck_t *deck, hand_t *hand, uint32_t idx) {
    const card_t card = hand->cards[idx];
    printfAt(120, 12, "%s discarded the card #%d %s.", hand->name, card.number, colors[card.color]);

    deck->discard_deck[card.number - 1][card.color]++;
    if (deck->length == 0)
        return false;

    hand->cards[idx] = draw_card(deck);
    return true;
}

card_t draw_card(deck_t *deck) {
    if (deck->length == 0) {
        return (card_t) {.number = -1, .color = -1, .number_known = false, .color_known = false};
    }
    return deck->cards[--deck->length];
}


int get_score(const deck_t *deck) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += deck->fireworks[i];
    }
    return sum;
}

int get_lowest_table(const deck_t *deck) {
    int min = 6;
    for (int i = 0; i < COLORS; i++) {
        if (deck->fireworks[i] < min) {
            min = deck->fireworks[i];
        }
    }
    return min;
}

bool is_table(const deck_t *deck) {
    for (int i = 0; i < HAND_LEN - 1; i++) {
        if (deck->fireworks[i] == deck->fireworks[i + 1]) {
            return true;
        }
    }

    return false;
}

cJSON *get_deck_json(const deck_t *deck) {
    // Create the JSON object
    cJSON *deck_json = cJSON_CreateObject();

    // Add the length of the deck
    cJSON_AddNumberToObject(deck_json, "length", (double) deck->length);

    // Add the cards array
    cJSON *cards = cJSON_CreateArray();
    for (int i = 0; i < deck->length; i++) {
        cJSON *card = save_card(&deck->cards[i]);
        cJSON_AddItemToArray(cards, card);
    }
    cJSON_AddItemToObject(deck_json, "cards", cards);

    // Add the discard deck
    cJSON *discard_deck = cJSON_CreateArray();
    for (int j = 0; j < NUMBERS; j++) {
        cJSON *number = cJSON_CreateArray();
        for (int i = 0; i < COLORS; i++) {
            cJSON_AddNumberToObject(number, "", deck->discard_deck[j][i]);
        }
        cJSON_AddItemToArray(discard_deck, number);
    }
    cJSON_AddItemToObject(deck_json, "discard_deck", discard_deck);

    // Add the fireworks
    cJSON *fireworks = cJSON_CreateArray();
    for (int i = 0; i < COLORS; i++) {
        cJSON_AddNumberToObject(fireworks, "", deck->fireworks[i]);
    }
    cJSON_AddItemToObject(deck_json, "fireworks", fireworks);

    return deck_json;
}

void load_deck(cJSON *deck_json, deck_t *deck) {
    // Load the length of the deck
    deck->length = cJSON_GetObjectItem(deck_json, "length")->valueint;

    // Load the cards array
    cJSON *cards = cJSON_GetObjectItem(deck_json, "cards");
    for (int i = 0; i < deck->length; i++) {
        cJSON *card_json = cJSON_GetArrayItem(cards, i);
        load_card(card_json, &deck->cards[i]);
    }

    // Load the discard deck
    cJSON *discard_deck = cJSON_GetObjectItem(deck_json, "discard_deck");
    for (int j = 0; j < NUMBERS; j++) {
        cJSON *number = cJSON_GetArrayItem(discard_deck, j);
        for (int i = 0; i < COLORS; i++) {
            deck->discard_deck[j][i] = cJSON_GetArrayItem(number, i)->valueint;
        }
    }

    // Load the fireworks
    cJSON *fireworks = cJSON_GetObjectItem(deck_json, "fireworks");
    for (int i = 0; i < COLORS; i++) {
        deck->fireworks[i] = cJSON_GetArrayItem(fireworks, i)->valueint;
    }
}
