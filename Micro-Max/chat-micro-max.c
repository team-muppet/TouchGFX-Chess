#include <stdio.h>

#define BOARD_SIZE 128
#define HASH_SIZE 16777224
#define INFINITE 8000
#define MAX_DEPTH 99

struct HashEntry {
    int key, value;
    char bestFrom, bestTo, depth;
} hashTable[HASH_SIZE]; // hash table, 16M+8 entries

int scorePawn = 112, outOfBounds = 136, boardEdge = 128, maxValue = 8000, hashMask = 799;
int quietNode, nodeCount, depth, iteration;
char currentPlayer, kingSquare, lastMoveTo,
pieceValues[] = {0, 1, 1, 3, -1, 3, 5, 9}, // relative piece values
moveOffsets[] = {-16, -15, -17, 0, 1, 16, 0, 1, 16, 15, 17, 0, 14, 18, 31, 33, 0, // step-vector lists
                 7, -1, 11, 6, 8, 3, 6, // 1st direction in moveOffsets[] per piece
                 6, 3, 5, 7, 4, 5, 3, 6}, // initial piece setup
board[BOARD_SIZE], // board: half of 16x8+dummy
translationTable[1035], // hash translation table
pieceSymbols[] = ".?+nkbrq?*?NKBRQ"; // piece symbols on printout

// Recursive minimax search with alpha-beta pruning
int minimax(int side, int alpha, int beta, int evaluation, int prevDest, int hashKey, int secondaryHashKey, int enPassant, int depth) {
    int moveFrom, moveTo, directionIndex, direction, moveIndex, hashIndex, bestFrom, bestTo;
    char piece, targetPiece, movedPiece, captureFlag;
    struct HashEntry *entry;

    // Lookup position in hash table
    hashIndex = (side * enPassant ^ hashKey) & (HASH_SIZE - 9); // try 8 consecutive locations
    while ((hashTable[++hashIndex].key && hashTable[hashIndex].key != secondaryHashKey) && --iteration);
    entry = hashTable + (iteration ? hashIndex : 0); // use found entry or default to 0 if none found

    if (entry->key) { // hash hit
        if (entry->depth >= depth) { // depth sufficient to use stored value
            if (entry->value >= beta || (entry->bestFrom & boardEdge && entry->value <= alpha))
                return entry->value; // use stored value if within bounds
            depth = depth - 1; // otherwise, use as iterative deepening start
        }
        bestFrom = entry->bestFrom & ~outOfBounds; // clear flags
        bestTo = entry->bestTo ? entry->bestTo : 0;
    } else {
        depth = bestFrom = bestTo = 0; // start iteration from scratch
    }

    nodeCount++; // Increment node count for statistics
    int value = -INFINITE;
    while (depth++ < MAX_DEPTH && (prevDest == 8 && nodeCount < 10000000 && depth < 98)) { // Iterative deepening loop
        moveFrom = bestFrom; // Start scan at previous best move
        bestTo |= 8 & (bestTo >> 4); // request try non-castle first
        value = depth > 1 ? -INFINITE : evaluation; // Use static evaluation if no depth left

        for (moveIndex = 0; moveIndex < BOARD_SIZE; moveIndex++) { // Loop through all board positions
            piece = board[moveFrom];
            if (piece & side) { // Own piece
                directionIndex = moveOffsets[piece & 7 + 16]; // Get first direction offset for piece
                while (direction = (piece > 2 && direction < 0) ? -direction : -moveOffsets[++directionIndex]) {
                    moveTo = moveFrom;
                    captureFlag = boardEdge;
                    do {
                        movedPiece = moveTo += direction; // Move piece along direction
                        if (bestTo & 8)
                            movedPiece = moveTo = bestTo & ~outOfBounds; // Use previous best move
                        if (moveTo & outOfBounds)
                            break; // Hit board edge
                        targetPiece = board[movedPiece];
                        if (targetPiece & side || (piece < 3 && !(direction & 7) != !targetPiece))
                            break; // Invalid move (capture own piece or pawn move not diagonal)
                        int pieceValue = 99 * pieceValues[targetPiece & 7]; // Value of captured piece
                        if (pieceValue < 0 || (enPassant - boardEdge && board[enPassant] && moveTo - enPassant < 2 && enPassant - moveTo < 2))
                            value = INFINITE; // King capture or bad castling
                        if (value >= beta)
                            goto cutoff; // Alpha-beta pruning cutoff

                        // Make move
                        board[captureFlag] = board[movedPiece] = board[moveFrom] = 0;
                        board[moveTo] = piece & 31; // Remove virgin bit from rooks or king
                        if (!(captureFlag & boardEdge)) {
                            board[moveFrom] = side + 6; // Put rook on board during castling
                            pieceValue += 30; // Increase score for castling
                        }
                        if (piece < 3) { // Pawn move
                            // Additional pawn evaluations go here
                        }

                        // Recursive call to evaluate opponent's response
                        int eval = -minimax(24 - side, -beta, -alpha, -evaluation - pieceValue, hashKey, secondaryHashKey, captureFlag, moveTo, depth - 1);
                        if (eval > value) {
                            value = eval;
                            bestFrom = moveFrom;
                            bestTo = moveTo | (side & captureFlag);
                        }
                        // Undo move
                        board[moveFrom] = piece;
                        board[moveTo] = targetPiece;
                        board[captureFlag] = side + 38; // Reset original rook position
                    } while (!targetPiece); // Continue while not capturing
                }
            }
            moveFrom = (moveFrom + 9 & ~boardEdge) - bestFrom; // Next square of board, wrap around
        }
    cutoff:
        if (value > INFINITE / 4 || value < -INFINITE / 4)
            depth = MAX_DEPTH; // Mate found, terminate search
        value = value + INFINITE ? value : -minimax(24 - side, -INFINITE, INFINITE, 0, hashKey, kingSquare, boardEdge, prevDest, 1) / 2; // Adjust for stalemate/mate
        if (!entry->key || (entry->bestFrom & outOfBounds) != outOfBounds || entry->depth <= depth) { // Update hash table if better entry found
            entry->key = secondaryHashKey;
            entry->value = value;
            entry->depth = depth;
            hashTable[0].key = 0; // Maintain a dummy entry for hash collisions
            entry->bestFrom = bestFrom | 8 * (value > beta) | boardEdge * (value < alpha);
            entry->bestTo = bestTo;
        }
    }
    if (prevDest & 8) { // If in check, determine legality
        kingSquare = bestFrom;
        lastMoveTo = bestTo & ~outOfBounds;
    }
    return value;
}

int main() {
    int j, *p, command[9];

    for (int i = 0; i < 8; i++) {
        board[i] = (board[i + scorePawn] = moveOffsets[i + 24] + 40) + 8;
        board[i + 16] = 18;
        board[i + 96] = 9; // Initial board setup
        for (j = 0; j < 8; j++)
            board[16 * j + i + 8] = (i - 4) * (i - 4) + (j - 3.5) * (j - 3.5); // Center-points table (in unused half board[])
    }
    for (int i = 0; i < 1035; i++) {
        translationTable[i] = random() >> 9;
    }

    while (1) { // Play loop
        for (int i = 0; i < 121; i++)
            printf(" %c", i & 8 && (i += 7) ? 10 : pieceSymbols[board[i] & 15]); // Print board
        p = command;
        while ((*p++ = getchar()) > 10); // Read input line
        nodeCount = 0;
        if (*command - 10) {
            kingSquare = command[0] - 16 * command[1] + hashMask;
            lastMoveTo = command[2] - 16 * command[3] + hashMask;
        } else // Parse entered move
            minimax(currentPlayer, -INFINITE, INFINITE, quietNode, 1, 1, lastMoveTo, 8, 0); // Or think up one
        for (int i = 0; i < HASH_SIZE; i++)
            hashTable[i].key = 0; // Clear hash table
        if (minimax(currentPlayer, -INFINITE, INFINITE, quietNode, 1, 1, lastMoveTo, 9, 2) == INFINITE)
            currentPlayer ^= 24; // Check legality & do move
    }
}
