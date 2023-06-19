#pragma once

#include "../state/state.hpp"

/**
 * @brief Policy class for Minimax algorithm
 * Your policy class should have get_move method
 */
class MiniMax{
public:
	static int minimax(State* node, int depth, bool maximizingPlayer);
};
