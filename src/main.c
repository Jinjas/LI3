#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../include/drivers.h"
#include "../include/rides.h"
#include "../include/users.h"
#include "../include/query_handler.h"
#include "../include/query4.h"
#include "../include/interactive.h"
 
int main (int argc, char **argv){
  if(argc == 1){
    //Modo interativo
    interactivemode();
    return 0;
  }
  else if (argc < 2){
    printf("este executável foi chamado com um número de argumentos inferior ao necessário.\n");
    return 1;
  }
  else {
    //Modo batch
    char *aux = (char*)malloc(1000* sizeof(char));
    strcpy(aux, argv[1]);
    strcat(aux, "/users.csv");
    FILE *users =  fopen(aux, "r");
    U_data* users_table = u_createTable(users);
    fclose(users);
    strcpy(aux, argv[1]);
    strcat(aux, "/drivers.csv");
    FILE *drivers =  fopen(aux, "r");
    D_data *drivers_table = d_createTable(drivers);
    fclose(drivers);
    strcpy(aux, argv[1]);
    strcat(aux, "/rides.csv");
    FILE *queries = fopen(argv[2],"r");
    void *query_list = q_createqueryslist(queries); 
    FILE *rides =  fopen(aux, "r");
    R_data *r_data = updateTables(rides, drivers_table, U_getTable(users_table));
    fclose(rides);
    D_sortAll(drivers_table);
    U_sortAll(users_table);
    City_sortDrivers(r_data, D_getTable(drivers_table), 100);
    execute_query(query_list, users_table, drivers_table, r_data);
    fclose(queries);
    d_free(drivers_table);
    u_free(users_table);
    R_free(r_data);
    free(aux);
    return 0;
  }
}