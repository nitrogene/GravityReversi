#include <QtTest>
#include "../src/core/BitBoard.h"
#include "../src/agents/RandomAgent.h"

class TestRandomAgent : public QObject {
    Q_OBJECT

private slots:
    void testRequestMove() {
        BitBoard board;
        RandomAgent agent(false); // Black
        
        QSignalSpy spy(&agent, SIGNAL(moveSelected(int)));
        agent.requestMove(board);
        
        // Wait for the simulated delay (500ms)
        QVERIFY(spy.wait(1000));
        
        QCOMPARE(spy.count(), 1);
        int move = spy.at(0).at(0).toInt();
        
        // Verify it's one of the initial legal moves for Black: 19, 26, 37, 44
        uint64_t possibleMoves = board.getPossibleMoves(false);
        QVERIFY(possibleMoves & (1ULL << move));
    }

    void testNoMoves() {
        BitBoard board;
        // Fill board to have no moves (simplified case: all black)
        board.black = ~0ULL;
        board.white = 0ULL;
        
        RandomAgent agent(false);
        QSignalSpy spy(&agent, SIGNAL(moveSelected(int)));
        agent.requestMove(board);
        
        QVERIFY(spy.wait(1000));
        QCOMPARE(spy.at(0).at(0).toInt(), -1);
    }
};

QTEST_MAIN(TestRandomAgent)
#include "test_randomagent.moc"
