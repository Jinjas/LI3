#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/drivers.h"
#include "../include/utilities.h"
#include "../include/users.h"   
#include "../include/rides.h"
#include <ctype.h>

/*Função que dá o resumo do perfil, guardando em variáveis os parâmetros pedidos se a conta do drivers ou do utilizador for ativa caso a conta for
inativa apenas abrimos um file vazio*/
void profile_resume(char *x, Drivers *drivers, Users *users, int linha, int d_limit){
    char *nome;
    char genero;
    int idade;
    double avaliacao;
    int viagens;
    double money;
    int string = 0;
        
    FILE *file; 
    char* filename = (char*)malloc(255 * sizeof(char)); 
    strcpy(filename, "Resultados/command");
    char *file_number = (char*)malloc((linha/2 + 2) *sizeof(char));
    sprintf(file_number,"%d",linha);
    strcat(strcat(filename,file_number), "_output.txt");

    for (int i = 0; x[i] != '\0'; i++){
        if ((x[i] < '0') || (x[i] > '9')){
            string = -1;
            break;
        }
    }

    if (string == 0){
        int id = atoi (x) -1;
        if (id > d_limit) file = fopen(filename, "w");
        else{

            if((file = fopen(filename, "w")) == NULL){
                printf("Erro a abrir file\n");
            }
            char account_status = getD_account_status(drivers, id);
            if (account_status == 'a' || account_status == 'A'){

                nome = getD_name(drivers, id);
                genero = getD_gender(drivers, id);
                idade = getD_age(drivers, id);
                avaliacao = getD_mscore(drivers, id);
                viagens = getD_total_rides(drivers, id);
                money = getD_money(drivers, id);
                
                fprintf(file, "%s;%c;%d;%.3f;%d;%.3f\n", nome, genero, idade, avaliacao, viagens, money);
                free(nome);
            }
        }
    }
    else{
        char account_status = u_getAccountStatus(users, x);

        if((file = fopen(filename, "w")) == NULL){
            printf("Erro a abrir file\n");
        }
        if (account_status == 'a' || account_status == 'A'){

            nome = u_getName(users, x);
            genero = u_getGender(users, x);
            idade = u_getAge(users, x);
            avaliacao = u_getScore(users, x);
            viagens = u_getTotalRides(users, x);
            money = u_getMoneyWasted(users, x);

            fprintf(file, "%s;%c;%d;%.3f;%d;%.3f\n", nome, genero, idade, avaliacao, viagens, money);
            free(nome);
        }
    }
    free(filename);
    fclose(file);
    free(file_number);
}













