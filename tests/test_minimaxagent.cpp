#include <QtTest>
#include "../src/agents/MinimaxAgent.h"
#include "../src/core/BitBoard.h"

class TestMinimaxAgent : public QObject {
    Q_OBJECT
private slots:
    void testCornerPreference() {
        BitBoard board;
        board.black = 0;
        board.white = 0;
        
        // Setup a board where a corner (0) is available and highly desirable
        // Black: B1(1)
        // White: C1(2)
        // If Black plays A1(0), it's a corner.
        board.black = (1ULL << 1);
        board.white = (1ULL << 2);
        
        MinimaxAgent agent(false, 3); // Black, depth 3
        QSignalSpy spy(&agent, &MinimaxAgent::moveSelected);
        agent.requestMove(board);
        
        QVERIFY(spy.wait(1000));
        int move = spy.at(0).at(0).toInt();
        QCOMPARE(move, 0); // Corner A1 should be chosen
    }

    void testAvoidBadMoves() {
        BitBoard board;
        board.black = 0;
        board.white = 0;
        
        // Setup a board where playing B2(9) is very bad (near corner)
        // and playing D3(19) is neutral.
        // Black to move.
        board.black = (1ULL << 18); // C3
        board.white = (1ULL << 17); // B3
        // Moves possible: A3(16), B2(9), D3(19)...
        
        MinimaxAgent agent(false, 3);
        QSignalSpy spy(&agent, &MinimaxAgent::moveSelected);
        agent.requestMove(board);
        
        QVERIFY(spy.wait(1000));
        int move = spy.at(0).at(0).toInt();
        QVERIFY(move != 9); // Should NOT pick B2 if better moves exist
    }
};

QTEST_MAIN(TestMinimaxAgent)
#include "test_minimaxagent.moc"
