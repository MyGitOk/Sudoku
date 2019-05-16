#pragma once

enum direction { DOWN = 80, UP = 72, LEFT = 75, RIGHT = 77,
ONE = 49, TWO = 50, THREE = 51, FOUR = 52, FIVE = 53,
SIX = 54, SEVEN = 55, EIGHT = 56, NINE = 57};

enum colors { GREY = 7, RED = 124, BLACK = 112, BLUE = 9, YELLOW = 14, DARKGREEN = 2,
	RED_WHITE = 252 };

struct cell
{
	bool image;
	int meaning;
};