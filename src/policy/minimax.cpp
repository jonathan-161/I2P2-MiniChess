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
int Minimax::minimax(State* node, int depth, bool max) {
    if (depth == 0) {
        return node->evaluate();
    }
    if (max) {
        int value = -999999999;
        for (auto& action : node->get_legal_actions()) {
            value = std::max(value, minimax(action, depth - 1, false));
            delete child;
        }
        return value;
    }
    else {
        int value = 999999999;
        for (auto& action : node->get_legal_actions()) {
            value = std::min(value, minimax(action, depth - 1, true));
            delete child;
        }
        return value;
    }
}