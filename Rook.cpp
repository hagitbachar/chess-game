//
// Created by pazcohen on 1/1/18.
//

#include "Rook.h"

/**
 * the rook's piece move ,check whether or not it's legal to the rook move to the pos that was entered by the user,
 * according to the games rules.
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * @return true if its legal ,false otherwise
 */
bool Rook::move(int currentCol, int currentRow, int futureCol, int futureRow)
{
    for (int i = 1; i < 8; ++i)
    {
        if ((futureRow == currentRow + i && futureCol == currentCol ) || (futureRow == currentRow - i &&
            futureCol == currentCol) || (futureRow == currentRow && futureCol == currentCol - i)
            || (futureRow == currentRow && futureCol == currentCol + i))
        {
            return true;
        }
    }
    return false;
}
