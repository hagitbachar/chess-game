//
// Created by pazcohen on 1/1/18.
//

#include "Queen.h"

/**
 * the queen's piece move ,check whether or not it's legal to the queen move to the pos that was entered by the user,
 * according to the games rules.
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * @return true if its legal ,false otherwise
 */
bool Queen::move(int currentCol, int currentRow, int futureCol, int futureRow)
{

    for (int i = 1; i < 8; ++i)
    {
        // check if the step was horizontal or vertical
        if ((futureRow == currentRow + i && futureCol == currentCol ) || (futureRow == currentRow - i &&
            futureCol == currentCol) || (futureRow == currentRow && futureCol == currentCol - i)
            || (futureRow == currentRow && futureCol == currentCol + i))
        {
            return true;
        }// check if the step was diagonal
        else if((futureCol == currentCol + i && futureRow == currentRow + i) || (futureCol == currentCol - i &&
                futureRow == currentRow - i) || (futureCol == currentCol - i && futureRow == currentRow + i) ||
                (futureCol == currentCol + i && futureRow == currentRow - i))
        {
            return true;
        }
    }
    return false;

}
