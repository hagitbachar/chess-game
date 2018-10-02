//
// Created by pazcohen on 1/1/18.
//

#ifndef EX2_BOARD_H
#define EX2_BOARD_H


#include <tuple>
#include "Board.h"
#include "Player.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"

#define WHITE "37"
#define BLACK "30"

class Player;

/**
 * Board class
 */
class Board
{
private:
    std::tuple <int, int> whiteKingPos = std::make_tuple(0, 4);
    std::tuple <int, int> blackKingPos = std::make_tuple(7, 4);
    bool isPlayerEaten = false;

public:
    /**
     * Board constructor
     */
    Board() //TODO
    {
        this->createPlayer(WHITE, this->whitePlayersArray);
        this->createPlayer(BLACK, this->blackPlayersArray);
        updateBoard(this->whitePlayersArray, this->blackPlayersArray);
    }
    Player* arrayPlayer[8][8];
    Player* blackPlayersArray[2][8];
    Player* whitePlayersArray[2][8];
    /**
 * This function create all the tools for one player
 * @param color the color of the player, white or black
 * @param array to assign the tools
 */
    void createPlayer(std::string color, Player* array[2][8]);

/**
 * the function that prints the board line by line ,when all empty cells represented as colored gaps
 */
    void printBoard();
/**
 * this function locates the players given as two arrays in the big array the represents the board
 * @param whiteArray an pointer array that contains pointers to all the white players
 * @param blackArray an pointer array that contains pointers to all the black players
 */    void updateBoard(Player* whiteArray[2][8], Player* blackArray[2][8]);

/**
 * the function checks whether or not the future pos deviates from the board borders
 * @param futureCol
 * @param futureRow
 * @return true if it's legal ,false otherwise
 */
    static bool isLegalPos(int futureCol, int futureRow);
/**
 * this function practically moves a piece according to the pos the players entered
 * if there is no piece in that pos it just locates it -otherwise it has to delete the eaten player
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * @return true if the movement went well
 */
    bool checkNewPos(int currentCol,  int currentRow, int futureCol,  int futureRow);

/**
 * if there is no piece in the future pos this function will be called exclusively
 * @param currentCol currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 */
    void transport(int currentCol, int currentRow , int futureCol, int futureRow);

/**
 * this function delete single piece from the sub array that contains only players from united color
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * @return the piece's color and where in the sub -array it's located
 */
    std::pair<int, int> deleteSpecificPlayer(int futureCol, int futureRow);
/**
 * this function is called if there is piece in the future pos that was entered by the player
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 */
    void eat(int currentCol, int currentRow, int futureCol, int futureRow);
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
    bool crossCollisionCheck(int currentCol, int currentRow, int futureCol, int futureRow);
/**
 * this function is  specified for queen and bishop that are limited in there movement if there are another piece in
 * their path.the function check if between the current ans the future piece's pos there are another pieces diagonally.
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * @return true if there will be collision , false otherwise
 */
    bool diagonalCollisionCheck(int currentCol, int currentRow, int futureCol, int futureRow);
/**
 * big castling function ,removes the king and the rook only if there are the terms according to the game's rules
 * @param color the piece's color
 * @return true if the castling was done ,false otherwise
 */
    bool bigCastling(std::string color);
/**
 * little castling function ,removes the king and the rook only if there are the terms according to the game's rules
 * @param color the piece's color
 * @return true if the castling was done ,false otherwise
 */
    bool littleCastling(std::string color);

/**
 * this function assemble all the functions that are about the piece movement and it's validity there were
 * implemented above ,if it cause threaten on the player's king it will cancel the changes
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * @return true if the movement went well ,false otherwise
 */
    bool moveBoard(int currentCol, int currentRow, int futureCol, int futureRow);
/**
 * this function transform  pawn to a queen if it arrives to the opposite side of the board
 * @param futureCol the future col where we would like to place the the piece
 * @param futureRow the current row where we would like to place the the piece
 * */
    void transformPawnToQueen(std::string color, int futureRow, int futureCol);
/**
 * this function checks whether or not there is threaten on the player's king after the last movement he did
 * @param array the array of pointers to pieces of the opponent's color
 * @param kingCol the col where the player's king is now
 * @param kingRow the row where the player's king is now
 * @return true if there is denger ,false otherwise
 */
    bool checkOppositeColor(int kingCol, int kingRow);
/**
 * this function checks if the player revealed it's own king to dengar by it's movemnet
 * @param currentCol the current col where the piece is now
 * @param currentRow the current row where the piece is now
 * @return true if the king is under danger ,fakse otherwise
 */
    bool isKingThreatened(int currentCol, int currentRow);
/**
 * the function updates the king's actual pis after it's movement
 * @param futureCol the actual king's col
 * @param futureRow the actual king's row
 */
    void updateKingPos(int futureCol,  int futureRow);

/**
 * getter
 * @return returns the white king's column
 */
    int getWhiteKingCol(){ return std::get<1>(this -> whiteKingPos); }
/**
 * getter
 * @return returns the white king's row
 */
    int getWhiteKingRow(){ return std::get<0>(this -> whiteKingPos); }
/**
* getter
* @return returns the black king's column
*/
    int getBlackKingCol(){ return std::get<1>(this -> blackKingPos); }
/**
* getter
* @return returns the black king's row
*/
    int getBlackKingRow(){ return std::get<0>(this -> blackKingPos); }
/**
 *check if the white king intimidated by one of the black pieces
 * @param kingCol the col where the king is right now
 * @param kingRow the row where the king is right now
 * @return true if it does ,false otherwise
 */
    bool checkWhite(int kingCol, int kingRow);
/**
 *check if the black king intimidated by one of the white pieces
 * @param kingCol the col where the king is right now
 * @param kingRow the row where the king is right now
 * @return true if it does ,false otherwise
 */
    bool checkBlack(int kingCol, int kingRow);
/**
 * getter to a private field
 * @return if there was eat
 */
    bool getIsEaten(){ return this->isPlayerEaten ; }










};


#endif //EX2_BOARD_H
