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

}

void Game::finish_him(int& res) const{
    if (Game::fail_check()) {
        draw();
        econio_rawmode();
        econio_gotoxy(0, get_h() * 2 + 5);
        econio_normalmode();
        econio_textcolor(COL_RED);
        std::cout << "YOU FAILED" << std::endl << "press anything except ESC to start new game," << std::endl << "press ESC to close game.";
        econio_textcolor(COL_RESET);
        econio_rawmode();
        res = econio_getch();
        econio_normalmode();
    }
    if (win_check()) {
        draw();
        econio_rawmode();
        econio_gotoxy(0, get_h() * 2 + 5);
        econio_normalmode();
        econio_textcolor(COL_GREEN);
        std::cout << "YOU WON!" << std::endl << "press anything except ESC to start new game," << std::endl << "press ESC to close game.";
        econio_textcolor(COL_RESET);
        econio_rawmode();
        res = econio_getch();
        econio_normalmode();
    }
}


void Game::first_step(int& res, int& x, int& y){
    draw();
    res = stepper(x, y, get_h(), get_w());

    if (res == KEY_ENTER) {
        get_table()->get((y - 2) / 2, (x - 6) / 5)->Uncover();
    }
    if (res == KEY_BACKSPACE)
        get_table()->flag_toggle((y - 2) / 2, (x - 6) / 5);

    rand_mine();

    if (res == KEY_ENTER) {
        get_table()->get((y - 2) / 2, (x - 6) / 5)->Cover();
        plus_revealed(get_table()->revealer((y - 2) / 2, (x - 6) / 5));
    }

}

void Game::game_loop(int& res, int& x, int& y){
    while (!fail_check() && !win_check()) {
        draw();
        fflush(stdin);
        res = stepper(x, y, get_h(), get_w());
        if (res == KEY_ENTER && !get_table()->get((y - 2) / 2, (x - 6) / 5)->is_mine() &&
            !get_table()->get((y - 2) / 2, (x - 6) / 5)->flagged())
            plus_revealed(get_table()->revealer((y - 2) / 2, (x - 6) / 5));
        if (res == KEY_BACKSPACE && !get_table()->get((y - 2) / 2, (x - 6) / 5)->uncovered())
            get_table()->flag_toggle((y - 2) / 2, (x - 6) / 5);
        if (res == KEY_ENTER && get_table()->get((y - 2) / 2, (x - 6) / 5)->is_mine() &&
            !get_table()->get((y - 2) / 2, (x - 6) / 5)->flagged())
            toggle_fail_state();
    }
};


