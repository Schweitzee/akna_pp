#include <iostream>
#include <string>

#include "Game.h"
#include "econio.h"



void start_print(){
    econio_clrscr();
    std::string sign = "This is my MINESWEEPER!";
    for (unsigned i = 0; i < sign.size(); ++i) {
        econio_sleep(i*0.004);
        std::cout << sign[i];
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
        while(branch != 1 && branch != 2 && branch != 3){
            std::cout << "Invalid input, 1, 2 or 3 please!" << std::endl;
            econio_flush();
            std::cin >> branch;
        }


        int x = 6;
        int y = 2;
        if(branch == 1) {
            int a = -1, b = -1, c = 10;
            std::cout << "Height and width between 10 and 40, mine number between 10% and 35%" << std::endl <<"Type in the parameters of the game separated with a space [height width number_of_mines]: ";
            std::cin >> a >> b >> c;

            while (a < 10 || a > 40 || b < 10 || b > 40 || c < a * b * 0.1 || c > a * b * 0.35) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Wrong numbers, try again: ";
                std::cin >> a >> b >> c;
            }
            gameszko = new Game(a, b, c);
            gameszko->first_step(res, x, y);
        }

        if(branch == 2){
            try {
                gameszko = Game::load();
            }
            catch (std::ifstream::failure){
                std::cout << "There's no saved game" << std::endl << "Press ENTER to return to the menu";
                econio_getch();
                std::getchar();
                branch = -1;
                continue;
            }

            if(gameszko == nullptr){
                std::cout << "Failed to load game, invalid format in saved game!" << std::endl << "Press ENTER to return to the menu";
                econio_flush();
                std::getchar();
                econio_clrscr();
                branch = -1;
                continue;
            }
            gameszko->get_table()->filler();
        }
        if(branch == 3)
            break;
        branch = -1;

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
