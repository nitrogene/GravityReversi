#include <QtTest>
#include "../src/core/BitBoard.h"

class TestRules : public QObject {
    Q_OBJECT
private slots:
    void testNoMovesOnOccupied() {
        BitBoard board;
        // Scenario where a shift might land on both an empty and an occupied square
        // Black: D4(27), F4(29)
        // White: E4(28)
        // If we check West from F4, it jumps over E4(White) and hits D4(Black, occupied).
        // If there's another Black piece elsewhere that hits an empty square in the same direction,
        // the logic might fail.
        
        board.black = 0;
        board.white = 0;
        
        // Let's set up a "divergent" case
        // Own (Black): A3 (16), C3 (18)
        // Opponent (White): B3 (17), D3 (19)
        // Possible move for Black: E3 (20) - coming from D3
        // Shift East from Black:
        // Candidates (Adjacent Opponent): B3, D3
        // Shift East from Candidates: C3 (Occupied by Own!), E3 (Empty)
        // The current bug: potential = {C3, E3}. potential & empty = {E3} (True). 
        // moves |= {C3, E3} -> C3 is added to moves!
        
        board.black = (1ULL << 16) | (1ULL << 18);
        board.white = (1ULL << 17) | (1ULL << 19);
        
        uint64_t moves = board.getPossibleMoves(false); // Black moves
        uint64_t occupied = board.getOccupied();
        
        QVERIFY((moves & occupied) == 0);
    }
};

QTEST_MAIN(TestRules)
#include "test_rules.moc"
