typedef struct drivers_Table Drivers;

typedef struct organized_by_score_drivers DS;

typedef struct d_data D_data;

//função para o parse do drivers
D_data *d_createTable(FILE *file);

//função para o debug print da tabela
void *d_printTable(Drivers *table, const int max);

//função para atualizar o D_data para cada nova viagem
void d_addValue (int id, int distance, int score, double tip, int lastride, D_data* currentTable, unsigned char *age, int *date, char*gender);

//função que retorna o id de um driver
int getD_id(Drivers *table, int key);
//função que retorna a ultima viagem de um driver
unsigned int  getD_lastRide (Drivers *table, int key);
//função que retorna o Score de um driver
double getD_mscore (Drivers *table, int key);
//função que retorna o estado da conta
char getD_account_status (Drivers *table, int key);
//função que retorna o nome do condudor
char* getD_name (Drivers *table, int key);
//função que retorna a classe do carro de um driver
char getD_car_class (D_data *table, int key);
//função que retorna o dinheiro ganho de um driver
double getD_money(Drivers *table, int key);
//função que retorna a distancia total percorrida por um driver
int getD_total_distance(Drivers *table, int key);
//função que retorna o gender do condudor
char getD_gender (Drivers *table, int key);
//função que retorna o numero de viagens totais de um driver
int getD_total_rides (Drivers *table, int key);
//função que retorna a idade do condudor
unsigned int getD_age(Drivers *table, int key);
//função para o free da estrutura
void d_free(D_data *drivers);
//função que retorna a estrutura drivers dentro de D_data
Drivers* D_getTable(D_data *data);
//função que retorna a estrutura DS dentro de D_data
DS * D_get_Organized_by_score(D_data *data);
//função para o debug print da tabela D_data
void dataPrintDrivers(D_data *data);

void D_sortAll(D_data *data);

void D_sort_by_score(DS *array, int low, int high);

void D_initializeScore(D_data *data);

Drivers* D_get_Drivers_Organized_by_Score(D_data *data, int n);

int getD_id(Drivers *table, int key);

int getD_limit(D_data *data);

int getD_limit_drivers(D_data *data);