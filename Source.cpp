#include <conio.h>
#include <iostream>
#include <vector>
#include <windows.h>
#include <time.h>

bool game_Over;
char map[25][40];
int score;

int height_of_map = sizeof(map) / sizeof(map[0]);
int width_of_map = sizeof(map[0]) / sizeof(map[0][0]);

enum Direction { STOP = 0, UP = 1, LEFT = 2, DOWN = 3, RIGHT = 4 };
Direction dir;

int head_pos_X, head_pos_Y;

std::vector <int> tail_pos_X, tail_pos_Y;

int fruit_pos_X, fruit_pos_Y;

void Setup()
{
	srand(time(NULL));
	game_Over = false;
	dir = STOP;
	score = 0;
	head_pos_X = width_of_map / 2;
	head_pos_Y = height_of_map / 2;

	for (int i = 0; i < width_of_map; i++)
	{
		map[0][i] = '#';
		map[height_of_map - 1][i] = '#';
	}

	for (int i = 0; i < height_of_map; i++)
	{
		map[i][0] = '#';
		map[i][width_of_map - 1] = '#';
	}

	fruit_pos_X = rand() % (width_of_map - 2) + 1;
	fruit_pos_Y = rand() % (height_of_map - 2) + 1;

	map[fruit_pos_Y][fruit_pos_X] = 'F';


}

void Input()
{
	if (_kbhit())
		switch (_getch())
		{
		case 'w': case 'W': 
			dir = UP;
			break;
		case 'a': case 'A':
			dir = LEFT;
			break;
		case 's': case 'S':
			dir = DOWN;
			break;
		case 'd': case 'D':
			dir = RIGHT;
			break;
		case 'x': case 'X':
			game_Over = true;
			break;
		}
}

void Logic()
{
	if (!tail_pos_X.empty())
		map[tail_pos_Y[tail_pos_Y.size() - 1]][tail_pos_X[tail_pos_X.size() - 1]] = ' ';

	if (!tail_pos_X.empty()) {
		tail_pos_X.pop_back();
		tail_pos_X.insert(tail_pos_X.begin(), head_pos_X);
	}

	if (!tail_pos_Y.empty()) {
		tail_pos_Y.pop_back();
		tail_pos_Y.insert(tail_pos_Y.begin(), head_pos_Y);
	}



	for (int i = 1; i < tail_pos_Y.size(); i++)
	{
		if (head_pos_X == tail_pos_X[i] && head_pos_Y == tail_pos_Y[i])
			game_Over = true;
	}

	switch (dir)
	{
	case UP:
		if (!tail_pos_X.empty())
			map[tail_pos_Y[tail_pos_Y.size() - 1]][tail_pos_X[tail_pos_X.size() - 1]] = ' ';
		else
			map[head_pos_Y][head_pos_X] = ' ';
		head_pos_Y--;
		break;
	case LEFT:
		if (!tail_pos_X.empty())
			map[tail_pos_Y[tail_pos_Y.size() - 1]][tail_pos_X[tail_pos_X.size() - 1]] = ' ';
		else
			map[head_pos_Y][head_pos_X] = ' ';
		head_pos_X--;
		break;
	case DOWN:
		if (!tail_pos_X.empty())
			map[tail_pos_Y[tail_pos_Y.size() - 1]][tail_pos_X[tail_pos_X.size() - 1]] = ' ';
		else
			map[head_pos_Y][head_pos_X] = ' ';
		head_pos_Y++;
		break;
	case RIGHT:
		if (!tail_pos_X.empty())
			map[tail_pos_Y[tail_pos_Y.size() - 1]][tail_pos_X[tail_pos_X.size() - 1]] = ' ';
		else
			map[head_pos_Y][head_pos_X] = ' ';
		head_pos_X++;
	}



	if (head_pos_X == fruit_pos_X && head_pos_Y == fruit_pos_Y)
	{
		score += 1;
		fruit_pos_X = rand() % (width_of_map - 2) + 1;
		fruit_pos_Y = rand() % (height_of_map - 2) + 1;
		map[fruit_pos_Y][fruit_pos_X] = 'F';
		tail_pos_X.push_back(head_pos_X);
		tail_pos_Y.push_back(head_pos_Y);
	}

	if (head_pos_X <= 0 || head_pos_X >= width_of_map || head_pos_Y <= 0 || head_pos_Y >= height_of_map - 1)
		game_Over = true;

}

void Draw()
{
	system("cls");

	map[head_pos_Y][head_pos_X] = 'O';
	for (int i = 0; i < tail_pos_X.size(); i++)
	{
		map[tail_pos_Y[i]][tail_pos_X[i]] = 'o';
	}

	for (int y = 0; y < height_of_map; y++)
	{
		for (int x = 0; x < width_of_map; x++)
		{
			std::cout << map[y][x];
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	std::cout << "The score is: " << score;


}

int main()
{
	Setup();
	while (!game_Over)
	{
		Input();
		Logic();
		Draw();
		Sleep(20);
	}

	system("cls");
	std::cout << "GAME OVER\n" << "Your score is: " << score << std::endl;

	system("pause");

	return 0;
}