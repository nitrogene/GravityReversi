#include "MinimaxAgent.h"
#include <QTimer>
#include <limits>
#include <algorithm>
#include <vector>

MinimaxAgent::MinimaxAgent(bool isWhite, int depth, QObject* parent)
    : QObject(parent), m_isWhite(isWhite), m_depth(depth) {}

void MinimaxAgent::requestMove(const BitBoard& board) {
    uint64_t possibleMoves = board.getPossibleMoves(m_isWhite);
    
    if (possibleMoves == 0) {
        QTimer::singleShot(50, this, [this]() {
            emit moveSelected(-1);
        });
        return;
    }
    
    int bestMove = -1;
    int bestValue = std::numeric_limits<int>::min();
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();

    for (int i = 0; i < 64; ++i) {
        if (possibleMoves & (1ULL << i)) {
            BitBoard simBoard = board;
            simBoard.makeMove(i, m_isWhite);
            
            int moveValue = minimax(simBoard, m_depth - 1, alpha, beta, false);
            
            if (moveValue > bestValue || bestMove == -1) {
                bestValue = moveValue;
                bestMove = i;
            }
            alpha = std::max(alpha, bestValue);
        }
    }

    // Simulate thinking time to avoid instant moves
    QTimer::singleShot(250, this, [this, bestMove]() {
        emit moveSelected(bestMove);
    });
}

int MinimaxAgent::minimax(const BitBoard& board, int depth, int alpha, int beta, bool maximizingPlayer) {
    bool nextColor = maximizingPlayer ? m_isWhite : !m_isWhite;
    uint64_t moves = board.getPossibleMoves(nextColor);
    
    if (depth == 0 || (moves == 0 && board.getPossibleMoves(!nextColor) == 0)) {
        return evaluate(board);
    }

    if (moves == 0) {
        // Skip turn
        return minimax(board, depth - 1, alpha, beta, !maximizingPlayer);
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (int i = 0; i < 64; ++i) {
            if (moves & (1ULL << i)) {
                BitBoard simBoard = board;
                simBoard.makeMove(i, nextColor);
                int eval = minimax(simBoard, depth - 1, alpha, beta, false);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) break;
            }
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (int i = 0; i < 64; ++i) {
            if (moves & (1ULL << i)) {
                BitBoard simBoard = board;
                simBoard.makeMove(i, nextColor);
                int eval = minimax(simBoard, depth - 1, alpha, beta, true);
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if (beta <= alpha) break;
            }
        }
        return minEval;
    }
}

int MinimaxAgent::evaluate(const BitBoard& board) {
    // Basic weight matrix for Reversi (coins are very valuable)
    static const int weights[64] = {
        100, -20, 10,  5,  5, 10, -20, 100,
        -20, -50, -2, -2, -2, -2, -50, -20,
         10,  -2,  5,  1,  1,  5,  -2,  10,
          5,  -2,  1,  0,  0,  1,  -2,   5,
          5,  -2,  1,  0,  0,  1,  -2,   5,
         10,  -2,  5,  1,  1,  5,  -2,  10,
        -20, -50, -2, -2, -2, -2, -50, -20,
        100, -20, 10,  5,  5, 10, -20, 100
    };

    int score = 0;
    for (int i = 0; i < 64; ++i) {
        uint64_t mask = (1ULL << i);
        if (board.white & mask) {
            score += weights[i];
        } else if (board.black & mask) {
            score -= weights[i];
        }
    }

    // Return score relative to the agent's color
    return m_isWhite ? score : -score;
}
