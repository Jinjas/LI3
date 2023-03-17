#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/utilities.h"
#include "../include/users.h"
#include "../include/query6.h" 
#define Data_de_referência 752100

typedef struct rides{
 unsigned int viagem;
 unsigned int d_id; 
 char *date;
 unsigned int data;
 char *username;
 double tip;
 unsigned char distance;
}Rides;
typedef struct city_driver
{
  unsigned short int total_rides;
  double total_score;
  unsigned int total_distance;
}city_driver;
typedef struct organized_by_score_city_drivers{
 city_driver *adress;
 double score;
 unsigned int id;
}CDS;
typedef struct cities
{
 city_driver *c_driver;
 unsigned int total_rides;
 double total_money;
 unsigned int row;
 unsigned int index;
 Rides **rides;
 char *name;
 unsigned int size;
 struct cities *copycats;
 unsigned char copycats_size;
 CDS *organized_by_score_city_drivers;
 int current_index_query7;
}Cities;

typedef struct q9{
Rides *viagem;
Cities *city;
unsigned int date;
unsigned char distance;
}Q9;

typedef struct organized_by_distance_query9{
 Q9 *adress;
 unsigned char distance;
}Q9D;
typedef struct q8{
unsigned int D_date;
unsigned int U_date;
Rides *ride;
}Q8;

typedef struct custoDeCadaDia{
    double price;
    int ntravels;
    unsigned int q9_index;
    unsigned int q9_size;
    Q9 *q9_array;
    unsigned int q8f_index;
    unsigned int q8f_size;
    Q8 *q8f_array;
    unsigned int q8m_index;
    unsigned int q8m_size;
    Q8 *q8m_array;
}Day_list;
typedef struct r_data{
 Cities *cities;
 unsigned int d_limit;
 unsigned int current_size_day_list;
 Day_list *daylist;
}R_data;

//Realloc da query 8
void memoryexpansionQ8(Q8 **q8, int size){
  Q8 *aux = (Q8*)realloc(q8[0], size * sizeof(Q8)); 
  if(aux == NULL) printf("Realloc Q8 falhou \n");
  else q8[0] = aux;
}

//inicializa o array da q8 feminino para o ano passado como argumento.
void initializeQ8F(R_data *data, int year, int d_limit){
 data->daylist[year].q8f_size = 3 * d_limit;
 data->daylist[year].q8f_array = (Q8*)malloc(data->daylist[year].q8f_size * sizeof(Q8));
}

//inicializa o array da q8 masculino para o ano passado como argumento.
void initializeQ8M(R_data *data, int year, int d_limit){
 data->daylist[year].q8m_size = 3 * d_limit;
 data->daylist[year].q8m_array = (Q8*)malloc(data->daylist[year].q8m_size * sizeof(Q8));
}

//Função que adiciona dados às estruturas da Q8 presentes no R_data. Se o gênero for feminino adiciona ao q8f_array caso contrário adiciona ao q8m_array
void addQ8(R_data *data, int year, int d_date, int u_date, char gender, Rides * ride){
 if(gender == 'F'){
  if(data->daylist[year].q8f_size == data->daylist[year].q8f_index)
  if(data->daylist[year].q8f_size == 0) initializeQ8F(data, year, data->d_limit);
  else{
    data->daylist[year].q8f_size = data->daylist[year].q8f_size * 1.5;
    memoryexpansionQ8(&data->daylist[year].q8f_array, data->daylist[year].q8f_size);
  }
  data->daylist[year].q8f_array[data->daylist[year].q8f_index].D_date = d_date;
  data->daylist[year].q8f_array[data->daylist[year].q8f_index].U_date = u_date;
  data->daylist[year].q8f_array[data->daylist[year].q8f_index].ride = ride;
  data->daylist[year].q8f_index++;
 }else{
  if(data->daylist[year].q8m_size == data->daylist[year].q8m_index)
  if(data->daylist[year].q8m_size == 0) initializeQ8M(data, year, data->d_limit);
  else{
    data->daylist[year].q8m_size = data->daylist[year].q8m_size * 1.5;
    memoryexpansionQ8(&data->daylist[year].q8m_array, data->daylist[year].q8m_size);
  }
  data->daylist[year].q8m_array[data->daylist[year].q8m_index].D_date = d_date;
  data->daylist[year].q8m_array[data->daylist[year].q8m_index].U_date = u_date;
  data->daylist[year].q8m_array[data->daylist[year].q8m_index].ride = ride;
  data->daylist[year].q8m_index++;
 }
}

//Função que cria um array com os dados pedidos para uma execução da Q8 (só funciona para o gênero masculino)
Q8* loadQ8M(R_data *data, unsigned char year, int* limit){
  int size = (22 - year) * (data->d_limit * 0.60);
  int current_index = 0;
  Q8 *q8 = (Q8*)malloc((22 - year) * (data->d_limit) * sizeof(Q8));
  for ( int i = year; i < 22; i++){
    for(unsigned int k = 0; k < data->daylist[i].q8m_index; k++){
      if(current_index == size){
        size *= size << 1;
        memoryexpansionQ8(&q8, size);
      }
      q8[current_index].D_date = data->daylist[i].q8m_array[k].D_date;
      q8[current_index].U_date = data->daylist[i].q8m_array[k].U_date;
      q8[current_index].ride = data->daylist[i].q8m_array[k].ride;
      current_index++;
    }
  }
  *limit = current_index;
  return q8;
}

//Função que cria um array com os dados pedidos para uma execução da Q8 (só funciona para o gênero feminino)
Q8* loadQ8F(R_data *data, unsigned char year, int* limit){
  int size = (22 - year) * (data->d_limit * 0.60);
  int current_index = 0;
  Q8 *q8 = (Q8*)malloc((22 - year) * (data->d_limit) * sizeof(Q8));
  for (unsigned char i = year; i < 22; i++){
    for(unsigned int k = 0; k < data->daylist[i].q8f_index; k++){
      if(current_index == size){
        size *= size << 1;
        memoryexpansionQ8(&q8, size);
      }
      q8[current_index].D_date = data->daylist[i].q8f_array[k].D_date;
      q8[current_index].U_date = data->daylist[i].q8f_array[k].U_date;
      q8[current_index].ride = data->daylist[i].q8f_array[k].ride;
      current_index++;
    }
  }
  *limit = current_index;
  return q8;
}

//Função auxiliar da Q8_sort_by_distance (é a função responsável pelo sort)
int Q8_partitions_by_date(Q8 *array, int low, int high){
    Q8 aux;
 const unsigned int pivot = array[high].D_date;
  int i = (low -1);
  for (int j = low; j < high; j++) {
    if(array[j].D_date < pivot){
      i++;
      aux = array[i];
      array[i] = array[j];
      array[j] = aux;
    }else if (array[j].D_date == pivot){
      if(array[j].U_date < array[high].U_date){
      i++;
      aux = array[i];
      array[i] = array[j];
      array[j] = aux;
      }else if((array[j].U_date == array[high].U_date) && (array[j].ride->viagem < array[high].ride->viagem)){
           i++;
      aux = array[i];
      array[i] = array[j];
      array[j] = aux;
      }
    }
  }
      aux = array[i+1];
      array[i+1] = array[high];
      array[high] = aux;
  return i+1;
}

//Função que ordena os dados relativos a uma execução da Q8 usando quicksort
void Q8_sort_by_date(Q8 *array, int low, int high){
  if(low < high){
    int pi = Q8_partitions_by_date(array, low, high);
    Q8_sort_by_date(array, low, pi-1);
    Q8_sort_by_date(array, pi+1, high);
  }
}

//Função que escreve o ficheiro associado a uma execução da Q8
void escreve_ficheiro_Q8(Q8 *array, Drivers* drivers, Users* users, int limit, int id){
      FILE *file; 
    char* filename = (char*)malloc(255 * sizeof(char)); 
    strcpy(filename, "Resultados/command");
    char *file_number = (char*)malloc((id/2 + 2) *sizeof(char));
    sprintf(file_number,"%d",id);
    strcat(strcat(filename,file_number), "_output.txt");

    if((file = fopen(filename, "w")) == NULL){
        printf("Erro a abrir file");
    }

    for(int i = 0; i < limit; i++){
      char *u_name = u_getName(users, array[i].ride->username);
      char *d_name = getD_name(drivers, array[i].ride->d_id);
      fprintf(file, "%012d;%s;%s;%s\n", array[i].ride->d_id + 1, d_name, array[i].ride->username, u_name);
      free(u_name);
      free(d_name);
    }
 fclose(file);
 free(filename);
 free(file_number);
}

//Função que executa a Q8 
void Query8(char *linha, R_data *data, Drivers* drivers, Users* users, int id){
  char age, gender;
  gender = linha[0];
  age = atoi(&linha[2]);
  Q8 *array = NULL;
  int limit = 0;
if((age >=  0) && (age < 128)) {
 if(gender == 'F') {
  array = loadQ8F(data, age, &limit);
  if(limit > 0)
  Q8_sort_by_date(array, 0, limit-1);
 }else if (gender == 'M'){
  array = loadQ8M(data, age, &limit);
  if(limit > 0)
  Q8_sort_by_date(array, 0, limit-1);
 }
}
escreve_ficheiro_Q8(array, drivers, users, limit, id);
free(array);
}

//Função auxiliar do quicksort
int Query9_partitions_by_distance(Q9D *array, int low, int high){
  Q9D aux;
 const double pivot = array[high].distance;
  int i = (low -1);
  for (int j = low; j < high; j++) {
    if(array[j].distance > pivot){
      i++;
      aux = array[i];
      array[i] = array[j];
      array[j] = aux;
    }else {
        int comparadatas = compareDates(array[j].adress->date, array[high].adress->date);
        if(((array[j].distance == pivot) && (comparadatas == 0)) || ((array[j].distance == pivot) && (comparadatas == -1) && array[j].adress->viagem->viagem > array[high].adress->viagem->viagem)){
        i++;
        aux = array[i];
        array[i] = array[j];
        array[j] = aux;
        }
    }
  }
      aux = array[i+1];
      array[i+1] = array[high];
      array[high] = aux;
  return i+1;
}

//quicksort das viagens por distância
void Query9_sort_by_distance(Q9D *array, int low, int high){
    if (low < high) {
    int pi = Query9_partitions_by_distance(array, low, high);
    Query9_sort_by_distance(array, low, pi - 1);
    Query9_sort_by_distance(array, pi + 1, high);
  }
}

//função que inicializa a variável distância do array organized_by_distance_query9 a partir do endereço
void Query9_initializeDistance (Q9D *organized_by_distance_query9,  int current_index_query9){
  const  int max = current_index_query9;
  Q9 *q9_array;
  for (int i = 0; i <= max; i++){
    q9_array = organized_by_distance_query9[i].adress;
    organized_by_distance_query9[i].distance = q9_array->distance;
  }
}

//função que inicializa a distancia do array organized_by_score_drivers e ordena a partir do quicksort
void Query9_sortAll(Q9D *organized_by_distance_query9,  int current_index_query9){
  if(current_index_query9 >= 0){
    Query9_initializeDistance(organized_by_distance_query9, current_index_query9);
    Query9_sort_by_distance(organized_by_distance_query9, 0, current_index_query9);
  }
}

//guarda os endereços no array organized_by_distance_query9
void addAdresses_query9(Q9D *organized_by_distance_query9, Q9 *q9_array,  int current_index_query9){
  organized_by_distance_query9[current_index_query9].adress = q9_array;
}

//expande o array organized_by_distance_query9 
void memory_expansion_organized_by_distance_query9(Q9D *organized_by_distance_query9, unsigned int key){
  Q9D * query9= (Q9D*)realloc(organized_by_distance_query9, key * sizeof(Q9D));
  if(query9 == NULL) printf("Realloc Query9 falhou \n");
  else organized_by_distance_query9 = query9;
}

//função que guarda os endereços no array organized_by_distance_query9, inicializa, ordena e escreve as variáveis pedidas no output file (QUERY 9)
void query9_sort_distance(char *data, char *datas, R_data *r_data, int linha){
  int current_index_query9 = -1;
  int data1 = Data_de_referência - calculateDateToCompare(data);
  int data2 = Data_de_referência - calculateDateToCompare(datas);
  int subtraction;
  int date;
  if(data1 > data2){
    subtraction = data1 - data2;
  }
  else{
    subtraction = data2 - data1;
  }
    FILE *file; 
    char* filename = (char*)malloc(255 * sizeof(char)); 
    strcpy(filename, "Resultados/command");
    char *file_number = (char*)malloc((linha/2 + 2) *sizeof(char));
    sprintf(file_number,"%d",linha);

    strcat(strcat(filename,file_number), "_output.txt");

    if((file = fopen(filename, "w")) == NULL){
        printf("Erro a abrir file");
    }
    if ((data1 > r_data->current_size_day_list) && (data2 > r_data->current_size_day_list)){ 
      fclose(file);
      free(filename);
      free(file_number);
      return;
      }
   else if((data1 > r_data->current_size_day_list) && (data2 <= r_data->current_size_day_list)){
        data1 = r_data->current_size_day_list;
    }
    else if((data2 > r_data->current_size_day_list) && (data1 <= r_data->current_size_day_list)){
        data2 = r_data->current_size_day_list;
      }
  if((data1 > 0) && (data2 > 0)){
    int size = 15000 * (subtraction + 1);
  Q9D *organized_by_distance_query9 = (Q9D*)((calloc(size,  sizeof(Q9D))));
  for(; data2 < data1+1; data2++){
      for (int i = 0; i < r_data->daylist[data2].q9_index; i++){
        current_index_query9++;
            addAdresses_query9(organized_by_distance_query9, &(r_data->daylist[data2].q9_array[i]), current_index_query9);
            if(current_index_query9 >= size){
              size = size << 1;
              memory_expansion_organized_by_distance_query9(organized_by_distance_query9, size);
            }
      }
  }
  Query9_sortAll(organized_by_distance_query9, current_index_query9);

  for (int i = 0; i <= current_index_query9; i++){

        int id_viagem = organized_by_distance_query9[i].adress->viagem->viagem;
        char *data_viagem = strdup(organized_by_distance_query9[i].adress->viagem->date);
        unsigned char distancia = organized_by_distance_query9[i].distance;
        char *cidade = strdup(organized_by_distance_query9[i].adress->city->name);
        double tip = organized_by_distance_query9[i].adress->viagem->tip;
        fprintf(file, "%012d;%s;%d;%s;%.3f\n", id_viagem, data_viagem, distancia, cidade, tip);
        free (data_viagem);
        free(cidade);
      }
    free(organized_by_distance_query9);
  }
    fclose(file);
    free(filename);
    free(file_number); 
}

//Função que inicializa o Day_list
void new_Day_list(R_data *data){
    //15 anos
    data->current_size_day_list = 5580;
    data->daylist = calloc(5580, sizeof(Day_list));
}

//Função que inicializa a Q9
void initializeQ9(R_data *r_data, unsigned int key){
 r_data->daylist[key].q9_array = (Q9*)malloc(45000 * sizeof(Q9));
 r_data->daylist[key].q9_size = 45000;
}

//Função de realloc do Day_list
void memory_expansion_day_list(R_data * data, int increase_amount){
  data->current_size_day_list += increase_amount;
  Day_list *day_list = (Day_list*)realloc(data->daylist, data->current_size_day_list * sizeof(Day_list));
  if(day_list == NULL) printf("Realoc day list falhou \n");
  else data->daylist = day_list;
}

//Função de realloc da Q9
void memory_expansion_Q9(R_data * data, unsigned int key){
  data->daylist[key].q9_size =   data->daylist[key].q9_size * 1.5;
  Q9 *q9array = (Q9*)realloc(data->daylist[key].q9_array, data->daylist[key].q9_size * sizeof(Q9));
  if(q9array == NULL) printf("Realoc Q9 falhou \n");
  else data->daylist[key].q9_array = q9array;
}

//Função que adiciona elementos à Q9
Rides * add_Q9(R_data *r_data, Rides *ride, Cities *city, unsigned char distance,  unsigned int date){
  unsigned int days = Data_de_referência - date;
  if(days >= r_data->current_size_day_list){
   memory_expansion_day_list(r_data, days + 1 - r_data->current_size_day_list);
  }
  if(r_data->daylist[days].q9_index == r_data->daylist[days].q9_size){ 
      if(r_data->daylist[days].q9_size == 0) initializeQ9(r_data, days);
      else memory_expansion_Q9(r_data, days);
    }
  r_data->daylist[days].q9_array[r_data->daylist[days].q9_index].date = date;
  r_data->daylist[days].q9_array[r_data->daylist[days].q9_index].distance = distance;
  r_data->daylist[days].q9_array[r_data->daylist[days].q9_index].viagem = ride;
  r_data->daylist[days].q9_array[r_data->daylist[days].q9_index].city = city;
  r_data->daylist[days].q9_index++;
  return ride;
}

//função para o ficheiro rides.c que insere cada data na sua respetiva posiçao("hoje"-"data" = indice)
void addTravelCost(R_data *data, int date, double price){
    date = Data_de_referência - date;
    data->daylist[date].ntravels ++;
    data->daylist[date].price += price;
}

//função que calcula o preço médio da viagem (QUERY 5)
double getMedia(R_data *data, int dataI,int dataF){
    Day_list *dias = data->daylist;
    double custoTotal = 0;
    int nViagens = 0;
    
    dataF = Data_de_referência - dataF;
    dataI = Data_de_referência - dataI;
    if (dataI < 0) return -1;
    if (dataF < 0) dataF = 0;
    if((dataI < data->current_size_day_list) && (dataF < data->current_size_day_list)){
    for(; dataF < dataI+1; dataF++) {
        custoTotal += dias[dataF].price;
        nViagens += dias[dataF].ntravels;
    }
    if (nViagens){
      return custoTotal/nViagens;
      }
    }
    return -1;
}

//calcula o index da cidade
int city_index_calculator(char *city){
  int sum = city[0];
  for(int i = 1; city[i] != '\0'; i++){
   sum += city[i];
  }
  return (sum%100);
}
//Auxiliar do quicksort
int DriversCity_partitions_by_score(CDS *array, int low, int high){
      CDS aux;
  double pivot = array[high].score;
  int i = (low -1);

  for (int j = low; j < high; j++) {
    if((array[j].score > pivot) || ((array[j].score == pivot) && (array[j].id > array[high].id))){
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

//quicksort dos condutores pela a avaliação dos mesmos
void DriversCity_sort_by_score(CDS *array, int low, int high){
   if (low < high) {
    int pi = DriversCity_partitions_by_score(array, low, high);
    DriversCity_sort_by_score(array, low, pi - 1);
    DriversCity_sort_by_score(array, pi + 1, high);
  }
}

//guarda no array organized_by_score_city_drivers a respetiva avaliação a partir do endereço
void DriversCity_initializeScore(Cities *cities, int key){
  const unsigned int max = cities[key].current_index_query7;
  city_driver *city_driver;
  for (unsigned int i = 0; i <= max; i++){
    city_driver = cities[key].organized_by_score_city_drivers[i].adress;
    if(city_driver->total_rides)
      cities[key].organized_by_score_city_drivers[i].score = (double)((city_driver->total_score) / (city_driver->total_rides)); 

  }
}

//função que inicializa as variável do array organized_by_score_city_drivers e ordena a partir do quicksort
void DriversCity_sortAll(Cities *cities, int key){
  if(cities[key].current_index_query7 > 0){
  DriversCity_initializeScore(cities, key);
  DriversCity_sort_by_score(cities[key].organized_by_score_city_drivers, 0, cities[key].current_index_query7);
  }
}

//função que guarda no array organized_by_score_city_drivers os respetivos endereços
void addAdresses_city_drivers(Cities *cities, city_driver *city_driver, int i){
  cities->current_index_query7++;
  cities->organized_by_score_city_drivers[cities->current_index_query7].adress = city_driver;
  cities->organized_by_score_city_drivers[cities->current_index_query7].id = i;
}

//função que guarda os endreços e ordena o array organized_by_score_city_drivers (QUERY 7)
void City_sortDrivers(R_data *r_data, Drivers *drivers, int x){
  Cities *cities = r_data->cities;
  const unsigned int size_c_data = r_data->d_limit -1;
  for (int key = 0; key < 100; key++){
    if(cities[key].total_rides != 0){
      for (int i = 0; i < size_c_data; i++){
            if((cities[key].c_driver[i].total_rides > 0) && ((getD_account_status(drivers, i) == 'a') || (getD_account_status(drivers, i) == 'A'))){
                  addAdresses_city_drivers(&(cities[key]), &(cities[key].c_driver[i]), i);
            }
            if((cities[key].copycats_size > 0) && ((getD_account_status(drivers, i) == 'a') || (getD_account_status(drivers, i) == 'A'))){
              City_sortDrivers(r_data, drivers, cities[key].copycats_size);
            }
      }
      DriversCity_sortAll(cities, key);
    }
  }
}

//Função que cria um novo R_data
R_data* new_R_data(int d_max_id){
  R_data *r_data = (R_data*)malloc(sizeof(R_data));
  r_data->cities = (Cities*)calloc(100, sizeof(Cities)); 
  r_data->d_limit = d_max_id;
  return r_data; 
}

//Função que inicializa as cidades
void initializeCity(Cities *cities, double score, int d_limit, int d_id, int distance, char *name, double money){
  cities->c_driver = (city_driver*)(calloc(d_limit, sizeof(city_driver)));
  cities->size =d_limit * 15;
  cities->index = 0;
  cities->rides = (Rides**)calloc(100, sizeof(Rides*));
  cities->rides[cities->row] = (Rides*)calloc(cities->size, sizeof(Rides));
  cities->c_driver[d_id].total_rides++;
  cities->c_driver[d_id].total_distance += distance;
  cities->c_driver[d_id].total_score += score;
  cities->total_money += money;
  cities->total_rides++;
  cities->name = strdup(name);
  cities->organized_by_score_city_drivers = (CDS*)((calloc(d_limit,  sizeof(CDS))));
  cities->current_index_query7 = -1; 
}

//Função que retorna o índice do copycat ou -1 se não o encontrar
int findCopycat(Cities* cities, char* name){
 for(int i = 0; cities[i].name[0] != '\0'; i++)
   if(strcmp(cities[i].name, name) == 0) return i;
 return -1;
}

//Função que guarda as viagens 
Rides* storeRide(Cities* cities, unsigned int ride_id, unsigned int d_id, char *date, char *username, unsigned char distance, int key, double tip, unsigned int dateN){
if(cities[key].index == cities[key].size){
  cities[key].row++;
  Rides *aux = (Rides*)calloc(cities[key].size, sizeof(Rides));
  cities[key].rides[cities[key].row] = aux;
  cities[key].index = 0;
}
 cities[key].rides[cities[key].row][cities[key].index].d_id = d_id;
 cities[key].rides[cities[key].row][cities[key].index].date = strdup(date);
 cities[key].rides[cities[key].row][cities[key].index].distance = distance; 
 cities[key].rides[cities[key].row][cities[key].index].username = strdup(username);
 cities[key].rides[cities[key].row][cities[key].index].viagem = ride_id;
 cities[key].rides[cities[key].row][cities[key].index].tip = tip;
 cities[key].rides[cities[key].row][cities[key].index].data = dateN;
 cities[key].index++;
 return &cities[key].rides[cities[key].row][cities[key].index -1];
}

void update_city(Cities *city, double score, int distance, double money, int d_id){
   city->c_driver[d_id].total_distance += distance;
   city->c_driver[d_id].total_rides ++;
   city->c_driver[d_id].total_score += score;
   city->total_money += money;
   city->total_rides++;
}

//Função que adiciona os dados à cidade respetiva
Rides * add_City(char *city, R_data *data, int d_id, double d_score, int distance, const int d_limit, int ride_id, char *date, char *username, double money, int dateN, double tip){
  int key = city_index_calculator(city);
  if (data->cities[key].name == NULL){
  initializeCity(&(data->cities[key]), d_score, d_limit, d_id, distance, city,  money);
 return add_Q9(data ,storeRide(data->cities, ride_id, d_id, date, username, (unsigned char)distance, key, tip, dateN), &data->cities[key], (unsigned char)distance, dateN);
  }
  else if(strcmp(data->cities[key].name, city) == 0){
    update_city(&(data->cities[key]), d_score, distance, money, d_id);
  return add_Q9(data,storeRide(data->cities, ride_id, d_id, date, username, (unsigned char)distance, key, tip, dateN),  &data->cities[key], (unsigned char)distance, dateN);
    
  }else{
    if(data->cities[key].copycats_size > 0){
      int copycat_key = findCopycat(data->cities[key].copycats, city);
      update_city(&(data->cities[key].copycats[copycat_key]), d_score, distance, money, d_id);
  return add_Q9(data, storeRide(data->cities[key].copycats, ride_id, d_id, date, username, (unsigned char)distance, copycat_key, tip, dateN), &data->cities[key].copycats[copycat_key], (unsigned char)distance, dateN);
    }else{
      data->cities[key].copycats_size = 3;
      data->cities[key].copycats = (Cities*)calloc(data->cities[key].copycats_size, sizeof(Cities));
      initializeCity(data->cities[key].copycats, d_score, d_limit, d_id, distance, city, money);
   return  add_Q9(data, storeRide(data->cities[key].copycats, ride_id, d_id, date, username, (unsigned char)distance, 0, tip, dateN), &data->cities[key].copycats[0], (unsigned int)distance, dateN);
    }
  }
}

//Função que calcula os dados estatísticos do drivers e do users
void addValues(FILE *file, R_data *r_data, D_data *drivers, Users *users, char *line, const int d_limit){
  char **parsed = Parser(file, line);
  if(!feof(file)){
    //inicio da validaçao
    if(((parsed[0][0] != '\0')) && ((parsed[1][0] != '\0')) &&((parsed[2][0] != '\0')) &&((parsed[3][0] != '\0')) &&((parsed[4][0] != '\0')) &&((parsed[5][0] != '\0')) &&((parsed[6][0] != '\0')) && ((parsed[7][0] != '\0')) && ((parsed[8][0] != '\0')) ){
      if(validateDates(parsed[1]));
      else{
        FreeParsed(parsed,9);
        free(parsed);
        return;
      }
      if(validateDistance(parsed[5])){
             FreeParsed(parsed,9);
            free(parsed);
            return;
        }
      if(validateDistance(parsed[6])){
            FreeParsed(parsed,9);
            free(parsed);
            return;
      }
       if(validateDistance(parsed[7])){
            FreeParsed(parsed,9);
            free(parsed);
            return;
      }
   if(validateFloats(parsed[8])){
      FreeParsed(parsed,9);
      free(parsed);
      return;
      }
      unsigned char d_age,u_age;
      unsigned int d_date, u_date;
      char d_gender, u_gender;
       const int distance = atoi(parsed[5]);
       const double tip = strtod(parsed[8], NULL);
       const int d_id = atoi(parsed[2])-1;
       const double custo = calculate_price(distance, getD_car_class(drivers, d_id),tip);
       const double custo_sem_tip = custo -tip;
      //fim da validaçao
        unsigned int lastRide = calculateDateToCompare(parsed[1]);
          double d_score, u_score;
        if(parsed[6][0] != '\0') 
        u_score = strtod(parsed[6], NULL);
        else d_score = 0;
        if(parsed[7][0] != '\0') 
        d_score = strtod(parsed[7], NULL);
        else u_score = 0;
        d_addValue(d_id,distance,d_score, tip, lastRide, drivers, &d_age, &d_date, &d_gender);
        u_addvalue(users, parsed[3], custo, u_score,distance, lastRide, &u_age, &u_date, &u_gender);
        //0  1    2      3    4    5        6          7            8   9
        //id;date;driver;user;city;distance;score_user;score_driver;tip;comment
        Rides *aux = add_City(parsed[4], r_data, d_id, d_score, distance, d_limit, atoi(parsed[0]), parsed[1], parsed[3], custo_sem_tip, lastRide, tip);
        if(d_gender == u_gender){
          if(d_gender != '\0'){
          if(u_age < d_age) d_age = u_age;
          addQ8(r_data, d_age, d_date, u_date, d_gender, aux);
          }
        }
          addTravelCost(r_data,lastRide,custo_sem_tip);
      }else{
        FreeParsed(parsed,9);
        free(parsed);
        return;
      }
    for (int i = 0; i < 9; i++) free(parsed[i]);
  }
  free(parsed);
}

//Função que percorre o ficheiro rides.csv todo para calcular os dados estatísticos necessários às queries
R_data * updateTables(FILE *file, D_data *drivers, Users * users){
  const int d_limit = getD_limit(drivers) + 1;
  R_data *r_data = new_R_data(d_limit);
  char *line = (char*)malloc(850 * sizeof(char));
  size_t j = 850;
  int aux;
  int iterations =0;
  new_Day_list(r_data);
  aux = getline(&line, &j, file);
  if (aux == -1)printf("getline do rides falhou\n");
      while(!feof(file)){
            addValues(file, r_data, drivers, users, line, d_limit);
      }
  free(line);
  return r_data;
}

//função que dá free ao Cities
int CityFree(Cities *cities){
  if(cities->total_rides == 0) return 1;
   free(cities->c_driver); 
    for(int k = 0; k < cities->row; k++){
      for(unsigned int j = 0;j < cities->size; j++){
      if(cities->rides[k][j].viagem != 0){
        free(cities->rides[k][j].date);
        free(cities->rides[k][j].username);
      }
      }
      free(cities->rides[k]);
    }
     for(unsigned int j = 0;j < cities->index; j++){
      if(cities->rides[cities->row][j].viagem != 0){
        free(cities->rides[cities->row][j].date);
        free(cities->rides[cities->row][j].username);
      }
      }
      free(cities->rides[cities->row]);
       free(cities->name);
       free(cities->rides);
       free(cities->organized_by_score_city_drivers);
       return 0;
}

//função que dá free ao R_data
void R_free(R_data *r_data){
  const unsigned int d_limit = r_data->d_limit -1;
  for(int i = 0; i < 100; i++){
    if(r_data->cities[i].total_rides > 0){
         for(int k =0; k < r_data->cities[i].copycats_size; k++){
           if(CityFree(&r_data->cities[i].copycats[k])) break;
         }
       CityFree(&r_data->cities[i]);
       }
    }
    const int limit = r_data->current_size_day_list;
    for(int i = 0; i < limit; i++){
      if(r_data->daylist[i].q9_index > 0) free(r_data->daylist[i].q9_array);
      if(r_data->daylist[i].q8f_size > 0) free(r_data->daylist[i].q8f_array);
      if(r_data->daylist[i].q8m_size > 0) free(r_data->daylist[i].q8m_array);
    }
    
    free(r_data->daylist);
    free(r_data->cities);
    free(r_data);
  }

//função que devolve o array da cidade pedida
Cities* get_City (R_data *data, char *name){
  int key = city_index_calculator(name);
  if((data->cities[key].total_rides >0) && (strcmp(data->cities[key].name, name) == 0)) return &(data->cities[key]);
  else{
    if(data->cities[key].copycats_size > 0){
    int copycatKey = findCopycat(&data->cities[key], name);
    if(copycatKey = -1) return calloc(1, sizeof(Cities));
       return &data->cities[key].copycats[copycatKey];
    }
    return calloc(1, sizeof(Cities));

  }
}

//função que devolve a distância média percorrida (QUERY 6)
double getDistMed(R_data *viagens, int dataI, int dataF, char* nome){
  Cities *cidade = get_City(viagens, nome);
  if (!cidade->total_rides){
    free(cidade);
     return -1;
  }
  Rides *datas; 
  unsigned int nTravels = 0;
  double distTotal = 0;
    unsigned int dateToCompare =-1;
    for(int r = 0; r < cidade->row; r++){
      datas = cidade->rides[r];
    for(int i = 0; i < cidade->size; i++) {
      if((dataI <= datas[i].data) && (datas[i].data <= dataF)){
        nTravels++;
        distTotal += datas[i].distance;
      }
    }
    }
    datas = cidade->rides[cidade->row];
    for(int i = 0; i < cidade->index; i++) {
      if((dataI <= datas[i].data) && (  datas[i].data <= dataF)){
        nTravels++;
        distTotal += datas[i].distance;
      }
    }
  if (nTravels)
    return distTotal/nTravels;
  return -1;
}

//função que verifica se a cidade existe
int existe_city(char *city, R_data *r_data){
  int key = city_index_calculator(city);
  Cities * cities = get_City(r_data, city);
  if((cities->total_rides == 0)){
    free(cities);
    return 0;
  }
  else return 1;
}

//vai buscar o dinheiro total da cidade
double get_City_money(R_data *r_data, char *city){
  int key = city_index_calculator(city);
  return r_data->cities[key].total_money;
}  

//vai buscar o total de viagens numa cidade
int get_City_totalrides(R_data *r_data, char *city){
  int key = city_index_calculator(city);
  return r_data->cities[key].total_rides;
}

//vai buscar o id do condutor na respetiva cidades
int get_City_DriversID(R_data *r_data, char *city, int i){
  Cities *cities = get_City(r_data, city);
  if(cities->total_rides == 0){
     free(cities);
  }
  else{
  return cities->organized_by_score_city_drivers[i].id;
  }
}

//vai buscar a avaliação média do condutor na respetiva cidade
double get_City_DriversScore(R_data *r_data, char *city, int i){
  Cities *cities = get_City(r_data, city);
  if(cities->total_rides == 0){
   free(cities);
  }
  else{
  return cities->organized_by_score_city_drivers[i].score;
  }
}

//vai buscar o limit do array organized_by_score_city_drivers
int get_City_DriversScore_limit(R_data *r_data, char *city){
  Cities *cities = get_City(r_data, city);
  if(cities->total_rides == 0){
   free(cities);
  }
  else{
  return cities->current_index_query7;
  }
}

//função que vai buscar o limit do drivers
int RgetD_limit(R_data *data){
  return data->d_limit;
}