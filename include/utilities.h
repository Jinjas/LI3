#include "drivers.h"
int calculateIdentifier(char *string);

char** Parser(FILE *file, char *line);

#define data_de_referência 738453
#define RPrime 2000003

double calculate_price(int distance, char car_class, double tip);

unsigned char calculateAge(int date);

int calculateDate(char * date);

int calculateDateToCompare(char * date);

int get_most_recent_date(int fdate, int sdate);

int compareDates(int fdate, int sdate);

int compareDatesWhileTheyAreStrings(char* date1, char* date2);

char validateDates(char* date);

char validateFloats(char *score);

char validateDistance(char *distance);

void FreeParsed(char** parsed, int n);

unsigned char calculateAgeToCompare(int date);