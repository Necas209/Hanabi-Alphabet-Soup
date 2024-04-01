#include "interface.h"

#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

void enter_to_continue() {
    printfAt(120, 32, "Press enter to continue...");
    while (getchar() != '\n') {
    }
    clear_screen();
}

char *read_string(FILE *stream) {
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, stream) == -1) {
        return NULL;
    }
    line[len - 1] = '\0';
    return line;
}

char read_char(FILE *stream) {
    char *line = read_string(stream);
    if (line == NULL) {
        return '\0';
    }
    const char c = line[0];
    free(line);
    return c;
}

int read_int(FILE *stream) {
    char *line = read_string(stream);
    if (line == NULL) {
        return -1;
    }
    const long number = strtoimax(line, NULL, 10);
    free(line);
    return (int) number;
}

void print_game_start() {
    FILE *file = fopen("logo.txt", "r");
    gotoxy(1, 1);
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        ansi_color color;
        switch (ch) {
            case 'H':
                color = ANSI_COLOR_BLUE;
                break;
            case 'A':
                color = ANSI_COLOR_GREEN;
                break;
            case 'N':
                color = ANSI_COLOR_RED;
                break;
            case 'B':
                color = ANSI_COLOR_YELLOW;
                break;
            case 'I':
                color = ANSI_COLOR_WHITE;
                break;
            default:
                color = ANSI_COLOR_BLACK;
                break;
        }
        setForeColor(color);
        printf("%c", ch);
    }
    fclose(file);
    resetColor();
    printfAt(85, 2, "Project by:");
    printfAt(85, 4, "- Diogo Medeiros");
    printfAt(85, 5, "- Eduardo Chaves");
    printfAt(85, 6, "- João Rodrigues");
}

void print_ui(const game_t *game) {
    print_player_hand(&game->player_hand);
    print_bot_hand(&game->bot_hand);
    print_deck(&game->deck);
    printfAt(85, 15, "Clues: %d", game->clues);
    printfAt(85, 20, "Lives: %d", game->lives);
}

ansi_color get_card_ui_color(const color_t color) {
    switch (color) {
        case YELLOW:
            return ANSI_COLOR_YELLOW;
        case BLUE:
            return ANSI_COLOR_BLUE;
        case GREEN:
            return ANSI_COLOR_GREEN;
        case RED:
            return ANSI_COLOR_RED;
        case WHITE:
            return ANSI_COLOR_WHITE;
        default:
            return ANSI_COLOR_BLACK;
    }
}

bool is_player_first() {
    const uint32_t i = generate_random_int(0, 1);
    if (i == 0) {
        printfAt(120, 6, "The bot is the first to play.");
        return false;
    }

    printfAt(120, 6, "The player is the first to play.\n");
    return true;
}

void print_card(const card_t card, const int x, const int y) {
    if (card.color_known) {
        const int ui_color = get_card_ui_color(card.color);
        setForeColor(ui_color);
    } else {
        setForeColor(ANSI_COLOR_WHITE);
    }

    showRectAt(x, y, CARD_WIDTH, CARD_HEIGHT);

    if (card.number_known) {
        printfAt(x + CARD_WIDTH / 2, y + CARD_HEIGHT / 2, "%d", card.number);
    } else {
        printfAt(x + CARD_WIDTH / 2, y + CARD_HEIGHT / 2, "?");
    }
    resetColor();
}

void print_player_hand(const hand_t *player_hand) {
    printfAt(80, 28, "%s", player_hand->name);

    for (int i = 0; i < HAND_LEN; i++) {
        const card_t card = player_hand->cards[i];
        print_card(card, 10 + 14 * i, 26);
    }
}

void print_bot_hand(const hand_t *bot_hand) {
    printfAt(3, 7, "Bot\n");

    for (int i = 0; i < HAND_LEN; i++) {
        card_t card = bot_hand->cards[i];
        // The player can see the robot's hand, so we can reveal the color and number of the cards
        card.color_known = true;
        card.number_known = true;
        print_card(card, 10 + 14 * i, 5);
    }
}

void print_score(const deck_t *deck) {
    const int score = get_score(deck);
    gotoxy(120, 6);
    if (score >= 0 && score <= 5) {
        printf("Oh! You were all booed.");
    } else if (score >= 6 && score <= 10) {
        printf("Very weak, the audience is bored.");
    } else if (score >= 11 && score <= 15) {
        printf("The show was alright, but the audience has seen better.");
    } else if (score >= 16 && score <= 20) {
        printf("Good show! The audience is pleased.");
    } else if (score >= 21 && score < 25) {
        printf("Very good! The audience is thrilled!");
    } else if (score == 25) {
        printf("Legendary! The audience will never forget this show!");
    }
    printfAt(120, 8, "  Final score: %d points", score);
    msleep(5000);
}

void print_no_lives() {
    printfAt(120, 6, "You lost all your lives.");
    printfAt(120, 8, "The gods showed their wrath in the form of a storm");
    printfAt(120, 9, " that ended the fireworks.");
    printfAt(120, 12, "Final score: 0 points");
    msleep(5000);
}

void print_deck(const deck_t *deck) {
    // Display the discard deck
    for (int i = 0; i < COLORS; i++) {
        const int ui_color = get_card_ui_color(i);
        setForeColor(ui_color);
        printfAt(85, 6 + i, "%s", colors[i]);
        resetColor();
        printfAt(96 + 4 * i, 5, "%d", i + 1);
        for (int j = 0; j < NUMBERS; j++) {
            printfAt(96 + 4 * i, 6 + j, "%d", deck->discard_deck[i][j]);
        }
    }
    // Display the deck
    showRectAt(100, 15, 9, 6);
    printfAt(101, 14, "Deck:");
    if (deck->length < 10) {
        printfAt(104, 18, "0%lu", deck->length);
    } else {
        printfAt(104, 18, "%lu", deck->length);
    }
    // Display the fireworks
    for (int k = 0; k < 5; k++) {
        const ansi_color color = get_card_ui_color(k);
        setForeColor(color);
        showRectAt(11 + 14 * k, 16, 6, 4);
        printfAt(14 + 14 * k, 18, "%d", deck->fireworks[k]);
        resetColor();
    }
}

void clear_screen() {
    char spaces[SCREEN_WIDTH + 1]; // 80 spaces + null terminator
    memset(spaces, ' ', SCREEN_WIDTH);
    spaces[SCREEN_WIDTH] = '\0'; // Null terminate the string

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        printfAt(120, 6 + i, "%s", spaces);
    }
}
