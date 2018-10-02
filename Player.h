//
// Created by pazcohen on 1/1/18.
//

#ifndef EX2_PLAYER_H
#define EX2_PLAYER_H

#include <string.h>
#include <iostream>

/**
 * represents all the pieces
 */
class Player
{
private:
    std::string _color;
    std::string _repr;
    bool isFirstMove = true;
    int _row;
    int _col;
    int subArrayRow;
    int subArrayCol;


public:
    bool isDiagonalStep;
    /**
     * the constructor to the player class
     * @param color
     * @param repr
     */
    Player(std::string color, std::string repr): _color(color), _repr(repr){}
    /**
     * getter to the player's color
     * @return the player's color
     */
    std::string getColor(){ return this->_color ; }
    /**
     * getter to the player's representation
     * @return the player's repr
     */
    std::string getRepr(){ return this->_repr ; }
    /**
     * the piece's move ,check whether or not it's legal to the pieces move to the pos that was entered by the user,
     * according to the games rules.
     * @param currentCol the current col where the piece is now
     * @param currentRow the current row where the piece is now
     * @param futureCol the future col where we would like to place the the piece
     * @param futureRow the current row where we would like to place the the piece
     * @return true if its legal ,false otherwise
     */
    virtual bool move(int currentCol, int currentRow, int futureCol, int futureRow) = 0;

    /**
     * getter to the boolean variable that indicates if it's the piece's first move
     * @return true if it's the first move ,false otherwise
     */
    bool getIsFirstMove(){ return this-> isFirstMove ; }
    /**
     * setter of the boolean variable that indicates if it's the piece's first move
     * @param value true if it's the first move ,false otherwise
     */
    void setIsFirstMove(bool value){ this->isFirstMove = value ; }
    /**
     * getter to the boolean variable that indicates if it's the pawn movement that willing to eat
     * @return true if it does ,false otherwise
     */
    bool getIsDiagonalStep(){ return this-> isDiagonalStep ; }
    /**
     * getter to the piece's row
     * @return the row
     */
    int getRow(){ return this -> _row ; }
    /**
     * getter to the piece's col
     * @return the col
     */
    int getCol(){ return this -> _col ; }
    /**
     * setter to the pieces actual row
     * @param row the row
     */
    void setRow(int row){this -> _row = row ; }
    /**
     * setter to the pieces actual col
     * @param row the col
     */
    void setCol(int col){this -> _col = col ; }
     /**
     * getter to the piece's row
     * @return the row
     */
    int getSubArrayRow(){ return this -> subArrayRow ; }
    /**
     * getter to the piece's col
     * @return the col
     */
    int getSubArrayCol(){ return this -> subArrayCol ; }
    /**
 * setter to the pieces actual row
 * @param row the row
 */
    void setSubRow(int row){this -> subArrayRow = row ; }
    /**
     * setter to the pieces actual col
     * @param row the col
     */
    void setSubCol(int col){this -> subArrayCol = col ; }


};


#endif //EX2_PLAYER_H
