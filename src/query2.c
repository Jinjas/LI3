#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/drivers.h"
#include "../include/utilities.h"
#include "../include/query2.h"

/*Esta função escreve no file a table da query2*/
void escreve_file(char *x, D_data *table, int linha, int d_limit){
    int n = atoi (x);
    FILE *file; 
    char* filename = (char*)malloc(255 * sizeof(char)); 
    strcpy(filename, "Resultados/command");
    char *file_number = (char*)malloc((linha/2 + 2) *sizeof(char));
    sprintf(file_number,"%d",linha);

    strcat(strcat(filename,file_number), "_output.txt");

    if((file = fopen(filename, "w")) == NULL){
        printf("Erro a abrir file");
    }
    Drivers *drivers;
    char *nome;
    int id;
    double score;
    int top;
    if(n < d_limit){top = n;}
    else{top = d_limit;}
    for (int j = 0; j < top; j++){
        drivers = D_get_Drivers_Organized_by_Score(table, j);
        nome = getD_name (drivers, 0);
        id = getD_id(drivers,0);
        score = getD_mscore(drivers,0);
        fprintf(file, "%012d;%s;%.3f\n", id, nome, score);

        free (nome);
       
    }
    fclose(file);
    free(filename);
    free(file_number); 
}