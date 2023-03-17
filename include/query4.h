typedef struct query4_Table Query4;

void *verificaintervalo4(void *cidades,char *city); //função para o parcer das querys --

void addTravel4(void **cidades,double price, char *city);//função para o parcer das rides -- 

void escreve_ficheiro4(char *city, Query4 *cidades, int linha);//função para o execute querys --

void free_query4(Query4 *lista);//função para pôr no query_handler --

void escreve_ficheiro4_Rides(char *city, R_data *r_data, int linha);