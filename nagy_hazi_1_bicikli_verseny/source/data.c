#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"list.h"
#include"menu.h"

/*
    This library contains the structs and functions for IO operations 
    and Score calculations.
*/

//Two input files
//Sensing data
#define sectors_file "sectors.csv"
//Racer data
#define competitors_file "competitors.csv"

//Storing data of sectors.csv
typedef struct sensing
{
    int point_id;
    int secondofDay;
    int racer_id;
}Sensing;

//Storing data of competitor.csv
typedef struct racer
{
    char name[51];
    int racer_id;
    int point;
}Racer;

//Stores calculated data from Sensing type data
typedef struct sector
{
    int sectorNumber;
    int sectorTime;
    int sectorStartTime;
}Sector;

//It helps in reversing second to time
typedef struct time
{
    int hour;
    int minute;
    int second;
}Time;

//One Lap of one Racer
typedef struct lap
{
    int lapNumb;
    int lapTime;
    int lapPoint;
    int racer_id;
    List sectors;
}Lap;

//Converts date to seconds
int time2Second(int hour,int minute,int second)
{
    return (hour*3600)+(minute*60)+second;
}

//Convert seconds to date
Time second2Time(int second)
{
    Time t;
    int hour = second / 3600;
    second -= hour*3600;
    int minute = second/60;
    second -= minute*60;
    t.hour = hour;
    t.minute = minute;
    t.second = second;
    return t;
}
//The following functions were needed because the get() function in list.c returns a void ptr
//Makes the get function easier from a List which contains Sensing type structs
Sensing getSensingfromList(List sensingList,int index)
{
    return *(Sensing *)get(sensingList,index);
}

//Makes the get function easier from a List which contains Sector type structs
Sector getSectorfromList(List sectorList,int index)
{
    return *(Sector *)get(sectorList,index);
}

//Makes the get function easier from a List which contains Racer type structs
Racer getRacerfromList(List racers,int index)
{
    return *(Racer *)get(racers,index);
}

//Makes the get function easier from a List which contains Lap type structs
Lap getLapfromList(List LapList,int index)
{
    return *(Lap *)get(LapList,index);
}

//Converts letter to lower case
char to_lower_case(char in){
    if(in>='A'&&in<='Z')
    {
        in = in-'A'+'a';
    }
    return in;
}

//Converts one hexa number in char format to its int value
int hexa_value(char hexa)
{
    if(hexa>='0'&&hexa<='9'){
        return hexa-'0';
    }
    else if(to_lower_case(hexa)>='a'&&to_lower_case(hexa)<='z'){
        return to_lower_case(hexa)-'a'+10;
    }
    else
    {
        return -1;
    }
}

//Converts hexa numbers in string format to its value
int hexa2decimal(char s[])
{
    int sum = 0;
    for(int i = 0; s[i]!='\0';i++)
    {
        sum *= 16;
        sum += hexa_value(s[i]);
    }
    return sum;
}

//It reads every line from sectors.csv and puts them into a list of Sensing structs.
//Error in read -> List head & tail == NULL
List readSensing()
{
    FILE *f = fopen(sectors_file,"r");
    if(!f)
    {
        printf("sectors.csv not found");
        List faulty;
        faulty.head = NULL;
        faulty.tail = NULL;
        return faulty;
    }
    List sensingList = createList();
    char buffer[21];
    Sensing current;
    while (fgets(buffer,21,f)!=NULL)
    {
        int hour;
        int minute;
        int second;
        char hexa[10];
        sscanf(buffer,"%d;%d:%d:%d;%s",&current.point_id,&hour,&minute,&second,hexa);
        current.racer_id = hexa2decimal(hexa);
        current.secondofDay = time2Second(hour,minute,second);
        add_value(&sensingList,&current,sizeof(Sensing));
    }
    int success = fclose(f);
    //File could not be closed
    if(success!=0)
    {
        free_list(&sensingList);
        List faulty;
        faulty.head = NULL;
        faulty.tail = NULL;
        return faulty;
    }
    if(sensingList.size==0)
    {
        //File was empty
        printf("sectors.csv was empty");
        free_list(&sensingList);
        List faulty;
        faulty.head = NULL;
        faulty.tail = NULL;
        return faulty;
    }
    return sensingList;
}

//It reads every line from competitors.csv and puts them into a list of Racer structs.
//Error in read -> List head & tail == NULL
List readCompetitors()
{
    FILE *f = fopen(competitors_file,"r");
    if(!f)
    {
        printf(competitors_file);
        printf(" not found");
        List faulty;
        faulty.head = NULL;
        faulty.tail = NULL;
        return faulty;
    }
    List racers = createList();
    char buffer[61];
    Racer racer;
    while (fgets(buffer,61,f)!=NULL)
    {
        //This is needed because otherwise the chars after the ; disappear
        char *p = strrchr (buffer, ';')+1;
        char hexa[9];
        char name[51];
        sscanf(buffer,"%[^;]s",hexa);
        sscanf(p,"%[^\n]s",name);
        strcpy(racer.name,name);
        racer.racer_id = hexa2decimal(hexa);
        add_value(&racers,&racer,sizeof(Racer));
    }
    int success = fclose(f);
    if(success!=0)
    {
        free_list(&racers);
        List faulty;
        faulty.head = NULL;
        faulty.tail = NULL;
        return faulty;
    }
    if(racers.size==0)
    {
        //File was empty
        printf(competitors_file);
        printf(" was empty");
        free_list(&racers);
        List faulty;
        faulty.head = NULL;
        faulty.tail = NULL;
        return faulty;
    }
    return racers;
}

//reads files with sectors.csv type syntax ~ readSensing()
List importSensing(char filename[])
{
    FILE *f = fopen(filename,"r");
    if(!f)
    {
        printf("%s not found",filename);
        List faulty;
        faulty.head = NULL;
        faulty.tail = NULL;
        return faulty;
    }
    List sensingList = createList();
    char buffer[21];
    Sensing current;
    while (fgets(buffer,21,f)!=NULL)
    {
        int hour;
        int minute;
        int second;
        char hexa[10];
        sscanf(buffer,"%d;%d:%d:%d;%s",&current.point_id,&hour,&minute,&second,hexa);
        current.racer_id = hexa2decimal(hexa);
        current.secondofDay = time2Second(hour,minute,second);
        add_value(&sensingList,&current,sizeof(Sensing));
    }
    int success = fclose(f);
    //File could not be closed
    if(success!=0)
    {
        free_list(&sensingList);
        List faulty;
        faulty.head = NULL;
        faulty.tail = NULL;
        return faulty;
    }
    if(sensingList.size==0)
    {
        //File was empty
        printf("%s was empty",filename);
        free_list(&sensingList);
        List faulty;
        faulty.head = NULL;
        faulty.tail = NULL;
        return faulty;
    }
    return sensingList;
}

//writing to competitors.csv from racers list
void writeCompetitors(List racers)
{
    FILE *f = fopen(competitors_file,"w");
    if(!f)
    {
        printf(competitors_file);
        printf(" not found");
        return;
    }
    Racer current;
    for(int i = 0; i < racers.size;i++)
    {
        current = getRacerfromList(racers,i);
        //Last line
        if(i==racers.size-1)
        {
            fprintf(f,"%08x;%s",current.racer_id,current.name);
        }
        else
        {
            fprintf(f,"%08x;%s\n",current.racer_id,current.name);
        }
        
    }
    int success = fclose(f);
    //could not be closed
    if(success!=0)
    {
        //File not closed properly
        printf(competitors_file);
        printf(" could not be closed");
    }
}

/*
Writes list into file
Append or write depending on mode parameter
*/
void writeSensing(List sensinglist,char mode[])
{
    FILE *f = fopen(sectors_file,mode);
    if(!f)
    {
        printf(sectors_file);
        printf(" not found");
        return;
    }
    Sensing current;
    Time c_time;
    if(strcmp(mode,"a")==0)
    {
        for(int i = 0; i < sensinglist.size;i++)
        {
            current = getSensingfromList(sensinglist,i);
            c_time = second2Time(current.secondofDay);
            fprintf(f,"\n%d;%02d:%02d:%02d;%08x",current.point_id,c_time.hour,c_time.minute,c_time.second,current.racer_id);
        }
    }
    else
    {
        for(int i = 0; i < sensinglist.size;i++)
        {
            current = getSensingfromList(sensinglist,i);
            c_time = second2Time(current.secondofDay);
            //Last line
            if(i==sensinglist.size-1)
            {
                fprintf(f,"%d;%02d:%02d:%02d;%08x",current.point_id,c_time.hour,c_time.minute,c_time.second,current.racer_id);
            }
            else
            {
                fprintf(f,"%d;%02d:%02d:%02d;%08x\n",current.point_id,c_time.hour,c_time.minute,c_time.second,current.racer_id);
            }
            
        }
    }
    
    int success = fclose(f);
    //could not be closed
    if(success!=0)
    {
        printf(sectors_file);
        printf(" could not be closed");
    }
}
/*
It removes the given racer from both files
-1 error
0 ok
*/
int deleteCompetitor(char name[],char id[],List *racers,List *sensinglist)
{
    if(strcmp(name,"\0")==0&&strcmp(id,"\0")==0)
    {
        return -1;
    }
    int index = -1;
    Racer current;
    //search for racer in racers list
    for(int i = 0; i < racers->size;i++)
    {
        current = getRacerfromList(*racers,i);
        if(strcmp(name,current.name)==0||hexa2decimal(id)==current.racer_id)
        {
            index = i;
            break;
        }
    }
    //if racer not found
    if(index==-1)
    {
        int x = getState().x_position;
        printf("Racer is not found");
        gotoxy(x,getState().y_position+1);
        printf("with this name or ID");
        return -1;
    }
    //removing racer from competitors database
    list_remove(racers,index);
    //writing updated list to file
    writeCompetitors(*racers);
    //removing racer from the sensing database
    Sensing actual;
    for(int i = 0; i < sensinglist->size;i++)
    {
        actual = getSensingfromList(*sensinglist,i);
        if(actual.racer_id==current.racer_id)
        {
            //removing racer(node) from the list->list becomes shorter
            list_remove(sensinglist,i);
            //so the next index becomes the current i
            i -= 1;
        }
    }
    //writing updated list to file
    writeSensing(*sensinglist,"w");
    return 0;
}

/*
Adding new racer to both files
-1 error
0 ok
*/
int addCompetitor(char name[],char id[],char filename[],List *racers,List *sensinglist)
{
    if((name[0]=='\0'&&id[0]=='\0')||filename[0]=='\0')
    {
        return -1;
    }
    int sensingRacer = 0;
    int first_id = getSensingfromList(*sensinglist,0).racer_id;
    for(int i = 0; i < sensinglist->size;i++)
    {
        if(getSensingfromList(*sensinglist,i).racer_id==first_id)
        {
            sensingRacer++;
        }
    }
    List importedSensing = importSensing(filename);
    //Error during read
    if(!importedSensing.head&&!importedSensing.tail)
    {
        return -1;
    }
    //Checking whether the imported file is correct
    if(importedSensing.size!=sensingRacer)
    {
        int x = getState().x_position;
        printf("The amount of information");
        gotoxy(x,getState().y_position+1);
        printf("is different from the rest of the racers");
        free_list(&importedSensing);
        return -1;
    }
    Sensing current;
    //Copying data to main list
    for(int i = 0; i < importedSensing.size;i++)
    {
        current = getSensingfromList(importedSensing,i);
        add_value(sensinglist,&current,sizeof(Sensing));
    }
    //Append imported data to sectors.csv
    writeSensing(importedSensing,"a");
    //free no longer needed imported list
    free_list(&importedSensing);
    //Adding new racer to competitors.csv
    Racer newRacer;
    newRacer.racer_id = hexa2decimal(id);
    strcpy(newRacer.name,name);
    //adding to list
    add_value(racers,&newRacer,sizeof(Racer));
    //write to file
    writeCompetitors(*racers);
    return 0;
}

//Converts void pointer to specific(Sensing type) struct value
Sensing pointer2Struct(void *data)
{
    return *(Sensing *)data;
}

//Sorts List with Sensing data type inside
void bubbleSort(List sensingList)
{
    if(sensingList.size==0)
    {
        return;
    }
    //Using list without get() function of list.c for better performance
    Node *head = sensingList.head;
    Node *tail = sensingList.tail;
    void *temp;
    for(Node *first = head->next; first->next!=tail;first=first->next)
    {
        for(Node *second = first->next;second!=tail;second=second->next)
        {
            if(pointer2Struct(first->data).secondofDay > pointer2Struct(second->data).secondofDay)
            {
                temp = first->data;
                first->data = second->data;
                second->data = temp;
            }
        }
    }
}

/*It returns an id for a sector where first_point_id is the sector opening sensor id
  and second_point_id is the sector closing sensor id max_point_id is the highest
  sensor id on the track.
*/
int getSector_id(int first_point_id, int second_point_id,int max_point_id)
{
    if(first_point_id == max_point_id&&second_point_id==0)
    {
        return max_point_id + 1;
    }
    if(first_point_id>second_point_id)
    {
        return -1;
    }
    return second_point_id;
}

/*For debugging purposes only
void printSectorList(List sectorlist,int racer_id)
{
    FILE *f = fopen("sector_list.csv","a");
    fprintf(f,"ID: %d\n",racer_id);
    Sector currentsector;
    for(int i = 0; i < sectorlist.size;i++)
    {
        currentsector = getSectorfromList(sectorlist,i);
        fprintf(f,"N: %d;T: %d\n",currentsector.sectorNumber,currentsector.sectorTime);
    }
    fclose(f);
}
*/

/*Gets the whole sectorList of a racer the starting index(sector where the lap starts)
and the last index(sector where the lap ends) and 
the Lap number and returns a Lap struct*/
Lap createLapfromSectorList(List sectorList,int start_index,int last_index,int lapNumb)
{
    Lap newLap;
    List newSectorList = createList();
    Sector current;
    for(int i = start_index; i <= last_index;i++)
    {
        current = getSectorfromList(sectorList,i);
        add_value(&newSectorList,&current,sizeof(Sector));
    }
    Sector last = getSectorfromList(sectorList,last_index);
    Sector first = getSectorfromList(sectorList,start_index);
    newLap.sectors = newSectorList;
    newLap.lapTime = (last.sectorStartTime + last.sectorTime) - first.sectorStartTime;
    newLap.lapNumb = lapNumb;
    return newLap;
}

List createLapList(List sensingList,int racer_id)
{
    List own_sensing = createList();
    Sensing current;
    int maxpoint_id = 0;
    /*It finds all the sensor data for one particular racer and adds them to a List
      It also looks for the highest sensor point id
    */
    for(int i = 0; i < sensingList.size; i++)
    {
        current = getSensingfromList(sensingList,i);
        if(current.racer_id==racer_id)
        {
            add_value(&own_sensing,&current,sizeof(Sensing));
        }
        if(current.point_id>maxpoint_id)
        {
            maxpoint_id = current.point_id;
        }
    }
    //FREE THE LIST AFTER USING THE FUNCTION free_list(&sensingList);!!!!
    bubbleSort(own_sensing);
    List sectorList = createList();
    Sensing next;
    Sector newSector;
    int maxSector_id = maxpoint_id + 1;
    //Creates sector data for the racer from his previous sensor data List
    for(int i = 0; i < own_sensing.size-1;i++)
    {
        current = getSensingfromList(own_sensing,i);
        next = getSensingfromList(own_sensing,i+1);
        newSector.sectorNumber = getSector_id(current.point_id,next.point_id,maxpoint_id);
        newSector.sectorTime = next.secondofDay-current.secondofDay;
        newSector.sectorStartTime = current.secondofDay;
        add_value(&sectorList,&newSector,sizeof(Sector));
    }
    //Frees the no longer needed sector data list
    free_list(&own_sensing);
    List lapList = createList();
    Lap currentLap;
    int lapNumb = 1;
    /*Creates lap datas from previously ordered but bulky sector data List
    (with the help of createLapFromSectorList funtion) and adds them to a List*/
    for(int i = 0; i < sectorList.size;i+=maxSector_id)
    {
        currentLap = createLapfromSectorList(sectorList,i,i+maxpoint_id,lapNumb);
        currentLap.racer_id = racer_id;
        add_value(&lapList,&currentLap,sizeof(Lap));
        lapNumb++;
    }

    free_list(&sectorList);
    return lapList;
}

//frees more complex LapList type
void free_LapList(List *LapList)
{
    Node *head = LapList->head;
    Node *tail = LapList->tail;
    Lap current;
    for(Node *first = head->next;first!=tail;first = first->next)
    {
        current = *(Lap *)first->data;
        free_list(&current.sectors);
    }
    free_list(LapList);
}

/*
    It creates a complex data structure which contains every data about the race.
    It returns an array of Lists which contain Lap type structs which other Lists
    with Sector data type.
    The SIZE of the (returned) array is always EQUIVALENT with the (parameter) racers.size.
*/  
List *createTotalRaceArray(List racers,List sensingList)
{   
    //Creating an array of LapLists
    List *TotalRaceArray = (List *) malloc(sizeof(List)*racers.size);
    if(!TotalRaceArray)
    {
        return NULL;    
    }
    // It adds every racer's every Lap into the TotalRaceArray
    for(int i = 0; i < racers.size;i++)
    {
        TotalRaceArray[i] = createLapList(sensingList,getRacerfromList(racers,i).racer_id);
    }
    return TotalRaceArray;
}

//It returns how many times was the racer in the top X of sectors at the given Lap
int numbInTop(int lapindex,int racer,List TotalRaceArray[],int size,int TopNumb)
{
    Lap lap = getLapfromList(TotalRaceArray[racer],lapindex);
    List racersectors = lap.sectors;
    int numbOfSectors = racersectors.size;
    Lap current;
    int inTop = 0;
    //It compares the racer's sector to everone else's
    for(int i = 0; i < numbOfSectors; i++)
    {
        int racersectorTime = getSectorfromList(racersectors,i).sectorTime;
        int smaller = 0;
        //Checking for everyone else
        for(int k = 0; k < size; k++)
        {
            if(k!=racer)
            {
                current = getLapfromList(TotalRaceArray[k],lapindex);
                //Counting how many faster sectors there are
                if(getSectorfromList(current.sectors,i).sectorTime<racersectorTime)
                {
                    smaller++;
                }
            }
        }
        if(smaller < TopNumb)
        {
            inTop++;
        }
    }
    return inTop;
}

// returns which place the given racer achieved in the given Lap
int placeinLap(int lapindex,int racer,List TotalRaceArray[],int size)
{
    //racer's lapTime
    int lapTime = getLapfromList(TotalRaceArray[racer],lapindex).lapTime;
    int currentlapTime;
    int faster = 0;
    for(int i = 0; i < size; i++)
    {
        if(i!=racer)
        {
            //other racer's
            currentlapTime = getLapfromList(TotalRaceArray[i],lapindex).lapTime;
            if(currentlapTime<lapTime)
            {
                faster++;
            }
        }
    }
    return faster + 1;
}

//It adds points to every Lap
void addPoints(List TotalRaceArray[],int size,int TopNumb)
{
    //Everyone goes the same number of laps, so the first 
    //racer's number of laps is equal to the rest.
    int numbOfRacers = size;
    int numbOfLaps = TotalRaceArray->size;
    Lap *current;
    //goes through every
    for(int i = 0; i < numbOfLaps; i++)
    {
        //goes through every racer
        for(int k = 0; k < numbOfRacers;k++)
        {
            //gets current racer's Lap
            current = (Lap *) get(TotalRaceArray[k],i);
            current->lapPoint = (numbOfRacers - placeinLap(i,k,TotalRaceArray,size) + 1) + numbInTop(i,k,TotalRaceArray,size,TopNumb);
        }
    }
}

//returns id of the fastest racer in the whole race
int fastestRacer_id(List TotalRaceArray[],int size)
{
    Lap first = getLapfromList(TotalRaceArray[0],0);
    int racer_id = first.racer_id;
    int lapNumb = TotalRaceArray->size;
    int fastest = first.lapTime;
    Lap current;
    //searching for minimum of laptime
    for(int i = 0; i < size; i++)
    {
        for(int k = 0; k < lapNumb;k++)
        {
            current = getLapfromList(TotalRaceArray[i],k);
            if(current.lapTime < fastest)
            {
                fastest = current.lapTime;
                racer_id = current.racer_id;
            }
        }
    }
    return racer_id;
}


List calculateResult(int fastest,int value,int TopNumb,List racers,List sensinglist)
{
    //creating complex data structure
    List *TotalRaceArray = createTotalRaceArray(racers,sensinglist);
    //adding points to Laps
    addPoints(TotalRaceArray,racers.size,TopNumb);
    int numbOfLaps = TotalRaceArray->size;
    int sum;
    int racer_id;
    //Total score calculation/racer
    //searching through racers
    for(int i = 0; i < racers.size;i++)
    {
        sum = 0;
        racer_id = getLapfromList(TotalRaceArray[i],0).racer_id;
        //sum of the lapPoints/racer
        for(int k = 0; k < numbOfLaps; k++)
        {
            sum += getLapfromList(TotalRaceArray[i],k).lapPoint;
        }
        //searching for racer and adding points
        for(int j = 0; j < racers.size; j++)
        {
            Racer *current = (Racer *) get(racers,j);
            if(racer_id==current->racer_id)
            {
                current->point = sum;
                break;
            }
        }
    }
    //Adding extra point for the fastest Lap
    if(fastest)
    {
        Racer *current;
        int fastest_id = fastestRacer_id(TotalRaceArray,racers.size);
        for(int i = 0; i < racers.size; i++)
        {
            current = (Racer *) get(racers,i);
            if(current->racer_id==fastest_id)
            {
                current->point += value;
                break;
            }
        }
    }
    //freeing up memory being used by LapLists
    for(int i = 0; i < racers.size;i++)
    {
        free_LapList(&TotalRaceArray[i]);
    }
    //Freeing up array of List type structs
    free(TotalRaceArray);
    return racers;
}

//writes the racers' points into the given file
void writeResult(List racers,char filename[])
{
    if(filename[0]=='\0')
    {
        printf("File name is empty");
        return;
    }
    FILE *f = fopen(filename,"w");
    if(!f)
    {
        printf("%s could not be created/opened",filename);
        return;
    }
    Racer current;
    fprintf(f,"NAME;SCORE\n");
    for(int i = 0; i < racers.size; i++)
    {
        current = getRacerfromList(racers,i);
        fprintf(f,"%s;%d\n",current.name,current.point);
    }
    int success = fclose(f);
    if(success!=0)
    {
        printf("%s could not be closed",filename);
    }
}

//prints racers on the podium to stdo 
void printTop(List racers,int x_position)
{
    int first_point = 0;
    int second_point = 0;
    int third_point = 0;
    Racer current;
    //searching for points of first, second and third place
    for(int k = 0; k < 3; k++){
        for(int i = 0; i < racers.size; i++)
        {
            current = getRacerfromList(racers,i);
            if(current.point>first_point)
            {
                first_point = current.point;
            }
            if(second_point<current.point&&current.point<first_point)
            {
                second_point = current.point;
            }
            if(third_point<current.point&&current.point<second_point)
            {
                third_point = current.point;
            }
        }
    }
    //prints out every racer which corresponds to the first/second/third place scores
    //gotoxy is cursor positioning in order to get NICE lines. =D
    for(int i = 0; i < racers.size;i++)
    {
        current = getRacerfromList(racers,i);
        if(current.point==first_point)
        {
            gotoxy(x_position,getState().y_position);
            printf("1. place:\n");
            gotoxy(x_position,getState().y_position);
            printf("%s\n",current.name);
        }
        if(current.point==second_point)
        {
            gotoxy(x_position,getState().y_position);
            printf("2. place:\n");
            gotoxy(x_position,getState().y_position);
            printf("%s\n",current.name);
        }
        if(current.point==third_point)
        {
            gotoxy(x_position,getState().y_position);
            printf("3. place:\n");
            gotoxy(x_position,getState().y_position);
            printf("%s\n",current.name);
        }
    }
}