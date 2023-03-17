#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/utilities.h"
#include "../include/rides.h"

//função que cria os ficheiros dos outputs com os resultados pretendidos
void escreve_ficheiro6(R_data *viagens, char*cidade, char *datas, int linha){
    datas[10] ='\0';//00/00/0000\0
    int dataI;
    int dataF;
    dataI = calculateDateToCompare(datas);
    dataF = calculateDateToCompare(&datas[11]);
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

    double media;
    if (dataI>dataF)
        media = getDistMed(viagens,dataF, dataI, cidade);
    else media = getDistMed(viagens,dataI, dataF, cidade);
    if(media != -1)
        fprintf(file, "%.3f\n", media);
    fclose(file);
    free(filename);
    free(file_number);
    free(output_name);  
    return;
}


