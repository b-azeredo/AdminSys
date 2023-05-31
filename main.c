#include <stdio.h>
#include <locale.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include "Functions.h"
#include <windows.h>

int main() {
    setlocale(LC_ALL, "");
    FILE *utilizadores;
    utilizadores = fopen("utilizadores.txt", "r");
    startCurses();
    printw(R"EOF(
              _           _        _____
     /\      | |         (_)      / ____|
    /  \   __| |_ __ ___  _ _ __ | (___  _   _ ___
   / /\ \ / _` | '_ ` _ \| | '_ \ \___ \| | | / __|
  / ____ \ (_| | | | | | | | | | |____) | |_| \__ \
 /_/    \_\__,_|_| |_| |_|_|_| |_|_____/ \__, |___/
                                          __/ |
                                         |___/     )EOF");


    autenticacao();

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
    printw("\n\t\tBem vindo, %s! Escolha um numero: \n\n\t\t1 - Gerir Funcionarios\n\t\t2 - Gerir Fornecedores\n\t\t3 - Gerir Despesas\n\t\t4 - Gerir Receita\n\t\t5 - Gerir Investimentos\n\t\t6 - Gerar Relatorio\n\t\t-> ", utilizador.nome);
    refresh();
    getch();
    endwin();
    return 0;
}
