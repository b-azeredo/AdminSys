#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include "Functions.h"
#include <locale.h>

int main() {
    startCurses();
    setlocale(LC_ALL, "Portuguese");
        printw(R"EOF(
              _           _        _____
     /\      | |         (_)      / ____|
    /  \   __| |_ __ ___  _ _ __ | (___  _   _ ___
   / /\ \ / _` | '_ ` _ \| | '_ \ \___ \| | | / __|
  / ____ \ (_| | | | | | | | | | |____) | |_| \__ \
 /_/    \_\__,_|_| |_| |_|_|_| |_|_____/ \__, |___/
                                          __/ |
                                         |___/     )EOF");
    menu();
    return 0;
}
