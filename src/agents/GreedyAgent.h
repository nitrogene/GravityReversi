#ifndef GREEDYAGENT_H
#define GREEDYAGENT_H

#include "IPlayer.h"
#include <QObject>

/**
 * @brief The GreedyAgent class picks the move that flips the most pieces.
 */
class GreedyAgent : public QObject, public IPlayer {
    Q_OBJECT
public:
    explicit GreedyAgent(bool isWhite, QObject* parent = nullptr);
    
    QString name() const override { return "GreedyAgent (The Glutton)"; }
    void requestMove(const BitBoard& board) override;

signals:
    void moveSelected(int index);

private:
    bool m_isWhite;
};

#endif // GREEDYAGENT_H
