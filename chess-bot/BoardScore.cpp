#include "BoardScore.h"

int BoardScore::Evaluate(const chess::Board& board) {
    int score = 0;
    for (size_t id = 0; id < 64; id++) {
        auto piece = board.at(id);
        if (piece == chess::Piece::NONE)
            continue;
        //accumulate scores
        int delta = 0;
        switch (piece.type().internal()) {
        case chess::PieceType::PAWN:
            delta = 1;
            break;
        case chess::PieceType::KNIGHT:
        case chess::PieceType::BISHOP:
            delta = 3;
            break;
        case chess::PieceType::ROOK:
            delta = 5;
            break;
        case chess::PieceType::QUEEN:
            delta = 9;
            break;
        case chess::PieceType::KING:
            delta = 100;
            break;
        default:
            break;
        }
        if (piece.color().internal() == chess::Color::WHITE)
            score += delta;
        else
            score -= delta;
    }

    return score;
}