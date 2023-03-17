#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
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
#include <sys/param.h>//para a função MAX

typedef struct querys {
    int id; // numero da query (ordem de chegada)
    char nquery; 
    char arguments[280];
} Querys;

void memoryExpansion2(Querys** list, int size){
    Querys* aux = (Querys*)realloc(*list, size * sizeof(Querys));
    if (aux != NULL){
       *list = aux;
    } else  printf("Realloc Falou \n");
}

//print das querys
void q_printList(Querys *list){
    int i = 0;
    printf("%d\n", list[i].id);
    while (list[i].id != 0){
        printf("id: %d\n",list[i].id);
        printf("nquery: %c\n",list[i].nquery);
        printf("arguments: %s\n",list[i].arguments);
        printf("------------------------------------------------------------------\n");
        i++;
    }
    printf("done\n");

} 

//função que recebe o ficheiro com inputs de querys e devolve uma lista com cada query no foturo irá para a main(query 5 e 6)
Querys *q_createqueryslist(FILE *querys){
    int current_list_size = 1000;//#total de querys
    int iterations = -1; //#da query
    Querys *list = (Querys*)calloc(current_list_size, sizeof(Querys));
    char *line = (char*)malloc(281 * sizeof(char));
    size_t j = 280;
    int aux = 0;
    while(!feof(querys)){
        aux = getline(&line, &j, querys);
        if (aux == -1) continue; //caso receba linhas vazias, para nao crachar
        iterations++; // o aux contem o valor que escolhe a query
        list[iterations].nquery = line[0];
        for(int i = 2; line[i] != '\n'; i++)
            list[iterations].arguments[i-2] = line[i];
        list[iterations].id = iterations + 1;
        if(iterations >= current_list_size - 5){
            current_list_size *=10;
            memoryExpansion2(&list, current_list_size);
        }
    }
    list[iterations+1].id = 0;
    free(line);
    return list;
}

//função que executa todas as queries pedidas
void execute_query(Querys *query_list, U_data *data, D_data *drivers_table, R_data *r_data){   
    if (query_list[0].id == 0) {free(query_list);return;}
    int maxQ2 = -1;
    for (int i =0; query_list[i].id != 0;i++){
        if(query_list[i].nquery =='2')
            maxQ2 = MAX(maxQ2,atoi (query_list[i].arguments));
    } 
    Drivers *drivers = D_getTable(drivers_table);
    Users *users_table = U_getTable(data);
    
    for (int j =0; query_list[j].id != 0;j++) 
        switch (query_list[j].nquery){
            case '1' : 
            profile_resume (query_list[j].arguments, drivers, users_table, query_list[j].id, RgetD_limit(r_data));
                        break; //query1 
            case '2' : 
            escreve_file(query_list[j].arguments, drivers_table, query_list[j].id, getD_limit_drivers(drivers_table));
                        break; //query2
            case '3' : 
            printFile(query_list[j].arguments, data, query_list[j].id, getU_limit(data)); 
                        break; //query3 
            case '4' :
            escreve_ficheiro4_Rides(query_list[j].arguments, r_data, query_list[j].id);
                        break; // query4
            case '5' :
            escreve_ficheiro5(query_list[j].arguments, r_data, query_list[j].id);
                        break; // query5
            case '6' :
            char *cidade = strdup(query_list[j].arguments);
            (strtok(cidade, " "));
            escreve_ficheiro6(r_data,cidade,&query_list[j].arguments[strlen(cidade)+1], query_list[j].id);
            free(cidade);
                        break; // query6
            case '7' :
            char *topn = strdup(query_list[j].arguments);
            (strtok(topn, " "));
            escreve_file_query7(topn,&query_list[j].arguments[strlen(topn)+1], r_data, drivers, query_list[j].id);
            free(topn);
                        break; // query7

            case '8':
            Query8(query_list[j].arguments, r_data, drivers, users_table, query_list[j].id);
            break; // query8

            case '9' :
            char *data = strdup(query_list[j].arguments);
            (strtok(data, " "));
            query9_sort_distance(data,&query_list[j].arguments[strlen(data)+1], r_data, query_list[j].id);
            free(data);
                        break;
            default: break;
        }
    if (maxQ2 != -1)
    free (query_list);
}
