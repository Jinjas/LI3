#include "../include/drivers.h"
#include "users.h"
typedef struct r_data R_data;
typedef struct organized_by_distance_query9 Q9D;

R_data *updateTables(FILE *file, D_data *drivers, Users * users);

double getMedia(R_data *data, int dataI,int dataF);

double getDistMed(R_data *viagens, int dataI, int dataF, char* nome);

void R_free(R_data *r_data);

void City_sortDrivers(R_data *r_data, Drivers *drivers, int x);

void dataPrintDriversCity(R_data *data);

double get_City_money(R_data *r_data, char *city);

int get_City_totalrides(R_data *r_data, char *city);

int get_City_DriversID(R_data *r_data, char *city, int i);

double get_City_DriversScore(R_data *r_data, char *city, int i);

int existe_city(char *city, R_data *r_data);

int city_index_calculator(char *city);

void query9_sort_distance(char *data, char *datas, R_data *r_data, int linha);

void Query8(char *linha, R_data *data, Drivers* drivers, Users* users, int id);

int RgetD_limit(R_data *data);

int get_City_DriversScore_limit(R_data *r_data, char *city);