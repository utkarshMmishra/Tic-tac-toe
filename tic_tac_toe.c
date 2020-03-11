
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <windows.h>

/**these are global variables i.e no need to declare them again in code*/
int board[10] = {2,2,2,2,2,2,2,2,2,2};                   
/**array to check whether there is a place in the grid*/
														///if value is 2 then place is vacant u can put X or 0
														
int turn = 1,flag = 0;									///if turn increases till 9 and still no one wins its draw
int player,comp;

void menu();
void go(int n);
void start_game();
void check_draw();
void draw_board();
void player_first();
void put_X_O(char ch,int pos);
COORD coord= {0,0}; /// this is global variable
///center of axis is set to the top left cornor of the screen


void gotoxy(int x,int y)                  ///go to x y
{
	///This function is created to place elements by giving their x-y co-ordinate in place of using
	///spaces to create the structure of grid
	
	///this is flexible(responsive)
	
	///this function is used to print text in any part of the game
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


void help()
{
	system("cls");
	printf("Select whether you want to play first or not\n");
	printf("Then select grid from 1 to 9 in which you want to place your character\n");
	printf("Repeat this until result\n");
	printf("Select whether you want to play again or not\n");
	gotoxy(30,10);
	printf("Press enter to go back");
	getch();
	menu();
}


void main()
{
    system("cls");
    menu();                                ///main function
    getch();

}

void menu()
{
    int choice;
    system("cls");                           /// system("cls");  used to clear screen linux users write clear in place of cls
    printf("\n--------MENU--------");
    printf("\n1 : Play with X");
    printf("\n2 : Play with O");
    printf("\n3 : Help");
    printf("\n4 : Exit");
    printf("\nEnter your choice:>");
    scanf("%d",&choice);
    turn = 1;
    switch (choice)
    {
	    case 1:
	        player = 1;
	        comp = 0;
	        player_first();                
	        break;
	    case 2:
	        player = 0;
	        comp = 1;
	        break;
	    case 3:
	    	help();
	    case 4:
	        exit(1);
	    default:
	        menu();
    }
}

int make2()        ///make computers move
{
	///the computer first check if centre is vacant or not if not it will place element in center else
	///check for other conditions because placing in centre gives one the highest probability of winning
    if(board[5] == 2)           
        return 5;
    if(board[2] == 2)
        return 2;
    if(board[4] == 2)
        return 4;
    if(board[6] == 2)
        return 6;
    if(board[8] == 2)
        return 8;
    return 0;
}

int make4()                   ///make computers move
{
    if(board[1] == 2)
        return 1;
    if(board[3] == 2)
        return 3;
    if(board[7] == 2)
        return 7;
    if(board[9] == 2)
        return 9;
    return 0;
}

int posswin(int p)
{
/// p==1 then X   p==0  then  O
    int i;
    int check_val,pos;

    if(p == 1)
        check_val = 18;                ///u can assign some different value in go function and modify check_val value here
    else
        check_val = 50;

    i = 1;
    while(i<=9)///row check
    {
        if(board[i] * board[i+1] * board[i+2] == check_val)
        {
            if(board[i] == 2)
                return i;
            if(board[i+1] == 2)
                return i+1;
            if(board[i+2] == 2)
                return i+2;
        }
        i+=3;
    }

    i = 1;
    while(i<=3)///column check
    {
        if(board[i] * board[i+3] * board[i+6] == check_val)
        {
            if(board[i] == 2)
                return i;
            if(board[i+3] == 2)
                return i+3;
            if(board[i+6] == 2)
                return i+6;
        }
        i++;
    }
 	///diagonal check
    if(board[1] * board[5] * board[9] == check_val)
    {
        if(board[1] == 2)
            return 1;
        if(board[5] == 2)
            return 5;
        if(board[9] == 2)
            return 9;
    }
	///diagonal check
    if(board[3] * board[5] * board[7] == check_val)
    {
        if(board[3] == 2)
            return 3;
        if(board[5] == 2)
            return 5;
        if(board[7] == 2)
            return 7;
    }
    return 0;
}

void go(int n)
{
    if(turn % 2)
        board[n] = 3;
    else
        board[n] = 5;
    turn++;
}

void player_first()
/** player plays */
{
    int pos,choice,i;

    check_draw();                          ///check for draw
    draw_board();                          /// draw board for X and 0
    gotoxy(30,18);
    printf("Your Turn :> ");
    scanf("%d",&pos);

    if(board[pos] != 2)
        player_first();                  ///until you dont put right position the computer wont play its move



    if(pos == posswin(player))          
    {
        go(pos);
        draw_board();
        gotoxy(30,20);
        //textcolor(128+RED);
        printf("Player Wins");
        getch();
        printf("\n\nPress 1 to play again or 0 to exit :>");
        scanf("%d",&choice);
        if(choice==1)
        {
        	for(i=0;i<11;i++)
        	{
        		board[i]=2;
			}
        	system("cls");
        	menu();
		}
		else
		{
			exit(1);
		}
    }
	/**
	suppose if player enters x at position 1,2 then the below if condition wont be executed
	and board[0],board[1] will be =3
	if player enters x at position 3 then before assigning value board[3]=2
	then posswin function will be evaluated for row check i.e 3*3*2=18 and its third if statement will return value 3
	thus the below if condition is satisfied and players win
	
	
	similary for column check and diagonal check
	*/
	
    go(pos);
    draw_board();                /// this function is used again so to update with position of X and 0
    start_game();                ///computers turn
}

void start_game()
/** computer plays */
{
	int choice,i;
/// p==1 then X   p==0  then  O
    if(posswin(comp))                 ///first checking if computer is winning or not
    {
        go(posswin(comp));
        flag = 1;
    }
    else if(posswin(player))         ///if not checking if player is winning or not   
        go(posswin(player));
    else if(make2())                ///if no one wins omputer makes its move
        go(make2());
    else
        go(make4());
    draw_board();

    if(flag)
    {
        gotoxy(30,20);
        //textcolor(128+RED);
        printf("Computer wins");
        getch();
        printf("\n\nPress 1 to play again or 0 to exit :>");
        scanf("%d",&choice);
        if(choice==1)
        {
        	for(i=0;i<11;i++)           ///resest board values to 2 else last match's board will be displayed
        	{
        		board[i]=2;
			}
        	system("cls");
        	menu();
		}
		else
		{
			exit(1);
		}
    }
    else 
        player_first();                  ///players turn
}

void check_draw()
{
    if(turn > 9)
    {
        gotoxy(30,20);                     
        //textcolor(128+RED);
        printf("Game Draw");
        getch(); 
		 printf("\n\nPress 1 to play again or 0 to exit :>");
        scanf("%d",&choice);
        if(choice==1)
        {
        	for(i=0;i<11;i++)
        	{
        		board[i]=2;
			}
        	system("cls");
        	menu();
		}
		else
		{
			exit(1);
		}
    }
}

void draw_board()
{
    int j;

    for(j=9; j<17; j++)
    {
        gotoxy(35,j);								 ///here we keep on changing the y co-ordinate keeping x constant to draw vertical
        printf("|       |");                       
    }
    gotoxy(28,11);                                  
    printf("-----------------------");               
    gotoxy(28,14);
    printf("-----------------------");

    for(j=1; j<10; j++)
    {
        if(board[j] == 3)
            put_X_O('X',j);
        else if(board[j] == 5)
            put_X_O('O',j);
    }
}

void put_X_O(char ch,int pos)
{
    int m;
    int x = 31, y = 10;

    m = pos;

    if(m > 3)
    {
        while(m > 3)
        {
            y += 3;
            m -= 3;
        }
    }
    if(pos % 3 == 0)
        x += 16;
    else
    {
        pos %= 3;
        pos--;
        while(pos)
        {
            x+=8;
            pos--;
        }
    }
    gotoxy(x,y);
    printf("%c",ch);
}
