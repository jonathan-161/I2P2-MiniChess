#include <cstdlib>

#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int AlphaBeta::alphabeta(State* node, int depth, int alpha, int beta, bool maxi) {
    if (depth == 0) {
        return node->evaluate();
    }
    if (!node->legal_actions.size())
        node->get_legal_actions();
    if (maxi) {
        if (node->game_state == WIN) {
            return node->evaluate() + 2000;
        }
        int value = -100000;
        for (auto& action : node->legal_actions) {
            value = std::max(value, alphabeta(node->next_state(action), depth - 1, alpha, beta, false));
            alpha = std::max(alpha, value);
            if (alpha >= beta)
                break;
        }
        return value;
    }
    else {
        if (node->game_state == WIN) {
            return node->evaluate() - 2000;
        }
        int value = 100000;
        for (auto& action : node->legal_actions) {
            value = std::min(value, alphabeta(node->next_state(action), depth - 1, alpha, beta, true));
            beta = std::min(beta, value);
            if (beta <= alpha)
                break;
        }
        return value;
    }
}