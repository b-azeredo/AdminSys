#ifndef COLORS_H_INCLUDED
#define COLORS_H_INCLUDED
#include <locale.h>

int id;

int returnID(){
    return id;
}

// FUNÇÕES PARA LOGIN E REGISTER
void startCurses(){
    initscr();  // Inicializa a biblioteca curses
    start_color();  // Habilita o uso de cores
    init_pair(1, COLOR_WHITE + 8, 60);  // Define um par de cores (cor do texto e cor do fundo)
    wbkgd(stdscr, COLOR_PAIR(1)); //Define a cor do background
    attron(COLOR_PAIR(1));  // Ativa o par de cores definido
    cbreak(); // Desabilitar o buffer de linha
    init_pair(2, COLOR_YELLOW + 8, 60);
    init_pair(3, COLOR_RED + 8, 60);
}

void printLogo(){
printw("\t\t\t                 _           _        _____           \n");
printw("\t\t\t        /\\      | |         (_)      / ____|          \n");
printw("\t\t\t       /  \\   __| |_ __ ___  _ _ __ | (___  _   _ ___ \n");
printw("\t\t\t      / /\\ \\ / _` | '_ ` _ \\| | '_ \\ \\___ \\| | | / __|\n");
printw("\t\t\t     / ____ \\ (_| | | | | | | | | | |____) | |_| \\__ \\\n");
printw("\t\t\t    /_/    \\_\\__,_|_| |_| |_|_| |_|_|_____/\\___  |___/\n");
printw("\t\t\t                                             __/ |    \n");
printw("\t\t\t                                           |____/     \n");

}

int autenticacao(){
    setlocale(LC_ALL, "Portuguese");
    int escolha, loginRealizado;
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
            attron(COLOR_PAIR(3));
            printw("\n\t\t\t\t\t\tErro, Tente novamente.");
            attron(COLOR_PAIR(1));
        }
    }while (escolha != 1 && escolha != 2);


}

void login(){
    FILE *utilizadores;
    utilizadores = fopen("utilizadores.txt", "r");
    clear();
    printLogo();
    char utilizador[20];
    char password[20];
    int i, ch;
    printw("\n\t\t\t\t\t\tUtilizador\n\t\t\t\t\t\t-> ");
    refresh();
    getstr(utilizador);
    printw("\n\t\t\t\t\t\tPalavra-passe\n\t\t\t\t\t\t-> ");
    noecho();
    while ((ch = getch()) != '\n') {
        password[i] = ch;
        addch('*'); // Exibir asterisco no lugar do caractere digitado
        refresh();
        i++;
    }
    password[i] = '\0'; // Adicionar o caractere nulo para finalizar a string
    echo();
    char utilizadorOriginal[20];
    char passwordOriginal[20];
    int contador = 0;
    while (fscanf(utilizadores, "%s %s %d", &utilizadorOriginal, &passwordOriginal, &id) != EOF){
        if (strcmp(utilizador, utilizadorOriginal) == 0 && strcmp(password, passwordOriginal) == 0){
            attron(COLOR_PAIR(2));
            printw("\n\t\t\t\t\tLogin realizado com sucesso :D");
            attron(COLOR_PAIR(1));
            contador++;
            break;
        }
    }
    if (contador == 0){
        clear();
        printLogo();
        attron(COLOR_PAIR(3));
        printw("\n\n\t\t\t\t\tUtilizador e/ou palavra-passe errados\n");
        attron(COLOR_PAIR(1));
        autenticacao();
    }
    getch();
    fclose(utilizadores);
}

void registar(){
    FILE *utilizadores;
    utilizadores = fopen("utilizadores.txt", "a+");
    clear();
    printLogo();
    char utilizador[20];
    char password[20];
    int i, ch;
    printw("\n\t\t\t\t\t\tUtilizador\n\t\t\t\t\t\t> ");
    refresh();
    getstr(utilizador);
    printw("\n\t\t\t\t\t\tPalavra-passe\n\t\t\t\t\t\t-> ");
    noecho();
    while ((ch = getch()) != '\n') {
        password[i] = ch;
        addch('*'); // Exibir asterisco no lugar do caractere digitado
        refresh();
        i++;
    }
    password[i] = '\0'; // Adicionar o caractere nulo para finalizar a string
    echo();
    int contador = 0;
    char utilizadorOriginal[20];
    char passwordOriginal[20];
    while (fscanf(utilizadores, "%s %s %d", &utilizadorOriginal, &passwordOriginal, &id) != EOF){
        if (strcmp(utilizador, utilizadorOriginal) == 0 || strlen(utilizador) < 2 || strlen(password) < 2){
            clear();
            printLogo();
            attron(COLOR_PAIR(3));
            printw("\n\n\t\t\t\tEste utilizador ja existe, Tente novamente.\n");
            attron(COLOR_PAIR(1));
            autenticacao();
            contador++;
        }
    }
    if (contador == 0){
        fprintf(utilizadores, "\n%s %s %d", utilizador, password, id + 1);
        fclose(utilizadores);
        clear();
        printLogo();
        attron(COLOR_PAIR(2));
        printw("\n\t\t\t\t\tRegisto realizado com sucesso.");
        refresh();
        attron(COLOR_PAIR(1));
        autenticacao();
    }
}

#endif // FUNCTIONS_H_INCLUDED
