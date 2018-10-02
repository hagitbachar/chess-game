//
// Created by pazcohen on 1/1/18.
//

#ifndef EX2_QUEEN_H
#define EX2_QUEEN_H


#include "Player.h"


/**
 * the queen pieces class
 */
class Queen : public Player
{
public:
    Queen(std::string color, std::string repr) :Player(color, repr){}
    virtual bool move(int currentCol, int currentRow, int futureCol, int futureRow);
};


#endif //EX2_QUEEN_H
