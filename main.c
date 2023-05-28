#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include "Functions.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");
    menu();
    return 0;
}
