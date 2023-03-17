#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/utilities.h"
#include "../include/rides.h"

//função que cria os ficheiros dos outputs com os resultados pretendidos
void escreve_ficheiro4_Rides(char *city, R_data *r_data, int linha){
    FILE *file; 
    char* filename = (char*)malloc(255 * sizeof(char)); 
    char* output_name = (char*)malloc(15 * sizeof(char));
    strcpy(filename, "Resultados/command");
    char *file_number = (char*)malloc((linha/2 + 2) *sizeof(char));
    sprintf(file_number,"%d",linha);
    strcpy(output_name, "_output.txt");
    strcat(strcat(filename,file_number), output_name);
    if((file = fopen(filename, "w")) == NULL){
        printf("Erro a abrir file");
    }
    if(existe_city(city, r_data)){
    double media;
    media = (get_City_money(r_data, city))/(get_City_totalrides(r_data, city));
        fprintf(file, "%.3f\n", media);
    }
    fclose(file);
    free(filename);
    free(file_number);
    free(output_name);  
    return;
    printf("its not supose to get here\n(error:escreve_ficheiro)\n");
}
