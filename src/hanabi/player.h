#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"

/// Returns the index of the card that can be played. If no card can be played, returns UINT32_MAX.
/// \param player_hand The hand of the player.
/// \param deck The deck of the game.
/// \return The index of the card that can be played. If no card can be played, returns UINT32_MAX.
uint32_t get_player_playable(const hand_t *player_hand, const deck_t *deck);

/// Comprises the player's turn.
/// \param game The game.
/// \return Whether the action is valid. If not, returns INVALID_ACTION.
int player_turn(game_t *game);

/// Gives a clue to the bot.
/// \param player_hand The hand of the player.
/// \param bot_hand The hand of the bot.
/// \param idx Whether the action is valid. If not, returns INVALID_ACTION.
int player_hint(game_t *game);

/// Plays a card.
/// \param game The game.
/// \return Whether the action is valid. If not, returns INVALID_ACTION.
int player_play(game_t *game);

/// Discards a card.
/// \param game The game.
/// \return Whether the action is valid. If not, returns INVALID_ACTION.
int player_discard(game_t *game);

#endif //PLAYER_H
