//
// Created by pazcohen on 1/1/18.
//

#include "Pawn.h"

#define WHITE "37"
#define BLACK "30"

/**
 * the pawn's piece move ,check whether or not it's legal to the pawn move to the pos that was entered by the user,
 * according to the games rules. Specially in the pawn character we have also to check if it's in eating state or not
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * @return true if its legal ,false otherwise
 */
bool Pawn::move( int currentCol, int currentRow, int futureCol, int futureRow)
{
    this-> isDiagonalStep = false;
    if(this->getColor() == WHITE)
    {
        if ((futureRow - currentRow <= 2 && futureRow - currentRow > 0 && futureCol == currentCol &&
            this -> getIsFirstMove()))
        {
            return true;
        }
        else if((futureRow == currentRow + 1 && futureCol == currentCol))
        {
            return true;
        }
        else if((futureRow == currentRow + 1 && futureCol == currentCol + 1) ||
                (futureRow == currentRow + 1 && futureCol == currentCol - 1))
        {
            this-> isDiagonalStep = true;
            return true;
        }
    }
    else if(this -> getColor() == BLACK)
    {
        if ((futureRow - currentRow >= -2 && futureRow - currentRow < 0 && futureCol == currentCol && this
            ->getIsFirstMove()))
        {
            return true;
        }
        else if((futureRow == currentRow - 1 && futureCol == currentCol))
        {
            return true;

        }
        else if((futureRow == currentRow - 1 && futureCol == currentCol - 1) ||
                (futureRow == currentRow - 1 && futureCol == currentCol + 1))
        {
            this -> isDiagonalStep = true;
            return true;
        }
    }
    return false;
}
