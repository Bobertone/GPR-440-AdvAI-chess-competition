#include "chess-simulator.h"
// disservin's lib. drop a star on his hard work!
// https://github.com/Disservin/chess-library
#include "chess.hpp"
#include <random>
#include "BoardScore.h"
#include "MinMax.h"
using namespace ChessSimulator;

std::string ChessSimulator::Move(std::string fen) {
    // create your board based on the board string following the FEN notation
    // search for the best move using minimax / monte carlo tree search /
    // alpha-beta pruning / ... try to use nice heuristics to speed up the search
    // and have better results return the best move in UCI notation you will gain
    // extra points if you create your own board/move representation instead of
    // using the one provided by the library

    // here goes a random movement
    
    chess::Board board(fen);

    /*if (board.sideToMove() == chess::Color::WHITE)
    {
        std::optional<MinMaxNode> mv = MinMax(board, 3);
        chess::Movelist moves;
        std::cout << board.getFen() << std::endl;
        chess::movegen::legalmoves(moves, board);
        if (mv->move == NULL)
            return "";
        return chess::uci::moveToUci(mv->move);
    }
    else
    {*/
        chess::Movelist moves;
        std::cout << board.getFen() << std::endl;
        chess::movegen::legalmoves(moves, board);

        // get random move
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, moves.size() - 1);
        chess::Move move = moves[dist(gen)];

        if (move == NULL)
            return "";

        // best move
        chess::Move bestMove = moves[dist(gen)];
        // score
        int bestScore;
        {
            // this is a copy
            chess::Board newBoard = board;
            // make the move
            newBoard.makeMove(bestMove);
            // get the score
            bestScore = BoardScore::Evaluate(newBoard);
        }

        for (const auto& move : moves) {
            chess::Board newBoard = board;
            newBoard.makeMove(move);
            // evaluate the board
            int score = BoardScore::Evaluate(newBoard);
            if (board.sideToMove() == chess::Color::WHITE) {
                if (score < bestScore) {
                    bestScore = score;
                    bestMove = move;
                }
            }
            else {
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = move;
                }
            }
        }
        return chess::uci::moveToUci(bestMove);
    //}
}