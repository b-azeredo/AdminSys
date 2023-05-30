#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include "Functions.h"
#include <locale.h>

int main() {
    FILE *utilizadores;
    utilizadores = fopen("utilizadores.txt", "r");
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
    struct utilizador{
        int id;
        char nome[20];
    }utilizador;
    utilizador.id = returnID();
    clear();
    char nomeTemp[20], password[20];
    int idTemp;
    while (fscanf(utilizadores, "%s %s %d", &nomeTemp, &password, &idTemp) != EOF){
        if (idTemp == utilizador.id){
            strcpy(utilizador.nome, nomeTemp);
        }
    }
    printw("\nBem vindo, %s! Escolha uma opção: \n\n1 - Gerir Funcionários\n2 - Gerir Fornecedores\n3 - Gerir Despesas\n4 - Gerir Receita\n5 - Gerir Investimentos\n6 - Gerar Relatório\n-> ", utilizador.nome);
    refresh();
    getch();
    endwin();
    return 0;
}
