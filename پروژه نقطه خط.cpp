#include <iostream>
#include<stdlib.h>
#include <cstdlib>
#include <ctime>
using namespace std;
int n;//map size
void welcome(char&, char&);//welcom,mode and level of the game+ recieving players names
void computermove(int pc[1][3]);//produces randome x,y,z for computer player
int validationcheck(int x, int y, int z, char H[6][5], char V[5][6]);//checking the validation of coordinates ,whether its a full line or out of range
int boxchecker(char, char C[5][5], char H[6][5], char V[5][6]);//checking if there is any completed square and nameing them
int freelinechecker(char H[6][5], char V[5][6]);//checking if there is any free lines left
void inboxcounter(char A, char B, char C[5][5]);//count how many boxes are B's & how many are A's

int main()
{
	char A, B;//for the first letter of players' names
	welcome(A, B);

	getchar();
	system("pause");
	system("cls");//to clear screan befor printing the map

	int x, y, z;//coordination: vertical or horizontal,row,column
	int m = 1;// counter of the loop that determindes the players turn
	char Gen[11][11];//Genaral array;a shelf to put other arrays in 
	char H[6][5];//Horizontal array ; the array of horizontal lines
	char V[5][6];//Vertical array ; the array of vertical lines
	char C[5][5];//Containing array; an array for empty boxes for the names

	//following lines give initial value of 'space' to the arrays
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < (n - 1); ++j)
		{
			H[i][j] = ' ';
		}

	}
	for (int i = 0; i < (n - 1); ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			V[i][j] = ' ';
		}

	}
	for (int i = 0; i < (n - 1); ++i)
	{
		for (int j = 0; j < (n - 1); ++j)
		{
			C[i][j] = ' ';
		}

	}
	//following lines gives the initial value of '*' and ' ' to the Genral array based on calculations, and prints the raw map
	for (int i = 0; i < (2 * n - 1); ++i)
	{
		for (int j = 0; j < (2 * n - 1); ++j)
		{
			if ((i % 2 == 0) && (j % 2 == 0))
				Gen[i][j] = '*';
			else
				Gen[i][j] = ' ';
			cout << Gen[i][j];
		}
		cout << endl;
	}
	// the main loop of the game,which gets the coordinations ,prints lines,check boxes & free lines
	for (m = 1; ; m++)
	{
		int VAL, BCH, FLC;//each are the return values of functions Validationcheck,Boxchecker & Freelinechecker
		FLC = freelinechecker(H, V);//the return value of function Freelinechecker
		if (FLC == 0)//if there was no free line...
			break;
		char X;//base on who's turn it is,their name will be inserted in char X
		do
		{

			do
			{
				if (m % 2 == 1)//first round always starts with player A,the one who entered their name first
				{
					X = A;
					printf_s("Player %c 's turn:\n", X);
					scanf_s("%d %d %d", &x, &y, &z);//getting the coordinates
				}
				if (m % 2 == 0)
				{
					X = B;
					if (X == '@')//if you chose to play with computer , its name will be @ and inserted in X
					{
						int pc[1][3];//the coordinates x,y,z must be stored in an array cause a function only can return one value
						computermove(pc);//gets a randon coordinate by generating random numbers and stors it in an array of 3 numbers :x,y,z
						printf_s("Computer's turn:\n");//getting the coordinates from the computer using computermove function
						x = pc[0][0];
						y = pc[0][1];
						z = pc[0][2];
					}
					else  if (X != '@')
					{
						printf_s("Player %c 's turn:\n", X);
						scanf_s("%d %d %d", &x, &y, &z);//getting the coordinates from player B
					}
				}

				VAL = validationcheck(x, y, z, H, V);//validation of coordinates is checked based on arrays H & V

			} while (VAL == 1);//until you get a valid coordination ,you shoud keep getting coordinates
			if (VAL == 0)//if the coordinates were fine...
			{
				if (x == 0)//if the first number was 0 ,we want to print a horizontal line
				{
					H[y - 1][z - 1] = '-';//insert the '-' value in the relavent H array member;

				}
				if (x == 1)//if the first number was 1 ,we want to print a vertical line
				{
					V[y - 1][z - 1] = '|';//insert the '|' value in the relavent V array member;
				}
				BCH = boxchecker(X, C, H, V);//check if any box is completed


			}
			//the following lines put the now finely valued minor arrays in the General array based on calculated indexes
			int q, p;
			for (q = 0; q < n; ++q)
			{
				for (p = 0; p < (n - 1); ++p)
				{
					Gen[2 * q][2 * p + 1] = H[q][p];
				}
			}
			for (q = 0; q < n - 1; ++q)
			{
				for (p = 0; p < n; ++p)
				{
					Gen[2 * q + 1][2 * p] = V[q][p];
				}
			}
			for (q = 0; q < (n - 1); ++q)
			{
				for (p = 0; p < (n - 1); ++p)
				{
					Gen[2 * q + 1][2 * p + 1] = C[q][p];
				}
			}
			for (int i = 0; i < (2 * n - 1); ++i)
			{
				for (int j = 0; j < (2 * n - 1); ++j)
				{
					cout << Gen[i][j];
				}
				cout << endl;
			}
			FLC = freelinechecker(H, V);//check if there is any free lines left


		} while (BCH == 1 && FLC == 1);//to continue this loop we need two conditions : 1)a box must be completed & 2)there shoud be a free line


		getchar();
		system("pause");
		system("cls"); //clear the screan in each change of player

		//the following loop shows the latest changed map for the new player to help them make better moves 
		for (int i = 0; i < (2 * n - 1); ++i)
		{
			for (int j = 0; j < (2 * n - 1); ++j)
			{
				cout << Gen[i][j];
			}
			cout << endl;
		}

	}
	inboxcounter(A, B, C);//ones your out of free lines ,now is time to count how many boxes each player's got

	return 0;
}

void welcome(char& A, char& B)
{
	char name1[100];
	char name2[100];
	int x, y, z;
	cout << "Welcome to dots and boxes\n";
	cout << "Please choose your playing mode\n";
	cout << "1.two players\n2.playing with computer\n";
	cin >> x;
	switch (x)
	{
	case 1:
		cout << "player one:please enter your name\n";
		cin >> name1;
		A = name1[0];//we need only the first letter of players name
		cout << "You will be known as :" << A << endl;
		cout << "player two:please enter your name\n";
		cin >> name2;
		B = name2[0];//we need only the first letter of players name
		cout << "You will be known as :" << B << endl;

		cout << "Select the level of game:\n";
		cout << "1.Normal(4*4)\n2.Professional(6*6)\n";
		cin >> y;
		switch (y)
		{
		case 1:
			n = 4;//gives the global variable the size of the map
			break;
		case 2:
			n = 6;//gives the global variable the size of the map
			break;
		}
		break;




	case 2:
		cout << "Please enter your name\n";

		cin >> name1;
		A = name1[0];
		cout << "You will be known as :" << A << endl;
		B = '@';//this must be the symbol of computer player 
		cout << "Computer will be known as :" << B << endl;

		cout << "Select the level of game:\n";
		cout << "1.Normal(4*4)\n2.Professional(6*6)\n";
		cin >> y;
		switch (y)
		{
		case 1:
			n = 4;
			break;
		case 2:
			n = 6;
			break;
		}


		break;
	}

}

void computermove(int pc[1][3])
{
	int j, x, y, z;
	srand(time(0));

	x = rand() % 2;
	if (x == 0)
	{
		y = rand() % n + 1;
		z = rand() % (n - 1) + 1;
	}
	if (x == 1)
	{
		y = rand() % (n - 1) + 1;
		z = rand() % n + 1;
	}
	pc[0][0] = x;
	pc[0][1] = y;
	pc[0][2] = z;
	return;
}

int validationcheck(int x, int y, int z, char H[6][5], char V[5][6])//based on x,y,z and arrays H&V checks the validation of inputs ,gives an integer flag as out put
{
	int flag = 0;
	if (x == 0 || x == 1)
	{
		if (x == 0)
		{
			if ((y <= 0) || (y > n) || (z <= 0) || (z > (n - 1)) || (H[y - 1][z - 1] == '-'))//out of range or full lines
			{
				cout << "invalid coordinates , please try again\n";
				flag = 1;
			}
		}
		if (x == 1)
		{
			if ((y <= 0) || (y > (n - 1)) || (z <= 0) || (z > n) || (V[y - 1][z - 1] == '|'))//out of range or full lines
			{
				cout << "invalid coordinates , please try again\n";
				flag = 1;
			}
		}

	}
	else// for invalid first number
	{
		cout << "invalid coordinates , please try again\n";
		flag = 1;
	}
	return flag;//flag 1 means invalid and flag 0 means valid
}


int  boxchecker(char X, char C[5][5], char H[6][5], char V[5][6])
{
	int BCH = 0;
	char d = '|', w = '-';//as sample desired values
	for (int i = 0; i < (n - 1); ++i)
	{
		for (int j = 0; j < (n - 1); ++j)
		{
			//check if there was a couple of sequentialy filled horizontal array member in a same collumn,and their relavent vertical members are fiiled too, and its container array is not formally named
			if (H[i][j] == w && H[i + 1][j] == w && V[i][j] == d && V[i][j + 1] == d && C[i][j] == ' ')
			{
				C[i][j] = X;//put the players name in the box(in the relavent member of Containing array)
				BCH = 1;//a box was made , so the player shoud get a reward
			}

		}
	}
	return BCH;//BCH=0 means no boxes were made and BCH=1 means a box was made
}


int freelinechecker(char H[6][5], char V[5][6])
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < (n - 1); ++j)
		{
			if ((H[i][j] == ' ') || (V[i][j] == ' '))//if there was a free mamber in  vertical or horizontal array
				return 1;// there is still a free line

		}
	return 0;//no free lines left

}


void inboxcounter(char A, char B, char C[5][5])
{
	int nA = 0;
	int nB = 0;
	for (int i = 0; i < (n - 1); ++i)
	{
		for (int j = 0; j < (n - 1); ++j)
		{
			if (C[i][j] == A)
				nA = nA + 1;
			if (C[i][j] == B)
				nB = nB + 1;
		}
	}
	if (nB > nA)
		cout << B << "is the winner";
	if (nB < nA)
		cout << A << " is the winner";
	if (nB == nA)
		cout << "TIE \n Sometimes no one wins";

}