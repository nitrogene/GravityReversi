#include "BitBoard.h"

BitBoard::BitBoard() {
    reset();
}

void BitBoard::reset() {
    // Initial Reversi setup: 4 pieces in the center
    // D4 (27), E5 (36) are White
    // D5 (35), E4 (28) are Black
    black = (1ULL << 35) | (1ULL << 28);
    white = (1ULL << 27) | (1ULL << 36);
}

uint64_t BitBoard::getPossibleMoves(bool isWhite) const {
    uint64_t own = isWhite ? white : black;
    uint64_t opponent = isWhite ? black : white;
    uint64_t empty = getEmpty();
    uint64_t moves = 0;

    const uint64_t NOT_A_COLUMN = 0xFEFEFEFEFEFEFEFEULL;
    const uint64_t NOT_H_COLUMN = 0x7F7F7F7F7F7F7F7FULL;

    auto check = [&](int shift, uint64_t mask) {
        // Find adjacent opponent pieces
        uint64_t candidates = (shift > 0) ? (own << shift) & mask : (own >> -shift) & mask;
        candidates &= opponent;
        
        while (candidates) {
            uint64_t potential = (shift > 0) ? (candidates << shift) & mask : (candidates >> -shift) & mask;
            if (potential & empty) {
                moves |= (potential & empty);
            }
            candidates = potential & opponent;
        }
    };

    // North: -8, South: +8, East: +1, West: -1
    check(-8, 0xFFFFFFFFFFFFFFFFULL); // North
    check(8, 0xFFFFFFFFFFFFFFFFULL);  // South
    check(1, NOT_A_COLUMN);           // East
    check(-1, NOT_H_COLUMN);          // West
    check(-7, NOT_A_COLUMN);          // North-East
    check(-9, NOT_H_COLUMN);          // North-West
    check(9, NOT_A_COLUMN);           // South-East
    check(7, NOT_H_COLUMN);           // South-West

    return moves;
}

void BitBoard::makeMove(int index, bool isWhite) {
    uint64_t move = 1ULL << index;
    uint64_t& own = isWhite ? white : black;
    uint64_t& opponent = isWhite ? black : white;

    uint64_t flips = calculateFlips(move, own, opponent);
    own |= (move | flips);
    opponent &= ~flips;
}

uint64_t BitBoard::calculateFlips(uint64_t move, uint64_t own, uint64_t opponent) const {
    uint64_t totalFlips = 0;
    const uint64_t NOT_A_COLUMN = 0xFEFEFEFEFEFEFEFEULL;
    const uint64_t NOT_H_COLUMN = 0x7F7F7F7F7F7F7F7FULL;

    auto checkDir = [&](int shift, uint64_t mask) {
        uint64_t dirFlips = 0;
        uint64_t curr = (shift > 0) ? (move << shift) & mask : (move >> -shift) & mask;
        while (curr & opponent) {
            dirFlips |= curr;
            curr = (shift > 0) ? (curr << shift) & mask : (curr >> -shift) & mask;
        }
        if (curr & own) totalFlips |= dirFlips;
    };

    checkDir(-8, 0xFFFFFFFFFFFFFFFFULL); // North
    checkDir(8, 0xFFFFFFFFFFFFFFFFULL);  // South
    checkDir(1, NOT_A_COLUMN);           // East
    checkDir(-1, NOT_H_COLUMN);          // West
    checkDir(-7, NOT_A_COLUMN);          // North-East
    checkDir(-9, NOT_H_COLUMN);          // North-West
    checkDir(9, NOT_A_COLUMN);           // South-East
    checkDir(7, NOT_H_COLUMN);           // South-West

    return totalFlips;
}

int BitBoard::getPieceCount(bool isWhite) const {
    uint64_t b = isWhite ? white : black;
    int count = 0;
    while (b) {
        b &= (b - 1);
        count++;
    }
    return count;
}
