#include"Functions.h"

int main()
{
	int size_field = 9;
	cell** field = new cell*[size_field];
	int level = 1;
	int check_open = 0;

	create_field(field, size_field);
	shuffle_field(&field, size_field);
	shuffle_field(&field, size_field);
	hide_visible(&field, size_field, level);
	show_field(field, size_field);
	count_open(&field, size_field, check_open);

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
		double progr = (check_open / 81.) * 100;
		progr = int(progr);
		cout << "Progress: " << progr << " %";
		panel.Y++;
		SetConsoleCursorPosition(h, panel);
		cout << char(201);
		//panel.Y++;
		//SetConsoleCursorPosition(h, panel);
		//cout << "Cursor image: " << field[pozition.Y][pozition.X].image;

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
			check_matched(field, pozition, h, check_open, key);
		}

		if (check_open == pow(size_field, 2))
		{
			MessageBoxA(0, "VICTORY", "SUDOKU", MB_OK);
			int rezult = MessageBoxA(0, "Do you want to continue?", "SUDOKU", MB_YESNO);
			if (rezult == IDYES)
			{
				system("cls");
				level++;
				shuffle_field(&field, size_field);
				shuffle_field(&field, size_field);
				hide_visible(&field, size_field, level);
				check_open = 0;
				count_open(&field, size_field, check_open);
				show_field(field, size_field);
			}
			else if (rezult == IDNO)
			{
				// сохранение в файл
				return 0;
			}
		}
	}
	_getch();
}