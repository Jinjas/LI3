#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/drivers.h"
#include "../include/utilities.h"
#include "../include/users.h"
#include "../include/rides.h"

//função que cria os ficheiros dos outputs com os resultados pretendidos
void escreve_file_query7(char *x, char *city, R_data *r_data, Drivers *drivers, int linha){
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
    char *nome;
    int id;
    double avaliação_driver;
    int top;
    if(n < get_City_DriversScore_limit(r_data, city)){ top = n;}
    else{ top = get_City_DriversScore_limit(r_data, city);}
    if(existe_city(city, r_data) == 1){
    for (int j = 0; j < top; j++){
        int id_drivers = get_City_DriversID(r_data, city, j);
        nome = getD_name (drivers, id_drivers);
        avaliação_driver = get_City_DriversScore(r_data, city, j);
        fprintf(file, "%012d;%s;%.3f\n", id_drivers +1, nome, avaliação_driver);

        free (nome);
      }
    }
    fclose(file);
    free(filename);
    free(file_number); 
}