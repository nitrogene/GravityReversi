#include <QtTest>
#include "../src/agents/GreedyAgent.h"
#include "../src/core/BitBoard.h"

class TestGreedyAgent : public QObject {
    Q_OBJECT
private slots:
    void initTestCase() {}
    void cleanupTestCase() {}

    void testGreedyMove() {
        BitBoard board;
        board.reset(); // Standard start

        GreedyAgent agent(false); // Black player
        
        QSignalSpy spy(&agent, &GreedyAgent::moveSelected);
        agent.requestMove(board);
        
        // Wait for asynchronous move (500ms in implementation)
        QVERIFY(spy.wait(1000));
        
        int move = spy.at(0).at(0).toInt();
        QVERIFY(move != -1);
        
        // At start, all moves (19, 26, 37, 44) give 1 flip. 
        // Greedy should pick one of them.
        uint64_t possible = board.getPossibleMoves(false);
        QVERIFY(possible & (1ULL << move));
    }
    
    void testBestMoveSelection() {
        BitBoard board;
        board.black = 0;
        board.white = 0;
        
        // Custom scenario where one move is clearly better
        // Black: D4(27)
        // White: D5(35), D6(43)
        // Move at D7(51) flips 2. Move at E4(28) (if hypothetical) flips 0.
        board.black = (1ULL << 27);
        board.white = (1ULL << 35) | (1ULL << 43);
        
        GreedyAgent agent(false);
        QSignalSpy spy(&agent, &GreedyAgent::moveSelected);
        agent.requestMove(board);
        
        QVERIFY(spy.wait(1000));
        int move = spy.at(0).at(0).toInt();
        QCOMPARE(move, 51); // D7 should be the best move
    }
};

QTEST_MAIN(TestGreedyAgent)
#include "test_greedyagent.moc"
