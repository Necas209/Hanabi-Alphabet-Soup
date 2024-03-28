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
        deck.cards[i] = (card_t){
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

bool play_card(deck_t *deck, hand_t *hand, const int idx) {
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

bool discard_card(deck_t *deck, hand_t *hand, const int idx) {
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
        return (card_t){.number = -1, .color = -1, .number_known = false, .color_known = false};
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

void save_deck(FILE *file, const deck_t *deck) {
    // Print as a JSON object
    fprintf(file, "{");
    fprintf(file, " \"length\": %lu,", deck->length);
    fprintf(file, " \"cards\": [");
    for (int i = 0; i < deck->length; i++) {
        save_card(file, &deck->cards[i]);
        if (i != deck->length - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "],");
    // Print the discard deck
    fprintf(file, " \"discard_deck\": [");
    for (int j = 0; j < NUMBERS; j++) {
        fprintf(file, "[");
        for (int i = 0; i < COLORS; i++) {
            fprintf(file, "%d", deck->discard_deck[j][i]);
            if (i != COLORS - 1) {
                fprintf(file, ", ");
            }
        }
        if (j != NUMBERS - 1) {
            fprintf(file, "], ");
        } else {
            fprintf(file, "]");
        }
    }
    fprintf(file, "],");
    // Print the fireworks
    fprintf(file, "\"fireworks\": [");
    for (int i = 0; i < COLORS; i++) {
        fprintf(file, "%d", deck->fireworks[i]);
        if (i != COLORS - 1) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]");
    // Print the closing curly brace
    fprintf(file, "}");
}

void load_deck(FILE *file, deck_t *deck) {
    // Read the opening curly brace
    fgetc(file);
    fscanf(file, " \"length\": %lu,", &deck->length);
    fscanf(file, " \"cards\": [");
    for (int i = 0; i < deck->length; i++) {
        load_card(file, &deck->cards[i]);
        if (i != deck->length - 1) {
            fgetc(file); // Skip the comma
        }
    }
    fscanf(file, "],");
    // Read the discard deck
    fscanf(file, " \"discard_deck\": [");
    for (int j = 0; j < NUMBERS; j++) {
        fscanf(file, "[");
        for (int i = 0; i < COLORS; i++) {
            fscanf(file, "%d", &deck->discard_deck[j][i]);
            if (i != COLORS - 1) {
                fgetc(file); // Skip the comma
                fgetc(file); // Skip the space
            }
        }
        fscanf(file, "]");
        if (j != NUMBERS - 1) {
            fgetc(file); // Skip the comma
            fgetc(file); // Skip the space
        }
    }
    // Read the closing square brace
    fscanf(file, "],");
    // Read the fireworks
    fscanf(file, "\"fireworks\": [");
    for (int i = 0; i < COLORS; i++) {
        fscanf(file, "%d", &deck->fireworks[i]);
        if (i != COLORS - 1) {
            fgetc(file); // Skip the comma
            fgetc(file); // Skip the space
        }
    }
    // Read the closing square brace
    fscanf(file, "]");
    // Read the closing curly brace
    fgetc(file);
}
