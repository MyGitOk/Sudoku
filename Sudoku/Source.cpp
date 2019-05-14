#include"Functions.h"

//HWND hwnd = GetConsoleWindow(); // дескриптор окна, используемый консолью
//HDC hdc = GetDC(hwnd); // данные типа HDC представляют собой 32-разрядное целое беззнаковое число.

int main()
{
	int size_field = 9;
	cell** field = new cell*[size_field];
	create_field(field, size_field);
	shuffle_field(&field, size_field);
	shuffle_field(&field, size_field);
	hide_visible(&field, size_field, 1);
	show_field(field, size_field);
	int check_open = 0;
	for (int i = 0; i < size_field; i++)
	{
		for (int j = 0; j < size_field; j++)
		{
			if (field[i][j].image == true)
			{
				check_open++;
			}
		}
	}

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = true;
	cci.dwSize = 100;
	SetConsoleCursorInfo(h, &cci);

	COORD pozition = { 0, 0 };
	SetConsoleCursorPosition(h, pozition);
	COORD panel;

	while (true)
	{
		panel = { 12, 0 };
		SetConsoleCursorPosition(h, panel);
		cout << "Open cells: " << check_open;
		panel.Y++;
		SetConsoleCursorPosition(h, panel);
		cout << "Cursor position Y: " << pozition.Y;
		panel.Y++;
		SetConsoleCursorPosition(h, panel);
		cout << "Cursor position X: " << pozition.X;
		panel.Y++;
		SetConsoleCursorPosition(h, panel);
		cout << "Cursor image: " << field[pozition.Y][pozition.X].image;

		SetConsoleCursorPosition(h, pozition);

		int key = _getch();
		if (key == 224)
		{
			key = _getch();
		}

		if (key == RIGHT && pozition.X + 1 < size_field)
		{
			pozition.X++;
		}
		else if (key == DOWN && pozition.Y + 1 < size_field)
		{
			pozition.Y++;
		}
		else if (key == LEFT && pozition.X > 0)
		{
			pozition.X--;
		}
		else if (key == UP && pozition.Y > 0)
		{
			pozition.Y--;
		}
		else if (key == ONE || key == TWO || key == THREE || key == FOUR ||
			key == FIVE || key == SIX || key == SEVEN || key == EIGHT || key == NINE)
		{
			check_matched(&field, pozition, h, check_open, key);
		}
		

		if (check_open == pow(size_field, 2))
		{
			MessageBoxA(0, "VICTORY", "SUDOKU", MB_OK);
		}


	}
	

	_getch();
}