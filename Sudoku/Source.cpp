#include"Functions.h"

int main()
{
	system("SUDOKU");
	system("mode con cols=37 lines=20");
	system("color 7B");

	int size_field = 9;
	cell** field = new cell*[size_field];
	int level = 1;
	int check_open = 0;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = true;
	cci.dwSize = 100;
	SetConsoleCursorInfo(h, &cci);
	SetConsoleTextAttribute(h, BLACK);

	create_field(field, size_field);
	shuffle_field(&field, size_field);
	shuffle_field(&field, size_field);
	hide_visible(&field, size_field, level);
	show_field_gr(field, size_field);
	count_open(&field, size_field, check_open);


	COORD pozition = { 2, 1 };
	SetConsoleCursorPosition(h, pozition);
	COORD panel;

	

	while (true)
	{
		panel = { 0, 19 };
		SetConsoleCursorPosition(h, panel);
		cout << " Open cells: " << check_open;
		panel.Y++;
		SetConsoleCursorPosition(h, panel);
		double progr = (check_open / 81.) * 100;
		progr = int(progr);
		cout << " Progress: " << progr << " %";
	//	//panel.Y++;
	//	//SetConsoleCursorPosition(h, panel);
	//	//cout << char(201);
	//	//panel.Y++;
	//	//SetConsoleCursorPosition(h, panel);
	//	//cout << "Cursor image: " << field[pozition.Y][pozition.X].image;

		SetConsoleCursorPosition(h, pozition);

		int key = _getch();
		if (key == 224)
		{
			key = _getch();
		}

		if (key == RIGHT && pozition.X + 4 < size_field * 4)
		{
			pozition.X += 4;
		}
		else if (key == DOWN && pozition.Y + 2 < size_field * 2)
		{
			pozition.Y += 2;
		}
		else if (key == LEFT && pozition.X > 2)
		{
			pozition.X -= 4;
		}
		else if (key == UP && pozition.Y > 1)
		{
			pozition.Y -= 2;
		}
		else if (key == ONE || key == TWO || key == THREE || key == FOUR ||
			key == FIVE || key == SIX || key == SEVEN || key == EIGHT || key == NINE)
		{
			check_matched(field, pozition, h, check_open, key);
		}

		if (check_open == pow(size_field, 2))
		{
			MessageBoxA(0, "VICTORY", "SUDOKU", MB_OK);
			int rezult = MessageBoxA(0, "Play more?", "SUDOKU", MB_YESNO);
			if (rezult == IDYES)
			{
				system("cls");
				level++;
				shuffle_field(&field, size_field);
				shuffle_field(&field, size_field);
				hide_visible(&field, size_field, level);
				check_open = 0;
				count_open(&field, size_field, check_open);
				show_field_gr(field, size_field);
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