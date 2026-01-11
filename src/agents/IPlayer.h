#ifndef IPLAYER_H
#define IPLAYER_H

#include "BitBoard.h"
#include <QString>

/**
 * @brief Interface for any Reversi player (Human or AI).
 */
class IPlayer {
public:
    virtual ~IPlayer() = default;
    
    virtual QString name() const = 0;
    
    // Asynchronous move request: will likely return a QFuture or use signals later
    // For now, defined as a placeholder
    virtual void requestMove(const BitBoard& board) = 0;
};

#endif // IPLAYER_H
