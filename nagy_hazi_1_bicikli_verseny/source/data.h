#ifndef HuData_D
#define HuData_D

#include"list.h"

typedef struct racer
{
    unsigned char name[50];
    int racer_id;
    int point;
}Racer;
//It reads every line from sectors.csv and puts them into a list of Sensing structs.
//Error in read -> List head & tail == NULL
List readSensing();
//It reads every line from competitors.csv and puts them into a list of Racer structs.
//Error in read -> List head & tail == NULL
List readCompetitors();
/*Returns result of race in form of Racers' List*/
List calculateResult(int fastest,int value,int TopNumb,List racers,List sensinglist);
/*Writes race result into the given file*/
void writeResult(List racers,char filename[]);
/*Prints racers on podium to stdo*/
void printTop(List racers,int x_position);
/*It removes the given racer from both files (-1/0_error/ok)*/
int deleteCompetitor(char name[],char id[],List *racers,List *sensinglist);
/*Adding new racer to both files (-1/0_error/ok)*/
int addCompetitor(char name[],char id[],char filename[],List *racers,List *sensinglist);

#endif