#pragma once

#include "chess.hpp"
#include "BoardScore.h"
#include <queue>
#include <tuple>

struct MinMaxNode {
    // move that led to this board state
    chess::Move move;
    // score of the board state
    int score;
};

// recursive MinMax function. it will explode the call stack!!! be careful and change it to an iterative version
std::optional<MinMaxNode> MinMax(const chess::Board& board, int maxDepth, bool whiteMove);

std::optional<MinMaxNode> BasicBot(const chess::Board& board, int maxDepth);
