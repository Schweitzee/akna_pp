//
// Created by svajc on 16/04/2023.
//

#ifndef AKNA_PP_TILE_H
#define AKNA_PP_TILE_H

#include <iostream>

#include "econio.h"



class Tile {
    enum Status { COVERED, UNCOVERED, FLAGGED } state;

public:

    Tile(){
        this->state = COVERED;
    }

    void Flag(){
        this->state = FLAGGED;
    }

    bool flagged(){return state == FLAGGED;}

    void Uncover(){
        this->state = UNCOVERED;
    }

    bool uncovered(){return this->state == UNCOVERED;}

    void Cover(){
        this->state = COVERED;
    }

    bool covered(){return this->state == COVERED;}

    virtual bool is_mine() = 0;

    virtual unsigned get_num() = 0;

    virtual void draw(bool) = 0;

    virtual void up() = 0;

    virtual ~Tile()= default;;

};



#endif //AKNA_PP_TILE_H
