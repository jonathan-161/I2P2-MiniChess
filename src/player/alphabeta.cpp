#include <iostream>
#include <fstream>

#include "../config.hpp"
#include "../state/state.hpp"
#include "../policy/alphabeta.hpp"


State* root;

/**
 * @brief Read the board from the file
 * 
 * @param fin 
 */
void read_board(std::ifstream& fin) {
  Board board;
  int player;
  fin >> player;

  for (int pl=0; pl<2; pl++) {
    for (int i=0; i<BOARD_H; i++) {
      for (int j=0; j<BOARD_W; j++) {
        int c; fin >> c;
        // std::cout << c << " ";
        board.board[pl][i][j] = c;
      }
      // std::cout << std::endl;
    }
  }
  root = new State(board, player);
  root->get_legal_actions();
}


/**
 * @brief randomly choose a move and then write it into output file
 * 
 * @param fout 
 */
void write_valid_spot(std::ofstream& fout) {
    // Keep updating the output until getting killed.
    if (!root->legal_actions.size())
        root->get_legal_actions();
    int res, cur, first = 1, overwrite = 0;
    Move dir, second; //second to store second best, in case the first one doesn't change anything
    for(auto& it: root->legal_actions) {
        cur = AlphaBeta::alphabeta(root->next_state(it), 4, -1000, 1000, false);
        if (first) {
            first = 0;
            res = cur;
        }
        else if (cur >= res) {
            res = cur;
            if (!overwrite)
                overwrite = 1;
            else if (overwrite)
                second = dir;
            dir = it;
        }
        if (dir.first == dir.second)
            dir = overwrite? second: root->legal_actions[0];

        
        fout << dir.first.first << " " << dir.first.second << " "\
            << dir.second.first << " " << dir.second.second << std::endl;

        // Remember to flush the output to ensure the last action is written to file.
        fout.flush();
    }
}


/**
 * @brief Main function for player
 * 
 * @param argv 
 * @return int 
 */
int main(int, char** argv) {
  srand(RANDOM_SEED);
  std::ifstream fin(argv[1]);
  std::ofstream fout(argv[2]);

  read_board(fin);
  write_valid_spot(fout);

  fin.close();
  fout.close();
  return 0;
}
