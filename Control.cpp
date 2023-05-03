//
// Created by svajc on 26/04/2023.
//

#include "Control.h"

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

        if (key == KEY_UP)
            y = max(y-2, 2);
        else if (key == KEY_DOWN)
            y = min(y+2, a*2);
        else if (key == KEY_LEFT)
            x = max(x-5, 6);
        else if (key == KEY_RIGHT)
            x = min(x+5, b*5+1);
        else if (key == KEY_ENTER)
            return KEY_ENTER;
        else if (key == KEY_BACKSPACE)
            return KEY_BACKSPACE;
    }
}
