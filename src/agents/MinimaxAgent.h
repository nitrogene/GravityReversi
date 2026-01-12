#ifndef MINIMAXAGENT_H
#define MINIMAXAGENT_H

#include <QObject>
#include "IPlayer.h"

/**
 * @brief AI agent using Minimax algorithm with Alpha-Beta pruning.
 */
class MinimaxAgent : public QObject, public IPlayer {
    Q_OBJECT
public:
    explicit MinimaxAgent(bool isWhite, int depth = 5, QObject* parent = nullptr);
    
    QString name() const override { return QString("Minimax Agent (d=%1)").arg(m_depth); }
    void requestMove(const BitBoard& board) override;

signals:
    void moveSelected(int index);

private:
    int minimax(const BitBoard& board, int depth, int alpha, int beta, bool maximizingPlayer);
    int evaluate(const BitBoard& board);
    
    bool m_isWhite;
    int m_depth;
};

#endif // MINIMAXAGENT_H
