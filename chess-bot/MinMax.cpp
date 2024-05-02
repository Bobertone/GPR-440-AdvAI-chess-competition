#include "MinMax.h"


// recursive MinMax function. it will explode the call stack!!! be careful and change it to an iterative version
std::optional<MinMaxNode> MinMax(const chess::Board& board, int maxDepth, bool whiteMove) {

    //int = maxDepth
    std::queue<std::tuple<chess::Board, int, MinMaxNode>> frontier;

    //bootstrap case
    if (maxDepth <= 0) {
        return std::nullopt;
    }
    // if the max depth is 1, evaluate the children and return the best move
    else if (maxDepth == 1) {
        chess::Movelist moves;
        chess::movegen::legalmoves(moves, board);

        //TODO: deal with endgame

        //return null if there is no move available
        if (moves.empty())
            return std::nullopt;

        // initialize best move as the first move
        chess::Move bestMove = moves[0];

        // initialize best score as the score of the first move
        int bestScore;
        {
            // this is a copy
            chess::Board newBoard = board;
            // make the move
            newBoard.makeMove(bestMove);
            // get the score
            bestScore = BoardScore::Evaluate(newBoard);
        }

        // iterate over moves skip the first one already evaluated
        for (size_t i = 1; i < moves.size(); i++) {
            const auto& move = moves[i];
            // make a board copy and apply the move
            chess::Board newBoard = board;
            newBoard.makeMove(move);
            // evaluate the board
            int score = BoardScore::Evaluate(newBoard);
            if (whiteMove) {
                //white is searching for the move that maximizes the score
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = move;
                }
            }
            else {
                //black is searching for the move that minimizes the score
                if (score < bestScore) {
                    bestScore = score;
                    bestMove = move;
                }
            }
        }
        return MinMaxNode{ bestMove, bestScore };
    }
    else
    {
        // if the max depth is greater than 1, evaluate the children recursively
        //recursive step
        chess::Movelist moves;
        chess::movegen::legalmoves(moves, board);

        if (moves.empty())
            return std::nullopt;

        // call the MinMax function recursively for each move
        std::vector<MinMaxNode> children;
        for (const auto& move : moves) {
            chess::Board newBoard = board;
            newBoard.makeMove(move);
            auto child = MinMax(newBoard, maxDepth - 1, !whiteMove);
            if (child.has_value()) {
                children.push_back(child.value());
            }
        }
        // return the best move
        std::optional<MinMaxNode> bestChild = std::nullopt;
        if (whiteMove) {
            for (const auto& child : children) {
                if (!bestChild.has_value() || child.score < bestChild.value().score) {
                    bestChild = child;
                }
            }
        }
        else {
            for (const auto& child : children) {
                if (!bestChild.has_value() || child.score > bestChild.value().score) {
                    bestChild = child;
                }
            }
        }
        return bestChild;
    }
}

// recursive MinMax function. it will explode the call stack!!! be careful and change it to an iterative version
std::optional<MinMaxNode> BasicBot(const chess::Board& board, int maxDepth) {

    //int = maxDepth
    std::queue<std::tuple<chess::Board, int, MinMaxNode>> frontier;

    //bootstrap case
    if (maxDepth <= 0) {
        return std::nullopt;
    }
    // if the max depth is 1, evaluate the children and return the best move
    //if (maxDepth == 1) {
        chess::Movelist moves;
        chess::movegen::legalmoves(moves, board);

        //TODO: deal with endgame

        //return null if there is no move available
        if (moves.empty())
            return std::nullopt;

        // initialize best move as the first move
        chess::Move bestMove = moves[0];

        // initialize best score as the score of the first move
        int bestScore;
        {
            // this is a copy
            chess::Board newBoard = board;
            // make the move
            newBoard.makeMove(bestMove);
            // get the score
            bestScore = BoardScore::Evaluate(newBoard);
        }

        // iterate over moves skip the first one already evaluated
        for (size_t i = 1; i < moves.size(); i++) {
            const auto& move = moves[i];
            // make a board copy and apply the move
            chess::Board newBoard = board;
            newBoard.makeMove(move);
            // evaluate the board
            int score = BoardScore::Evaluate(newBoard);
            if (board.sideToMove() == chess::Color::WHITE) {
                //white is searching for the move that maximizes the score
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = move;
                }
            }
            else {
                //black is searching for the move that minimizes the score
                if (score < bestScore) {
                    bestScore = score;
                    bestMove = move;
                }
            }
        }
        return MinMaxNode{ bestMove, bestScore };
    //}
    /*
    // if the max depth is greater than 1, evaluate the children recursively
    //recursive step
    chess::Movelist moves;
    chess::movegen::legalmoves(moves, board);

    if (moves.empty())
        return std::nullopt;

    // call the MinMax function recursively for each move
    std::vector<MinMaxNode> children;
    for (const auto& move : moves) {
        chess::Board newBoard = board;
        newBoard.makeMove(move);
        auto child = BasicBot(newBoard, maxDepth - 1);
        if (child.has_value()) {
            children.push_back(child.value());
        }
    }
    // return the best move
    std::optional<MinMaxNode> bestChild = std::nullopt;
    if (board.sideToMove() == chess::Color::WHITE) {
        for (const auto& child : children) {
            if (!bestChild.has_value() || child.score > bestChild.value().score) {
                bestChild = child;
            }
        }
    }
    else {
        for (const auto& child : children) {
            if (!bestChild.has_value() || child.score < bestChild.value().score) {
                bestChild = child;
            }
        }
    }
    return bestChild;*/
}