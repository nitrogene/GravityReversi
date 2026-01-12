#include "GreedyAgent.h"
#include <QTimer>
#include <vector>

GreedyAgent::GreedyAgent(bool isWhite, QObject* parent)
    : QObject(parent), m_isWhite(isWhite) {}

void GreedyAgent::requestMove(const BitBoard& board) {
    uint64_t possibleMoves = board.getPossibleMoves(m_isWhite);
    
    if (possibleMoves == 0) {
        QTimer::singleShot(50, this, [this]() {
            emit moveSelected(-1);
        });
        return;
    }
    
    int bestMove = -1;
    int maxFlips = -1;
    std::vector<int> candidates;

    for (int i = 0; i < 64; ++i) {
        if (possibleMoves & (1ULL << i)) {
            BitBoard simBoard = board;
            int countBefore = simBoard.getPieceCount(m_isWhite);
            simBoard.makeMove(i, m_isWhite);
            int countAfter = simBoard.getPieceCount(m_isWhite);
            int flips = countAfter - countBefore - 1; // -1 for the placed piece
            
            if (flips > maxFlips) {
                maxFlips = flips;
                bestMove = i;
                candidates.clear();
                candidates.push_back(i);
            } else if (flips == maxFlips) {
                candidates.push_back(i);
            }
        }
    }
    
    // If multiple moves have same flips, we could pick one (here, first one or could be random)
    // Let's just pick the first one for deterministic behavior in tests for now
    int selectedMove = candidates.empty() ? -1 : candidates[0];

    // Simulate thinking time
    QTimer::singleShot(500, this, [this, selectedMove]() {
        emit moveSelected(selectedMove);
    });
}
