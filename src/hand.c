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

void save_hand(FILE *file, const hand_t *hand) {
    // Print as a JSON object
    fprintf(file, "{");
    fprintf(file, " \"name\": \"%s\",", hand->name);
    fprintf(file, " \"cards\": [");
    for (int i = 0; i < HAND_LEN; i++) {
        save_card(file, &hand->cards[i]);
        if (i != HAND_LEN - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "]");
    fprintf(file, "}");
}

void load_hand(FILE *file, hand_t *hand) {
    // Read the opening curly brace
    fgetc(file);
    fscanf(file, " \"name\": \"%[^\"]\",", hand->name);
    fscanf(file, " \"cards\": [");
    for (int i = 0; i < HAND_LEN; i++) {
        load_card(file, &hand->cards[i]);
        if (i != HAND_LEN - 1) {
            fgetc(file); // Skip the comma
        }
    }
    // Read the closing square brace
    fgetc(file);
    // Read the closing curly brace
    fgetc(file);
}
