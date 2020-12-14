#ifndef HuMenu_M
#define HuMenu_M

#include<windows.h>

typedef struct ConsoleState
{
	int x_position;
	int y_position;
	int x_window;
	int y_window;
}ConsoleState;

enum Arrow{UP,DOWN,LEFT,RIGHT,ENTER,ESC,BACK,INSERT,ONE,TWO,THREE};

void adjust_window_size(int x_size, int y_size);

void changeFont(int size);

void show_main_menu();

void show_settings();

void show_edit_database();

ConsoleState getState();

void gotoxy(int x,int y);

COORD print_logo_title(int x_length,int y_length,int x_window,int y_window,char s[]);

void printLinefromPosition(COORD *coord,char s[]);

enum Arrow navigate();

void instructions(char options, int x_position);

char *isOn(int in);

#endif