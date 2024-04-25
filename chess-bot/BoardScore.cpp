#include "BoardScore.h"

int BoardScore::Evaluate(chess::Board& board) {
	int score = 0;
	for (size_t row = 0; row < 8; row++) {
		for (size_t col = 0; col < 8; col++) {
			auto piece = board.at(chess::Square(chess::File(col), chess::Rank(row)));
			//accumulate scores
			switch (piece.type()) {
			/*
			case chess::PieceType::underlying::PAWN:
				if (piece.color().internal() == chess::Color::underlying::BLACK)
					score += 1;
				else
					score -= 1;
				break;
			*/
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
		}
	}
	return score;
}