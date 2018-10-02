//
// Created by pazcohen on 1/1/18.
//

#include "King.h"

/**
 * the king's piece move ,check whether or not it's legal to the king move to the pos that was entered by the user,
 * according to the games rules.
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * @return true if its legal ,false otherwise
 */
bool King::move(int currentCol, int currentRow, int futureCol, int futureRow)
{
    if ((futureRow == currentRow + 1 && futureCol == currentCol ) ||
        (futureRow == currentRow - 1 && futureCol == currentCol ) || ( futureCol == currentCol + 1 &&
        futureRow == currentRow ) || (futureCol == currentCol -1 && futureRow == currentRow)
        || ( futureCol == currentCol + 1  && futureRow == currentRow + 1) || ( futureCol == currentCol- 1 &&
        futureRow == currentRow -1) || (futureCol == currentCol -1 && futureRow == currentRow + 1) ||
        (futureCol == currentCol + 1 && futureRow == currentRow -1 ))
    {
        return true;
    }
    return false;

}

