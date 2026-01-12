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
    
    // Initial setup
    void reset();
    
    // Move generation and execution
    uint64_t getPossibleMoves(bool isWhite) const;
    void makeMove(int index, bool isWhite);
    
    // Utilities
    int getPieceCount(bool isWhite) const;
    uint64_t getOccupied() const { return black | white; }
    uint64_t getEmpty() const { return ~(black | white); }

private:
    // Helper for shift-based flip calculation
    uint64_t calculateFlips(uint64_t move, uint64_t own, uint64_t opponent) const;
};

#endif // BITBOARD_H
