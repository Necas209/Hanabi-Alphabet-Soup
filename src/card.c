#include "card.h"

const char *colors[] = {"Yellow", "Blue", "Green", "Red", "White"};

// Function Implementation

void save_card(FILE *file, const card_t *card) {
    // Print as a JSON object
    fprintf(file, "{");
    fprintf(file, " \"number\": %d,", card->number);
    fprintf(file, " \"color\": %d,", card->color);
    fprintf(file, " \"number_known\": %d,", card->number_known);
    fprintf(file, " \"color_known\": %d", card->color_known);
    fprintf(file, "}");
}

void load_card(FILE *file, card_t *card) {
    // Read the opening curly brace
    fgetc(file);
    fscanf(file, " \"number\": %d,", &card->number);
    fscanf(file, " \"color\": %d,", &card->color);
    int temp;
    fscanf(file, " \"number_known\": %d,", &temp);
    card->number_known = temp;
    fscanf(file, " \"color_known\": %d", &temp);
    card->color_known = temp;
    // Read the closing curly brace
    fgetc(file);
}
