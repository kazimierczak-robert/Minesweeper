#include "game_board.h"

game_board::game_board(std::string beg_int_exp)
{
	fields = NULL;
	this->beg_int_exp = beg_int_exp;

	if (beg_int_exp.compare("Beginner") == 0)
	{
		g_b_width = 9;
		g_b_height = 9;
		mines_number = 10;
	}
	if (beg_int_exp.compare("Intermediate") == 0)
	{
		g_b_width = 16;
		g_b_height = 16;
		mines_number = 40;
	}
	if (beg_int_exp.compare("Expert") == 0)
	{
		g_b_width = 30;
		g_b_height = 16;
		mines_number = 99;
	}

	this->create_fields();

	srand(time(NULL));
	this->rand_mines();
	this->neighbours_mines();
}
game_board::game_board(int X_width, int Y_height, int mines_number)
{
	/*Player should type board size between 9x9 and 30x24
	and mines number between 10 and 667.
	Max mines number is related with board size, so if board size is AxB,
	max number is (A-1)x(B-1)
	*/
	fields = NULL;
	beg_int_exp = "Custom";

	if (X_width < 9) X_width = 9;
	else if (X_width > 30) X_width = 30;

	if (Y_height < 9) Y_height = 9;
	else if (Y_height > 24) Y_height = 24;

	g_b_width = X_width;
	g_b_height = Y_height;

	this->create_fields();

	int max_mines_number = 0;
	max_mines_number = (g_b_width - 1)*(g_b_height - 1);

	if (mines_number < 10) mines_number = 10;
	else if (mines_number>max_mines_number) mines_number = max_mines_number;

	this->mines_number = mines_number;

	srand(time(NULL));
	this->rand_mines();
	this->neighbours_mines();
}
game_board::~game_board()
{
	for (int i = 0; i < g_b_width; i++)
	{
		delete[]fields[i];
	}
	delete[]fields;
}
void game_board::create_fields()
{
	fields = new int*[g_b_width];
	for (int i = 0; i < g_b_width; i++)
	{
		fields[i] = new int[g_b_height];
		for (int j = 0; j < g_b_height; j++)
		{
			fields[i][j] = 0;
		}
	}
}
void game_board::show_fields()
{
	for (int i = 0; i < g_b_width; i++)
	{
		for (int j = 0; j < g_b_height; j++)
		{
			std::cout << fields[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}
void game_board::rand_mines()
{
	int X = 0;
	int Y = 0;

	char bufor[200];

	for (int i = 0; i < mines_number; i++)
	{
		do
		{
			X = rand() % g_b_width;
			Y = rand() % g_b_height;
			/*sprintf_s(bufor, "(%i, %i)", X, Y);
			std::cout << bufor << std::endl;*/
		} while (fields[X][Y] == -1);

		fields[X][Y] = -1;
	}
}
void game_board::neighbours_mines()
{
	for (int i = 0; i < g_b_width; i++)
	{
		for (int j = 0; j < g_b_height; j++)
		{
			if (fields[i][j] == -1)
			{
				if ((i - 1 >= 0) && (fields[i - 1][j] != -1))
				{
					fields[i - 1][j]++; //up
				}
				if ((j + 1 < g_b_height) && (fields[i][j + 1] != -1))
				{
					fields[i][j + 1]++; //right
				}
				if ((i + 1 < g_b_width) && (fields[i + 1][j] != -1))
				{
					fields[i + 1][j]++; //down
				}
				if ((j - 1 >= 0) && (fields[i][j - 1] != -1))
				{
					fields[i][j - 1]++; //left
				}
				if ((i - 1 >= 0) && (j - 1 >= 0) && (fields[i - 1][j - 1] != -1)) //upper left diagonally
				{
					fields[i - 1][j - 1]++;
				}
				if ((i - 1 >= 0) && (j + 1 < g_b_height) && (fields[i - 1][j + 1] != -1)) //upper right diagonally
				{
					fields[i - 1][j + 1]++;
				}
				if ((i + 1 < g_b_width) && (j - 1 >= 0) && (fields[i + 1][j - 1] != -1)) //bottom left diagonally
				{
					fields[i + 1][j - 1]++;
				}
				if ((i + 1 < g_b_width) && (j + 1 < g_b_height) && (fields[i + 1][j + 1] != -1)) //bottom right diagonally
				{
					fields[i + 1][j + 1]++;
				}
			}
		}
	}
}