#ifndef RANDOMAGENT_H
#define RANDOMAGENT_H

#include "IPlayer.h"
#include <QObject>

class RandomAgent : public QObject, public IPlayer {
    Q_OBJECT
public:
    explicit RandomAgent(bool isWhite, QObject* parent = nullptr);
    
    QString name() const override { return "RandomAgent (The Monkey)"; }
    void requestMove(const BitBoard& board) override;

signals:
    void moveSelected(int index);

private:
    bool m_isWhite;
};

#endif // RANDOMAGENT_H
