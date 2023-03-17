typedef struct query5_Table Query5;

//void *verificaintervalo5(void *intervalos,char *arguments); //função para o parcer das querys -- done
//
//void addTravel5(void **intervalos,int date,double price);//função para o parcer das rides -- done
//
//void escreve_ficheiro5(char *arguments, Query5 *intervalos, int linha);//função para o execute querys -- done
void escreve_ficheiro5(char *arguments, void *dias, int linha);//função para o execute querys -- done

//
//void free_query5(Query5 *lista);//função para pôr no query_handler -- done