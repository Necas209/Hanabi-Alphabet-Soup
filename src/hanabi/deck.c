#include "deck.h"

#include <string.h>

#include "../lib/lab.h"

deck_t new_deck() {
    deck_t deck = {
            .discard_deck = {0},
            .fireworks = {0}
    };
    vec_init(&deck.cards);

    const int numbers[NUMBERS_PER_COLOR] = {1, 1, 1, 2, 2, 3, 3, 4, 4, 5};

    for (int i = 0; i < DECK_LEN; i++) {
        card_t card = {
                .number = numbers[i % NUMBERS_PER_COLOR],
                .color = i / NUMBERS_PER_COLOR,
                .number_known = false,
                .color_known = false
        };
        vec_push(&deck.cards, card);
    }
    return deck;
}

void free_deck(deck_t *const deck) {
    vec_deinit(&deck->cards);
}

void shuffle_deck(deck_t *const deck, const uint32_t iterations) {
    for (int j = 0; j < iterations; j++) {
        for (int i = 0; i < deck->cards.length; i++) {
            const uint32_t swapper = vec_random_idx(&deck->cards);
            vec_swap(&deck->cards, i, swapper);
        }
    }
}

bool is_playable(const deck_t *const deck, const card_t *const card) {
    return card->number == deck->fireworks[card->color] + 1;
}

int play_card(deck_t *const deck, hand_t *const hand, const uint32_t idx) {
    // Get the card to play
    const card_t card = vec_at(&hand->cards, idx);
    printfAt(120, 8, "%s played the card #%d %s.", hand->name, card.number, colors[card.color]);
    // Check if the card is playable
    if (!is_playable(deck, &card)) {
        printfAt(120, 10, " The card %s played was illegal.", hand->name);
        discard_card(deck, hand, idx);
        return -1;
    }
    // Add the card to the fireworks
    deck->fireworks[card.color]++;
    if (deck->fireworks[card.color] == 5) {
        printfAt(120, 10, "Congratulations! %s completed the %s fireworks!", hand->name, colors[card.color]);
    }
    // Draw a new card
    vec_pop_at(&hand->cards, idx);
    optional_card_t drawn_card = draw_card(deck);
    if (drawn_card.present) {
        vec_push(&hand->cards, drawn_card.value);
    }
    return 0;
}

void discard_card(deck_t *const deck, hand_t *const hand, const uint32_t idx) {
    // Get the card to discard
    card_t card = vec_at(&hand->cards, idx);
    printfAt(120, 12, "%s discarded the card #%d %s.", hand->name, card.number, colors[card.color]);
    // Add the card to the discard deck
    deck->discard_deck[card.number - 1][card.color]++;
    // Draw a new card
    vec_pop_at(&hand->cards, idx);
    optional_card_t drawn_card = draw_card(deck);
    if (drawn_card.present) {
        vec_push(&hand->cards, drawn_card.value);
    }
}

optional_card_t draw_card(deck_t *const deck) {
    if (deck_len(deck) == 0) {
        return (optional_card_t) {.present = false};
    }
    return (optional_card_t) {
            .present = true,
            .value = vec_pop(&deck->cards)
    };
}

size_t deck_len(const deck_t *const deck) {
    return deck->cards.length;
}

int get_score(const deck_t *const deck) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += deck->fireworks[i];
    }
    return sum;
}

int get_lowest_table(const deck_t *const deck) {
    int min = 6;
    for (int i = 0; i < COLORS; i++) {
        if (deck->fireworks[i] < min) {
            min = deck->fireworks[i];
        }
    }
    return min;
}

bool is_table(const deck_t *const deck) {
    for (int i = 1; i < COLORS; i++) {
        if (deck->fireworks[i - 1] == deck->fireworks[i]) {
            return true;
        }
    }
    return false;
}

cJSON *get_deck_json(const deck_t *const deck) {
    // Create the JSON object
    cJSON *deck_json = cJSON_CreateObject();

    // Add the cards structure
    cJSON *cards = get_card_vec_json(&deck->cards);
    cJSON_AddItemToObject(deck_json, "cards", cards);

    // Add the discard deck
    cJSON *discard_deck = cJSON_CreateArray();
    for (int i = 0; i < NUMBERS; i++) {
        cJSON *array = cJSON_CreateIntArray(deck->discard_deck[i], COLORS);
        cJSON_AddItemToArray(discard_deck, array);
    }
    cJSON_AddItemToObject(deck_json, "discard_deck", discard_deck);

    // Add the fireworks
    cJSON *fireworks = cJSON_CreateIntArray(deck->fireworks, COLORS);
    cJSON_AddItemToObject(deck_json, "fireworks", fireworks);

    return deck_json;
}

void load_deck(deck_t *deck, const cJSON *deck_json) {
    // Load the cards array
    cJSON *cards = cJSON_GetObjectItem(deck_json, "cards");
    deck->cards = load_card_vec(cards);

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
