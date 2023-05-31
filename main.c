#include <stdio.h>
#include <locale.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include "Functions.h"
#include <windows.h>

void criarTabela(FILE *ficheiro,char *campo1, char *campo2, char *campo3) {
    clear();
    printw("-------------------------------------------------------\n");
    printw("| %-15s | %-15s | %-15s |\n", campo1, campo2, campo3);
    printw("-------------------------------------------------------\n");

    char valor1[30], valor2[30], valor3[30];

    while (fscanf(ficheiro, "%s %s %s", &valor1, &valor2, valor3) == 3) {
        printw("| %-15s | %-15s | %-15s |\n", valor1, valor2, valor3);
    }
    printw("-------------------------------------------------------\n");
    printw("\n");
}

int main() {
    setlocale(LC_ALL, "");
    FILE *utilizadores;
    utilizadores = fopen("utilizadores.txt", "r");
    startCurses();

printw("\t\t\t                 _           _        _____           \n");
printw("\t\t\t        /\\      | |         (_)      / ____|          \n");
printw("\t\t\t       /  \\   __| |_ __ ___  _ _ __ | (___  _   _ ___ \n");
printw("\t\t\t      / /\\ \\ / _` | '_ ` _ \\| | '_ \\ \\___ \\| | | / __|\n");
printw("\t\t\t     / ____ \\ (_| | | | | | | | | | |____) | |_| \\__ \\\n");
printw("\t\t\t    /_/    \\_\\__,_|_| |_| |_|_| |_|_|_____/\\___  |___/\n");
printw("\t\t\t                                             __/ |    \n");
printw("\t\t\t                                           |____/     \n");


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
    fclose(utilizadores);
    int escolha;
    char idChar[10];
    sprintf(idChar, "%d", id);
    do{
        clear();
        printw("\n\t\t\t\tBem vindo, %s! Escolha um numero: \n\n\t\t\t\t\t1 - Gerir Funcionarios\n\t\t\t\t\t2 - Gerir Fornecedores\n\t\t\t\t\t3 - Gerir Despesas\n\t\t\t\t\t4 - Gerir Receita\n\t\t\t\t\t5 - Gerir Investimentos\n\t\t\t\t\t6 - Gerar Relatorio\n\t\t\t\t\t-> ", utilizador.nome);
        refresh();
        scanw("%d", &escolha);
        if (escolha == 1){
            int num;
            char nomeFicheiroFuncionarios[30];
            strcpy(nomeFicheiroFuncionarios, idChar);
            strcat(nomeFicheiroFuncionarios, "funcionarios.txt");
            FILE *funcionarios;
            funcionarios = fopen(nomeFicheiroFuncionarios, "a+");
            criarTabela(funcionarios, "ID", "Salário", "Nome");
            printw("\nDigita:\n1 - Adicionar\n2 - Remover\n3 - Voltar");
            scanw("%d", &num);
        }
        else if (escolha == 2){
            char nomeFicheiroFornecedores[30];
            strcpy(nomeFicheiroFornecedores, idChar);
            strcat(nomeFicheiroFornecedores, "fornecedores.txt");
            FILE *fornecedores;
            fornecedores = fopen(nomeFicheiroFornecedores, "a+");
            criarTabela(fornecedores, "ID", "Nome", "Produto Fornecido");
            printw("\nDigita:\n1 - Adicionar\n2 - Remover\n3 - Voltar");
        }
        else if (escolha == 3){
            char nomeFicheiroDespesas[30];
            strcpy(nomeFicheiroDespesas, idChar);
            strcat(nomeFicheiroDespesas, "despesas.txt");
            FILE *despesas;
            despesas = fopen(nomeFicheiroDespesas, "a+");
        }
        else if (escolha == 4){
            char nomeFicheiroReceitas[30];
            strcpy(nomeFicheiroReceitas, idChar);
            strcat(nomeFicheiroReceitas, "receitas.txt");
            FILE *receitas;
            receitas = fopen(nomeFicheiroReceitas, "a+");
        }
        else if (escolha == 5){
            char nomeFicheiroInvestimentos[30];
            strcpy(nomeFicheiroInvestimentos, idChar);
            strcat(nomeFicheiroInvestimentos, "investimentos.txt");
            FILE *investimentos;
            investimentos = fopen(nomeFicheiroInvestimentos, "a+");
        }
        else if (escolha == 6){

        }

    }while(escolha > 6 || escolha < 1);
    endwin();
    return 0;
}
