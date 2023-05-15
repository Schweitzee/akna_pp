#include <iostream>
#include <string>

#include <chrono>
#include <thread>

#include "Game.h"

void wait_n_print(unsigned to_w, char ch){
    std::chrono::milliseconds dura( to_w);
    std::this_thread::sleep_for(dura);
    std::cout << ch;
}

void start_print(){
    econio_clrscr();
    std::string sign = "This is my MINESWEEPER!";
    for (unsigned i = 0; i < sign.size(); ++i) {
        wait_n_print(i*4, sign[i]);
    }
    std::cout << std::endl;
}

int main() {
    int res = KEY_ENTER;
    while(res != KEY_ESCAPE) {
        Game* gameszko= nullptr;
        int branch = -1;
        start_print();
        std::cout << "   - Press '0' to start a new game" << std::endl << "   - Press '1' to load a saved one" << std::endl << "   - Press '2' to exit game" << std::endl;
        std::cin >> branch;
        while(branch != 0 && branch != 1 && branch != 2){
            std::cout << "Invalid input, 0, 1 or 2 please!" << std::endl;
            std::cin >> branch;
        }

        int x = 6;
        int y = 2;
        if(branch == 0) {
            int a = -1, b = -1, c = 10;
            std::cout << "Height and width between 10 and 40, mine number between 10% and 35%" << std::endl <<"Type in the parameters of the game separated with a space [height width number_of_mines]: ";
            std::cin >> a >> b >> c;

            while (a < 10 || a > 40 || b < 10 || b > 40 || c < a * b * 0.1 || c > a * b * 0.35) {
                fflush(stdin);
                std::cout << "Wrong numbers, try again: ";
                std::cin >> a >> b >> c;
            }
            gameszko = new Game(a, b, c);
            gameszko->first_step(res, x, y);
        }

        if(branch == 1){
            try {
                gameszko = Game::load();
            }
            catch (std::ifstream::failure){
                fflush(stdin);
                std::cout << "There's no saved game" << std::endl << "Press ENTER to return to the menu";
                getchar();
                continue;
            }

            if(gameszko == nullptr){
                std::cout << "Failed to load game, invalid format in saved game!" << std::endl << "Press ENTER to return to the menu";
                fflush(stdin);
                getchar();
                econio_clrscr();
                continue;
            }
            gameszko->get_table()->filler();
        }
        if(branch == 2)
            break;

        gameszko->game_loop(res, x, y);
        if(res == KEY_END){
            delete gameszko;
            res = KEY_ENTER;
            continue;
        }
        gameszko->finish_him(res);
        delete gameszko;
    }

    getchar();
    return 0;
}


