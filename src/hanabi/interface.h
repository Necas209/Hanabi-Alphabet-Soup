#ifndef INTERFACE_H
#define INTERFACE_H

#include "game.h"
#include "../lib/lab.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 30
#define CARD_HEIGHT 6
#define CARD_WIDTH 9
#define INVALID_ACTION (-1)

// Function Prototypes

/// Prints a string and waits for the user to press enter.
void enter_to_continue();

/// Read a character from a file stream.
/// \param stream  The file stream to read the character from.
/// \return  The character read from the file stream.
char read_char(FILE *stream);

/// Read an integer from a file stream.
/// \param stream  The file stream to read the integer from.
/// \return  The integer read from the file stream.
int read_int(FILE *stream);

/// Read a string from a file stream.
/// \param stream  The file stream to read the string from.
/// \return  The string read from the file stream.
char *read_string(FILE *stream);

/// Inform the player that they have done an invalid action.
/// \param message  The message to print to the player.
void error_msg(const char *message);

/// Print the game's logo to the screen.
void print_game_start();

/// Clear the screen.
void clear_screen();

/// Get the ANSI color for a given card color.
/// \param color  The color to get the ANSI color for.
/// \return  The ANSI color for the given card color.
ansi_color_t get_card_ui_color(color_t color);

/// Check if the player is going first in the game. It also prints a message to the screen.
/// \return  True if the player is going first, false otherwise.
bool is_player_first();

/// Print the final score of the game to the screen.
/// \param deck  The deck to print the score of.
void print_score(const deck_t *deck);

/// Print the message "No lives left!" to the screen.
void print_no_lives();

/// Print a card to the screen at the given coordinates.
/// \param card  The card to print.
/// \param x  The x-coordinate to print the card.
/// \param y  The y-coordinate to print the card.
void print_card(const card_t *card, int x, int y);

/// Print a hand of cards to the screen at the given coordinates.
/// If the hand is the bot's hand, the cards will be visible to the player.
/// \param hand  The hand to print.
/// \param x  The x-coordinate to print the hand.
/// \param y  The y-coordinate to print the hand.
/// \param bot  Whether the hand is the bot's hand.
void print_hand(const hand_t *hand, int x, int y, bool bot);

/// Print a deck of cards to the screen.
/// \param deck  The deck to print.
void print_deck(const deck_t *deck);

/// Print the game's user interface to the screen.
/// \param game  The game to print.
void print_ui(const game_t *game);

#endif //INTERFACE_H
