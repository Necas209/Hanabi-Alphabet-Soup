#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "hanabi/game.h"
#include "hanabi/interface.h"
#include "lib/lab.h"

/// Play a game of Hanabi
void play_game();

int main(void) {
    printf("\033[8;50;200t");
    print_game_start();
    msleep(500);

    while (true) {
        setlocale(LC_ALL, "");
        puts("\n\n Menu:");
        puts("\n\t 1 - Play a game of Hanabi");
        puts("\n\t 2 - Load a game from a file");
        puts("\n\t 3 - Show a description of the game in the console");
        puts("\n\t 4 - Exit the application");
        printf("\n Option: ");
        const int option = read_int(stdin);
        system("clear");
        switch (option) {
            case 1: {
                play_game();
                break;
            }
            case 2: {
                game_t game;
                game_t *loaded_game = load_game("save.json");
                if (loaded_game == NULL) {
                    enter_to_continue();
                    system("clear");
                    break;
                }
                game_loop(loaded_game);
                free(loaded_game);
                break;
            }
            case 3: {
                FILE *rules = fopen("rules.txt", "r");
                char *line = NULL;
                size_t len = 0;
                while (getline(&line, &len, rules) != -1) {
                    printf("%s", line);
                }
                fclose(rules);
                enter_to_continue();
                system("clear");
                break;
            }
            case 4:
                exit(0);
            default:
                puts("\nThe option does not exist.");
                enter_to_continue();
                system("clear");
                break;
        }
    }
}

void play_game() {
    printf("\n\n Welcome to Hanabi!\n");
    printf("\n In this game, you will play with a bot to create the best fireworks show possible.");
    printf("\n You will have to give hints to the bot and vice versa to play the game.");
    printf("\n The game ends when the deck is empty or when the fireworks show is complete.");
    printf("\n The fireworks show is complete when all the fireworks are in order from 1 to 5.");
    printf("\n If you give the wrong hint, you will lose a life.");
    printf("\n If you give the wrong card to the bot, you will lose a life.");
    printf("\n If you lose all your lives, the game is over.");
    printf("\n If you complete the fireworks show, you win the game.");
    printf("\n Good luck!\n");
    enter_to_continue();
    system("clear");

    printfAt(1, 1, "\n\n Let's start the game!\n");
    printf("\n You will have to give your name to start the game.\n");
    printf("\n The bot will also have a name.\n");

    printf("\n Your name: ");
    const char *name = read_string(stdin);

    // Create a new deck and shuffle it
    deck_t deck = new_deck();
    shuffle_deck(&deck, 5);
    // Draw 5 cards for the player and the bot
    card_t player_cards[HAND_LEN];
    card_t bot_cards[HAND_LEN];
    for (int i = 0; i < HAND_LEN; i++) {
        player_cards[i] = draw_card(&deck).value;
        bot_cards[i] = draw_card(&deck).value;
    }
    // Create the hands for the player and the bot
    const hand_t player_hand = new_hand(player_cards, name);
    const hand_t bot_hand = new_hand(bot_cards, "Bot");
    // Decide who goes first
    const bool player_first = is_player_first();
    // Create the game
    game_t game = new_game(deck, player_hand, bot_hand, player_first);
    // Start the game loop
    game_loop(&game);
    // Free the game
    free_game(&game);
}
