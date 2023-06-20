#pragma once

#include "../state/state.hpp"

/**
 * @brief Policy class for Minimax algorithm
 * Your policy class should have get_move method
 */
class Submission{
public:
	static int alphabeta(State* node, int depth, int alpha, int beta, bool maximizingPlayer);
};
