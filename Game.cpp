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
            table->get(i,j)->draw(fail_state);
            econio_textcolor(COL_RESET);
            std::cout << " |";
        }
        line(width);
    }
    std::cout << "No. of tiles: " << height*width << std::endl << "No. of mines: " << mine_n << std::endl << "No. of revealed: " << revealed_n << std::endl;

}

void Game::finish_him(int& res) const{
        draw();
        econio_rawmode();
        econio_gotoxy(0, get_h() * 2 + 5);
        econio_normalmode();
        if(Game::fail_check()){
            econio_textcolor(COL_RED);
            std::cout << "YOU FAILED" << std::endl << "press anything except ESC to start new game," << std::endl << "press ESC to close game.";
            econio_textcolor(COL_RESET);
            toggle_fail_state();
        }
        if(win_check()){
            econio_textcolor(COL_GREEN);
            std::cout << "YOU WON!" << std::endl << "press anything except ESC to start new game," << std::endl << "press ESC to close game.";
            econio_textcolor(COL_RESET);
        }
        econio_rawmode();
        res = econio_getch();
        econio_normalmode();
}


template<class T>
T max(T a, T b){
    return a > b ? a : b;
}

template<class T>
T min(T a, T b){
    return a < b ? a : b;
}

/**
 * @brief handles the in-game stepping of the cursor
 * @param x horizontal location of the cursor
 * @param y vertical location of the cursor
 * @param a height of the game table
 * @param b width of the game table
 * @return the pressed key (enter - reveal, backspace - flag toggle)
 */
EconioKey stepper(int &x, int &y, int a, int b){
    fflush(stdin);
    econio_rawmode();
    while (true) {
        econio_gotoxy(x, y);
        econio_textcolor(COL_LIGHTGREEN);
        std::cout << "X";
        econio_gotoxy(0, 0);

        int key = econio_getch();
        econio_gotoxy(x,y);
        printf(" ");

        if (key == KEY_UP || key == 'w')
            y = max(y-2, 2);
        else if (key == KEY_DOWN || key == 's')
            y = min(y+2, a*2);
        else if (key == KEY_LEFT || key == 'a')
            x = max(x-5, 6);
        else if (key == KEY_RIGHT || key == 'd')
            x = min(x+5, b*5+1);
        else if (key == KEY_ENTER) {
            econio_normalmode();
            return KEY_ENTER;
        }
        else if (key == KEY_BACKSPACE){
            econio_normalmode();
            return KEY_BACKSPACE;
        }
        else if(key == 'm'){
            econio_normalmode();
            return KEY_END;
        }
    }
}

template<class T>
T placer(T a, bool decide){
    if(decide)
        return (a-2)/2;
    else
        return (a-6)/5;
}

void Game::first_step(int& res, int& x, int& y){
    draw();
    res = stepper(x, y, get_h(), get_w());

    if (res == KEY_ENTER) {
        get_table()->get(placer(y, true), placer(x, false))->Uncover();
    }
    if (res == KEY_BACKSPACE)
        get_table()->flag_toggle(placer(y, true), placer(x, false));

    rand_mine();
    
    if (res == KEY_ENTER) {
        get_table()->get(placer(y, true), placer(x, false))->Cover();
        plus_revealed(get_table()->revealer(placer(y, true), placer(x, false)));
    }

}

void Game::game_loop(int& res, int& x, int& y){
    while (!fail_check() && !win_check() && res != KEY_END) {
        draw();
        fflush(stdin);
        res = stepper(x, y, get_h(), get_w());
        if (res == KEY_ENTER && !get_table()->get(placer(y, true), placer(x, false))->is_mine() &&
            !get_table()->get((y - 2) / 2, (x - 6) / 5)->flagged())
            plus_revealed(get_table()->revealer(placer(y, true), placer(x, false)));
        if (res == KEY_BACKSPACE && !get_table()->get(placer(y, true), placer(x, false))->uncovered())
            get_table()->flag_toggle(placer(y, true), placer(x, false));
        if (res == KEY_ENTER && get_table()->get(placer(y, true), placer(x, false))->is_mine() &&
            !get_table()->get(placer(y, true), placer(x, false))->flagged())
            toggle_fail_state();
        if(res == KEY_END){
            bool s = save();
            fflush(stdin);
            econio_gotoxy(0,get_h()*2+5);
            if(s){
                econio_textcolor(COL_GREEN);
                std::cout << "Game saved, press ENTER to return to the menu";
            }
            else{
                econio_textcolor(COL_RED);
                std::cout << "Couldn't save game, because the file can't be opened or couldn't be created, check the file permissions in the directory!" << std::endl << "Press ENTER to return to the menu";
            }
            econio_textcolor(COL_RESET);
            getchar();
        }
    }
}

void Game::rand_mine() {
    srand((unsigned)time(nullptr)*91);
    int ready_mine = 0;
    while(ready_mine < mine_n){
        int x = rand() % height, y = rand() % width;
        if((!table->get(x,y)->is_mine()) && !table->get(x,y)->uncovered()){
            table->place_mine(x,y);
            ready_mine++;
        }
    }
    table->filler();
}

Game* Game::load(std::string from){
    int he =0, wi =0, min = 0, rev = 0;
    std::ifstream input;
    input.open(from);
    if(!input.is_open()){
        throw std::ifstream::failure("Couldn't find the saved game");
    }
    input >> he >> wi;
    VektorTable* t = new VektorTable(he, wi);
    for(int i = 0; i < he; ++i){
        for (int j = 0; j < wi; ++j) {
            int k;
            input >> k;
            switch (k) {
                case 0:
                    t->place_mine(i,j);
                    min++;
                    break;
                case 1:
                    t->get(i,j)->Cover();
                    break;
                case 2:
                    t->get(i,j)->Uncover();
                    rev++;
                    break;
                case 3:
                    t->get(i,j)->Flag();
                    break;
                case 4:
                    t->place_mine(i,j);
                    t->get(i,j)->Flag();
                    min++;
                    break;
                default:
                    delete t;
                    return nullptr;
            }
        }
    }
    input.close();
    return new Game(he,wi,min, t, rev);
}

bool Game::save(std::string file){
    std::ofstream output;
    output.open(file);
    if(!output.is_open()){
        std::cout << "Unable to open file to save game." << std::endl;
        return false;
    }
    output << get_w() << " " << get_h() << std::endl;
    for(int i = 0; i < get_h(); ++i){
        for (int j = 0; j < get_w(); ++j) {
            if (get_table()->get(i, j)->is_mine() && !get_table()->get(i, j)->flagged())
                output << 0 << " ";
            if(!get_table()->get(i, j)->is_mine() && get_table()->get(i, j)->covered())
                output << 1 << " ";
            if(!get_table()->get(i, j)->is_mine() && get_table()->get(i, j)->uncovered())
                output << 2 << " ";
            if(!get_table()->get(i, j)->is_mine() && get_table()->get(i, j)->flagged())
                output << 3 << " ";
            if(get_table()->get(i, j)->is_mine() && get_table()->get(i, j)->flagged())
                output << 4 << " ";
        }
        output << std::endl;
    }
    output.close();
    return true;
}

