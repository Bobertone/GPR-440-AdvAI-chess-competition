#ifndef CHESS_BOARDSCORE_H
#define CHESS_BOARDSCORE_H
#include "chess.hpp"

class BoardScore {
public:
    // Receive a board and then evaluate the piece score heuristic
    static int Evaluate(chess::Board& board);
};


#endif //CHESS_BOARDSCORE_H