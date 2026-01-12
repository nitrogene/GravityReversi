#include <QtTest>
#include "../src/core/BitBoard.h"

class TestBitBoard : public QObject {
    Q_OBJECT

private slots:
    void initTestCase() {
        // Initialization code if needed
    }

    void testInitialBoard() {
        BitBoard board;
        // Check initial setup (D4, E5 White; D5, E4 Black)
        QCOMPARE(board.getPieceCount(false), 2); // Black
        QCOMPARE(board.getPieceCount(true), 2);  // White
        
        uint64_t d4 = 1ULL << (3 * 8 + 3);
        uint64_t e5 = 1ULL << (4 * 8 + 4);
        uint64_t d5 = 1ULL << (4 * 8 + 3);
        uint64_t e4 = 1ULL << (3 * 8 + 4);
        
        QVERIFY(board.white & d4);
        QVERIFY(board.white & e5);
        QVERIFY(board.black & d5);
        QVERIFY(board.black & e4);
    }

    void testLegalMoves() {
        BitBoard board;
        uint64_t moves = board.getPossibleMoves(false); // Black's turn
        
        // Expected initial moves for Black: 19, 26, 37, 44
        uint64_t expected = (1ULL << 19) | (1ULL << 26) | (1ULL << 37) | (1ULL << 44);
        QCOMPARE(moves, expected);
    }

    void testMakeMove() {
        BitBoard board;
        // Move D3 (index 19) for Black
        board.makeMove(19, false);
        
        // After D3, Black should have 4 pieces, White should have 1
        QCOMPARE(board.getPieceCount(false), 4);
        QCOMPARE(board.getPieceCount(true), 1);
        
        // Verify cell 19 is now Black
        QVERIFY(board.black & (1ULL << 19));
        // Verify cell 27 (D4) was flipped to Black
        QVERIFY(board.black & (1ULL << 27));
    }
};

QTEST_MAIN(TestBitBoard)
#include "test_bitboard.moc"
