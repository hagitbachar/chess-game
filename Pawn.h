//
// Created by pazcohen on 1/1/18.
//

#ifndef EX2_PAWN_H
#define EX2_PAWN_H


#include "Player.h"


/**
 * the pawn pieces class
 */
class Pawn : public Player
{
public:
    Pawn(std::string color, std::string repr) :Player(color, repr){}
    virtual bool move(int currentCol, int currentRow, int futureCol, int futureRow);

};


#endif //EX2_PAWN_H
