//
// Created by svajc on 16/04/2023.
//

#ifndef AKNA_PP_MINE_H
#define AKNA_PP_MINE_H

#include "Tile.h"


class Mine : public Tile {
public:
    Mine() : Tile(){}

    bool is_mine() override{return true;}

    void draw(bool end) override{
        if(end) {
            econio_textcolor(COL_YELLOW);
            std::cout << " X";
        }
        else if(this->covered())
            std::cout << " x";
        else if(this->flagged()) {
            econio_textcolor(COL_LIGHTCYAN);
            std::cout << " P";
        }
    };

    unsigned get_num(){return 10;}

    void up(){}; //nothing

};

#endif //AKNA_PP_MINE_H
