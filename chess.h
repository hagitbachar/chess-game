//
// Created by pazcohen on 1/1/18.
//

#ifndef EX2_CHESS_H
#define EX2_CHESS_H


#include "Player.h"
#include "Board.h"


/**
 * the class that is about running the chess game
 */
class chess
{
public:
    /**
 * this function checks if after player's movement there is threaten on the king
 * @param board Board instance
 * @param color the player's color hence the king's color
 * @return true if there is threaten on the king , false otherwise
 */
    bool isCheck(Board* board, std::string color);



/**
 * this function convert the player's input to numbers
 * @param input 'A' -'H'
 * @return 0-7
 */
    int conversionToNum(char input);

/**
 * converts the player's input from char to number
 * @param input char
 * @return number
 */
    int convertCharToNum(char input);

/**
 * in case of check this function checks whether or not the king can move and rescue itself from that situation
 * @param board Boarrd instance
 * @param isUnderCheck boolean param that is indication if the is check situation
 * @param color the player's color hence the king's color
 * @return true if there is checkmate ,false otherwise
 */
    bool isCheckmate(Board* board, bool isUnderCheck, std::string color);

/**
 * checks if the players moves it's own piece and not the opponent's one
 * @param board Board instance
 * @param playerColor the color that is recognized with the player
 * @param curCol the current col where the piece is now
 * @param curRow the current row where the piece is now
 * @return true if the color is valid ,false otherwise
 */
    bool validColor(Board* board, std::string playerColor, int curCol , int curRow);


/**
 * the main function
 * @return 0 if the game run properly
 */
    void runGame();


};


#endif //EX2_CHESS_H
