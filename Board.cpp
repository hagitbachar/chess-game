//
// Created by pazcohen on 1/1/18.
//


#include "Board.h"

#define WHITE "37"
#define BLACK "30"
#define BLUE "46m"
#define GREEN "42m"

#define ROOK "\u265C"
#define KNIGHT "\u265E"
#define BISHOP "\u265D"
#define KING "\u265A"
#define QUEEN "\u265B"
#define PAWN "\u265F"





/**
 * This function create all the tools for one player
 * @param color the color of the player, white or black
 * @param array to assign the tools
 */
void Board::createPlayer(std::string color, Player* array[2][8])
{
    for (int j = 0; j < 2; ++j)
    {
        Rook* rook = new Rook(color, ROOK);
        array[0][7 * j] = rook;
        array[0][7 * j]->setSubRow(0);
        array[0][7 * j]->setSubCol(7 * j);
    }
    for (int k = 0; k < 2; ++k)
    {
        Knight* knight = new Knight(color, KNIGHT);
        array[0][(5 * k) + 1] = knight;
        array[0][(5 * k) + 1]->setSubRow(0);
        array[0][(5 * k) + 1]->setSubCol((5 * k) + 1);
    }
    for (int l = 0; l < 2; ++l)
    {
        Bishop* bishop = new Bishop(color, BISHOP);
        array[0][(3 * l) + 2] = bishop;
        array[0][(3 * l) + 2]->setSubRow(0);
        array[0][(3 * l) + 2]->setSubCol((3 * l) + 2);
    }
    King* king = new King(color, KING);
    array[0][4] = king;
    array[0][4]->setSubRow(0);
    array[0][4]->setSubCol(4);

    Queen* queen = new Queen(color, QUEEN);
    array[0][3] = queen;
    array[0][3]->setSubRow(0);
    array[0][3]->setSubCol(3);

    for (int i = 8; i < 16; ++i)
    {
        Pawn* pawn = new Pawn(color, PAWN);
        array[1][i - 8] = pawn;
        array[1][i - 8]->setSubRow(1);
        array[1][i - 8]->setSubCol(i - 8);
    }
}

/**
 * this function locates the players given as two arrays in the big array the represents the board
 * @param whiteArray an pointer array that contains pointers to all the white players
 * @param blackArray an pointer array that contains pointers to all the black players
 */
void Board::updateBoard(Player* whiteArray[2][8], Player* blackArray[2][8])
{

    for (int i = 0; i < 2 ; ++i)
    {
        for (int j = 0; j < 8 ; ++j)
        {
            this->arrayPlayer[i][j] = whiteArray[i][j];
            this->arrayPlayer[i][j] -> setRow(i);
            this->arrayPlayer[i][j] -> setCol(j);
            whiteArray[i][j] -> setRow(i);
            whiteArray[i][j] -> setCol(j);

        }
    }
    for (int m = 2; m <5 ; ++m)
    {
        for (int n = 0; n <8 ; ++n)
        {
            this->arrayPlayer[m][n] = nullptr;

        }
    }
    for (int k = 0; k < 2; ++k)
    {
        for (int l = 0; l< 8; ++l)
        {
            this->arrayPlayer[k + 6][l] = blackArray[1 - k][l];
            this->arrayPlayer[k + 6][l] -> setRow(k + 6);
            this->arrayPlayer[k + 6][l] -> setCol(l);
            blackArray[1 - k][l] -> setRow(k + 6);
            blackArray[1 - k][l] -> setCol(l);
        }
    }
}


/**
 * the function that prints the board line by line ,when all empty cells represented as colored gaps
 */
void Board::printBoard()
{
    std::cout << "\n" << "  ABCDEFGH" << "\n";

    std::string ground, playerRepr, playerColor;
    for (int i = 7; i >= 0; --i)
    {
        std::cout << i + 1 << " ";

        for (int j = 0; j < 8; ++j)
        {
            if((i % 2 == 0 && j % 2 == 0) || (i % 2 !=0 && j % 2 != 0))
            {
                ground = BLUE;
            }
            if((i % 2 == 0 && j % 2 != 0) || (i % 2 !=0 && j % 2 == 0))
            {
                ground = GREEN;
            }
            if ( this->arrayPlayer[i][j] != nullptr)
            {
                playerRepr = this->arrayPlayer[i][j]->getRepr();
                playerColor = this->arrayPlayer[i][j]->getColor();
                std::cout << "\33[" + playerColor + ";" + ground + playerRepr + "\33[0m";
            }
            else
            {
                std::cout << "\33[0;" + ground + " \33[0m";
            }
        }
        std::cout << " " << i + 1 ;
        std::cout << "\n";
    }
    std::cout << "\n" << "  ABCDEFGH" << "\n" << std::endl;
}

/**
 * the function checks whether or not the future pos deviates from the board borders
 * @param futureCol
 * @param futureRow
 * @return true if it's legal ,false otherwise
 */
bool Board::isLegalPos(int futureCol, int futureRow)
{
    if (futureCol < 8 && futureRow < 8 && futureCol >= 0 && futureRow  >= 0)
    {
        return true;
    }
    return false;
}

/**
 * the function updates the king's actual pis after it's movement
 * @param futureCol the actual king's col
 * @param futureRow the actual king's row
 */
void Board::updateKingPos(int futureCol,  int futureRow)
{
    if(this -> arrayPlayer[futureRow][futureCol] -> getColor() == WHITE)
    {
        std::get<0>(this->whiteKingPos) = futureRow;
        std::get<1>(this->whiteKingPos) = futureCol;
    }
    if(this -> arrayPlayer[futureRow][futureCol] -> getColor() == BLACK)
    {
        std::get<0>(this->blackKingPos) = futureRow;
        std::get<1>(this->blackKingPos) = futureCol;
    }
}

/**
 * this function practically moves a piece according to the pos the players entered
 * if there is no piece in that pos it just locates it -otherwise it has to delete the eaten player
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * @return true if the movement went well
 */
bool Board::checkNewPos(int currentCol,  int currentRow, int futureCol,  int futureRow)
{
    if (this->arrayPlayer[futureRow][futureCol] == nullptr)
    {
        if (this->arrayPlayer[currentRow][currentCol]->getRepr() != PAWN ||
            (!(this->arrayPlayer[currentRow][currentCol] -> getIsDiagonalStep())))
        {
            transport(currentCol, currentRow, futureCol, futureRow);
            if(this->arrayPlayer[futureRow][futureCol]->getRepr() == KING)
            {
                this->updateKingPos(futureCol, futureRow);
            }
            return true;
        }
    }
    else if (this->arrayPlayer[futureRow][futureCol] -> getColor() !=
             this->arrayPlayer[currentRow][currentCol] -> getColor())
    {
        if (this->arrayPlayer[currentRow][currentCol] -> getRepr() != PAWN ||
            (this->arrayPlayer[currentRow][currentCol] -> getIsDiagonalStep()))
        {
            eat(currentCol, currentRow, futureCol, futureRow);
            if(this->arrayPlayer[futureRow][futureCol]->getRepr() == KING)
            {
                this->updateKingPos(futureCol, futureRow);
            }
            return true;
        }
    }
    return false;
}

/**
 * if there is no piece in the future pos this function will be called exclusively
 * @param currentCol currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 */
void Board::transport(int currentCol, int currentRow, int futureCol, int futureRow)
{
    std::string repr = this->arrayPlayer[currentRow][currentCol]->getRepr();
    if(repr == KING || repr == ROOK || repr == PAWN)
    {
        this->arrayPlayer[currentRow][currentCol] -> setIsFirstMove(false);
    }
    this->arrayPlayer[futureRow][futureCol] = this -> arrayPlayer[currentRow][currentCol];
    this->arrayPlayer[currentRow][currentCol] = nullptr;

    this->arrayPlayer[futureRow][futureCol] -> setRow(futureRow);
    this->arrayPlayer[futureRow][futureCol] -> setCol(futureCol);

}

/**
 * this function delete single piece from the sub array that contains only players from united color
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * @return the piece's color and where in the sub -array it's located
 */
std::pair<int, int> Board::deleteSpecificPlayer(int futureCol, int futureRow)
{
    int row, col;
    if (this->arrayPlayer[futureRow][futureCol]->getColor() == WHITE)
    {
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                if(this->whitePlayersArray[i][j] == nullptr)
                {
                    continue;
                }
                if (this->whitePlayersArray[i][j]->getCol() == futureCol &&
                    this->whitePlayersArray[i][j]->getRow() == futureRow)
                {
                    this->whitePlayersArray[i][j] = nullptr;
                    row = i;
                    col = j;
                }
            }
        }
    }
    if (this->arrayPlayer[futureRow][futureCol]->getColor() == BLACK)
    {
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                if(this->blackPlayersArray[i][j] == nullptr)
                {
                    continue;
                }
                if (this->blackPlayersArray[i][j]->getCol() == futureCol &&
                    this->blackPlayersArray[i][j]->getRow() == futureRow)
                {
                    this->blackPlayersArray[i][j] = nullptr;
                    row = i;
                    col = j;
                }
            }
        }
    }
    return std::make_pair(row, col); //where is the deleted player was located

}

/**
 * this function is called if there is piece in the future pos that was entered by the player
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 */
void Board::eat(int currentCol, int currentRow, int futureCol, int futureRow)
{
    this->deleteSpecificPlayer(futureCol, futureRow);
    this -> arrayPlayer[futureRow][futureCol] = nullptr;
    transport(currentCol, currentRow, futureCol, futureRow);
    this->isPlayerEaten = true;

}

/**
 * this function is  specified for queen and rook that are limited in there movement if there are another piece in their
 * path  .the function check if between the current ans the future piece's pos there are another pieces vertically
 * and horizontal
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * @return true if there will be collision , false otherwise
 */
bool Board::crossCollisionCheck(int currentCol, int currentRow, int futureCol, int futureRow)
{
    if ((currentCol < futureCol) && (currentRow == futureRow)) //there is player there
    {
        for (int i = currentCol + 1; i < futureCol; ++i)
        {
            if(this->arrayPlayer[currentRow][i] != nullptr)
            {
                return true;
            }
        }
    }
    else if((currentCol > futureCol) && (currentRow == futureRow)) //there is player there
    {
        for (int i = currentCol - 1; i > futureCol; --i)
        {
            if(this->arrayPlayer[currentRow][i] != nullptr)
            {
                return true;
            }
        }
    }
    else if((currentRow < futureRow) && (currentCol == futureCol)) //there is player there
    {
        for (int i = currentRow + 1; i < futureRow; ++i)
        {
            if(this->arrayPlayer[i][currentCol] != nullptr)
            {
                return true;
            }
        }
    }
    else if((currentRow > futureRow) && (currentCol == futureCol)) //there is player there
    {
        for (int i = currentRow - 1; i > futureRow; --i)
        {
            if(this->arrayPlayer[i][currentCol] !=nullptr)
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * this function is  specified for queen and bishop that are limited in there movement if there are another piece in
 * their path.the function check if between the current ans the future piece's pos there are another pieces diagonally.
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * @return true if there will be collision , false otherwise
 */
bool Board::diagonalCollisionCheck(int currentCol, int currentRow, int futureCol, int futureRow)
{
    if (currentRow < futureRow && currentCol < futureCol)
    {
        for (int i = 1; i < abs(currentRow - futureRow); ++i)
        {
            if (this->arrayPlayer[currentRow + i][currentCol + i] != nullptr) //there is player there
            {
                return true;
            }
        }
    }
    else if (currentRow < futureRow && currentCol > futureCol)
    {
        for (int i = 1; i < abs(currentRow - futureRow); ++i)
        {
            if (this->arrayPlayer[currentRow + i][currentCol - i] != nullptr) //there is player there
            {
                return true;
            }
        }
    }
    else if (currentRow > futureRow && currentCol < futureCol)
    {
        for (int i = 1; i < abs(currentRow - futureRow); ++i)
        {
            if (this->arrayPlayer[currentRow - i][currentCol + i] != nullptr) //there is player there
            {
                return true;
            }
        }
    }
    else if (currentRow > futureRow && currentCol > futureCol)
    {
        for (int i = 1; i < abs(currentRow - futureRow); ++i)
        {
            if (this->arrayPlayer[currentRow - i][currentCol - i] != nullptr) //there is player there
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * big castling function ,removes the king and the rook only if there are the terms according to the game's rules
 * @param color the piece's color
 * @return true if the castling was done ,false otherwise
 */
bool Board::bigCastling(std::string color)
{
    int row;
    if (color == WHITE)
    {
        row = 0;
    }
    else
    {
        row = 7;
    }
    if (this->arrayPlayer[row][4]-> getIsFirstMove() && this-> arrayPlayer[row][0]->getIsFirstMove()
        && this->arrayPlayer[row][1] == nullptr && this->arrayPlayer[row][2] == nullptr &&
        this->arrayPlayer[row][3] == nullptr) //check if the terms exist
    {
        this->transport(4 , row, 2 , row);
        this->transport(0 , row, 3 , row);
        this->updateKingPos(2, row);
        return true;
    }
    else
    {
        std::cout << "\33[37;41m illegal move\33[0m" << std::endl;
        return false;

    }

}

/**
 * little castling function ,removes the king and the rook only if there are the terms according to the game's rules
 * @param color the piece's color
 * @return true if the castling was done ,false otherwise
 */
bool Board::littleCastling(std::string color)
{
    int row;
    if (color == WHITE)
    {
        row = 0;
    }
    else
    {
        row = 7;
    }
    if (this->arrayPlayer[row][4] -> getIsFirstMove() && this->arrayPlayer[row][7] -> getIsFirstMove()
        && this->arrayPlayer[row][5] == nullptr && this->arrayPlayer[row][6] == nullptr) //check if the terms exist
    {
        this->transport(4 , row, 6 , row);
        this->transport(7 , row, 5 , row);
        this->updateKingPos(6, row);
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * this function assemble all the functions that are about the piece movement and it's validity there were
 * implemented above ,if it cause threaten on the player's king it will cancel the changes
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * @return true if the movement went well ,false otherwise
 */
bool Board::moveBoard(int currentCol, int currentRow, int futureCol, int futureRow)
{
    this->isPlayerEaten = false;
    Player* eatenPlayer = this-> arrayPlayer[futureRow][futureCol];
    std::string eatenColor, playerColor;
    playerColor =   this-> arrayPlayer[currentRow][currentCol]-> getColor();

    if(eatenPlayer != nullptr)
    {
        eatenColor =   this-> arrayPlayer[futureRow][futureCol]-> getColor();
    }

    if (! this-> arrayPlayer[currentRow][currentCol] -> move(currentCol , currentRow, futureCol , futureRow))
    {
        return false;
    }

    if (! this -> isLegalPos(futureCol, futureRow))
    {
        return false;
    }
    if (this->arrayPlayer[currentRow][currentCol] -> getRepr() == QUEEN || //because they can't jump over another player
        this->arrayPlayer[currentRow][currentCol] -> getRepr() == BISHOP )
    {
        if ( Board:: diagonalCollisionCheck(currentCol , currentRow , futureCol , futureRow))
        {
            return false;
        }
    }
    if (this->arrayPlayer[currentRow][currentCol] ->getRepr() == QUEEN ||
        this->arrayPlayer[currentRow][currentCol] ->getRepr() == ROOK ) //because they can't jump over another player
    {
        if (Board::crossCollisionCheck(currentCol, currentRow, futureCol, futureRow))
        {
            return false;
        }
    }
    if(! this -> checkNewPos(currentCol, currentRow , futureCol , futureRow))
    {
        return false;
    }

    if (this->arrayPlayer[futureRow][futureCol] ->getRepr() == PAWN && (futureRow == 7 || futureRow == 0))
    {
        this -> transformPawnToQueen(playerColor, futureCol, futureRow);
    }
    if(this -> isKingThreatened(futureCol, futureRow))
    {
        this->arrayPlayer[currentRow][currentCol] = this -> arrayPlayer[futureRow][futureCol];
        this->arrayPlayer[futureRow][futureCol] = nullptr;
        if(this -> isPlayerEaten)
        {
            this->arrayPlayer[futureRow][futureCol] = eatenPlayer;
        }
        if(eatenColor == WHITE)
        {
            this->whitePlayersArray[eatenPlayer->getSubArrayRow()][eatenPlayer->getSubArrayCol()] = eatenPlayer;
        }
        else if(eatenColor == BLACK)
        {
            this->blackPlayersArray[eatenPlayer->getSubArrayRow()][eatenPlayer->getSubArrayCol()] = eatenPlayer;
        }
        return false;
    }
    return true;


}

/**
 * this function transform  pawn to a queen if it arrives to the opposite side of the board
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * */
void Board::transformPawnToQueen(std::string color, int futureCol, int futureRow)
{
    std::pair<int, int> pos = this -> deleteSpecificPlayer(futureCol, futureRow);
    Queen *queen = new Queen(color, QUEEN);
    this -> arrayPlayer[futureRow][futureCol] = queen;
    if(this->arrayPlayer[futureRow][futureCol] -> getColor() == WHITE)
    {
        this->whitePlayersArray[pos.first][pos.second] = queen;
    }
    else if(this->arrayPlayer[futureRow][futureCol] -> getColor() == BLACK)
    {
        this->blackPlayersArray[pos.first][pos.second] = queen;
    }
}



/**
 *check if the white king intimidated by one of the black pieces
 * @param kingCol the col where the king is right now
 * @param kingRow the row where the king is right now
 * @return true if it does ,false otherwise
 */
bool Board::checkWhite(int kingCol, int kingRow)
{
    bool canMove;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (blackPlayersArray[i][j] == nullptr)
            {
                continue;
            }
            else if (arrayPlayer[blackPlayersArray[i][j]->getRow()][blackPlayersArray[i][j]->getCol()] == nullptr)
            {
                continue;
            }
            canMove = this->arrayPlayer[blackPlayersArray[i][j]->getRow()][blackPlayersArray[i][j]->getCol()]->
                    move(blackPlayersArray[i][j]->getCol(), blackPlayersArray[i][j]->getRow(), kingCol, kingRow);
            if (canMove && (this->arrayPlayer[blackPlayersArray[i][j]->getRow()][blackPlayersArray[i][j]->getCol()]
                ->getRepr() == QUEEN || this->arrayPlayer[blackPlayersArray[i][j]
                ->getRow()][blackPlayersArray[i][j]->getCol()]->getRepr() == BISHOP))
            {
                if (Board::diagonalCollisionCheck(blackPlayersArray[i][j]->getCol(),
                    blackPlayersArray[i][j]->getRow(), kingCol, kingRow))
                {
                    canMove = false;
                }
            }
            if (canMove && (this->arrayPlayer[blackPlayersArray[i][j]->getRow()][blackPlayersArray[i][j]->getCol()]
                ->getRepr() == QUEEN || this->arrayPlayer[blackPlayersArray[i][j]->
                getRow()][blackPlayersArray[i][j]->getCol()]->getRepr() == ROOK))
            {
                if (Board::crossCollisionCheck(blackPlayersArray[i][j]->getCol(), blackPlayersArray[i][j]->getRow(),
                    kingCol, kingRow))
                {
                    canMove = false;
                }
            }
            if(canMove)
            {
                return true;
            }
        }
    }
    return false;
}


/**
 *check if the black king intimidated by one of the white pieces
 * @param kingCol the col where the king is right now
 * @param kingRow the row where the king is right now
 * @return true if it does ,false otherwise
 */
bool Board::checkBlack(int kingCol, int kingRow)
{
    bool canMove;
    for (int i = 0; i < 2; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (whitePlayersArray[i][j] == nullptr)
            {
                continue;
            }
            else if (arrayPlayer[whitePlayersArray[i][j]->getRow()][whitePlayersArray[i][j]->getCol()] == nullptr)
            {
                continue;
            }
            canMove = this->arrayPlayer[whitePlayersArray[i][j]->getRow()][whitePlayersArray[i][j]->getCol()]->
                    move(whitePlayersArray[i][j]->getCol(), whitePlayersArray[i][j]->getRow(), kingCol, kingRow);
            if (canMove && (this->arrayPlayer[whitePlayersArray[i][j]->getRow()][whitePlayersArray[i][j]->getCol()]
                ->getRepr() == QUEEN || this->arrayPlayer[whitePlayersArray[i][j]
                ->getRow()][whitePlayersArray[i][j]->getCol()]->getRepr() == BISHOP))
            {
                if (Board::diagonalCollisionCheck(whitePlayersArray[i][j]->getCol(),
                    whitePlayersArray[i][j]->getRow(), kingCol, kingRow))
                {
                    canMove = false;
                }
            }
            if (canMove && (this->arrayPlayer[whitePlayersArray[i][j]->getRow()][whitePlayersArray[i][j]->getCol()]
                ->getRepr() == QUEEN || this->arrayPlayer[whitePlayersArray[i][j]
                ->getRow()][whitePlayersArray[i][j]->getCol()]->getRepr() == ROOK))
            {
                if (Board::crossCollisionCheck(whitePlayersArray[i][j]->getCol(), whitePlayersArray[i][j]->getRow(),
                    kingCol, kingRow))
                {
                    canMove = false; //because there is collision
                }
            }
            if(canMove)
            {
                return true;
            }
        }
    }
    return false;

}

/**
 * this function checks whether or not there is threaten on the player's king after the last movement he did
 * @param array the array of pointers to pieces of the opponent's color
 * @param kingCol the col where the player's king is now
 * @param kingRow the row where the player's king is now
 * @return true if there is danger ,false otherwise
 */
bool Board::checkOppositeColor(int kingCol, int kingRow)
{
    bool result = false;

    if(this->arrayPlayer[kingRow][kingCol]->getColor() == WHITE)
    {
        result = this->checkWhite(kingCol, kingRow);
    }
    else if(this->arrayPlayer[kingRow][kingCol]->getColor() == BLACK)
    {
        result = this->checkBlack(kingCol, kingRow);
    }
    return result;
}


/**
 * this function checks if the player revealed it's own king to danger by it's movement
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @return true if the king is under danger ,false otherwise
 */
bool Board::isKingThreatened(int currentCol,  int currentRow)
{
    if (this -> arrayPlayer[currentRow][currentCol] -> getColor() == WHITE)
    {
        int whiteKingRow = std::get<0>(this -> whiteKingPos);
        int whiteKingCol = std::get<1>(this -> whiteKingPos);

        return this->checkOppositeColor(whiteKingCol, whiteKingRow);
    }
    if (this -> arrayPlayer[currentRow][currentCol] -> getColor() == BLACK)
    {
        int blackKingRow = std::get<0>(this -> blackKingPos);
        int blackKingCol = std::get<1>(this -> blackKingPos);

        return this->checkOppositeColor(blackKingCol, blackKingRow);
    }
    return false;
}