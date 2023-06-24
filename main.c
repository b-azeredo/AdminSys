#include <stdio.h>
#include <locale.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include "Functions.h"
#include <windows.h>
#include <unistd.h>
#include "gestao.h"

struct utilizador{
    int id;
    char nome[20];
}utilizador;

void criarTabela(FILE *ficheiro,char *campo1, char *campo2, char *campo3, int totalCampo, int somarAutomatico) {
    char idChar[20];
    sprintf(idChar, "%d", utilizador.id);
    clear();
    printw("\n\n\n\n\t\t\t\t----------------------------------------------------\n");
    printw("\t\t\t\t|");

    attron(COLOR_PAIR(3));
    printw(" %-10s ", campo1);
    attron(COLOR_PAIR(1));
    printw("|");
    attron(COLOR_PAIR(3));
    printw(" %-20s ", campo2);
    attron(COLOR_PAIR(1));
    printw("|");
    attron(COLOR_PAIR(3));
    printw(" %-12s ", campo3);
    attron(COLOR_PAIR(1));

    printw("|\n");
    printw("\t\t\t\t----------------------------------------------------\n");
    int total;
    char valor1[30], valor2[30], valor3[30];
    while (fscanf(ficheiro, "%s %s %s", &valor1, &valor2, valor3) == 3) {
        printw("\t\t\t\t|");
        attron(COLOR_PAIR(3));
        printw(" %-10s ", valor1);
        attron(COLOR_PAIR(1));
        printw("|");
        printw(" %-20s | %-12s |\n", valor2, valor3);
        total += atoi(valor3);
    }
    if (somarAutomatico == 1){ // Despesas (pegar o total dos funcionarios)
            int num, somaTotal = 0;
            char tmp1[20], tmp2[20];
            char nomeFicheiroFuncionarios[30];
            strcpy(nomeFicheiroFuncionarios, idChar);
            strcat(nomeFicheiroFuncionarios, "funcionarios.txt");
            FILE* funcionarios;
            funcionarios = fopen(nomeFicheiroFuncionarios, "a+");
            while (fscanf(funcionarios, "%s %s %d", tmp1, tmp2, &num) != EOF){
                somaTotal += num;
            }
            printw("\t\t\t\t|");
            attron(COLOR_PAIR(3));
            printw(" %-10s ", "*");
            attron(COLOR_PAIR(1));
            printw("|");
            printw(" %-20s | %-12d |\n", "Funcionarios", somaTotal);
            total += somaTotal;
            fclose(funcionarios);

    }
    else if (somarAutomatico == 2){ // Receita (pegar os investimentos totais)
            int num, somaTotal = 0;
            char tmp1[20], tmp2[20];
            char nomeFicheiroInvestimentos[30];
            strcpy(nomeFicheiroInvestimentos, idChar);
            strcat(nomeFicheiroInvestimentos, "investimentos.txt");
            FILE* investimentos;
            investimentos = fopen(nomeFicheiroInvestimentos, "a+");
            while (fscanf(investimentos, "%s %s %d", tmp1, tmp2, &num) != EOF){
                somaTotal += num;
            }
            printw("\t\t\t\t|");
            attron(COLOR_PAIR(3));
            printw(" %-10s ", "*");
            attron(COLOR_PAIR(1));
            printw("|");
            printw(" %-20s | %-12d |\n", "Investimentos", somaTotal);
            total += somaTotal;
            fclose(investimentos);
    }
    printw("\t\t\t\t----------------------------------------------------\n");
    if (totalCampo == 1){
            printw("\t\t\t\t|");
            attron(COLOR_PAIR(2));
            printw(" %-10s ", "Total");
            attron(COLOR_PAIR(1));
            printw("|");
            printw(" %-20s | %-12d |\n", "", total);
            printw("\t\t\t\t----------------------------------------------------\n");
    }
    refresh();
}


int main() {
    attron(COLOR_PAIR(1));
    setlocale(LC_ALL, "Portuguese");
    FILE *utilizadores;
    utilizadores = fopen("utilizadores.txt", "r");
    startCurses();
    printw("                         ______         __                __             ______\n");
    printw("                        /      \\       |  \\              |  \\           /      \\\n");
    printw("                       |  $$$$$$\\  ____| $$ ______ ____   \\$$ _______  |  $$$$$$\\ __    __   _______\n");
    printw("                       | $$__| $$ /      $$|      \\    \\ |  \\|       \\ | $$___\\$$|  \\  |  \\ /       \\\n");
    printw("                       | $$    $$|  $$$$$$$| $$$$$$\\$$$$\\| $$| $$$$$$$\\ \\$$    \\ | $$  | $$|  $$$$$$$\n");
    printw("                       | $$$$$$$$| $$  | $$| $$ | $$ | $$| $$| $$  | $$ _\\$$$$$$\\| $$  | $$ \\$$    \\\n");
    printw("                       | $$  | $$| $$__| $$| $$ | $$ | $$| $$| $$  | $$|  \\__| $$| $$__/ $$ _\\$$$$$$\\\n");
    printw("                       | $$  | $$ \\$$    $$| $$ | $$ | $$| $$| $$  | $$ \\$$    $$ \\$$    $$|       $$\n");
    printw("                        \\$$   \\$$  \\$$$$$$$ \\$$  \\$$  \\$$ \\$$ \\$$   \\$$  \\$$$$$$  _\\$$$$$$$ \\$$$$$$$\n");
    printw("                                                                                 |  \\__| $$\n");
    printw("                                                                                  \\$$    $$\n");
    printw("                                                                                   \\$$$$$$\n");

    autenticacao();
    utilizador.id = returnID();
    clear();
    char nomeTemp[20], password[20];
    int idTemp;
    while (fscanf(utilizadores, "%s %s %d", &nomeTemp, &password, &idTemp) != EOF){
        if (idTemp == utilizador.id){
            strcpy(utilizador.nome, nomeTemp);
        }
    }
    fclose(utilizadores);
    int escolha, num;
    char idChar[10];
    sprintf(idChar, "%d", utilizador.id);
    do{
        clear();
        do{
            printw("\n\n\n\n\n\n\n\n\t\t\t\t\t");
            attron(A_UNDERLINE);
            printw("Bem-vindo, ");
            attron(COLOR_PAIR(2));
            printw("%s!", utilizador.nome);
            attron(COLOR_PAIR(1));
            printw(" Escolha um numero:");
            attroff(A_UNDERLINE);
            printw("\n\n\t\t\t\t\t\t1 - Gerir Funcionarios\n\t\t\t\t\t\t2 - Gerir Fornecedores\n\t\t\t\t\t\t3 - Gerir Despesas\n\t\t\t\t\t\t4 - Gerir Receita\n\t\t\t\t\t\t5 - Gerir Investimentos\n\t\t\t\t\t\t6 - Gerar Relatorio\n\t\t\t\t\t\t7 - Finalizar programa\n\t\t\t\t\t\t-> ");
            box(stdscr, ACS_VLINE, ACS_HLINE);
            refresh();
            scanw("%d", &escolha);
            if (escolha < 1 || escolha > 7){
                clear();
            }
        }while(escolha < 1 || escolha > 7);

        if (escolha == 1) {
            gerirFuncionarios(idChar);
        }

        else if (escolha == 2){
            gerirFornecedores(idChar);
        }

        else if (escolha == 3){
            gerirDespesas(idChar);
        }

        else if (escolha == 4){
            gerirReceitas(idChar);
        }

        else if (escolha == 5){
            gerirInvestimentos(idChar);
        }

        else if (escolha == 6) {
            gerarRelatorio(idChar);
        }
    }while(escolha != 7);
    endwin();
    return 0;
}
