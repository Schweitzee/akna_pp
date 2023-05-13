//
// Created by svajc on 16/04/2023.
//

#include "Mine.h"

void Mine::draw(bool end){
if(end) {
econio_textcolor(COL_YELLOW);
std::cout << " X";
}
else if(this->covered())
std::cout << "  ";
else if(this->flagged()) {
econio_textcolor(COL_LIGHTCYAN);
std::cout << " P";
}
}
