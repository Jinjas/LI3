#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>
#include "../include/drivers.h"
#include "../include/rides.h"
#include "../include/users.h"
#include "../include/query1.h"
#include "../include/query2.h"
#include "../include/query3.h"
#include "../include/query4.h"
#include "../include/query5.h"
#include "../include/query6.h"
#include "../include/query7.h"

typedef struct data{
    int id;
    char arguments[280];
}Data;

void print_query_list (Data **query){
    int *totais = (int*)calloc(9, sizeof(int));
    for (int i = 0; i < 9; i++){
        for(; query[i][totais[i]].id != 0; totais[i]++){
            printf("query = %d ; argumento = %s ; linha = %d\n", i, query[i][totais[i]].arguments, query[i][totais[i]].id);
        }
    }
}

void free_query_list(Data ** query_list){
    for (int i = 0; i < 9; i++){
            free(query_list[i]);
    }
}

//cria uma Data **query que vai conter todos os argumentos necessários para a execução das queries
Data **query_lista(FILE *input){
    int current_size = 1000;
    int linha = -1;
    int *index = (int*)calloc(9, sizeof(int));
    int nquery;
    int i;
    Data **query_list = (Data**)calloc(9, sizeof(Data*));
    for(i = 0; i < 9; i++){
        query_list[i] = (Data*)calloc(current_size, sizeof(Data));
    }
    char *line = (char*)malloc(281 * sizeof(char));
    size_t j = 280;
    while(!feof(input)){
    int qtype;   
        getline(&line, &j, input);
        qtype = line[0] - '1';
        linha++;
        for(int i = 2; line[i] != '\n'; i++)
        query_list[qtype][index[qtype]].arguments[i-2] = line[i];
        query_list[qtype][index[qtype]].id = linha+1;
        
        index[qtype]++;
    }
    free(index);
    free(line);
    return query_list;
}

//função que determina quanto tempo demora a correr cada query
void executa_query(Data **query_list, D_data *drivers_table, U_data *users_table, R_data *r_data){
    int *totais = (int*)calloc(9, sizeof(int));
    clock_t start, end;
    double cpu_time_used;
    Drivers *drivers = D_getTable(drivers_table);
    Users *users = U_getTable(users_table);
    for (int i = 0; i < 9; i++){
        for(; query_list[i][totais[i]].id != 0; totais[i]++){
                int nquery = i + 1;
                start = clock();
                switch (nquery){
                    case 1 : 
                    profile_resume (query_list[i][totais[i]].arguments, drivers, users, query_list[i][totais[i]].id, RgetD_limit(r_data));
                                        break; //query1 
                    case 2 : 
                    escreve_file(query_list[i][totais[i]].arguments, drivers_table, query_list[i][totais[i]].id, getD_limit_drivers(drivers_table));
                                        break; //query2
                    case 3 : 
                    printFile(query_list[i][totais[i]].arguments, users_table, query_list[i][totais[i]].id, getU_limit(users_table)); 
                                        break; //query3 
                    case 4 :
                    escreve_ficheiro4_Rides(query_list[i][totais[i]].arguments, r_data, query_list[i][totais[i]].id);
                                        break; // query4
                    case 5 :
                    escreve_ficheiro5(query_list[i][totais[i]].arguments, r_data, query_list[i][totais[i]].id);
                                        break; // query5
                    case 6 :
                    char *cidade = strdup(query_list[i][totais[i]].arguments);
                    (strtok(cidade, " "));
                    escreve_ficheiro6(r_data,cidade,&query_list[i][totais[i]].arguments[strlen(cidade)+1], query_list[i][totais[i]].id);
                    free(cidade);
                                        break; // query6
                    case 7 :
                    char *topn = strdup(query_list[i][totais[i]].arguments);
                    (strtok(topn, " "));
                    escreve_file_query7(topn,&query_list[i][totais[i]].arguments[strlen(topn)+1], r_data, drivers, query_list[i][totais[i]].id);
                    free(topn);
                                        break; //query7
                    case 8 :
                    Query8(query_list[i][totais[i]].arguments, r_data, drivers, users, query_list[i][totais[i]].id);
                                        break;
                    case 9 :
                    char *data = strdup(query_list[i][totais[i]].arguments);
                    (strtok(data, " "));
                    query9_sort_distance(data,&query_list[i][totais[i]].arguments[strlen(data)+1], r_data, query_list[i][totais[i]].id);
                    free(data);
                                        break;
                    default: break;
                }
        }
            end = clock();
            cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
            int nquery = i + 1;
            printf("CPU time for %d queries %d is %fs\n", totais[i], nquery, cpu_time_used);
    }
    free(totais);
}

//função que faz a verificação dos files
void compareFiles(Data **query_list){
    int *totais = (int*)calloc(9, sizeof(int));
    int *corretos = (int*)calloc(9, sizeof(int));
    for (int i = 0; i < 9; i++){
        for(; query_list[i][totais[i]].id != 0; totais[i]++){
            int linha = 1;  
            int incorrect = 0;
            char* obtained_file = (char*)malloc(255 * sizeof(char)); 
            strcpy(obtained_file, "Resultados/command");
            
            char* correct_file = (char*)malloc(255 * sizeof(char)); 
            strcpy(correct_file, "test_output/command");
            
            
            char *file_number = (char*)malloc((query_list[i][totais[i]].id/2 + 2) *sizeof(char));
            sprintf(file_number,"%d",query_list[i][totais[i]].id);
            strcat(strcat(obtained_file, file_number), "_output.txt");
            strcat(strcat(correct_file, file_number), "_output.txt");

            FILE *file1 = fopen(obtained_file  ,"r");
            FILE *file2 = fopen(correct_file, "r");
            //char line1[900];
            if((file1 = fopen(obtained_file, "r")) == NULL){
                printf("Erro a abrir file");
            }
            if((file2 = fopen(correct_file, "r")) == NULL){
                printf("Erro a abrir file");
            }       
            char *line1 = (char*)malloc(851 * sizeof(char *));
            char *line2 = (char*)malloc(851 * sizeof(char *));
            size_t j = 850;
            while(getline(&line1, &j, file1) != -1 && getline(&line2, &j, file2) != -1){
                if(strcmp(line1, line2) != 0){
                    incorrect = -1;
                    printf("File command%s_output.txt incorrect, first line with error %d\n", file_number, linha);
                    break;
                }
                linha++;
            }
            fseek(file1, 0, SEEK_END);
            fseek(file2, 0, SEEK_END);
            if(ftell(file1) != ftell(file2)){
                printf("The files command%s_output.txt have different sizes\n", file_number);
                incorrect = -1;
            }
            if(incorrect == 0){
                corretos[i]++;
            }
            fclose(file1);
            fclose(file2);
            free(obtained_file);
            free(correct_file);
            free(file_number);
            free(line1);
            free(line2);
        }
        int percentage = (corretos[i] * 100) / totais[i]; ;
        int nquery = i + 1;
        printf("Query %d is %d%% correct\n", nquery, percentage);
    }
    free(totais);
    free(corretos);
}

int main(int argc, char **argv){
    char *aux = (char*)malloc(1000* sizeof(char));
    double cpu_time_user, cpu_time_driver, cpu_time_rides;
    clock_t start_users, end_users, start_drivers, end_drivers, start_rides, end_rides;

    start_users = clock();
    strcpy(aux, argv[1]);
    strcat(aux, "/users.csv");
    FILE *users =  fopen(aux, "r");
    U_data* users_table = u_createTable(users);
    fclose(users);
    end_users = clock();
    cpu_time_user = ((double) (end_users - start_users)) / CLOCKS_PER_SEC;
    printf("CPU time loading users.cvs is %fs\n", cpu_time_user);

    start_drivers = clock();
    strcpy(aux, argv[1]);
    strcat(aux, "/drivers.csv");
    FILE *drivers =  fopen(aux, "r");
    D_data *drivers_table = d_createTable(drivers);
    fclose(drivers);
    end_drivers = clock();
    cpu_time_driver = ((double) (end_drivers - start_drivers)) / CLOCKS_PER_SEC;
    printf("CPU time loading drivers.cvs is %fs\n", cpu_time_driver);

    start_rides = clock();
    strcpy(aux, argv[1]);
    strcat(aux, "/rides.csv");
    FILE *rides =  fopen(aux, "r");
    R_data *r_data = updateTables(rides, drivers_table, U_getTable(users_table));
    fclose(rides);
    end_rides = clock();
    cpu_time_rides = ((double) (end_rides - start_rides)) / CLOCKS_PER_SEC;
    printf("CPU time loading rides.cvs is %fs\n\n", cpu_time_rides);

    FILE *input = fopen(argv[2],"r");
    Data **query_list = query_lista(input); 
    
    D_sortAll(drivers_table);
    U_sortAll(users_table);
    City_sortDrivers(r_data, D_getTable(drivers_table), 100);
    executa_query(query_list, drivers_table, users_table, r_data);
    printf("\n");
    compareFiles(query_list);

    d_free(drivers_table);
    u_free(users_table);
    R_free(r_data);
    free(aux);
    fclose(input);
}
