//
// Created by pazcohen on 1/1/18.
//

#ifndef EX2_KNIGHT_H
#define EX2_KNIGHT_H


#include "Player.h"


/**
 * the knight pieces class
 */
class Knight : public Player
{
public:
    Knight(std::string color, std::string repr) :Player(color, repr){}
    virtual bool move(int currentCol, int currentRow, int futureCol, int futureRow);

};


#endif //EX2_KNIGHT_H
