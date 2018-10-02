//
// Created by pazcohen on 1/1/18.
//

#ifndef EX2_KING_H
#define EX2_KING_H


#include "Player.h"


/**
 * the king pieces class
 */
class King : public Player
{

public:
    King(std::string color, std::string repr) :Player(color, repr){}
    virtual bool move(int currentCol, int currentRow, int futureCol, int futureRow);


};


#endif //EX2_KING_H
