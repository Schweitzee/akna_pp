//
// Created by svajc on 16/04/2023.
//

#ifndef AKNA_PP_FIELD_H
#define AKNA_PP_FIELD_H

#include "Tile.h"

void colornum(unsigned i);


class Field : public Tile{
    unsigned mine_c;
public:

    Field() : Tile(), mine_c(0){}

    bool is_mine() override{return false;}

    void draw(bool end) override{
        if(end || this->uncovered())
            colornum(mine_c);
        if(this->covered() && !end)
            std::cout << "  ";
        if(this->flagged()){
            econio_textcolor(COL_LIGHTCYAN);
            std::cout << " P";
        }
    };

    unsigned get_num(){return mine_c;}

    void up(){
        mine_c++;
    }
};

#endif //AKNA_PP_FIELD_H
