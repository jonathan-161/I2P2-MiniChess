#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int MiniMax::minimax(State* node, int depth, bool maxi) {
    if (depth == 0) {
        return node->evaluate();
    }
    if (maxi) {
        int value = -999999999;
        for (auto& action : node->legal_actions) {
            value = std::max(value, minimax(node->next_state(action), depth - 1, false));
        }
        return value;
    }
    else {
        int value = 999999999;
        for (auto& action : node->legal_actions) {
            value = std::min(value, minimax(node->next_state(action), depth - 1, true));
        }
        return value;
    }
}