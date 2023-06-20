#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED
#include <locale.h>
#include <time.h>
#include <unistd.h>

int id;

int returnID(){
    return id;
}


void loadingBar(int progress, int total) {
    int barWidth = 50;
    float percentage = (float)progress / total;
    int filledWidth = barWidth * percentage;
    attron(A_BOLD);
    mvprintw(19, 30, "[");
    for (int i = 0; i < barWidth; i++) {
        if (i < filledWidth) {
            addch('=');
        } else {
            addch(' ');
        }
    }
    printw("] %.0f%%", percentage * 100);
    attroff(A_BOLD);
    refresh();
}

void criarPDFGraficos(char ganhosNome[][30], int ganhos[], int contadorGanhos, char perdasNome[][30], int perdas[], int contadorDespesas) {

    int intPerdas = 0;
    int intGanhos = 0;
    int lucro = 0;
    for (int i = 0; i < contadorGanhos; i++) {
        intGanhos += ganhos[i];
    }
    for (int i = 0; i < contadorDespesas; i++) {
        intPerdas += perdas[i];
    }
    lucro = intGanhos - intPerdas;

    FILE *gnuplot = popen("gnuplot -persistent", "w");
    fprintf(gnuplot, "set terminal pdfcairo\n");
    fprintf(gnuplot, "set output 'graficos.pdf'\n");

    // Primeiro gráfico: Lucro Bruto
    fprintf(gnuplot, "set title 'Lucro Bruto (Total: %d)'\n", intGanhos);
    fprintf(gnuplot, "set xlabel 'Nome'\n");
    fprintf(gnuplot, "set ylabel 'Euros (€)'\n");
    fprintf(gnuplot, "unset key\n");
    fprintf(gnuplot, "set style histogram cluster gap 1\n");
    fprintf(gnuplot, "set style fill solid\n");
    fprintf(gnuplot, "set boxwidth 0.5 relative\n");

    int maxGanhos = 0;
    for (int i = 0; i < contadorGanhos; i++) {
        if (ganhos[i] > maxGanhos) {
            maxGanhos = ganhos[i];
        }
    }
    fprintf(gnuplot, "set yrange [0:%d*1.1]\n", maxGanhos);
    fprintf(gnuplot, "plot '-' using 2:xticlabels(1) lc rgb 'blue' with boxes title 'Lucros'\n");

    // Enviar os dados para o primeiro gráfico
    for (int i = 0; i < contadorGanhos; i++) {
        fprintf(gnuplot, "%s %d\n", ganhosNome[i], ganhos[i]);
    }
    fprintf(gnuplot, "e\n");

    // Segundo gráfico: Despesas

    fprintf(gnuplot, "set title 'Despesas (Total: %d)'\n", intPerdas);
    fprintf(gnuplot, "set xlabel 'Nome'\n");
    fprintf(gnuplot, "set ylabel 'Euros (€)'\n");
    fprintf(gnuplot, "unset key\n");
    fprintf(gnuplot, "set style histogram cluster gap 1\n");
    fprintf(gnuplot, "set style fill solid\n");
    fprintf(gnuplot, "set boxwidth 0.5 relative\n");
    fprintf(gnuplot, "set label 'Lucro: %d' at screen 0.9, screen 0.03 right\n", lucro);



    int maxPerdas = 0;
    for (int i = 0; i < contadorDespesas; i++) {
        if (perdas[i] > maxPerdas) {
            maxPerdas = perdas[i];
        }
    }
    fprintf(gnuplot, "set yrange [0:%d*1.1]\n", maxPerdas);
    fprintf(gnuplot, "plot '-' using 2:xticlabels(1) lc rgb 'red' with boxes title 'Despesas'\n");

    // Enviar os dados para o segundo gráfico
    for (int i = 0; i < contadorDespesas; i++) {
        fprintf(gnuplot, "%s %d\n", perdasNome[i], perdas[i]);
    }

    fprintf(gnuplot, "e\n");

    pclose(gnuplot);
}



// FUNÇÕES PARA  E REGISTER
void startCurses(){
    initscr();  // Inicializa a biblioteca curses
    start_color();  // Habilita o uso de cores


    init_pair(1, COLOR_WHITE + 8, COLOR_WHITE + 5);
    init_pair(2, COLOR_YELLOW + 8, COLOR_WHITE + 5);
    init_pair(3, 120, COLOR_WHITE + 5);
    init_pair(4, 650, COLOR_WHITE + 5);

    wbkgd(stdscr, COLOR_PAIR(1)); //Define a cor do background
    attron(COLOR_PAIR(1));
    cbreak();
}

void printLogo(){
    attron(COLOR_PAIR(3));
    printw("                          ______         __                __             ______\n");
    printw("                         /      \\       |  \\              |  \\           /      \\\n");
    printw("                        |  $$$$$$\\  ____| $$ ______ ____   \\$$ _______  |  $$$$$$\\ __    __   _______\n");
    printw("                        | $$__| $$ /      $$|      \\    \\ |  \\|       \\ | $$___\\$$|  \\  |  \\ /       \\\n");
    printw("                        | $$    $$|  $$$$$$$| $$$$$$\\$$$$\\| $$| $$$$$$$\\ \\$$    \\ | $$  | $$|  $$$$$$$\n");
    printw("                        | $$$$$$$$| $$  | $$| $$ | $$ | $$| $$| $$  | $$ _\\$$$$$$\\| $$  | $$ \\$$    \\\n");
    printw("                        | $$  | $$| $$__| $$| $$ | $$ | $$| $$| $$  | $$|  \\__| $$| $$__/ $$ _\\$$$$$$\\\n");
    printw("                        | $$  | $$ \\$$    $$| $$ | $$ | $$| $$| $$  | $$ \\$$    $$ \\$$    $$|       $$\n");
    printw("                         \\$$   \\$$  \\$$$$$$$ \\$$  \\$$  \\$$ \\$$ \\$$   \\$$  \\$$$$$$  _\\$$$$$$$ \\$$$$$$$\n");
    printw("                                                                                  |  \\__| $$\n");
    printw("                                                                                   \\$$    $$\n");
    printw("                                                                                    \\$$$$$$\n");
    attron(COLOR_PAIR(1));
}

int autenticacao(){
    setlocale(LC_ALL, "Portuguese");
    int escolha, Realizado;
    do{
        printw("\n\t\t\t\t\t\t1 - Login\n\t\t\t\t\t\t2 - Registar\n\t\t\t\t\t\t-> ");
        scanw("%d", &escolha);
        if (escolha == 1){
            login();
        } else if (escolha == 2){
            registar();
        } else{
            clear();
            printLogo();
            attron(COLOR_PAIR(4));
            printw("\n\t\t\t\t\t\tErro, Tente novamente.\n");
            attron(COLOR_PAIR(1));
        }
    }while (escolha != 1 && escolha != 2);


}

void login() {
    FILE *utilizadores;
    utilizadores = fopen("utilizadores.txt", "r");
    clear();
    printLogo();
    char utilizador[20];
    char password[20];
    int i = 0, ch;
    printw("\n\t\t\t\t\t\tUtilizador\n\t\t\t\t\t\t-> ");
    refresh();
    getstr(utilizador);
    printw("\n\t\t\t\t\t\tPalavra-passe\n\t\t\t\t\t\t> ");
    noecho();
    while ((ch = getch()) != '\n') {
        if (ch == '\b') {
            if (i > 0) {
                i--;
                move(getcury(stdscr), getcurx(stdscr) - 1);
                delch();
                refresh();
            }
        } else {
            password[i] = ch;
            addch('*');
            refresh();
            i++;
        }
    }
    password[i] = '\0';
    echo();
    char utilizadorOriginal[20];
    char passwordOriginal[20];
    int contador = 0;

    rewind(utilizadores); // Reposiciona o ponteiro do ficheiro para o início

    while (fscanf(utilizadores, "%s %s %d", utilizadorOriginal, passwordOriginal, &id) != EOF) {
        if (strcmp(utilizador, utilizadorOriginal) == 0 && strcmp(password, passwordOriginal) == 0) {
            attron(COLOR_PAIR(3));
            int total = 70;
            for (int i = 0; i <= total; i++) {
                loadingBar(i, total);
                usleep(10000);
            }
            attron(COLOR_PAIR(2));
            printw("\n\n\t\t\t\t\tLogin realizado com sucesso :D");
            refresh();
            sleep(1);
            attron(COLOR_PAIR(1));
            contador++;
            break;
        }
    }
    if (contador == 0) {
        clear();
        printLogo();
        attron(COLOR_PAIR(4));
        printw("\n\t\t\t\t\tUtilizador e/ou palavra-passe errados\n");
        attron(COLOR_PAIR(1));
        autenticacao();
    }
    fclose(utilizadores);
}

void registar() {
    FILE *utilizadores;
    utilizadores = fopen("utilizadores.txt", "a+");
    clear();
    printLogo();
    char utilizador[20];
    char password[20];
    int i = 0, ch;
    printw("\n\t\t\t\t\t\tUtilizador\n\t\t\t\t\t\t-> ");
    refresh();
    getstr(utilizador);

    // Verificar se o nome de utilizador contém espaços
    if (strchr(utilizador, ' ') != NULL) {
        clear();
        printLogo();
        attron(COLOR_PAIR(4));
        printw("\n\t\t\t\tO nome de utilizador nao pode conter espacos. Tente novamente.\n");
        attron(COLOR_PAIR(1));
        autenticacao();
        return;
    }

    printw("\n\t\t\t\t\t\tPalavra-passe\n\t\t\t\t\t\t> ");
    noecho();
    while ((ch = getch()) != '\n') {
        if (ch == '\b') {
            if (i > 0) {
                i--;
                move(getcury(stdscr), getcurx(stdscr) - 1);
                delch();
                refresh();
            }
        } else {
            password[i] = ch;
            addch('*');
            refresh();
            i++;
        }
    }
    password[i] = '\0';
    echo();
    int contador = 0;
    char utilizadorOriginal[20];
    char passwordOriginal[20];

    rewind(utilizadores); // Reposiciona o ponteiro do ficheiro para o início

    while (fscanf(utilizadores, "%s %s %d", utilizadorOriginal, passwordOriginal, &id) != EOF) {
        if (strcmp(utilizador, utilizadorOriginal) == 0 || strlen(utilizador) < 2 || strlen(password) < 2) {
            clear();
            printLogo();
            attron(COLOR_PAIR(4));
            printw("\n\t\t\t\tEste utilizador ja existe, tente novamente.\n");
            attron(COLOR_PAIR(1));
            autenticacao();
            contador++;
            break;
        }
    }
    if (contador == 0) {
        fprintf(utilizadores, "\n%s %s %d", utilizador, password, id + 1);
        fclose(utilizadores);

        attron(COLOR_PAIR(3));
        int total = 70;
        for (int i = 0; i <= total; i++) {
            loadingBar(i, total);
            usleep(10000);
        }
        clear();
        attron(COLOR_PAIR(1));
        printLogo();
        attron(COLOR_PAIR(3));
        printw("\n\t\t\t\t\tRegisto realizado com sucesso.\n");
        refresh();
        attron(COLOR_PAIR(1));
        autenticacao();
    }
}



#endif // FUNCTIONS_H_INCLUDED
