#include <iostream>
#include <string>

#include <chrono>
#include <thread>

#include "Game.h"




void wait_n_print(int to_w, char ch){
    std::chrono::milliseconds dura( to_w);
    std::this_thread::sleep_for(dura);
    std::cout << ch;
}

void start_print(){
    econio_clrscr();
    std::string sign = "This is my MINESWEEPER!";
    for (int i = 0; i < sign.size(); ++i) {
        wait_n_print(i*5, sign[i]);
    }
    std::cout << std::endl;
}



int main() {
    int res = KEY_ENTER;
    while(res != KEY_ESCAPE) {
        Game* gameszko= nullptr;
        int branch = -1;
        start_print();
        std::cout << "   - Press '0' to start a new game" << std::endl << "   - Press '1' to load a saved one" << std::endl;
        std::cin >> branch;
        while(branch != 0 && branch != 1){
            std::cout << "Invalid input, 0 or 1 please!" << std::endl;
            std::cin >> branch;
        }
        //
        //      JÁTÉK LEÍRÁS? INPUT ÉS BUILD
        //

        int x = 6;
        int y = 2;
        if(branch == 0) {
            int a = -1, b = -1, c = 10;
            std::cout << "Type in the parameters of the game separated with a space [height width number_of_mines]: ";
            std::cin >> a >> b >> c;

            while (a < 10 || a > 40 || b < 10 || b > 40 || c < a * b * 0.1 || c > a * b * 0.35) {
                fflush(stdin);
                std::cout << "elbasztad zsiguli, geci a b c-t: ";
                std::cin >> a >> b >> c;
            }
            gameszko = new Game(a, b, c);
            gameszko->first_step(res, x, y);

        }

        if(branch == 1){
            gameszko = Game::load();
            if(gameszko == nullptr){
                std::cout << "Failed to load game" << std::endl;
                fflush(stdin);
                getchar();
                econio_clrscr();
                continue;
            }
            gameszko->get_table()->filler();
        }


        gameszko->game_loop(res, x, y);
        if(res == KEY_END){
            delete gameszko;
            continue;
        }
        gameszko->finish_him(res);
        delete gameszko;


    }

    getchar();
    return 0;
}


