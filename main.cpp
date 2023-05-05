#include <iostream>

#include "Game.h"
//#include "Control.h"
#include "memtrace.h"

int main() {
    std::cout << "anyad"<< std::endl;
    int res = KEY_ENTER;
    while(res != KEY_ESCAPE) {
        //
        //      JÁTÉK LEÍRÁS? INPUT ÉS BUILD
        //
        int a = -1, b = -1, c = 10;

        std::cout << "geci a b c-t: ";
        std::cin >> a >> b >> c;

        while (a < 10 || a > 25 || b < 10 || b > 25 || c < a * b * 0.1 || c > a * b * 0.35) {
            fflush(stdin);
            std::cout << "elbasztad zsiguli, geci a b c-t: ";
            std::cin >> a >> b >> c;
        }
        Game gameszko(a, b, c);

        int x = 6;
        int y = 2;

        gameszko.first_step(res, x, y);


        while (!Game::fail_check() && !gameszko.win_check()) {
            gameszko.draw();
            res = stepper(x, y, gameszko.get_h(), gameszko.get_w());
            if (res == KEY_ENTER && !gameszko.get_table()->get((y - 2) / 2, (x - 6) / 5)->is_mine() &&
                !gameszko.get_table()->get((y - 2) / 2, (x - 6) / 5)->flagged())
                gameszko.plus_revealed(gameszko.get_table()->revealer((y - 2) / 2, (x - 6) / 5));
            if (res == KEY_BACKSPACE && !gameszko.get_table()->get((y - 2) / 2, (x - 6) / 5)->uncovered())
                gameszko.get_table()->flag_toggle((y - 2) / 2, (x - 6) / 5);
            if (res == KEY_ENTER && gameszko.get_table()->get((y - 2) / 2, (x - 6) / 5)->is_mine() &&
                !gameszko.get_table()->get((y - 2) / 2, (x - 6) / 5)->flagged())
                Game::toggle_fail_state();
        }
        gameszko.finish_him(res);
    }
    return 0;
}


