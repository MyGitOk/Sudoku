#pragma once
#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<ctime>
#include<math.h>
#include"Structs.h"

using namespace std;

void create_field(cell** field, const int& size);
void swap_one_col(cell** field, const int& size);
void swap_one_line(cell** field, const int& size);
void turn_round_field(cell*** field, const int& size);
void shuffle_field(cell*** field, int& size);
void hide_visible(cell*** field, const int& size, int level);
//void fill_field(int** field, int r);
//bool check_col(int** ar, const int& h, const int& w, int i);
//bool check_line(int** ar, const int& h, const int& w, int i);
//void check_square(int** ar, const int& num, int& h, int& w);
void show_field(cell**& field, const int& size);
void show_field_gr(cell**& field, const int& size);
void count_open(cell*** field, const int& size, int& open);
void print_sucsess_cell(cell*** field, COORD& poz, HANDLE& h, int& check_open);
void print_wrong_cell(cell*** field, COORD& poz, HANDLE& h, int digit);
void check_matched(cell**& field, COORD& poz, HANDLE& h, int& check_open, int& key);


void create_field(cell** field, const int& size)
{
	int digit = 0;
	for (int h = 0; h < size; h++)
	{
		field[h] = new cell[size] {};
		if (h == 0)
		{
			digit = 1;
		}
		else if (h % 3 == 0)
		{
			digit = field[h - 3][0].meaning + 1;
		}
		else
		{
			digit = field[h - 1][0].meaning + 3;
			if (digit > 9)
			{
				digit -= 9;
			}
		}
		for (int w = 0; w < size; w++)
		{
			if (w == 0)
			{
				field[h][w].meaning = digit;
			}
			else if (digit < 8)
			{
				digit += 2;
				field[h][w].meaning = digit;
			}
			else
			{
				digit += 2;
				digit -= 9;
				field[h][w].meaning = digit;
			}
		}
	}
}

void swap_one_col(cell** field, const int& size)
{
	int ind = rand() % 3;
	ind *= 3;
	for (int h = 0; h < size; h++)
	{
		cell temp;
		temp.meaning = field[h][ind].meaning;
		field[h][ind].meaning = field[h][ind + 2].meaning;
		field[h][ind + 2].meaning = temp.meaning;
	}
}

void swap_one_line(cell** field, const int& size)
{
	int ind = rand() % 3;
	ind *= 3;
	for (int w = 0; w < size; w++)
	{
		cell temp;
		temp.meaning = field[ind][w].meaning;
		field[ind][w].meaning = field[ind + 2][w].meaning;
		field[ind + 2][w].meaning = temp.meaning;
	}
}

void turn_round_field(cell*** field , const int& size)
{
	cell** new_field = new cell*[size];
	for (int h = 0; h < size; h++)
	{
		new_field[h] = new cell[size];
		for (int w = 0; w < size; w++)
		{
			new_field[h][w].meaning = (*field)[w][h].meaning;
		}
	}
	*field = new_field;
	//delete[] *field;
}

void shuffle_field(cell*** field, int& size)
{
	for (int i = 0; i < 3; i++)
	{
		swap_one_col(*field, size);
		swap_one_line(*field, size);
		turn_round_field(field, size);
	}
}

void hide_visible(cell*** field, const int& size, int level)
{
	int hide;
	srand(time(0));
	for (int h = 0; h < size; h++)
	{
		for (int w = 0; w < size; w++)
		{
			hide = rand() % 5;
			if (hide == 0)
			{
				(*field)[h][w].image = false;
			}
			else
			{
				(*field)[h][w].image = true;
			}
		}
	}
}

//void fill_field(int** field, int r)
//{
//	srand(time(NULL));
//	rand();
//	int a = 0;
//	for (int h = 0; h < r; h++)
//	{
//		field[h] = new int[r] {};
// 		for (int w = 0; w < r; w++)
//		{
//			field[h][w] = rand() % 9 + 1;
//			//проверка текущей линии
//			bool check;
//			check = check_line(field, h, w, w - 1);
//			if (check)
//			{
//				w--;
//			}
//			else if (!check)
//			{
//				//проверка текущей колонки
//				check = check_col(field, h, w, h - 1);
//				if (check && (w == r - 2 || w == r - 1))
//					{
//						w -= 3;
//					}
//				else if (check)
//				{
//					w--;
//				}
//				else if (!check)
//				{
//					for (int i = 0; i < h + 1; i++)
//					{
//						for (int j = 0; j < 9; j++)
//						{
//							cout << field[i][j] << " ";
//						}
//						cout << "\n";
//					}
//					//проверка текущего квадрата
//					check_square(field, field[h][w], h, w);
//				}
//			}
//		}
//	}
//}

//bool check_line(int** ar, const int& h, const int& w, int i)
//{
//	if (i < 0)
//	{
//		return false;
//	}
//	//если не нашел совпадения
//	else if (ar[h][w] != ar[h][i])
//	{
//		//если дошел до последнего индекса
//		if (i == 0)
//		{
//			return false;
//		}
//		else
//		{
//			check_line(ar, h, w, i - 1);
//		}
//	}
//	//если нашел совпадения
//	else if (ar[h][w] == ar[h][i])
//	{
//		return true;
//	}
//}

//bool check_col(int** ar, const int& h, const int& w, int i)
//{
//	if (i < 0)
//	{
//		return false;
//	}
//	//если не нашел совпадения
//	else if (ar[h][w] != ar[i][w])
//	{
//		//если дошел до последнего индекса
//		if (i == 0)
//		{
//			return false;
//		}
//		else
//		{
//			check_col(ar, h, w, i - 1);
//		}
//	}
//	//если нашел совпадения
//	else if (ar[h][w] == ar[i][w])
//	{
//		return true;
//	}
//}

//void check_square(int** ar, const int& num, int& h, int& w)
//{
//	if (h < 3 && w < 3)
//	{
//		for (int i = 0; i < h; i++)
//		{
//			for (int j = 0; j < 3; j++)
//			{
//				//cout << ar[i][j] << " ";
//				//_getch();
//				if (ar[i][j] == num)
//				{
//					w--;
//				}
//			}
//			//cout << "\n";
//		}
//	}
//	else if (h < 3 && w > 2 && w < 6)
//	{
//		for (int i = 0; i < h; i++)
//		{
//			for (int j = 3; j < 6; j++)
//			{
//				if (ar[i][j] == num)
//				{
//					w -= 3;
//				}
//			}
//		}
//	}
//	else if (h < 3 && w > 5)
//	{
//		for (int i = 0; i < h; i++)
//		{
//			for (int j = 6; j < 9; j++)
//			{
//				/*if (ar[i][j] == num && j == 8)
//				{
//					h--;
//					_getch();
//				}
//				else */if (ar[i][j] == num)
//				{
//					w -= 4;
//				}
//			}
//		}
//	}
//	else if (h > 2 && h < 6 && w < 3)
//	{
//		for (int i = 3; i < h; i++)
//		{
//			for (int j = 0; j < 3; j++)
//			{
//				if (ar[i][j] == num)
//				{
//					w--;
//				}
//			}
//		}
//	}
//	else if (h > 2 && h < 6 && w > 2 && w < 6)
//	{
//		for (int i = 3; i < h; i++)
//		{
//			for (int j = 3; j < 6; j++)
//			{
//				if (ar[i][j] == num)
//				{
//					w -= 3;
//				}
//			}
//		}
//	}
//	else if (h > 2 && h < 6 && w > 5)
//	{
//		for (int i = 3; i < h; i++)
//		{
//			for (int j = 6; j < 9; j++)
//			{
//				/*if (ar[i][j] == num && j == 8)
//				{
//					h--;
//					_getch();
//				}*/
//				/*else */if (ar[i][j] == num)
//				{
//					cout << "\n" << h << " - h\t" << w << " - w\n";
//					_getch();
//					w -= 4;
//				}
//			}
//		}
//	}
//	else if (h > 5 && w < 3)
//	{
//		for (int i = 6; i < h; i++)
//		{
//			for (int j = 0; j < 3; j++)
//			{
//				if (ar[i][j] == num)
//				{
//					w--;
//				}
//			}
//		}
//	}
//	else if (h > 5 && w > 2 && w < 6)
//	{
//		for (int i = 6; i < h; i++)
//		{
//			for (int j = 3; j < 6; j++)
//			{
//				if (ar[i][j] == num)
//				{
//					w -= 3;
//				}
//			}
//		}
//	}
//	else if (h > 5 && w > 5)
//	{
//		for (int i = 6; i < h; i++)
//		{
//			for (int j = 6; j < 9; j++)
//			{
//				if (ar[i][j] == num)
//				{
//					/*if (ar[i][j] == num && j == 8)
//					{
//						h--;
//					}
//					else */if (ar[i][j] == num)
//					{
//						w -= 4;
//					}
//				}
//			}
//		}
//	}	
//}

void show_field(cell**& field, const int& size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (field[i][j].image == true)
			{
				cout << field[i][j].meaning;
			}
			else if (field[i][j].image == false)
			{
				cout << " ";
			}
		}
		cout << "\n";
	}
}

void show_field_gr(cell**& field, const int& size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (field[i][j].image == true)
			{
				cout << field[i][j].meaning;
			}
			else if (field[i][j].image == false)
			{
				cout << " ";
			}
		}
		cout << "\n";
	}
}


void count_open(cell*** field, const int& size, int& open)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if ((*field)[i][j].image == true)
			{
				open++;
			}
		}
	}
}

void print_sucsess_cell(cell*** field, COORD& poz, HANDLE& h, int& check_open)
{
	(*field)[poz.Y][poz.X].image = true;
	check_open++;
	SetConsoleCursorPosition(h, poz);
	cout << (*field)[poz.Y][poz.X].meaning;
}

void print_wrong_cell(cell*** field, COORD& poz, HANDLE& h, int digit)
{
	SetConsoleCursorPosition(h, poz);
	SetConsoleTextAttribute(h, RED);
	cout << digit;
	SetConsoleTextAttribute(h, GREY);
	SetConsoleCursorPosition(h, poz);
}

void check_matched(cell**& field, COORD& poz, HANDLE& h, int& check_open, int& key)
{
	int a = 0;
	switch (key)
	{
	case ONE: a = 1;
		break;
	case TWO: a = 2;
		break;
	case THREE: a = 3;
		break;
	case FOUR: a = 4; 
		break;
	case FIVE: a = 5; 
		break;
	case SIX: a = 6; 
		break;
	case SEVEN: a = 7; 
		break;
	case EIGHT: a = 8; 
		break;
	case NINE: a = 9; 
		break;
	default:
		break;
	}

	if (field[poz.Y][poz.X].meaning == a &&
		field[poz.Y][poz.X].image == false)
	{
		print_sucsess_cell(&field, poz, h, check_open);
	}
	else if (field[poz.Y][poz.X].meaning != a &&
		field[poz.Y][poz.X].image == false)
	{
		print_wrong_cell(&field, poz, h, a);
	}
}