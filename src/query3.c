#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/users.h"
#include "../include/utilities.h"
#include "../include/query3.h"

//função que cria os ficheiros dos outputs com os resultados pretendidos
void printFile(char *x, U_data *data, int linha, int u_limit){
    int n = atoi (x);
    FILE *file; 
    char* filename = (char*)malloc(255 * sizeof(char)); 
    char* output_name = (char*)malloc(15 * sizeof(char));
    strcpy(filename, "Resultados/command");
    char *file_number = (char*)malloc((linha/10 + 2) *sizeof(char));
    sprintf(file_number,"%d",linha);
    strcpy(output_name, "_output.txt");
    Query3 *list;
    strcat(strcat(filename,file_number), output_name);
    
    if((file = fopen(filename, "w")) == NULL){
        printf("Erro a abrir file");
    }
    Users* user;
    char *username;
    char *name;
    int top;
    if(n < u_limit){top = n;}
    else{top = u_limit;}
    for (int j = 0; j < top; j++){
        user = U_get_User_Organized_by_Distance(data, j);
        username = U_getUsername(user, 0);
        name = U_getNamebyIndex(user, 0);
        fprintf(file, "%s;%s;%d\n", username, name, U_getdistancebyIndex(user,0));
        free(name);
        free(username);
    }
    fclose(file);
    free(filename);
    free(output_name);  
    free(file_number);
}

