#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ncurses.h>
#include "../include/drivers.h"
#include "../include/rides.h"
#include "../include/users.h"
#include "../include/query_handler.h"
#include "../include/query1.h"
#include "../include/query2.h"
#include "../include/query3.h"
#include "../include/query4.h"
#include "../include/query5.h"
#include "../include/query6.h"
#include "../include/query7.h"

typedef struct dataset {
    D_data *drivers_table;
    U_data *users_table;
    R_data *r_data;
}Dataset;

//Função que escreve a capa do modo
void welcomeInteractive(int xMax){
    int xMid = xMax/2-40;
    char base[xMax-7];
    for (int i = 0; i < xMax-7; base[i++] = '_');
    base[xMax-8] = '\0';
    mvprintw(2,4,"%s",base);

    mvprintw (4,xMid+6 ," ___       _                      _   _       \n");    
    mvprintw (5,xMid+6 ,"|_ _|_ __ | |_ ___ _ __ __ _  ___| |_(_)_   _____ \n");
    mvprintw (6,xMid+6 ," | || '_ \\| __/ _ \\ '__/ _` |/ __| __| \\ \\ / / _ \\\n");
    mvprintw (7,xMid+6 ," | || | | | ||  __/ | | (_| | (__| |_| |\\ V /  __/\n");
    mvprintw (8,xMid+6 ,"|___|_| |_|\\__\\___|_|  \\__,_|\\___|\\__|_| \\_/ \\___|\n");

    mvprintw(9,xMid + 43, " __  __           _      ");
    mvprintw(10,xMid + 43, "|  \\/  | ___   __| | ___ ");
    mvprintw(11,xMid + 43,"| |\\/| |/ _ \\ / _` |/ _ \\");
    mvprintw(12,xMid + 43,"| |  | | (_) | (_| |  __/");
    mvprintw(13,xMid + 43,"|_|  |_|\\___/ \\__,_|\\___|");

    mvprintw(16,4,"%s",base);
}
//Função que pede um dataset ao utilizador e faz o parse do mesmo
Dataset* NewDataset(Dataset* dataset,WINDOW * win,int xMax){
    
    refresh();
    char*path = malloc(1000*sizeof(char));
    char *aux = (char*)malloc(1000* sizeof(char));
    short int errado = 1;
    mvwin(win,4,5);
    wrefresh(win);
    
    while (errado){
        box(win,0,0);
        wrefresh(win);
        mvwprintw(win,1,2,"Please insert the path to the directory with the files");
        mvwprintw(win,2,2,"-> ");
        wrefresh(win);
        wgetstr(win,path);

        refresh();
        strcpy(aux, path);
        strcat(aux, "/users.csv");
        FILE *users =  fopen(aux, "r");

        strcpy(aux, path);
        strcat(aux, "/drivers.csv");
        FILE *drivers =  fopen(aux, "r");
        
        strcpy(aux, path);
        strcat(aux, "/rides.csv");
        FILE *rides =  fopen(aux, "r");
        move(9,4);

        if (users && drivers && rides){
            move(9,0);
            clrtobot();
            mvprintw(9,6,"Processing Drivers");
            refresh();
            dataset->drivers_table = d_createTable(drivers);
            fclose(drivers);
            move(9,6);
            clrtobot();
            printw("Drivers process completed");
            move(10,6);
            printw("Processing Users");
            refresh();
            dataset->users_table = u_createTable(users);
            fclose(users);
            move(10,6);
            clrtobot();
            printw("Users process completed");
            move(11,6);
            printw("Processing Rides");
            refresh();
            dataset->r_data = updateTables(rides, dataset->drivers_table, U_getTable(dataset->users_table));
            fclose(rides);
            move(11,6);
            clrtobot();
            printw("Rides process completed");
            refresh();
            errado = 0;//break the cicle
        }
        wclear(win);
        if (errado){
            printw("  The directory given is not a path to a valid dataset");
        }
        refresh();
    }
    //free the temporary paths
    free(aux);
    free(path);
    D_sortAll(dataset->drivers_table);
    U_sortAll(dataset->users_table);
    City_sortDrivers(dataset->r_data, D_getTable(dataset->drivers_table), 100);
    return dataset;
}
//Função para o free da estrutura criada
void free_dataset(Dataset* dataset){
    d_free(dataset->drivers_table);
    u_free(dataset->users_table);
    R_free(dataset->r_data);
    
}
//Função para selecionar a query a ser executada 
int selectQuery(WINDOW* queryWin, WINDOW* win){

    wrefresh(queryWin);
    refresh();
    mvwin(win,2,5);
    box(win,0,0);
    wrefresh(win);
    mvwprintw(win,2,2,"Select a query to execute");
    mvprintw(21,6,"Press ESC if u want to chose other dataset");
    refresh();
    wrefresh(win);
    box(queryWin,0,0);
    wrefresh(queryWin);
    keypad(win,true);
    
    char *queryChoices[9] = {"1: Profile Resume", "2: Top N drivers organized by rate", "3: Top N Users organized by distance", "4: Average price of a travel in a city", "5: Average price of a travel between 2 days", "6: Average distance of a travel in a city between 2 days", "7: Top N drivers of a certain city", "8: Travels where Usr. and Drv. share genders and have X acc years", "9: All travels where the User gave tip between 2 days"};
    int choice;
    int highlight=0;
    noecho();
    while(1){
        for(int i = 0;i<9;i++){
            if(i==highlight)
                wattron(queryWin,A_REVERSE);
            mvwprintw(queryWin,i+1,2,"%s",queryChoices[i]);
            wattroff(queryWin,A_REVERSE);
        }
        wrefresh(queryWin);
        choice = wgetch(win);
        switch(choice){
            case KEY_UP:
                highlight --;
                if(highlight==-1)
                    highlight = 8;
                break;
            case KEY_DOWN:
                highlight ++;
                if(highlight==9)
                    highlight = 0;
                break;
            default:
                if (choice >='1'&& choice <='9')
                    highlight = choice-'1';
                break;
        }
        if (choice == 27){
            wclear(win);
            wclear(queryWin);
            clear();
            return 27;
        }
        if (choice == 10)
            break;
    }
    echo();
    return highlight;
}
//Função que pede ao utilizador os argumentos da query
char* getArgumentsQ(WINDOW*win,char* msg,char* msgType){
    char*identifier = malloc(255*sizeof(char));
    mvwprintw(win,1,2,"%s",msg);
    mvwprintw(win,3,2,"-> ");
    mvprintw(7,6,"%s",msgType);
    refresh();
    wgetstr(win,identifier);
    mvprintw(7,6,"                                                     ");
    refresh();
    return identifier;
}
//Função para criar as paginas de impressao dos varios outputs 
int paginar(char* lineR, size_t j,FILE* resultado, WINDOW* queryWin,int yMax, int xMax){
    if(getline(&lineR, &j, resultado)==-1) {
        wrefresh(queryWin);
        mvwprintw(queryWin,1,1,"The input you gave its not valid or there's no output");
        wrefresh(queryWin);
        mvprintw(yMax-5,4,"press ENTER if you want to execute other query");
        mvprintw(yMax-4,4,"press ESC if you want to use other dataset");
        refresh();
        int command = wgetch(queryWin);
        for (; command!=27 && command !=10; command = wgetch(queryWin));
            return command;
    }
    else{
        int command;
        unsigned int maxLines = 1000;
        char **document = malloc(maxLines*(510*sizeof(char)));
        int i = 0;
        document[i] = strdup(lineR);
        while (getline(&lineR, &j, resultado)!=-1){
            if (i == maxLines-1) {
                maxLines = maxLines * 2 - 1;
                document = realloc(document,maxLines*(510*sizeof(char)));
            }
            document[++i] = strdup(lineR);
        }
        unsigned int pagAt = 0, pagMax;
        if (++i % 10 != 0) pagMax = i/10;
        else pagMax = i/10-1;
        while(1){
            move(22,2);
            clrtobot();
            mvprintw(22,xMax/2-33,"ENTER: Ask for a new query   ESC: Change dataset   page : %d / %d",pagAt+1,pagMax+1);
            refresh();
            if (pagAt != pagMax){
                for(int j = 0 ;j < 10;){
                    for(int s = 0;(document[pagAt*10+j][s] != '\n'); s++)
                        mvwprintw(queryWin,j+1,2+s,"%c",document[pagAt*10+j][s]);
                    wrefresh(queryWin);
                    j++;
                }
            }else{
                for(int j = pagAt*10;j < i;){
                    for(int s = 0;(document[j][s] != '\n'); s++)
                        mvwprintw(queryWin,j-pagAt*10+1,2+s,"%c",document[j][s]);
                    wrefresh(queryWin);
                    j++;
                }
            }
            //comandos
            noecho();
            curs_set(0);
            keypad(queryWin, true);
            for (command = wgetch(queryWin); command!=27 && command!=KEY_RIGHT && command!=KEY_LEFT && command !=10; command = wgetch(queryWin));
            if(command == 27){ 
                break;
            }
            if(command == 10){
                break;
            }
            if(command == KEY_RIGHT && pagAt < pagMax)
                pagAt++;
            else if(command == KEY_LEFT && pagAt > 0)
                pagAt--;
            wclear(queryWin);
            wrefresh(queryWin);
        }
        wclear(queryWin);
        wrefresh(queryWin);
        for(int aux = 0; aux <i; aux++){
            free(document[aux]);
        }
        free(document);
        keypad(queryWin, false);
        return command;
    }
}
//Função executeQuery-> executa a query pedida e imprime os resultados
int processQuery(Dataset* dataset, WINDOW* queryWin, WINDOW* win,int queryNumb, int yMax, int xMax){
    Drivers *drivers = D_getTable(dataset->drivers_table);
    Users *users = U_getTable(dataset->users_table);
    clear();
    wclear(win);
    refresh();
    box(win,0,0);
    wrefresh(win);
    char *arguments;
    char *lineR = (char*)malloc(281 * sizeof(char));
    size_t j = 280;
    FILE *resultado;
    int command = 1;
    switch (queryNumb){
        case 1 : 
        arguments = getArgumentsQ(win,"Identify the Driver(Id) or User(Username) that you want to see","");
        profile_resume (arguments, drivers, U_getTable(dataset->users_table), 1, RgetD_limit(dataset->r_data));
        free(arguments);
        wclear(queryWin);
        resultado = fopen("Resultados/command1_output.txt","r");
        wrefresh(queryWin);
        
        if(getline(&lineR, &j, resultado)==-1) {
            wrefresh(queryWin);
            mvwprintw(queryWin,1,1,"The input you gave to process does not correspond to a profile");
            wrefresh(queryWin);
        }
        else{
            int s = 0;
            int i = 0;
            char *query1params[6] = {"Nome","Genero","Idade","Avaliacao_media","Numero de Viagens","Total"};
            wrefresh(queryWin);
            while (i<6){
                mvwprintw(queryWin,i+1,2,"%s: ",query1params[i]);
                for(; (lineR[s] != ';') && (lineR[s] != '\n'); s++)
                    wprintw(queryWin,"%c",lineR[s]); 
                i++;s++;
            }
            wrefresh(queryWin);
        }
        free(lineR);
        fclose(resultado);
                    break; //query1 
        case 2 : 
        arguments = getArgumentsQ(win,"How many drivers do u want to see","Insert a number above 0");
        escreve_file(arguments, dataset->drivers_table, 1,getD_limit_drivers(dataset->drivers_table));
        wclear(queryWin);
        resultado = fopen("Resultados/command1_output.txt","r");
        wrefresh(queryWin);
        free(arguments);
        command = paginar(lineR, j,resultado,queryWin,yMax,xMax);
        free(lineR);
        fclose(resultado);
                    break; //query2
        case 3 : 
        arguments = getArgumentsQ(win,"How many Users do u want to see","Insert a number above 0");
        printFile(arguments, dataset->users_table, 1,getU_limit(dataset->users_table)); 
        wclear(queryWin);
        resultado = fopen("Resultados/command1_output.txt","r");
        wrefresh(queryWin);
        free(arguments);
        command = paginar(lineR, j,resultado,queryWin,yMax,xMax);
        free(lineR);
        fclose(resultado);
                    break; //query3 
        case 4 :
        arguments = (getArgumentsQ(win,"From which city do you want to know the average price?","Insert the city name"));
        escreve_ficheiro4_Rides(arguments, dataset->r_data, 1);
        wclear(queryWin);
        resultado = fopen("Resultados/command1_output.txt","r");
        wrefresh(queryWin);
        if(getline(&lineR, &j, resultado)==-1) {
            wrefresh(queryWin);
            mvwprintw(queryWin,1,1,"The input you gave to process does not correspond to a city in our system");
            wrefresh(queryWin);
        }
        else{
            mvwprintw(queryWin,1,2,"the average cost of %s: ",arguments);
            for(int s = 0;(lineR[s] != '\n'); s++)
                wprintw(queryWin,"%c",lineR[s]);
            wrefresh(queryWin);
        }
        free(arguments);
        free(lineR);
        fclose(resultado);
                    break; // query4
        case 5 :
        arguments =(getArgumentsQ(win,"From between which dates do you want to know the average price?","Insert 2 dates: DD/MM/YYYY DD/MM/YYYY"));
        escreve_ficheiro5(arguments, dataset->r_data, 1);
        free(arguments);
        wclear(queryWin);
        resultado = fopen("Resultados/command1_output.txt","r");
        wrefresh(queryWin);
        if(getline(&lineR, &j, resultado)==-1) {
            wrefresh(queryWin);
            mvwprintw(queryWin,1,1,"The input you gave does not has travels associated to in our system");
            wrefresh(queryWin);
        }
        else{
            mvwprintw(queryWin,1,2,"the average cost of that time: ");
            for(int s = 0;(lineR[s] != '\n'); s++)
                wprintw(queryWin,"%c",lineR[s]);
            wrefresh(queryWin);
        }
        free(lineR);
        fclose(resultado);
                    break; // query5
        case 6 :
        arguments = getArgumentsQ(win,"From which city and date gap do you want to know the average distance?","Insert a city and 2 dates: city DD/MM/YYYY DD/MM/YYYY");
        char *cidade = strdup(arguments);
        (strtok(cidade, " "));
        escreve_ficheiro6(dataset->r_data,cidade,&(arguments)[strlen(cidade)+1], 1);
        free(arguments);
        wclear(queryWin);
        resultado = fopen("Resultados/command1_output.txt","r");
        wrefresh(queryWin);
        if(getline(&lineR, &j, resultado)==-1) {//o resultado n existe(precisa de msg)
            wrefresh(queryWin);
            mvwprintw(queryWin,1,1,"The input you gave does not has travels associated to in our system");
            wrefresh(queryWin);
        }
        else{
            mvwprintw(queryWin,1,2,"the average distance in %s of that time: ",cidade);
            for(int s = 0;(lineR[s] != '\n'); s++)
                wprintw(queryWin,"%c",lineR[s]);
            wrefresh(queryWin);
        }
        free(cidade);
        free(lineR);
        fclose(resultado);
                    break; // query6
        case 7 :
        arguments = getArgumentsQ(win,"How many drivers and which city do you want to see?","Insert a positive number and the city name: N City");
        char *topn = strdup(arguments);
        (strtok(topn, " "));
        escreve_file_query7(topn,&(arguments)[strlen(topn)+1], dataset->r_data, drivers, 1);
        free(topn);
        wclear(queryWin);
        resultado = fopen("Resultados/command1_output.txt","r");
        wrefresh(queryWin);
        free(arguments);
        command = paginar(lineR, j,resultado,queryWin,yMax,xMax);
        free(lineR);
        fclose(resultado);
                    break; // query7
        case 8 :
        arguments = getArgumentsQ(win, "Insert the gender and then the number of minimum years you want to see the travels","Insert gender and  a positive number: M/F N");
        Query8(arguments, dataset->r_data, drivers, users, 1);
        free(arguments);
        wclear(queryWin);
        resultado = fopen("Resultados/command1_output.txt","r");
        wrefresh(queryWin);
        command = paginar(lineR, j,resultado,queryWin,yMax,xMax);
        free(lineR);
        fclose(resultado);
                    break;
        case 9 :
        arguments = getArgumentsQ(win,"From between which dates do you want to see the travels?","Insert 2 dates: DD/MM/YYYY DD/MM/YYYY");
        char *data = strdup(arguments);
        (strtok(data, " "));
        query9_sort_distance(data,&arguments[strlen(data)+1], dataset->r_data, 1);
        free(data);
        wclear(queryWin);
        resultado = fopen("Resultados/command1_output.txt","r");
        wrefresh(queryWin);
        free(arguments);
        command = paginar(lineR, j,resultado,queryWin,yMax,xMax);
        free(lineR);
        fclose(resultado);
                    break;
        default:break;
    }
    return command;
}
//Função principal do modulo, é responsavel pelo modo iterativo.Quando o utilizador chama o executavel sem agrumentos esta função é chamada e vai pedindo ao utilizador tudo o que precisa para executar o programa
void interactivemode(){

    initscr();
    
    int yMax, xMax;
    getmaxyx(stdscr,yMax,xMax);
    refresh();
    WINDOW * queryWin = newwin(11,xMax-12,8,5);
    WINDOW * win = newwin(5,xMax-12,4,5);
    int control;
    Dataset* dataset;
    while(1){
        dataset = malloc(sizeof(Dataset));
        mvprintw(yMax-5,4,"press ENTER if you want to use other dataset");
        mvprintw(yMax-4,4,"press ESC if you want to quit");
        welcomeInteractive(xMax);
        curs_set(0);
        refresh();
        noecho();
        for (control = getch(); control!=27 && control !=10; control = getch());
        if(control == 27)
            break;
        echo();
        clear();

        mvprintw(1,6,"Welcome to our interctive mode!");
        mvprintw(2,6,"This mode is optimized to deal with small operations");
        mvprintw(3,6,"For large operations please use the batch mode");
        curs_set(1);
        dataset = NewDataset(dataset,win, xMax);
        clear();
        int queryNumb;
        while(1){
            curs_set(0);
            queryNumb = (selectQuery(queryWin,win))+1;
            curs_set(1);
            if (queryNumb == 28)
                break;
            control = 5;
            control = processQuery(dataset,queryWin,win,queryNumb,yMax,xMax);
            wclear(win);
            wclear(queryWin);
            if (queryNumb == 1 || (queryNumb >= 4 && queryNumb <= 6)){
                mvprintw(yMax-5,4,"press ENTER if you want to execute other query");
                mvprintw(yMax-4,4,"press ESC if you want to use other dataset");
                noecho();
                curs_set(0);
                for (control = getch(); control!=27 && control !=10; control = getch());
                if(control == 27)  
                    break;
            }
            if(control == 27)
                    break;
            echo();
            clear();
            
        }
        clear();
        refresh();
        mvprintw(yMax/2,xMax/2-4,"Closing");
        refresh();
        free_dataset(dataset);
        dataset->users_table = NULL;
        dataset->drivers_table = NULL;
        dataset->r_data = NULL;
        dataset = NULL;
        clear();
    }
        free(dataset);
    endwin();
}
