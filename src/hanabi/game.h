#ifndef GAME_H

#define GAME_H

#include "deck.h"

#define MAX_LIVES 3
#define MAX_HINTS 8
#define MAX_SCORE 25

typedef struct game {
    deck_t deck;
    int lives;
    int hints;
    hand_t player_hand;
    hand_t bot_hand;
    bool player_first;
} game_t;

/// Create a new game
/// \param deck The deck of cards
/// \param player_hand The player's hand
/// \param bot_hand The bot's hand
/// \param player_first Whether the player goes first
/// \return The new game
game_t new_game(deck_t deck, hand_t player_hand, hand_t bot_hand, bool player_first);

/// Free the memory allocated for a game
/// \param game The game to free
void free_game(game_t *game);

/// Start the game loop
/// \param game The game to play
void game_loop(game_t *game);

/// Play a turn of the game
/// \param game The game to play
void game_turn(game_t *game);

/// Check if the game is over
/// \param game The game to check
/// \return Whether the game is over
bool is_over(const game_t *game);

/// Get a cJSON object representing a game
/// \param game The game to get the cJSON object for
/// \return The cJSON object representing the game
cJSON *get_game_json(const game_t *game);

/// Get a game from a cJSON object
/// \param game_json The cJSON object to get the game from
/// \return The game represented by the cJSON object
game_t* get_game_from_json(const cJSON *game_json);

/// Save a game to a file
/// \param game The game to save
/// \param filename The file to save the game to
void save_game(const game_t *game, const char *filename);

/// Load a game from a file
/// \param filename The file to load the game from
/// \return The loaded game
game_t *load_game(const char *filename);

#endif //GAME_H
