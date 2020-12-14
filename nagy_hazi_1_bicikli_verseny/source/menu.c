/*
	This library contains function for the menu visualisation
	and to control parts of the terminal, such as the cursor,
	font and window size
*/
#include<stdio.h>
#include<windows.h>
#include<conio.h>

/*
windows.h function->
Retrieves a handle to the specified standard device
(standard output)*/
#define hStdout GetStdHandle(STD_OUTPUT_HANDLE)
//enum for key mapping
enum Arrow{UP,DOWN,LEFT,RIGHT,ENTER,ESC,BACK,INSERT,ONE,TWO,THREE};

//struct for the status of console
typedef struct ConsoleState
{
	int x_position;
	int y_position;
	int x_window;
	int y_window;
}ConsoleState;


//change the size of window
void adjust_window_size(int x_size, int y_size)
{
	char s[40];
	//changing the actual size
	sprintf(s,"mode con: cols=%d lines=%d",x_size,y_size);
	system(s);
	//changing cmd to UTF-8
	system("CHCP 65001 >nul");
}

//change the size of Font in cmd
void changeFont(int size) 
{	/*Font struct in windows.h
	docs:
	https://docs.microsoft.com/en-us/windows/console/console-font-infoex
	*/
	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(font);
	font.nFont = 0;
	font.dwFontSize = (COORD){0,size};
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;
	//Font type
	wcscpy(font.FaceName, L"Consolas");
	//actually changing the font
	SetCurrentConsoleFontEx(hStdout, FALSE, &font);
}

//returns basic information about the console such as window size(x,y) and current cursor position(x,y)
ConsoleState getState()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hStdout,&info);
	return (ConsoleState) {info.dwCursorPosition.X,info.dwCursorPosition.Y,info.dwMaximumWindowSize.X,info.dwMaximumWindowSize.Y};
}

//prints a rectangle around the given text and returns coordinates of the lower left corner
COORD print_logo_title(int x_length,int y_length,int x_window,int y_window,char s[]) 
{
	int string_length;
	for(string_length = 0; s[string_length] != '\0'; string_length++);
	//left and right margin from window
	int margin_x = (x_window-x_length)/2;
	//left and right padding of text from window
	int padding_x = ((x_window-string_length)/2)+1;
	int printed = 0;
	y_length--;
	for(int i = 0; i < y_length; i++)
	{
		int k;
		for(k = 0; k < x_window; k++)
		{	
			if(k < margin_x || k > x_window-margin_x)
			{
				printf(" ");
			}
			else
			{
				//First or last row ans within the margin
				if((i==0&&k>margin_x&&k<x_window-margin_x)||(i==y_length-1&&k>margin_x&&k<x_window-margin_x))
				{
					printf("═");
				}
				else if(k==margin_x||k==x_window-margin_x)
				{
					if((i==0||i==y_length-1)&&k==margin_x)
					{
						//Top left corner
						if(i==0)
						{
							printf("╔");
						}
						//Bottom left corner
						else if(i==y_length-1)
						{
							printf("╚");
						}
					}
					else if((i==0||i==y_length-1)&&k==x_window-margin_x)
					{	
						//Top right corner
						if(i==0)
						{
							printf("╗");
						}
						//Bottom right corner
						else if(i==y_length-1)
						{
							printf("╝");
						}
					}
					//Left and right vertical line
					else
					{
						printf("║");
					}
				}
				//Filling out empty space
				else if(((i != (y_length/2))||(i==(y_length/2)&&(k<padding_x||k>padding_x+string_length-1)&& k >margin_x&&k<x_window-margin_x)))
				{
					printf(" ");
				}
				if(i==(y_length/2)&&k==padding_x&&!printed)
				{
					//Writing the text in the box and compensating with index
					k -= 1;
					printf(s);
					printed = 1;
				}	
			}
		}
	}
	return (COORD) {margin_x,y_length};
}

//move cursor to (x,y) position
void gotoxy(int x,int y)
{
	SetConsoleCursorPosition(hStdout,(COORD) {x,y});
}

//keyMapping to enum Arrow
enum Arrow getDirection()
{
	unsigned char a = _getch();
	if(a==224)
	{
		unsigned char b = _getch();
		switch(b)
		{
			//Arrows
			case 72: return UP;
			case 80: return DOWN;
			case 75: return LEFT;
			case 77: return RIGHT;
			//Insert key (not in use at the moment)
			case 82: return INSERT;
			default: return -1;
		}
	}
	else
	{
		switch (a)
		{
			// 1-key
			case 49: return ONE;
			// 2-key
			case 50: return TWO;
			// 3-key
			case 51: return THREE;
			// ENTER-key (not used at the moment)
			case 13: return ENTER;
			//ESC-key
			case 27: return ESC;
			// Q-key
			case 113: return BACK;
			default:
			return -1;
		}
	}
	
}

//it provides cursor navigation with arrow keys(not used)
//directly returns other defined keys in enum
enum Arrow navigate()
{
	int x = getState().x_position;
	int y = getState().y_position;
	int x_window = getState().x_window;
	int y_window = getState().y_window;
	switch (getDirection())
	{
		case UP:
			if(y!=0)
			{
				gotoxy(x,y-1);
			}
			break;
		case DOWN:
			if(y<y_window)
				{
					gotoxy(x,y+1);
				}
			break;
		case LEFT:
			if(x!=0)
			{
				gotoxy(x-1,y);
			}
			break;
		case RIGHT:
			if(x<x_window)
			{
				gotoxy(x+1,y);
			}
			break;
		case ESC:
			return ESC;
		case ENTER:
			return ENTER;
		case BACK:
			return BACK;
		case INSERT:
			return INSERT;
		case ONE:
			return ONE;
		case TWO:
			return TWO;
		case THREE:
			return THREE;
	default:
		return -1;
	}
	return -1;
}

//Prints the given text from the given coordinates
void printLinefromPosition(COORD *coord,char s[])
{
	gotoxy(coord->X-4,coord->Y);
	printf("%s\n",s);
	coord->Y += 1;
}

//Prints main menu to the screen
void show_main_menu() 
{
	int x_size = getState().x_window;
	int y_size = getState().y_window;
	int width = 21;
	int height = 4;
	if(x_size<=width)
	{
		width = x_size-1;
	}
	if(y_size<=height)
	{
		height = y_size-1;
	}
	system("cls");
	char title[] = "Main Menu";
	COORD margin = print_logo_title(width,height,x_size,y_size,title);
	printLinefromPosition(&margin,"(1) Start scoring");
	printLinefromPosition(&margin,"(2) Database");
	printLinefromPosition(&margin,"(3) Settings");
	margin.Y++;
	printLinefromPosition(&margin,"Press the number of option");
	printLinefromPosition(&margin,"Press ESC to exit");
	gotoxy(margin.X,margin.Y+1);
}

//prints settings page to screen
void show_settings() 
{
	int x_size = getState().x_window;
	int y_size = getState().y_window;
	int width = 21;
	int height = 4;
	if(x_size<=width)
	{
		width = x_size-1;
	}
	if(y_size<=height)
	{
		height = y_size-1;
	}
	system("cls");
	char title[] = "Settings";
	COORD margin = print_logo_title(width,height,x_size,y_size,title);
	printLinefromPosition(&margin,"(1) TOP X");
	printLinefromPosition(&margin,"(2) Fastest lap point");
	printLinefromPosition(&margin,"(3) Window size");
	margin.Y++;
	printLinefromPosition(&margin,"Press the number of option");
	printLinefromPosition(&margin,"Press q to go back");
	printLinefromPosition(&margin,"Press ESC to exit");
	gotoxy(margin.X,margin.Y+1);
}

//Prints database page to screen
void show_edit_database() 
{
	int x_size = getState().x_window;
	int y_size = getState().y_window;
	int width = 21;
	int height = 4;
	if(x_size<=width)
	{
		width = x_size-1;
	}
	if(y_size<=height)
	{
		height = y_size-1;
	}
	system("cls");
	char title[] = "Edit database";
	COORD margin = print_logo_title(width,height,x_size,y_size,title);
	printLinefromPosition(&margin,"(1) Add new racer");
	printLinefromPosition(&margin,"(2) Delete racer");
	margin.Y++;
	printLinefromPosition(&margin,"Press the number of option");
	printLinefromPosition(&margin,"Press q to go back");
	printLinefromPosition(&margin,"Press ESC to exit");
	gotoxy(margin.X,margin.Y+1);
}

//Prints navigation instructions
//for user to the screen
void instructions(char options,int x_position)
{
	printf("\n");
	if(options){
		gotoxy(x_position,getState().y_position);
		printf("Press 1/2/3\n");
		gotoxy(x_position,getState().y_position);
		printf("for the options above\n");
		printf("\n");
	}
	gotoxy(x_position,getState().y_position);
	printf("Press q to go back\n");
	printf("\n");
	gotoxy(x_position,getState().y_position);
	printf("Press ESC to quit the program\n");
	gotoxy(x_position,getState().y_position);
}

//returns ON OFF to the boolean value
char *isOn(int in)
{
	return in ? "ON":"OFF";
}