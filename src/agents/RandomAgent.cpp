#include "RandomAgent.h"
#include <vector>
#include <random>
#include <QTimer>

RandomAgent::RandomAgent(bool isWhite, QObject* parent)
    : QObject(parent), m_isWhite(isWhite) {}

void RandomAgent::requestMove(const BitBoard& board) {
    uint64_t possibleMoves = board.getPossibleMoves(m_isWhite);
    
    if (possibleMoves == 0) {
        // No moves possible
        QTimer::singleShot(50, this, [this]() {
            emit moveSelected(-1);
        });
        return;
    }
    
    std::vector<int> moveIndices;
    for (int i = 0; i < 64; ++i) {
        if (possibleMoves & (1ULL << i)) {
            moveIndices.push_back(i);
        }
    }
    
    // Pick a random index
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, moveIndices.size() - 1);
    
    int selectedMove = moveIndices[dis(gen)];
    
    // Simulate thinking time to not be instantaneous
    QTimer::singleShot(500, this, [this, selectedMove]() {
        emit moveSelected(selectedMove);
    });
}
