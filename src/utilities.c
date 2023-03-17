#include <string.h>
#include <stdlib.h> 
#include <stdio.h>
#include "../include/utilities.h"


unsigned char calculateAge(int date){
  unsigned char age = (data_de_referência - date)/365.25;
  return age;
}

unsigned char calculateAgeToCompare(int date){
  unsigned char age = (752100 - date)/372;
  return age;
}

int calculateDate(char * date){
  return (date[0] - '0')*10 + date[1] - '0' + ((date[3] - '0')*10 + (date[4] - '0')-1)*30.4375 + ((((date[6] -'0')*1000 + (date[7]-'0')*100 + (date[8] - '0')*10 + date[9]- '0'))-1)*365.25;
}

int calculateDateToCompare(char * date){
  return (date[0] - '0')*10 + date[1] - '0' + ((date[3] - '0')*10 + (date[4] - '0')-1)*31 + ((((date[6] -'0')*1000 + (date[7]-'0')*100 + (date[8] - '0')*10 + date[9]- '0'))-1)*372;
}


int calculateIdentifier(char *string){
    unsigned long int identifier = 0;
    for(int i = 0; string[i] != '\0'; i++){
        identifier = (identifier << 5) + identifier + string[i];
    }
    identifier = identifier % RPrime;
    return identifier;
}

int get_most_recent_date(int fdate, int sdate){
     if(fdate > sdate) {
      return fdate;
     }
      return sdate;
}

//retorna -1 se forem iguais, 0 se date1 for maior e 1 se date1 for menor
int compareDates(int fdate, int sdate){
    if(fdate > sdate) 
      return 0;
    else if(fdate < sdate) 
      return 1;
    else
      return -1; 
}

//retorna -1 se forem iguais, 0 se date1 for maior e 1 se date1 for menor
int compareDatesWhileTheyAreStrings(char* date1, char* date2){
  if(date1[0] != '\0'){  //12/12/2021
                         //01 34 6789
    int fdate = calculateDate(date1);
    int sdate = calculateDate(date2);
    if(fdate > sdate) {
      return 0;
    }else if(fdate < sdate) {
      return 1;
    }else if (fdate == sdate){
      return -1; } 
  }
  return 1;
}


//parser geral
char** Parser(FILE *file, char *line){
    char **stringArray = (char**)calloc(10, sizeof(char*));
    size_t j = 840;
    int augha = getline(&line, &j, file);
    augha++;
    char *beginning;
    int s = 0;
    if(!feof(file)){
      for(int i = 0; (i < 9) && (line[s]); i++){
        beginning = &line[s];
        for(; (line[s] != ';') && (line[s] != '\n'); s++); line[s] = '\0';
        s++;
        if(beginning)
        stringArray[i] = strdup(beginning);
        else
        stringArray[i] = (char*)calloc(1, sizeof(char));
      }
    }
    return stringArray; 
}

//calculadora de custo de cada viagem
double calculate_price(int distance, char car_class, double tip){
    double price =0;
    if (car_class == 'b' || car_class == 'B'){
      price = 3.25 + 0.62 * distance + tip; 
    }
    else if (car_class == 'g' ||car_class == 'G'){ 
      price = 4.00 + 0.79 * distance + tip;
    }
    else {
      price = 5.20 + 0.94 * distance + tip;
    }
    return price;
}

char validateDates(char* date){
  if(strlen(date) != 10) return 0;
   if(date[10]=='\0'
   && date[2]=='/' 
   && date[5]=='/' 
   && ((date[0] >= '0' 
   &&  date[0]<='2' 
   && date[1]>='0' 
   && date[1]<='9') 
   || (date[0] == '3' && (date[1]=='0' || date[1]=='1'))) 
   && ((date[3] == '0' && date[4]>='0' && date[4]<='9') || (date[3] == '1' && date[4]>='0' && date[4]<='2'))
   && (date[6] >= '0' && date[6] <= '9' && date[7] >= '0' && date[7] <= '9' && date[8] >= '0' && date[8] <= '9' && date[9] >= '0' && date[9] <= '9'))
  return 1;
  else
 return 0; 
}

char validateFloats(char *score){
  char dotStock = 1;
  for(int i = 0; score[i] != '\0'; i++){
    switch (score[i])
    {
    case '0' ... '9':
      break;
    case '.':
     dotStock--;
     if(dotStock < 0) return 1;
     break;
    default:
      return 1;
    }
  }
  return 0;
}

void FreeParsed(char** parsed, int n){
  for (int i = 0; i < n; i++){
  if(parsed[i])
  free(parsed[i]);
  }
}

char validateDistance(char *distance){
      if(distance[0] == '\0') return 0;
    char absoluteZero = 1;
  for(int i = 0; distance[i] != '\0'; i++){
    switch (distance[i])
    {
    case '0':
    break;
    case '1' ... '9':
      absoluteZero = 0;
      break;
    default:
      return 1;
    }
  }
  if(absoluteZero == 1) return 1; else
  return 0;
}