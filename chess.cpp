//
// Created by pazcohen on 1/1/18.
//

#include <iostream>
#include "chess.h"

#define WHITE "37"
#define BLACK "30"
#define INVALID_INPUT -1
static bool isLegalMove;

/**
 * this function checks if after player's movement there is threaten on the king
 * @param board Board instance
 * @param color the player's color hence the king's color
 * @return true if there is threaten on the king , false otherwise
 */
bool chess::isCheck(Board* board, std::string color)
{
    int kingCol, kingRow;
    if(color == WHITE)
    {
        kingRow = board -> getWhiteKingRow();
        kingCol = board -> getWhiteKingCol();

        if(board -> checkOppositeColor(kingCol, kingRow))
        {
            return true;
        }
    }
    if(color == BLACK)
    {
        kingRow = board -> getBlackKingRow();
        kingCol = board -> getBlackKingCol();

        if(board -> checkOppositeColor(kingCol, kingRow))
        {
            return true;
        }
    }
    return false; // there is no danger
}





/**
 * in case of check this function checks whether or not the king can move and rescue itself from that situation
 * @param board Boarrd instance
 * @param isUnderCheck boolean param that is indication if the is check situation
 * @param color the player's color hence the king's color
 * @return true if there is checkmate ,false otherwise
 */
bool chess::isCheckmate(Board* board, bool isUnderCheck, std::string color)
{
    bool moved;
    if(!isUnderCheck)
    {
        return false;
    }
    else
    {
        int kingCol = 0, kingRow = 0;
        if(color == WHITE)
        {
            kingRow = board->getWhiteKingRow();
            kingCol = board->getWhiteKingCol();
        }
        else if(color == BLACK)
        {
            kingRow = board->getBlackKingRow();
            kingCol = board->getBlackKingCol();
        }
        int rowArray[8] =
                {
                    kingRow, kingRow, kingRow + 1, kingRow + 1, kingRow + 1, kingRow - 1, kingRow - 1,
                    kingRow - 1
                };
        int colArray[8] =
                {
                    kingCol + 1, kingCol - 1, kingCol + 1, kingCol, kingCol - 1, kingCol + 1, kingCol,
                    kingCol - 1
                };
        for (int i = 0; i < 8; ++i)
        {
             moved = false;
            Player* eatenPlayer = board-> arrayPlayer[rowArray[i]][colArray[i]];
            std::string eatenColor;
            if(eatenPlayer != nullptr)
            {
                eatenColor =   board-> arrayPlayer[rowArray[i]][colArray[i]]-> getColor();
            }

            if(board -> moveBoard(kingCol, kingRow, colArray[i], rowArray[i]))
            {
                moved = true;
            }
            if(moved && !this -> isCheck(board, color)) //if there is a legal move and there is no check
            {
                board->arrayPlayer[kingRow][kingCol] = board->arrayPlayer[rowArray[i]][colArray[i]];
                board->arrayPlayer[rowArray[i]][colArray[i]] = nullptr;
                if(board -> getIsEaten())
                {
                    board->arrayPlayer[rowArray[i]][colArray[i]] = eatenPlayer;
                }
                if(eatenColor == WHITE)
                {
                    board->whitePlayersArray[eatenPlayer->getSubArrayRow()][eatenPlayer->getSubArrayCol()] = eatenPlayer;
                }
                else if(eatenColor == BLACK)
                {
                    board->blackPlayersArray[eatenPlayer->getSubArrayRow()][eatenPlayer->getSubArrayCol()] = eatenPlayer;
                }
                board->updateKingPos(kingCol, kingRow);
                return false;
            }
            else if(moved)
            {
                board->arrayPlayer[kingRow][kingCol] = board -> arrayPlayer[rowArray[i]][colArray[i]];
                board->arrayPlayer[rowArray[i]][colArray[i]] = nullptr;
                if(board -> getIsEaten())
                {
                    board->arrayPlayer[rowArray[i]][colArray[i]] = eatenPlayer;
                }
                if(eatenColor == WHITE)
                {
                    board->whitePlayersArray[eatenPlayer->getSubArrayRow()][eatenPlayer->getSubArrayCol()] = eatenPlayer;
                }
                else if(eatenColor == BLACK)
                {
                    board->blackPlayersArray[eatenPlayer->getSubArrayRow()][eatenPlayer->getSubArrayCol()] = eatenPlayer;
                }
                board->updateKingPos(kingCol, kingRow);
            }
        }
        return true;
    }
}


/**
 * this function convert the player's input to numbers
 * @param input 'A' -'H'
 * @return 0-7 if input valid, -1 else
 */
int chess::conversionToNum(char input)
{
    switch (input)
    {
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
        case 'D':
            return 3;
        case 'E':
            return 4;
        case 'F':
            return 5;
        case 'G':
            return 6;
        case 'H':
            return 7;
        default:
        isLegalMove = false;
    }
    return INVALID_INPUT;

}


/**
 * converts the player's input from char to number
 * @param input char
 * @return number
 */
int chess::convertCharToNum(char input)
{
    return (input - '0') - 1;
}

/**
 * checks if the players moves it's own piece and not the opponent's one
 * @param board Board instance
 * @param playerColor the color that is recognized with the player
 * @param curCol the current col where the piece is now
 * @param curRow the current row where the piece is now
 * @return true if the color is valid ,false otherwise
 */
bool chess::validColor(Board* board, std::string playerColor, int curCol , int curRow)
{
    if(playerColor == board -> arrayPlayer[curRow][curCol]->getColor())
    {
        return true;
    }
    return false;
}

std::string switchPlayer (std::string curPlayer)
{
    if (curPlayer == WHITE)
    {
        return BLACK;
    }
    return WHITE;
}
/**
 * the function that visualize complete game , when every turn represented as while loop iteration.
 */
void chess::runGame()
{
    std::string step;
    int curCol , curRow, futureCol , futureRow ;
    std::string whitePlayer, blackPlayer, playerColor;
    bool isCastling, isUnderCheck = false;
    std::cout << "Enter white player name:\n";
    std::cin >> whitePlayer;
    std::cout << "Enter black player name:\n";
    std::cin >> blackPlayer;
    Board* board = new Board();
    std::string playerName = whitePlayer;
    playerColor = WHITE;
    while (!this -> isCheckmate(board, isUnderCheck, switchPlayer(playerColor))) //while there is no
        // checkmate we would like to continue the game
    {
        isLegalMove = true;
        isCastling = false;
        isUnderCheck = false;
        board->printBoard();
        if (playerName == whitePlayer)
        {
            playerColor = WHITE;
        }
        else
        {
            playerColor = BLACK;
        }
        if (this -> isCheck(board, playerColor))
        {
            isUnderCheck = true;
            std::cout << "\33[37;41mCheck!\33[0m" << std::endl;
        }
        std::cout << playerName << ":Please enter your move:\n";
        std::cin >> step;

        if (step == "o-o")
        {
            isLegalMove = board -> littleCastling(playerColor);
            isCastling = true;
        }
        else if (step == "o-o-o")
        {
            isLegalMove = board -> bigCastling(playerColor);
            isCastling = true;
        }
        if (!isCastling)
        {
            curCol = this -> conversionToNum(step[0]);
            curRow = this -> convertCharToNum(step[1]);
            futureCol = this -> conversionToNum(step[2]);
            futureRow = this -> convertCharToNum(step[3]);

            if (board->arrayPlayer[curRow][curCol] == nullptr)
            {
                isLegalMove = false;
            }
            if (isLegalMove && !this -> validColor(board, playerColor, curCol, curRow))
            {
                isLegalMove = false; //the color is not valid
            }
            else if (isLegalMove && !board -> moveBoard(curCol, curRow, futureCol, futureRow))
            {
                isLegalMove = false; //because move board returned false
            }
            if(isUnderCheck)
            {
                if(this -> isCheck(board, playerColor))
                {
                    isLegalMove = false;
                }
                isUnderCheck = false;
            }
            if (!isLegalMove)
            {
                std::cout << "\33[37;41m illegal move\33[0m" << std::endl ;
            }
        }
        if (isLegalMove) //switch player to the next turn
        {
            if (playerName == whitePlayer)
            {
                playerName = blackPlayer;
            }
            else
            {
                playerName = whitePlayer;
            }
        }
        if (this -> isCheck(board, switchPlayer(playerColor)))
        {
            isUnderCheck = true;
        }
    }
    if (playerName == whitePlayer)
    {
        playerName = blackPlayer;
    }
    else
    {
        playerName = whitePlayer;
    }
    board->printBoard();
    std::cout << playerName + " won!" << std::endl;


}


/**
 * the main function
 * @return 0 if the game run properly
 */
int main()
{
    chess* chessGame = new chess();
    chessGame -> runGame();
    return 0;
}
