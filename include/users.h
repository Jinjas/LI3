typedef struct users_Table Users;

typedef struct u_data U_data;

typedef struct organized_by_last_ride ULR;
typedef struct organized_by_score US;
typedef struct organized_by_distance UD;


U_data *u_createTable(FILE *file);
//função que retorna o nome do usuario
char *u_getName(Users *users, char * username);
//função que retorna a idade do usuario
int u_getAge(Users *users, char *username);
//função que retorna o gender do usuario
char u_getGender(Users *users, char*username);

void u_addvalue(Users* table, char*username, double cash, int avaliation, int distance, unsigned int last_ride, unsigned char *age, int *date, char *gender);
//função que retorna a distancia total do usuario
int u_getTotalRides(Users* users, char*username);
//função que retorna o total gasto pelo usuario
double u_getMoneyWasted(Users* users, char*username);
//função que retorna o Score do usuario
double u_getScore(Users* users, char*username);
//função que retorna o estado da conta do usuario
char u_getAccountStatus (Users *users, char *username);
//função que retorna os copycats do usuario
Users *u_getcopycats(Users *users, char*username);
//função que retorna o username do usuario atraves do indice
char* U_getUsername(Users *users, int index);
//função que retorna o nome do usuario atraves do indice
char * U_getNamebyIndex(Users *users, int index);
//função que retorna a distancia percorrida pelo usuario atraves do indice
int U_getdistancebyIndex(Users *users, int index);
//função que retorna o numero de viagens total atraves do indice
int U_getTotalRidesbyIndex(Users *users, int index);
//função que retorna o estado da conta do usuario atraves do indice
char U_getAccountStatusbyIndex(Users *users, int index);
//função que retorna a ultima viagem feita pelo usuario atraves do indice
unsigned int U_getlast_ridebyIndex(Users *users, int index);
//função que retorna a distancia total percorrida pelo usuario 
int getU_total_distance(Users *users, char* username);
//função para o free da estrutura
void u_free(U_data *data);
//função que retorna os copycats atraves do indice
Users * u_getcopycatsByIndex(Users *users, int index);
//função para o debug atraves do print da estrutura users
void u_print(Users *table);
//função que retorna o identifier de um user atraves do indice
int u_getIdentifierByIndex(Users *users, int index);
//função que retorna o tamanho de elementos no copycats atraves do indice
int u_getSizeByIndex(Users *users, int index);
//função que retorna a estrutura Users atraves da U_data
Users* U_getTable(U_data *data);
//função que retorna UD atraves de U_data
UD* U_get_Organized_by_distance(U_data *data);
//função para o debug atraves do print da estrutura U_data
void dataPrint(U_data *data);
//função que inicializa o array UD e organiza atravez do quick Sort 
void U_sortAll(U_data *data);
//quick sort dos Utilizadores
void U_sort_by_distance(UD *array, int low, int high);
//função que retorna os users organizados por distancia
Users* U_get_User_Organized_by_Distance(U_data *data, int n);
//função que retorna o numero maximo de Users
int getU_limit(U_data *data);