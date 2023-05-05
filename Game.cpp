//
// Created by svajc on 02/04/2023.
//

#include "Game.h"

bool Game::fail_state = false;

static void line(int w)
{
    econio_textcolor(COL_GREEN);
    std::cout << std::endl << "----|" ;
    econio_textcolor(COL_RESET);
    for (int i = 0; i < w; i++)
        std::cout << "----|";
    std::cout << std::endl;
}

void Game::draw() const{
    econio_clrscr();
    std::cout << "     ";
    econio_textcolor(COL_RED);
    for(int i = 1; i <= width; i++){
        if(i<10){
            std::cout << "  " << i << " |";
        }
        else{
            std::cout << " " << i << " |";
        }
    }
    line(width);

    //---------------------------------------------
    for(int i = 0; i <=  height-1; i++){
        if(i+1 <10)
        {
            econio_textcolor(COL_GREEN);
            std::cout << "  " << i+1 << " |";
            econio_textcolor(COL_RESET);
        }
        else
        {
            econio_textcolor(COL_GREEN);
            std::cout << " " << i+1 << " |";
            econio_textcolor(COL_RESET);
        }
        for(int j = 0; j<= width-1;j++)
        {
            std::cout << " ";
            table.get(i,j)->draw(fail_state);
            econio_textcolor(COL_RESET);
            std::cout << " |";
        }
        line(width);
    }
    std::cout << "No. of tiles: " << height*width << std::endl << "No. of mines: " << mine_n << std::endl << "No. of revealed: " << revealed_n << std::endl;
//-----------------------------

}
