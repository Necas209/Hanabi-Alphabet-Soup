#ifndef BOT_H

#define BOT_H

#include "game.h"

typedef enum discard_strategy {
    // Discard a card that has both color and number unknown
    DISCARD_UNKNOWN = 1,
    // Discard a card with known number that is less than or equal to the lowest number on the table
    DISCARD_LOWEST_TABLE = 2,
    // Discard a card with known color and number that is less than or equal to the number of fireworks of its color
    DISCARD_KNOWN_FIREWORKS = 3,
    // Discard a card that has either color or number known, but not both
    DISCARD_HALF_KNOWN = 4,
    // Discard a random card
    DISCARD_RANDOM = 5
} discard_strategy_t;

/// Returns the index of the card that can be discarded. If no card can be discarded, returns UINT32_MAX.
/// \param hand The hand of the bot.
/// \param strategy The strategy to use for discarding.
/// \param deck The deck of the game.
/// \return The index of the card that can be discarded. If no card can be discarded, returns UINT32_MAX.
uint32_t get_bot_discardable(const hand_t *hand, discard_strategy_t strategy, const deck_t *deck);

/// Returns the index of the card that can be played. If no card can be played, returns UINT32_MAX.
/// \param hand The hand of the bot.
/// \param deck The deck of the game.
/// \return The index of the card that can be played. If no card can be played, returns UINT32_MAX.
uint32_t get_bot_playable(const hand_t *hand, const deck_t *deck);

/// Comprises the bot's turn.
/// \param game The game.
void bot_turn(game_t *game);

/// Gives a clue to the player.
/// \param bot_hand The hand of the bot.
/// \param player_hand The hand of the player.
/// \param idx The index of the card to give a clue about.
void bot_hint(const hand_t *bot_hand, hand_t *player_hand, uint32_t idx);

#endif //BOT_H
