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
    if (!node->legal_actions.size())
        node->get_legal_actions();
    if (depth == 0) {
        return node->evaluate();
    }
    if (maxi) {
        if (node->game_state == WIN) {
            return node->evaluate() + 2000;
        }
        int value = -1000000;
        for (auto& action : node->legal_actions) {
            value = std::max(value, minimax(node->next_state(action), depth - 1, false));
        }
        return value;
    }
    else {
        if (node->game_state == WIN) {
            return node->evaluate() - 2000;
        }
        int value = 1000000;
        for (auto& action : node->legal_actions) {
            value = std::min(value, minimax(node->next_state(action), depth - 1, true));
        }
        return value;
    }
}