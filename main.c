#include <stdio.h>
#include <locale.h>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include "Functions.h"
#include <windows.h>

int addOrRemove(){
    int num;
    printw("\n\t\t\t\t1 - Adicionar\n\t\t\t\t2 - Remover\n\t\t\t\t3 - Voltar\n\t\t\t\t-> ");
    scanw("%d", &num);
    return num;
}

void criarTabela(FILE *ficheiro,char *campo1, char *campo2, char *campo3) {
    clear();
    printw("\t\t\t\t--------------------------------------------\n");
    printw("\t\t\t\t| %-5s | %-20s | %-9s |\n", campo1, campo2, campo3);
    printw("\t\t\t\t--------------------------------------------\n");

    char valor1[30], valor2[30], valor3[30];

    while (fscanf(ficheiro, "%s %s %s", &valor1, &valor2, valor3) == 3) {
        printw("\t\t\t\t| %-5s | %-20s | %-9s |\n", valor1, valor2, valor3);
    }
    printw("\t\t\t\t--------------------------------------------\n");
    printw("\n");
}


int main() {
    /*
    HWND console = GetConsoleWindow(); // Deteta a janela da consola
    ShowWindow(console, SW_MAXIMIZE); // O ShowWindow maximiza a consola apos ser detetada */
    //Cores
    init_pair(2, COLOR_YELLOW + 8, 60);
    init_pair(3, COLOR_RED + 8, 60);
    init_pair(1, COLOR_WHITE + 8, 60);

    attron(COLOR_PAIR(1));
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
    int escolha, num;
    char idChar[10];
    sprintf(idChar, "%d", utilizador.id);
    do{
        clear();
        do{
            printw("\n\t\t\t\tBem vindo, %s! Escolha um numero: \n\n\t\t\t\t\t1 - Gerir Funcionarios\n\t\t\t\t\t2 - Gerir Fornecedores\n\t\t\t\t\t3 - Gerir Despesas\n\t\t\t\t\t4 - Gerir Receita\n\t\t\t\t\t5 - Gerir Investimentos\n\t\t\t\t\t6 - Gerar Relatorio\n\t\t\t\t\t7 - Finalizar programa\n\t\t\t\t\t-> ", utilizador.nome);
            refresh();
            scanw("%d", &escolha);
            if (escolha < 1 || escolha > 7){
                clear();
            }
        }while(escolha < 1 || escolha > 7);


        if (escolha == 1) {
            char nomeFicheiroFuncionarios[30];
            strcpy(nomeFicheiroFuncionarios, idChar);
            strcat(nomeFicheiroFuncionarios, "funcionarios.txt");

            FILE *funcionarios;

            do{
                clear();
                funcionarios = fopen(nomeFicheiroFuncionarios, "a+");
                criarTabela(funcionarios, "ID", "Nome", "Salario");
                fclose(funcionarios);
                num = addOrRemove();
            }while (!(num >= 1 && num <= 3));


            while (num != 3){
                if (num == 1) {
                        struct funcionario {
                            int id;
                            char nome[30];
                            char salario[30];
                        } funcionario;

                        FILE *funcionarios;
                        funcionarios = fopen(nomeFicheiroFuncionarios, "a+");

                        int idTemp = 0;
                        char nomeTemp[30], salarioTemp[30];

                        while (fscanf(funcionarios, "%d %s %s", &idTemp, nomeTemp, salarioTemp) != EOF) {
                        }

                        idTemp++;
                        funcionario.id = idTemp;

                        printw("\n\t\t\t\tDigite o nome do funcionario que deseja adicionar:\n\t\t\t\t-> ");
                        scanw("%s", funcionario.nome);
                        printw("\n\t\t\t\tDigite o salario deste funcionario:\n\t\t\t\t-> ");
                        scanw("%s", funcionario.salario);

                        fprintf(funcionarios, "\n%d %s %s", funcionario.id, funcionario.nome, funcionario.salario);
                        fclose(funcionarios);
                        do{
                            clear();
                            funcionarios = fopen(nomeFicheiroFuncionarios, "a+");
                            criarTabela(funcionarios, "ID", "Nome", "Salario");
                            fclose(funcionarios);
                            num = addOrRemove();
                        }while (!(num >= 1 && num <= 3));

            }
                else if (num == 2) {
                    int idRemover;
                    printw("\n\t\t\t\tDigite o ID do funcionario que deseja remover:\n\t\t\t\t-> ");
                    scanw("%d", &idRemover);


                    FILE *funcionarios;
                    funcionarios = fopen(nomeFicheiroFuncionarios, "r+");

                    // Criei um ficheiro temporário para guardar os regitos atualizados
                    FILE *temp;
                    temp = fopen("temp.txt", "w");

                    // Variáveis temporárias para ler os registos
                    int idTemp;
                    char nomeTemp[30], salarioTemp[30];

                    // Ler os registos do ficheiro original e copiá-los para o ficheiro temporário, exceto o registo a ser removido
                    while (fscanf(funcionarios, "%d %s %s", &idTemp, nomeTemp, salarioTemp) != EOF) {
                        if (idTemp != idRemover) {
                            fprintf(temp, "%d %s %s\n", idTemp, nomeTemp, salarioTemp);
                        }
                    }

                    fclose(funcionarios);
                    fclose(temp);

                    // Remover o ficheiro original
                    remove(nomeFicheiroFuncionarios);
                    // Renomear o ficheiro temporário para o nome original
                    rename("temp.txt", nomeFicheiroFuncionarios);
                        do{
                            clear();
                            funcionarios = fopen(nomeFicheiroFuncionarios, "a+");
                            criarTabela(funcionarios, "ID", "Nome", "Salario");
                            fclose(funcionarios);
                            num = addOrRemove();
                        }while (!(num >= 1 && num <= 3));
                }
            }
        }
        else if (escolha == 2){
            char nomeFicheiroFornecedores[30];
            strcpy(nomeFicheiroFornecedores, idChar);
            strcat(nomeFicheiroFornecedores, "fornecedores.txt");

            FILE *fornecedores;

            do{
                clear();
                fornecedores = fopen(nomeFicheiroFornecedores, "a+");
                criarTabela(fornecedores, "ID", "Produto", "Contacto");
                fclose(fornecedores);
                num = addOrRemove();
            }while (!(num >= 1 && num <= 3));


            while (num != 3){
                if (num == 1) {
                        struct fornecedor {
                            int id;
                            char produto[30];
                            char contacto[30];
                        }fornecedor;

                        FILE *fornecedores;
                        fornecedores = fopen(nomeFicheiroFornecedores, "a+");

                        int idTemp = 0;
                        char nomeTemp[30], salarioTemp[30];

                        while (fscanf(fornecedores, "%d %s %s", &idTemp, nomeTemp, salarioTemp) != EOF) {
                        }

                        idTemp++;
                        fornecedor.id = idTemp;

                        printw("\n\t\t\t\tDigite o produto fornecido pelo fornecedor:\n\t\t\t\t-> ");
                        scanw("%s", fornecedor.produto);
                        printw("\n\t\t\t\tDigite o contacto deste fornecedor:\n\t\t\t\t-> ");
                        scanw("%s", fornecedor.contacto);

                        fprintf(fornecedores, "\n%d %s %s", fornecedor.id, fornecedor.produto, fornecedor.contacto);
                        fclose(fornecedores);
                        do{
                            clear();
                            fornecedores = fopen(nomeFicheiroFornecedores, "a+");
                            criarTabela(fornecedores, "ID", "Produto", "Contacto");
                            fclose(fornecedores);
                            num = addOrRemove();
                        }while (!(num >= 1 && num <= 3));

            }
                else if (num == 2) {
                    int idRemover;
                    printw("\n\t\t\t\tDigite o ID do fornecedor que deseja remover:\n\t\t\t\t-> ");
                    scanw("%d", &idRemover);


                    FILE *fornecedores;
                    fornecedores = fopen(nomeFicheiroFornecedores, "r+");

                    // Criei um ficheiro temporário para guardar os regitos atualizados
                    FILE *temp;
                    temp = fopen("temp.txt", "w");

                    // Variáveis temporárias para ler os registos
                    int idTemp;
                    char produtoTemp[30], contactoTemp[30];

                    // Ler os registos do ficheiro original e copiá-los para o ficheiro temporário, exceto o registo a ser removido
                    while (fscanf(fornecedores, "%d %s %s", &idTemp, produtoTemp, contactoTemp) != EOF) {
                        if (idTemp != idRemover) {
                            fprintf(temp, "%d %s %s\n", idTemp, produtoTemp, contactoTemp);
                        }
                    }

                    fclose(fornecedores);
                    fclose(temp);

                    // Remover o ficheiro original
                    remove(nomeFicheiroFornecedores);
                    // Renomear o ficheiro temporário para o nome original
                    rename("temp.txt", nomeFicheiroFornecedores);
                        do{
                            clear();
                            fornecedores = fopen(nomeFicheiroFornecedores, "a+");
                            criarTabela(fornecedores, "ID", "Produto", "Contacto");
                            fclose(fornecedores);
                            num = addOrRemove();
                        }while (!(num >= 1 && num <= 3));
                }
            }
        }
        else if (escolha == 3){
            char nomeFicheiroDespesas[30];
            strcpy(nomeFicheiroDespesas, idChar);
            strcat(nomeFicheiroDespesas, "despesas.txt");

            FILE *despesas;
            do{
                clear();
                despesas = fopen(nomeFicheiroDespesas, "a+");
                criarTabela(despesas, "ID", "Descricao", "Valor");
                fclose(despesas);
                num = addOrRemove();
            }while (!(num >= 1 && num <= 3));


            while (num != 3){
                if (num == 1) {
                        struct despesa {
                            int id;
                            char descricao[30];
                            char valor[30];
                        }despesa;

                        FILE *despesas;
                        despesas = fopen(nomeFicheiroDespesas, "a+");

                        int idTemp = 0;
                        char nomeTemp[30], salarioTemp[30];

                        while (fscanf(despesas, "%d %s %s", &idTemp, nomeTemp, salarioTemp) != EOF) {
                        }

                        idTemp++;
                        despesa.id = idTemp;

                        printw("\n\t\t\t\tDigite o a descricao da despesa:\n\t\t\t\t-> ");
                        scanw("%s", despesa.descricao);
                        printw("\n\t\t\t\tDigite o valor desta despesa:\n\t\t\t\t-> ");
                        scanw("%s", despesa.valor);

                        fprintf(despesas, "\n%d %s %s", despesa.id, despesa.descricao, despesa.valor);
                        fclose(despesas);
                        do{
                            clear();
                            despesas = fopen(nomeFicheiroDespesas, "a+");
                            criarTabela(despesas, "ID", "Descricao", "Valor");
                            fclose(despesas);
                            num = addOrRemove();
                        }while (!(num >= 1 && num <= 3));

            }
                else if (num == 2) {
                    int idRemover;
                    printw("\n\t\t\t\tDigite o ID da despesa que deseja remover:\n\t\t\t\t-> ");
                    scanw("%d", &idRemover);


                    FILE *despesas;
                    despesas = fopen(nomeFicheiroDespesas, "r+");

                    // Criei um ficheiro temporário para guardar os registos atualizados
                    FILE *temp;
                    temp = fopen("temp.txt", "w");

                    // Variáveis temporárias para ler os registos
                    int idTemp;
                    char descTemp[30], valorTemp[30];

                    // Ler os registos do ficheiro original e copiá-los para o ficheiro temporário, exceto o registo a ser removido
                    while (fscanf(despesas, "%d %s %s", &idTemp, descTemp,valorTemp) != EOF) {
                        if (idTemp != idRemover) {
                            fprintf(temp, "%d %s %s\n", idTemp, descTemp, valorTemp);
                        }
                    }

                    fclose(despesas);
                    fclose(temp);

                    // Remover o ficheiro original
                    remove(nomeFicheiroDespesas);
                    // Renomear o ficheiro temporário para o nome original
                    rename("temp.txt", nomeFicheiroDespesas);
                        do{
                            clear();
                            despesas = fopen(nomeFicheiroDespesas, "a+");
                            criarTabela(despesas, "ID", "Descricao", "Valor");
                            fclose(despesas);
                            num = addOrRemove();
                        }while (!(num >= 1 && num <= 3));
                }
            }
        }
        else if (escolha == 4){
            char nomeFicheiroReceitas[30];
            strcpy(nomeFicheiroReceitas, idChar);
            strcat(nomeFicheiroReceitas, "receitas.txt");

            FILE *receitas;
            do{
                clear();
                receitas = fopen(nomeFicheiroReceitas, "a+");
                criarTabela(receitas, "ID", "Descricao", "Valor");
                fclose(receitas);
                num = addOrRemove();
            }while (!(num >= 1 && num <= 3));


            while (num != 3){
                if (num == 1) {
                        struct receita {
                            int id;
                            char descricao[30];
                            char valor[30];
                        }receita;

                        FILE *receitas;
                        receitas = fopen(nomeFicheiroReceitas, "a+");

                        int idTemp = 0;
                        char descricaoTemp[30], valorTemp[30];

                        while (fscanf(receitas, "%d %s %s", &idTemp, descricaoTemp, valorTemp) != EOF) {
                        }

                        idTemp++;
                        receita.id = idTemp;

                        printw("\n\t\t\t\tDigite a descricao da receita:\n\t\t\t\t-> ");
                        scanw("%s", receita.descricao);
                        printw("\n\t\t\t\tDigite o valor desta receita:\n\t\t\t\t-> ");
                        scanw("%s", receita.valor);

                        fprintf(receitas, "\n%d %s %s", receita.id, receita.descricao, receita.valor);
                        fclose(receitas);
                        do{
                            clear();
                            receitas = fopen(nomeFicheiroReceitas, "a+");
                            criarTabela(receitas, "ID", "Descricao", "Valor");
                            fclose(receitas);
                            num = addOrRemove();
                        }while (!(num >= 1 && num <= 3));

            }
                else if (num == 2) {
                    int idRemover;
                    printw("\n\t\t\t\tDigite o ID da receita que deseja remover:\n\t\t\t\t-> ");
                    scanw("%d", &idRemover);


                    FILE *receitas;
                    receitas = fopen(nomeFicheiroReceitas, "r+");

                    // Criei um ficheiro temporário para guardar os registos atualizados
                    FILE *temp;
                    temp = fopen("temp.txt", "w");

                    // Variáveis temporárias para ler os registos
                    int idTemp;
                    char descTemp[30], valorTemp[30];

                    // Ler os registos do ficheiro original e copiá-los para o ficheiro temporário, exceto o registo a ser removido
                    while (fscanf(receitas, "%d %s %s", &idTemp, descTemp,valorTemp) != EOF) {
                        if (idTemp != idRemover) {
                            fprintf(temp, "%d %s %s\n", idTemp, descTemp, valorTemp);
                        }
                    }

                    fclose(receitas);
                    fclose(temp);

                    // Remover o ficheiro original
                    remove(nomeFicheiroReceitas);
                    // Renomear o ficheiro temporário para o nome original
                    rename("temp.txt", nomeFicheiroReceitas);
                        do{
                            clear();
                            receitas = fopen(nomeFicheiroReceitas, "a+");
                            criarTabela(receitas, "ID", "Descricao", "Valor");
                            fclose(receitas);
                            num = addOrRemove();
                        }while (!(num >= 1 && num <= 3));
                }
            }
        }
        else if (escolha == 5){
            char nomeFicheiroInvestimentos[30];
            strcpy(nomeFicheiroInvestimentos, idChar);
            strcat(nomeFicheiroInvestimentos, "investimentos.txt");

            FILE *investimentos;

            do{
                clear();
                investimentos = fopen(nomeFicheiroInvestimentos, "a+");
                criarTabela(investimentos, "ID", "TAG", "Retorno");
                fclose(investimentos);
                num = addOrRemove();
            }while (!(num >= 1 && num <= 3));


            while (num != 3){
                if (num == 1) {
                        struct investimento {
                            int id;
                            char tag[30];
                            char retorno[30];
                        }investimento;

                        FILE *investimentos;
                        investimentos = fopen(nomeFicheiroInvestimentos, "a+");

                        int idTemp = 0;
                        char tagTemp[30], retornoTemp[30];

                        while (fscanf(investimentos, "%d %s %s", &idTemp, tagTemp, retornoTemp) != EOF) {
                        }

                        idTemp++;
                        investimento.id = idTemp;

                        printw("\n\t\t\t\tDigite a TAG do investimento:\n\t\t\t\t-> ");
                        scanw("%s", investimento.tag);
                        printw("\n\t\t\t\tDigite o retorno deste investimento:\n\t\t\t\t-> ");
                        scanw("%s", investimento.retorno);

                        fprintf(investimentos, "\n%d %s %s", investimento.id, investimento.tag, investimento.retorno);
                        fclose(investimentos);
                        do{
                            clear();
                            investimentos = fopen(nomeFicheiroInvestimentos, "a+");
                            criarTabela(investimentos, "ID", "TAG", "Retorno");
                            fclose(investimentos);
                            num = addOrRemove();
                        }while (!(num >= 1 && num <= 3));

            }
                else if (num == 2) {
                    int idRemover;
                    printw("\n\t\t\t\tDigite o ID da investimento que deseja remover:\n\t\t\t\t-> ");
                    scanw("%d", &idRemover);


                    FILE *investimentos;
                    investimentos = fopen(nomeFicheiroInvestimentos, "r+");

                    // Criei um ficheiro temporário para guardar os registos atualizados
                    FILE *temp;
                    temp = fopen("temp.txt", "w");

                    // Variáveis temporárias para ler os registos
                    int idTemp;
                    char tagTemp[30], retornoTemp[30];

                    // Ler os registos do ficheiro original e copiá-los para o ficheiro temporário, exceto o registo a ser removido
                    while (fscanf(investimentos, "%d %s %s", &idTemp, tagTemp, retornoTemp) != EOF) {
                        if (idTemp != idRemover) {
                            fprintf(temp, "%d %s %s\n", idTemp, tagTemp, retornoTemp);
                        }
                    }

                    fclose(investimentos);
                    fclose(temp);

                    // Remover o ficheiro original
                    remove(nomeFicheiroInvestimentos);
                    // Renomear o ficheiro temporário para o nome original
                    rename("temp.txt", nomeFicheiroInvestimentos);
                        do{
                            clear();
                            investimentos = fopen(nomeFicheiroInvestimentos, "a+");
                            criarTabela(investimentos, "ID", "TAG", "Retorno");
                            fclose(investimentos);
                            num = addOrRemove();
                        }while (!(num >= 1 && num <= 3));
                }
            }
        }
            else if (escolha == 6) {
                int ganhos[30];
                int perdas[30];
                char ganhosNome[30][30];
                char perdasNome[30][30];
                char temp1[30];
                int num;
                char nome[30];
                int contadorGanhos = 0;
                int contadorDespesas = 0;
                // RECEITAS
                char nomeFicheiroReceita[30];
                strcpy(nomeFicheiroReceita, idChar);
                strcat(nomeFicheiroReceita, "receitas.txt");

                FILE *receita;
                receita = fopen(nomeFicheiroReceita, "a+");
                // DESPESAS
                char nomeFicheiroDespesa[30];
                strcpy(nomeFicheiroDespesa, idChar);
                strcat(nomeFicheiroDespesa, "despesas.txt");

                FILE *despesa;
                despesa = fopen(nomeFicheiroDespesa, "a+");

                while (fscanf(receita, "%s %s %d", temp1, nome, &num) != EOF) {
                    strcpy(ganhosNome[contadorGanhos], nome);
                    ganhos[contadorGanhos] = num;
                    contadorGanhos++;
                }

                while (fscanf(despesa, "%s %s %d", temp1, nome, &num) != EOF) {
                    strcpy(perdasNome[contadorDespesas], nome);
                    perdas[contadorDespesas] = num;
                    contadorDespesas++;
                }

                for (int i = 0; i < contadorGanhos; i++) {
                    printw("%s\n", ganhosNome[i]);
                }

                fclose(receita);
                fclose(despesa);
                getch();
            }


    }while(escolha != 7);
    endwin();
    return 0;
}
