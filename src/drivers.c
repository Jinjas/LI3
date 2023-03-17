#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../include/drivers.h"
#include "../include/utilities.h"

typedef struct drivers_Table
{
    unsigned int driver_id; 
    char *name;
    unsigned char age;
    char car_class;
    char *city;
    unsigned int account_creation_date;
    char account_age;
    char account_status;
    char gender;
    unsigned int total_score;
    unsigned int total_distance;
    double money; 
    double total_rides;
    int lastRide;
}Drivers;

typedef struct organized_by_score_drivers{
 Drivers *adress;
 double score;
}DS;

typedef struct d_data{
  unsigned int size;
  int current_index;
  unsigned int d_limit;
  Drivers *table;
  DS *organized_by_score_drivers;
}D_data;

//ordena todos os condutores pela avaliação média, data e id
int D_partitions_by_score(DS *array, int low, int high){
      DS aux;
 double pivot = array[high].score;
 unsigned int id = array[high].adress->driver_id;
  int i = (low -1);

  for (int j = low; j < high; j++) {
    int comparadatas = compareDates(array[j].adress->lastRide, array[high].adress->lastRide);
    if((array[j].score > pivot) || ((array[j].score == pivot) && (comparadatas == 0)) || ((array[j].score == pivot) && (comparadatas == -1) && (array[j].adress->driver_id < id))){
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

//quicksort dos condutores
void D_sort_by_score(DS *array, int low, int high){
   if (low < high) {

    int pi = D_partitions_by_score(array, low, high);
    
    D_sort_by_score(array, low, pi - 1);
    
    D_sort_by_score(array, pi + 1, high);
  }
}

//função que inicializa a variável score do array organized_by_score_drivers a partir dos endereços
void D_initializeScore(D_data *data){
  const unsigned int max = data[0].current_index;
   Drivers *drivers;
  for(int i = 0; i <= max; i++){
    drivers = data[0].organized_by_score_drivers[i].adress;
   if(drivers->total_rides == 0){
   data[0].organized_by_score_drivers[i].score = 0;
   } else{
    data[0].organized_by_score_drivers[i].score = ((drivers->total_score)/drivers->total_rides);
   } 
  }
}

//função que inicializa o array organized_by_score_drivers e ordena a partir do quicksort
void D_sortAll(D_data *data){
  if(data[0].current_index > 0){
  D_initializeScore(data);
  D_sort_by_score(data[0].organized_by_score_drivers, 0, data[0].current_index);
  }
}


DS* D_data_memory_expansion(D_data *data){
  DS *aux = (DS*)realloc(data[0].organized_by_score_drivers, data[0].size * sizeof(DS));
  if((aux == NULL)){
     printf("Realloc do drivers \n");
  }
 return aux;
} 

//função que dá ao array organized_by_score_drivers os respetivos endereços
void addAdresses_drivers(D_data *data, Drivers* drivers){
   data[0].current_index++;
 data[0].organized_by_score_drivers[data[0].current_index].adress = drivers;
} 

D_data* new_D_data(){
  D_data *data = (D_data*)malloc(sizeof(D_data));
 data[0].size = 10010;
 data[0].current_index = -1;
 data[0].organized_by_score_drivers = (DS*)malloc(10010 * sizeof(DS));
 data[0].table = (Drivers*)malloc(10010 * sizeof(Drivers));
  return data;
}

void d_InicializeNode(Drivers *drivers, char**parsed, int id){
  drivers->driver_id = id;
  drivers->name = strdup(parsed[1]);
  drivers->age = calculateAge(calculateDate(parsed[2]));
  drivers->gender = parsed[3][0];
  drivers->car_class = parsed[4][0];
  drivers->city = strdup(parsed[6]);
  drivers->account_creation_date = calculateDateToCompare(parsed[7]);
  drivers->account_age = calculateAgeToCompare(drivers->account_creation_date);
  drivers->account_status = parsed[8][0];
  drivers->total_distance = 0;
  drivers->total_rides = 0;
  drivers->total_score = 0;
  drivers->money = 0;
}

void memoryExpansion (D_data* data, int size){
    Drivers* aux = (Drivers*)realloc(data->table, size * sizeof(Drivers));
    if (aux != NULL){
       data->table = aux;
    } else { printf("Realloc Falhou, retrying ...\n");
     memoryExpansion(data, size);
    }
}
//cria um novo nodo para o drivers
void* d_addNode(D_data *data, FILE *file,  char *line, char *word){
   char **parsed = Parser(file, line);
    if(!feof(file)){
      //inicio da validação
      if(((parsed[0][0] != '\0')) && ((parsed[1][0] != '\0')) &&((parsed[2][0] != '\0')) &&((parsed[3][0] != '\0')) &&((parsed[4][0] != '\0')) &&((parsed[5][0] != '\0')) &&((parsed[6][0] != '\0')) && ((parsed[7][0] != '\0')) && ((parsed[8][0] != '\0')) ){
        if(validateDates(parsed[2]));
        else{
          FreeParsed(parsed,9);
                free(parsed);
          return 0;
        }

        if(validateDates(parsed[7]));   
        else{
          FreeParsed(parsed,9);
                free(parsed);

          return 0;
        }
          if((parsed[8][0]=='a'||parsed[8][0]=='A') && (parsed[8][1]=='c'||parsed[8][1]=='C') && (parsed[8][2]=='t'||parsed[8][2]=='T') && (parsed[8][3]=='i'||parsed[8][3]=='I') && (parsed[8][4]=='v'||parsed[8][4]=='V') && (parsed[8][5]=='e'||parsed[8][5]=='E') && parsed[8][6]=='\0');
          else if((parsed[8][0]=='i'||parsed[8][0]=='I') && (parsed[8][1]=='n'||parsed[8][1]=='N') && (parsed[8][2]=='a'||parsed[8][2]=='A') && (parsed[8][3]=='c'||parsed[8][3]=='C') && (parsed[8][4]=='t'||parsed[8][4]=='T') && (parsed[8][5]=='i'||parsed[8][5]=='I') && (parsed[8][6]=='v'||parsed[8][6]=='V') && (parsed[8][7]=='e'||parsed[8][7]=='E') && parsed[8][8]=='\0');
          else {
            FreeParsed(parsed,9);
            free(parsed);
            return 0;
          }
          if((parsed[4][0]=='p'||parsed[4][0]=='P') && (parsed[4][1]=='r'||parsed[4][1]=='R') && (parsed[4][2]=='e'||parsed[4][2]=='E') && (parsed[4][3]=='m'||parsed[4][3]=='M') && (parsed[4][4]=='i'||parsed[4][4]=='I') && (parsed[4][5]=='u'||parsed[4][5]=='U') && (parsed[4][6]=='m'||parsed[4][6]=='M') && parsed[4][7]=='\0');         
          else if((parsed[4][0]=='g'||parsed[4][0]=='G') && (parsed[4][1]=='r'||parsed[4][1]=='R') && (parsed[4][2]=='e'||parsed[4][2]=='E') && (parsed[4][3]=='e'||parsed[4][3]=='E') && (parsed[4][4]=='n'||parsed[4][4]=='N') && parsed[4][5]=='\0');         
          else if((parsed[4][0]=='b'||parsed[4][0]=='B') && (parsed[4][1]=='a'||parsed[4][1]=='A') && (parsed[4][2]=='s'||parsed[4][2]=='S') && (parsed[4][3]=='i'||parsed[4][3]=='I') && (parsed[4][4]=='c'||parsed[4][4]=='C') && parsed[4][5]=='\0');         
          else {
          FreeParsed(parsed,9);
          free(parsed);
          return 0;
          }
      //fim da validação
    const int index = atoi(parsed[0])-1;
    if(index >= data->size - 1){  
      data[0].size *= 10;
      const int size = data[0].size;
        memoryExpansion(data, size);
        for(int i = index; i < size; i++)
        data[0].table[i].account_status = '\0';
       data[0].organized_by_score_drivers = D_data_memory_expansion(data);
       int aux = 0;
          for(int k = 0; k < index; k++){
          if((data[0].table[k].account_status == 'a') || (data[0].table[k].account_status == 'A')){ 
            data[0].organized_by_score_drivers[aux].adress = &data[0].table[k];
            aux++;
          }
          }
    }
    d_InicializeNode(&data[0].table[index], parsed, index+1);
    data[0].d_limit = data[0].table[index].driver_id;
    if((data[0].table[index].account_status == 'a') || (data[0].table[index].account_status == 'A'))
    addAdresses_drivers(data, &(data[0].table[index]));
    
    }else {
      FreeParsed(parsed, 9);
      free(parsed);
      return 0;
    }
    for (int k = 0; k < 9; k++){
      free(parsed[k]);
    }
    }
        free(parsed);
}

D_data *d_createTable(FILE *file){
  D_data *data = new_D_data();
      char *line = (char*)malloc(850 * sizeof(char));
   char *word;
    size_t j = 850;
     getline(&line, &j, file);
    int iterations = 0;
    while(!feof(file)){
        d_addNode(data, file, line, word);
      }
      free(line);
   return data;
}

//serve para acrescentar valores dos drivers, provenientes do parser das rides 
void d_addValue (int id, int distance, int score, double tip, int lastride, D_data* currentTable, unsigned char *age, int *date, char*gender){
  if(id >=  currentTable->size) return;
  currentTable->table[id].total_distance += distance;
   currentTable->table[id].total_score += score;
   currentTable->table[id].total_rides++;
  double arroz = calculate_price(distance,  currentTable->table[id].car_class, tip);
   currentTable->table[id].money += arroz;
   currentTable->table[id].lastRide = get_most_recent_date( currentTable->table[id].lastRide, lastride); 
   *age = currentTable->table[id].account_age;
   *date = currentTable->table[id].account_creation_date;
   if((currentTable->table[id].account_status == 'a') || (currentTable->table[id].account_status == 'A'))
   *gender = currentTable->table[id].gender;
   else    *gender = '\0';
}

//vai buscar o drivers
Drivers* D_getTable(D_data* data){
  return data[0].table;
}

//vai buscar a avaliação média
DS * D_get_Organized_by_score(D_data *data){
 return data[0].organized_by_score_drivers;
}

//vai buscar a avaliação média
Drivers* D_get_Drivers_Organized_by_Score(D_data *data, int n){
  return data[0].organized_by_score_drivers[n].adress;
}

//vai buscar o id 
int getD_id(Drivers *table, int key){
  return table[key].driver_id;
}

//vai buscar a última viagem
 unsigned int getD_lastRide (Drivers *table, int key){
  return table[key].lastRide;
}

//vai buscar a avaliação média
double getD_mscore (Drivers *table, int key){
  double average_rating = 0;
  if(table[key].total_rides)
  average_rating = ((table[key].total_score) / (table[key].total_rides));
  return average_rating;
}

//vai buscar o estado da conta
char getD_account_status (Drivers *table, int key){
  return table[key].account_status;
}

//vai buscar o nome
char* getD_name (Drivers *table, int key){
 return strdup(table[key].name);
}

//vai buscar a classe do carro
char getD_car_class (D_data *table, int key){
  return table->table[key].car_class;
}

//vai buscar a distancia
int getD_total_distance(Drivers *table, int key){
  return table[key].total_distance;
}

//vai buscar o género
char getD_gender (Drivers *table, int key){
  return table[key].gender;
}

//vai buscar o total de viagens
int getD_total_rides (Drivers *table, int key){
  return table[key].total_rides;
}

//vai buscar a idade
unsigned int getD_age(Drivers *table, int key){
  return table[key].age;  
}

//vai buscar o dinhero recebido do condutor
double getD_money(Drivers *table, int key){
  double money = table[key].money;
  return money;
}

//vai buscar o limit do drivers
int getD_limit(D_data *data){
  return data[0].d_limit;
}

//vai buscar o limite do organized_by_score_drivers
int getD_limit_drivers(D_data *data){
  return data[0].current_index;
}

//dá free ao D_data
void d_free(D_data *drivers){
  const int size = drivers[0].size;
  for (int i = 0; i < size; i++){
    if(drivers[0].table[i].account_status != '\0'){
    free(drivers[0].table[i].name);
    free(drivers[0].table[i].city);
    }
  }
  free(drivers[0].organized_by_score_drivers);
  free(drivers[0].table);
  free(drivers);
}

//verifica se está organizado
void checkIfOrganizedrivers(D_data *data){
  const int max = data[0].current_index;
  double ant = 1000000;
  double aux;
  for(int i = 0; i < max; i++){
    if(data->organized_by_score_drivers[i].adress->total_rides != 0){
      aux = ((double)data[0].organized_by_score_drivers[i].adress->total_score)/data[0].organized_by_score_drivers[i].adress->total_rides;
      printf("nome = %s\n", data->organized_by_score_drivers[i].adress->name);
    }
    else{
      aux = 0;
    }
     printf("Score = %f", aux);
     printf("     Ant = %f\n", ant);
     printf("I = %d\n", i);
    if(aux > ant){ printf("F \n"); break;}
    ant = aux;
  }
}

//print ao D_data
void dataPrintDrivers(D_data *data){
  int max = data[0].current_index;
  for(int i = 0; i <= max; i++){
  printf("%d \n", data[0].organized_by_score_drivers[i].adress->driver_id);
  printf("%p \n", data[0].organized_by_score_drivers[i].adress);
  Drivers *aux = data[0].organized_by_score_drivers[i].adress;
  printf("%s \n", aux->name);
  if(aux->total_rides)
  printf("%.3f \n",(((double)aux->total_score) / (aux->total_rides)));
  else printf("0.000 \n");
  printf("_________________________________________________________________________________\n");
  }
}

//debug print da drivers
void *d_printTable(Drivers *table, const int max){
  for(int i = 0; i < max; i++){
      printf("ID = %d\n", table[i].driver_id);
      printf("age = %d\n", table[i].age);
      printf("age = %d\n", calculateAge(table[i].age));
      printf("name = %s\n", table[i].name);
      printf("city = %s\n", table[i].city);
      printf("gender = %c\n", table[i].gender);
      printf("account_status = %c\n", table[i].account_status);
      printf("car_class = %c\n", table[i].car_class);
      printf("Total score = %d\n", table[i].total_score);
      printf("Total rides = %f\n", table[i].total_rides);
      printf("Total distance = %d\n", table[i].total_distance);
      printf("------------------------------------------------------------------\n");
    }
}


