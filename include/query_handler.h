typedef struct querys Querys;

Querys *q_createqueryslist(FILE *querys);

//função que executa td relativo as querys
void execute_query(Querys *query_list, U_data *data, D_data *drivers_table, R_data *r_data);