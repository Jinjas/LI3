typedef struct query2_Table Query2;

Query2 *TopN_classificacao (int n, Drivers *table);

void escreve_file(char *x, D_data *table, int linha, int d_limit);

void free_query2 (Query2 *lista);
