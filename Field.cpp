//
// Created by svajc on 16/04/2023.
//

#include "Field.h"


void colornum(unsigned i, bool end){
    switch (i) {
        case 0:
            if(end)
                std::cout << "  ";
            else
                std::cout << " #";
            break;
        case 1:
            econio_textcolor(COL_RED);
            std::cout << " 1";
            break;
        case 2:
            econio_textcolor(COL_LIGHTGREEN);
            std::cout << " 2";
            break;
        case 3:
            econio_textcolor(COL_LIGHTRED);
            std::cout << " 3";
            break;
        case 4:
            econio_textcolor(COL_BLUE);
            std::cout << " 4";
            break;
        case 5:
            econio_textcolor(COL_RED);
            std::cout << " 5";
            break;
        case 6:
            econio_textcolor(COL_CYAN);
            std::cout << " 6";
            break;
        case 7:
            econio_textcolor(COL_MAGENTA);
            std::cout << " 7";
            break;
        case 8:
            econio_textcolor(COL_BROWN);
            std::cout << " 8";
            break;
    }
}


void Field::draw(bool end){
    if(end || this->uncovered())
        colornum(mine_c, end);
    if(this->covered() && !end)
        std::cout << "  ";
    if(this->flagged() && !end){
    econio_textcolor(COL_LIGHTCYAN);
    std::cout << " P";
    }
}