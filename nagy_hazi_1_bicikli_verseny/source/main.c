#include"debugmalloc.h"
#include"data.h"
#include"menu.h"
#include<stdio.h>
#include<string.h>
/*
    It controls the menu and pages and functions of the whole project.
*/

int menu(List *racers,List *sensinglist)
{
    //settings
    int fastest = 0;
    //value of extra point
    int extra_point = 1;
    //TOP X
    int TopNumb = 3;
    //stores strings read from user
    char buffer[51];
    char name[51];
    char id[10];
    char filename[51];
    //enum for key presses->data.c
    enum Arrow in;
    //windows.h struct position in window
    COORD c;
    //bool if main menu is shown
    char isShown = 0;
    //bool: two times key press not needed in database and settings page
    char back;
    //setting up cmd
    changeFont(30);
    adjust_window_size(38,20);
    while (1)
    {
        if(!isShown){
            show_main_menu();
            isShown = 1;
        }
        //read key press->menu.c
        in = navigate();
        switch (in)
        {
            //Start Scoring
            case ONE:   //List of racers with points->data.c
                        *racers = calculateResult(fastest,extra_point,TopNumb,*racers,*sensinglist);
                        //Clearing screen
                        system("cls");
                        isShown = 0;
                        //Title with frame->menu.c
                        c = print_logo_title(21,4,getState().x_window,getState().y_window,"Enter the filename");
                        //cursor positioning->data.c
                        gotoxy(c.X,c.Y+1);
                        //clear filename
                        filename[0] = '\0';
                        fgets(buffer,51,stdin);
                        sscanf(buffer,"%s",filename);
                        system("cls");
                        //Title with frame->menu.c
                        c = print_logo_title(21,4,getState().x_window,getState().y_window,"ON THE PODIUM");
                        //writing racers with points to file->data.c
                        writeResult(*racers,filename);
                        printTop(*racers,c.X);
                        //cursor positioning,getState()->data.c
                        gotoxy(c.X,getState().y_position);
                        //printing instruction for ESC and quit->menu.c
                        instructions(0,c.X);
                        //wait for back or escape after calculation
                        while(1)
                        {
                            in = navigate();
                            if(in==ESC)
                            {
                                return 0;
                            }
                            if(in==BACK)
                            {
                                break;
                            }
                        }
                        break;
            //Database
            case TWO:
                    //database page -> menu.c
                    show_edit_database();
                    //main is not shown
                    isShown = 0;
                    //back not pressed yet
                    back = 0;
                    switch(navigate())
                    {
                        //Add racer/DATABASE
                        case ONE:
                            //Clearing screen
                            system("cls");
                            name[0] = '\0';
                            filename[0] = '\0';
                            //Title with frame
                            c = print_logo_title(21,4,getState().x_window,getState().y_window,"New racer");
                            gotoxy(c.X,getState().y_position);
                            printf("Don't use accented letters!");
                            //cursor positioning to next line
                            gotoxy(c.X,getState().y_position+1);
                            printf("Name:");
                            //reading in name
                            fgets(buffer,51,stdin);
                            sscanf(buffer,"%[^\n]s",name);
                            gotoxy(c.X,getState().y_position+1);
                            printf("ID:");
                            //reading in ID
                            fgets(buffer,51,stdin);
                            sscanf(buffer,"%s",id);
                            gotoxy(c.X,getState().y_position+1);
                            printf("Import filename:");
                            //reading in filename for import
                            fgets(buffer,51,stdin);
                            sscanf(buffer,"%s",filename);
                            gotoxy(c.X,getState().y_position+1);
                            if(addCompetitor(name,id,filename,racers,sensinglist)==0)
                            {
                                printf("Successful import\n");
                                gotoxy(c.X,getState().y_position);
                            }
                            else
                            {
                                gotoxy(c.X,getState().y_position+1);
                                printf("Unsuccessful import\n");
                                gotoxy(c.X,getState().y_position);
                            }
                            //printing instruction for ESC and quit->menu.c
                            instructions(0,c.X);
                            break;
                    //Delete racer/DATABASE
                    case TWO:
                        //Clearing screen
                        system("cls");
                        //Title with frame
                        c = print_logo_title(21,4,getState().x_window,getState().y_window,"Delete racer");
                        gotoxy(c.X,getState().y_position);
                        printf("Don't use accented letters!");
                        gotoxy(c.X,getState().y_position+1);
                        printf("Name:");
                        //reading in name
                        fgets(buffer,51,stdin);
                        sscanf(buffer,"%[^\n]",name);
                        gotoxy(c.X,getState().y_position+1);
                        printf("ID:");
                        //reading in ID
                        fgets(buffer,51,stdin);
                        sscanf(buffer,"%s",id);
                        gotoxy(c.X,getState().y_position+1);
                        //deleting racer
                        if(deleteCompetitor(name,id,racers,sensinglist)==0)
                        {
                            printf("%s",name);
                            printf(" is successfully deleted");
                            gotoxy(c.X,getState().y_position);
                        }
                        //printing instruction for ESC and quit->menu.c
                        instructions(0,c.X);
                        break;
                    case ESC:
                        return 0;
                        break;
                    case BACK:
                        //back pressed
                        back = 1;
                        break;
                    default: break;
                }
                /*skip loop if back pressed
                otherwise wait for quit*/
                while(!back)
                {
                    in = navigate();
                    if(in==ESC)
                    {
                        return 0;
                    }
                    if(in==BACK)
                    {
                        break;
                    }
                }
                break;
            //Settings
            case THREE:
                //shows settings page -> menu.c
                show_settings();
                isShown = 0;
                //back not pressed yet
                back = 0;
                switch(navigate())
                {
                    //TOP X / SETTINGS
                    case ONE:
                    system("cls");
                    c = print_logo_title(21,4,getState().x_window,getState().y_window,"TOP X");
                    gotoxy(c.X,getState().y_position);
                    printf("Current TOP value: %d\n",TopNumb);
                    gotoxy(c.X,getState().y_position);
                    printf("Add new TOP value: ");
                    fgets(buffer,51,stdin);
                    sscanf(buffer,"%d",&TopNumb);
                    instructions(0,c.X);
                    break;
                    //Fastest Lap point /SETTINGS
                    case TWO: 
                    system("cls");
                    c = print_logo_title(21,4,getState().x_window,getState().y_window,"Fastest lap point");
                    gotoxy(c.X,getState().y_position);
                    printf("Points for the\n");
                    gotoxy(c.X,getState().y_position);
                    //print current state isOn()->menu.c
                    printf("fastest lap is %s\n",isOn(fastest));
                    if(fastest)
                    {
                        gotoxy(c.X,getState().y_position);
                        printf("Point: %d\n",extra_point);
                    }
                    gotoxy(c.X,getState().y_position);
                    printf("Turn on(1)/Turn OFF(0):");
                    fgets(buffer,51,stdin);
                    sscanf(buffer,"%d",&fastest);
                    if(fastest)
                    {
                        printf("\n");
                        gotoxy(c.X,getState().y_position);
                        printf("Value of point:");
                        fgets(buffer,51,stdin);
                        sscanf(buffer,"%d",&extra_point);
                    }
                    //printing instruction for ESC and quit->menu.c
                    instructions(0,c.X);
                    break;
                    //Window size adjustment
                    case THREE: 
                    system("cls");
                    c = print_logo_title(21,4,getState().x_window,getState().y_window,"Window size");
                    gotoxy(c.X,getState().y_position);
                    int width;
                    int height;
                    printf("Width:");
                    //reading in width
                    fgets(buffer,51,stdin);
                    sscanf(buffer,"%d",&width);
                    printf("\n");
                    gotoxy(c.X,getState().y_position);
                    printf("Height:");
                    //reading in height
                    fgets(buffer,51,stdin);
                    sscanf(buffer,"%d",&height);
                    gotoxy(c.X,getState().y_position);
                    //Checking whether the size is correct
                    if(width<21||height<4)
                    {
                        printf("It's too small");
                        instructions(0,c.X);
                        break;
                    }
                    if(width>200||height>100)
                    {
                        printf("It's too large");
                        instructions(0,c.X);
                        break;
                    }
                    //changing window to the given size
                    adjust_window_size(width,height);
                    //printing instruction for ESC and quit->menu.c
                    instructions(0,c.X);
                    break;
                    case ESC:
                        return 0;
                        break;
                    case BACK:
                        back = 1;
                        break;
                    default: break;
                }
                //BACK and ESC from Settings Menu
                while(!back)
                {
                    in = navigate();
                    if(in==ESC)
                    {
                        return 0;
                    }
                    if(in==BACK)
                    {
                        break;
                    }
                }
                break;
            //MAIN MENU ESC
            case ESC:
                return 0;
                break;
        default:
            break;
        }       
    }
}


int main()
{
    List racers = readCompetitors();
    if(!racers.head||!racers.tail)
    {
        debugmalloc_dump();
        return -1;
    }
    List sensinglist = readSensing();
    if(!sensinglist.head||!sensinglist.tail)
    {
        free_list(&racers);
        debugmalloc_dump();
        return -1;
    }
    menu(&racers,&sensinglist);
    free_list(&racers);
    free_list(&sensinglist);
    //clear console after escape
    system("cls");
    debugmalloc_log_file("memlog.txt");
    debugmalloc_dump();
    return 0;
}