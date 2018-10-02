//
// Created by pazcohen on 1/1/18.
//

#ifndef EX2_BISHOP_H
#define EX2_BISHOP_H


#include "Player.h"

/**
 * the bishop pieces class
 */
class Bishop : public Player
{

public:
    Bishop(std::string color, std::string repr) :Player(color, repr){}
    virtual bool move( int currentCol, int currentRow, int futureCol, int futureRow);

};


#endif //EX2_BISHOP_H
