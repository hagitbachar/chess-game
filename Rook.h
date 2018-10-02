//
// Created by pazcohen on 1/1/18.
//

#ifndef EX2_ROOK_H
#define EX2_ROOK_H


#include "Player.h"


/**
 * the rook pieces class
 */
class Rook : public Player
{
public:
    Rook(std::string color, std::string repr) :Player(color, repr){}
    virtual bool move(int currentCol, int currentRow, int futureCol, int futureRow);

};


#endif //EX2_ROOK_H
