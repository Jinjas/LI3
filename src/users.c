#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../include/users.h"
#include "../include/utilities.h"
typedef struct users_Table
{
    unsigned int identifier;
    unsigned short int size;
    char *username;
    char *name;
    unsigned char age;
    unsigned int account_creation_date;
    unsigned char account_age;
    unsigned int last_ride;
    double money_wasted;
    unsigned short int total_rides;
    unsigned int total_distance;
    unsigned int total_score;
    char gender;
    char account_status;

    struct users_Table* copycats;
}Users;

typedef struct organized_by_distance{
   Users *adress;
   unsigned int distance;
}UD;
typedef struct u_data{
  unsigned int size;
  int current_index;
  Users * table;
  UD *organized_by_distance;
}U_data;

//Função de realloc do Users
void u_memoryExpansion(Users** table, int size){
    Users* aux = (Users*)realloc(*table, size * sizeof(Users));
    if (aux != NULL){
       *table = aux;
    } else  printf("Realloc Falhou \n");
}

//Função auxiliar do quicksort
int U_partitions_by_distance(UD *array, int low, int high){
  const unsigned int pivot = array[high].distance;
      UD aux;

  int i = (low -1);
  int cD = 0;

  for (int j = low; j < high; j++) {
    cD = compareDates(array[j].adress->last_ride, array[high].adress->last_ride);
    if((array[j].distance > pivot) || ((array[j].distance == pivot) && ((cD ==0) || ((cD < 0) && (strcmp(array[j].adress->username, array[high].adress->username) < 0))))){
      i++;
      aux = array[i];
      array[i] = array[j];
      array[j] = aux;
    }
  }
      aux = array[i+1];
      array[i+1] = array[high];
      array[high] = aux;
  return i+1;
}

//Função que organiza por distância usando realloc
void U_sort_by_distance(UD *array, int low, int high){
   if (low < high) {
    int pi = U_partitions_by_distance(array, low, high);
    U_sort_by_distance(array, low, pi - 1);
    U_sort_by_distance(array, pi + 1, high);
  }
}

//Função que inicializa o array de endereços para a query 3
void U_initializeAll(U_data *data){
  const unsigned int max = data[0].current_index;
   Users *user;
  for(int i = 0; i <= max; i++){
    user = data[0].organized_by_distance[i].adress;
    data[0].organized_by_distance[i].distance = user->total_distance;
  }
}

//Função que initializa e ordena a estrutura para a query 3 usando quick sort
void U_sortAll(U_data *data){
  if((data[0].current_index > 0)){
  U_initializeAll(data);
  U_sort_by_distance(data[0].organized_by_distance, 0, data[0].current_index);
  }
}

//Função de realloc do array de endereços
U_data* U_data_memory_expansion(U_data *data){
  data[0].size *= 10;
  data[0].organized_by_distance = (UD*)realloc(data[0].organized_by_distance, data[0].size * sizeof(UD));
  if((data[0].organized_by_distance == NULL)) printf("Realloc falhou\n");
  return data;
} 

//Função que adiciona os endereços dos users ao array de endereços
void addAdresses(U_data *data, Users* user, int index){
  if(index > data[0].size) U_data_memory_expansion(data);
 data[0].organized_by_distance[index].adress = user;
}

//Função que cria um novo U_data
U_data* new_U_data(){
  U_data *data = malloc(sizeof(U_data));
 data[0].size = 1000001;
 data[0].current_index = -1;
 data[0].organized_by_distance = (UD*)malloc(1000001 * sizeof(UD));
 data[0].table = (Users*)calloc(RPrime, sizeof(Users));
  return data;
}

//Função que inicializa um utilizador 
void u_InicializeNode(Users *user, char**parsed, int identifier){
  user->username = strdup(parsed[0]);
  user->name = strdup(parsed[1]);
  user->gender = parsed[2][0];
  user->age = calculateAge(calculateDate(parsed[3]));
  user->account_creation_date = calculateDateToCompare(parsed[4]);
  user->account_age = calculateAgeToCompare(user->account_creation_date);
  user->account_status = parsed[6][0];
  user->identifier = identifier;
}

/*Esta função serve para adicionar um user à hash table. Esta função pode ser dividida em duas partes, a primeira é o que fazer se a key apontar para um endereço não inicializado,
e a segunda é o que fazer se apontar para um valor já inicalizado*/
char u_addNode(U_data *data, FILE *file,  char *line, char *word){
  char **parsed = Parser(file, line);
  if(!feof(file)){
    //inicio da verificação
    if(((parsed[0][0] != '\0')) && ((parsed[1][0] != '\0')) &&((parsed[2][0] != '\0')) &&((parsed[3][0] != '\0')) &&((parsed[4][0] != '\0')) &&((parsed[5][0] != '\0')) &&((parsed[6][0] != '\0'))){
      if(validateDates(parsed[3]));
      else{
        FreeParsed(parsed, 7);
              free(parsed);
        return 0;
      }
      if(validateDates(parsed[4]));
      else{
          FreeParsed(parsed, 7);
                free(parsed);
          return 0;
      }
      if((parsed[6][0]=='a'||parsed[6][0]=='A') && (parsed[6][1]=='c'||parsed[6][1]=='C') && (parsed[6][2]=='t'||parsed[6][2]=='T') && (parsed[6][3]=='i'||parsed[6][3]=='I') && (parsed[6][4]=='v'||parsed[6][4]=='V') && (parsed[6][5]=='e'||parsed[6][5]=='E') && (parsed[6][6]=='\0' || parsed[6][6]=='\n'));
      else if((parsed[6][0]=='i'||parsed[6][0]=='I') && (parsed[6][1]=='n'||parsed[6][1]=='N') && (parsed[6][2]=='a'||parsed[6][2]=='A') && (parsed[6][3]=='c'||parsed[6][3]=='C') && (parsed[6][4]=='t'||parsed[6][4]=='T') && (parsed[6][5]=='i'||parsed[6][5]=='I') && (parsed[6][6]=='v'||parsed[6][6]=='V') && (parsed[6][7]=='e'||parsed[6][7]=='E') && (parsed[6][8]=='\0' || parsed[6][6]=='\n'));
      else {
        FreeParsed(parsed,7);
              free(parsed);
        return 0;
      }
        int key = calculateIdentifier(parsed[0]);
        if (data->table[key].account_status == '\0'){
          //primeira parte
          //Regista os parâmetros do user na posição dada pela chave
          u_InicializeNode(&data[0].table[key], parsed, 0);
          if((data->table[key].account_status == 'a') || (data->table[key].account_status == 'A')){
          addAdresses(data, &(data[0].table[key]), ++data[0].current_index);
          }
        }else{
          //Segunda parte da função
          //Procura a primeira posição livre no copycats e regista o user aí
          if(data->table[key].size == 0){
            data[0].table[key].size = 3;
            data[0].table[key].copycats = (Users*)calloc(data->table[key].size, sizeof(Users));
          }
          else if(data->table[key].identifier ==data[0].table[key].size -1) {
            const int aux = data[0].table[key].size;
            data[0].table[key].size =data[0].table[key].size << 1;
            u_memoryExpansion(&data->table[key].copycats,data[0].table[key].size);
            for(int k = 0; k < aux; k++){
              if((data[0].table[key].copycats[k].account_status == 'a') || (data[0].table[key].copycats[k].account_status == 'A'))
              addAdresses(data, &data[0].table[key].copycats[k], data[0].table[key].copycats[k].identifier);
            }
            for(int k = aux; k < aux*2; k++){
              data[0].table[key].copycats[k].account_status = '\0';
              data[0].table[key].copycats[k].total_distance = 0;
              data[0].table[key].copycats[k].total_rides = 0;
              data[0].table[key].copycats[k].total_score = 0;
              data[0].table[key].copycats[k].money_wasted = 0;      
            }
          }
          u_InicializeNode(&data[0].table[key].copycats[data[0].table[key].identifier], parsed, ++data[0].current_index);
          if((data[0].table[key].copycats[data[0].table[key].identifier].account_status == 'a') || (data[0].table[key].copycats[data[0].table[key].identifier].account_status == 'A')){
          addAdresses(data, &(data[0].table[key].copycats[data[0].table[key].identifier]), data[0].current_index);
          }else {
            data[0].current_index--;
          }
          data[0].table[key].identifier++;
        }
        for (int k = 0; k < 7; k++){
          free(parsed[k]);
        }
    }
    else{
      FreeParsed(parsed,7);
      free(parsed);
      return 0;
    }
  }
  free(parsed);
  return 1;
}

//Cria a hash table dinâmica do users
U_data *u_createTable(FILE *file){
  U_data *data = new_U_data();
      char *line = (char*)malloc(850 * sizeof(char));
   char *word;
    size_t j = 850;
     getline(&line, &j, file);
    while(!feof(file)){
        if(u_addNode(data, file, line, word));
      }
      free(line);
   return data;
}

//Retorna o indice do copycats, onde se encontra o username recebido. Se não encontrar retorna o primeiro indice não inicializado
int findCopycats(Users *copycats, char* username){
  int i = 0;
  for(; copycats[i].account_status != '\0'; i++){
    if(strcmp(copycats[i].username, username) == 0) break;
  }
  return i;
}

//Retorna o user correspondente ao username recebido, retorna um username vazio se não encontrar;
Users getUser(Users *table, char* username){
  int key = calculateIdentifier(username); 
  if (table[key].account_status != '\0')
  if (strcmp(table[key].username, username) == 0){
    return table[key];
  }else{
    if(table[key].size){
    int copycatkey = findCopycats(table[key].copycats, username);
    return table[key].copycats[copycatkey];
    }
  }
      Users user;
      user.account_status = '\0';
      user.username = strdup("\0");
      user.name = strdup("\0");
      user.age = 0;
      user.account_creation_date = 0;
      user.total_distance = 0;
      user.gender = '\0';
      user.last_ride = 0;
      user.total_score = 0;
      user.money_wasted = 0;
      return user;
}


//Esta função serve para alterar os valores estatísticos da tabela fora do ficheiro de origem
void u_addvalue(Users* table, char*username, double cash, int avaliation, int distance, unsigned int last_ride, unsigned char *age, int *date, char *gender){
    int key = calculateIdentifier(username); 
    if(!(table[key].username)){ 
      printf("This wasn't supposed to happen, the cause was this username -> %s", username);
      return;
      }
  if (strcmp(table[key].username, username) == 0){
    table[key].money_wasted += cash;
    table[key].total_score += avaliation;
    table[key].total_distance += distance;
    table[key].total_rides++;
    *age = table[key].account_age;
    *date = table[key].account_creation_date;
    if((table[key].account_status == 'a') || (table[key].account_status == 'A'))
    *gender = table[key].gender;
    else *gender = '\0';
      if (compareDates(table[key].last_ride, last_ride) == 1)
  table[key].last_ride = last_ride; 
  }else{
    int copycatkey = findCopycats(table[key].copycats, username);
     table[key].copycats[copycatkey].money_wasted += cash;
     table[key].copycats[copycatkey].total_score += avaliation;
     table[key].copycats[copycatkey].total_rides++;
     table[key].copycats[copycatkey].total_distance += distance;
     *age = table[key].copycats[copycatkey].account_age;
     *date = table[key].copycats[copycatkey].account_creation_date;
     if((table[key].copycats[copycatkey].account_status == 'a') || (table[key].copycats[copycatkey].account_status == 'A'))
     *gender = table[key].copycats[copycatkey].gender;
     else *gender = '\0';
     if (compareDates(table[key].copycats[copycatkey].last_ride, last_ride) == 1)
      table[key].copycats[copycatkey].last_ride = last_ride; 
  }
}

char *u_getName(Users *users, char * username){
  Users aux = getUser(users, username);
  char * string = strdup(aux.name);
  return string;
}

int u_getAge(Users *users, char *username){
   Users aux = getUser(users, username);
   return aux.age;
}

Users *u_getcopycats(Users *users, char*username){
   Users aux = getUser(users, username);
   return aux.copycats;
}

char* U_getUsername(Users *users, int index){
 return strdup(users[index].username);
}

char u_getGender(Users *users, char*username){
  Users aux = getUser(users, username);
  return aux.gender;
}

double u_getMoneyWasted(Users* users, char*username){
     Users aux = getUser(users, username);
     return aux.money_wasted;
}

int u_getTotalRides(Users* users, char*username){
       Users aux = getUser(users, username);
       return aux.total_rides;
}

double u_getScore(Users* users, char*username){
     Users aux = getUser(users, username);
     if(aux.total_rides == 0) return 0; else
     return ((double)(aux.total_score)/(aux.total_rides));
}

char u_getAccountStatus (Users *users, char *username){
  Users aux = getUser(users, username);
       return aux.account_status;
}


int getU_total_distance(Users *users, char* username){
  Users aux = getUser(users, username);
  return aux.total_distance;
}

unsigned int getU_last_ride (Users *users, char* username){
  Users aux = getUser(users, username);
  return aux.last_ride;
}

char * U_getNamebyIndex(Users *users, int index){
 return strdup(users[index].name);
}

int U_getdistancebyIndex(Users *users, int index){
  return users[index].total_distance;
}
int U_getTotalRidesbyIndex(Users *users, int index){
  return users[index].total_rides;
}

unsigned int U_getlast_ridebyIndex(Users *users, int index){
  return users[index].last_ride;
}

char U_getAccountStatusbyIndex(Users *users, int index){
  return users[index].account_status;
}

Users * u_getcopycatsByIndex(Users *users, int index){
 return users[index].copycats;
}

int u_getIdentifierByIndex(Users *users, int index){
  return users[index].identifier;
}

int u_getSizeByIndex(Users *users, int index){
  return users[index].size;
}

Users* U_getTable(U_data* data){
  return data[0].table;
}

UD* U_get_Organized_by_distance(U_data *data){
 return data[0].organized_by_distance;
}

Users* U_get_User_Organized_by_Distance(U_data *data, int n){
  return data[0].organized_by_distance[n].adress;
}

int getU_limit(U_data *data){
  return data[0].current_index;
}
void u_free(U_data *data){
  for (int i = 0; i < RPrime; i++){
    if(data[0].table[i].account_status != '\0'){
      free(data[0].table[i].name);
      free(data[0].table[i].username);
    for(int k = 0; k < data[0].table[i].size; k++){
      if(data[0].table[i].copycats[k].account_status == '\0') break;
      free(data[0].table[i].copycats[k].name);
      free(data[0].table[i].copycats[k].username);
    }
    free(data[0].table[i].copycats);
    }
  }
  free(data[0].table);
  free(data[0].organized_by_distance);
  free(data);
}

void u_print(Users *table){
  int users = 0;
  for(int i = 0; i < RPrime; i++){
    if(table[i].account_status != '\0'){
      users++;
      printf("Users %s \n", table[i].username);
      if(table[i].size >0){
        int aux = table[i].identifier;
      for(int k = 0; k < aux; k++){
        users++;
        printf("COPYCATS %s \n", table[i].copycats[k].username);
      }
      }
    }

  }
  printf("Iterations %d \n", users);
}

void dataPrint(U_data *data){
  int max = data[0].current_index;
  printf("max = %d \n\n", max);
  for(int i = 0; i < max; i++){
  printf("%d \n", i);
  printf("%p \n", data[0].organized_by_distance[i].adress);
  Users *aux = data[0].organized_by_distance[i].adress;
  printf("%s \n", aux->name);
  printf("_________________________________________________________________________________\n");
  }
}