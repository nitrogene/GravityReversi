#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>

/**
 * @brief The BitBoard class manages the Reversi board using 64-bit integers.
 */
class BitBoard {
public:
    BitBoard();
    
    // Core game state representation
    uint64_t black;
    uint64_t white;
    
    // Future operations: getLegalMoves, makeMove, etc.
};

#endif // BITBOARD_H
