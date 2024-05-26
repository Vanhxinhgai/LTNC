// Snake Game
#include <iostream>
#include <conio.h>
#include <vector>
#include <windows.h>
#include "cursor.h"

using namespace std;

const int UP = 72;
const int DOWN = 80;
const int LEFT = 75;
const int RIGHT = 77;
const int FAST_FOOD_EXIST = 60;
const int FAST_FOOD_LIVE_TIME = 40;

struct Coordinates
{
	int x, y;
};

void welcome(void);
void display(const Coordinates size, const Coordinates lefttop);
void newFood(Coordinates &food, Coordinates size, const vector<Coordinates> snake, const Coordinates lefttop);
void getKey(vector<Coordinates> &snake, const Coordinates lefttop, const Coordinates food);
int liveStatus(vector<Coordinates> &snake, const Coordinates lefttop, Coordinates size, Coordinates &food);
int fastFoodStatus(const Coordinates size, const Coordinates lefttop, const vector<Coordinates> snake, int &loopCount);
void gameOver(const vector<Coordinates> snake);

int main()
{
	system("color A");
	// welcome();
	ShowCur(false); // an con tro

	const Coordinates lefttop = {10, 5}; // dinh phia tren ben trai cua hinh chu nhat khong gian.
	Coordinates size = {30, 20};

	display(size, lefttop); // in hinh chu nhat, khu vuc di chuyen

	vector<Coordinates> snake; ////Decaled Snake
	Coordinates snakeBody;
	snakeBody.x = 18;
	snakeBody.y = 10;
	SetColor(13);
	for (int i = 0; i < 4; i++)
	{
		snakeBody.x--;
		snake.push_back(snakeBody);
		gotoxy(lefttop.x + snakeBody.x, lefttop.y + snakeBody.y);
		cout << '*';
	}
	Coordinates food; // Decaled Food
	newFood(food, size, snake, lefttop);
	gotoxy(lefttop.x + size.x + 5, lefttop.y + 2); // Score
	SetColor(9);
	cout << "Score: " << (snake.size() - 4) * 50;

	int loopCount(0);
	while (true)
	{
		Sleep(150);
		getKey(snake, lefttop, food);
		if (liveStatus(snake, lefttop, size, food))
			break;
		loopCount++;
		//	if (loopCount >= FAST_FOOD_EXIST)
		//		fastFoodStatus (size, lefttop, snake, loopCount);
		gotoxy(lefttop.x + size.x + 5, lefttop.y + 2);
		SetColor(9);
		cout << "Score: " << (snake.size() - 4) * 50;
	}
	gameOver(snake);

	cin.get();
	return 0;
}

void welcome(void)
{
	cout << "\n\n     MINI GAME: \n\n";
	cout << "         .*****.   ***       **         ***         **   '*'   *.*.*.*.*.   " << endl;
	cout << "        **'    '*  **'*      **        *' '*        **  '*'     **''''''*   " << endl;
	cout << "        **      '  ** *'     **       *'   '*       ** '*'      **          " << endl;
	cout << "         **        **  '*    **      '*     *'      **'*'       **.....     " << endl;
	cout << "           '**.    **   *.   **     .*'.....'*.     ***'        **.*.*.     " << endl;
	cout << "              '*   **    *'  **     *.*.*.*.*.*     **'*'       **          " << endl;
	cout << "        .      **  **     '* **    *'         '*    ** '*'      **          " << endl;
	cout << "        **.   .**  **      *'**   '*           *'   **  '*'     **......*   " << endl;
	cout << "         '*****'   **       ***  '*'           '*'  **   '*'.  *'*'*'*'*'   " << endl;
	cout << "\n                                                   Coder: ...\n\n\n";
	system("pause");
}

void display(const Coordinates size, const Coordinates lefttop)
{ // In Khung tro choi
	system("cls");
	SetColor(10);
	gotoxy(lefttop.x, lefttop.y - 1);
	for (int x = 0; x < size.x; x++) // in truc hoanh
		if (0 == x % 5)
			cout << x % 10;
		else
			cout << " ";

	for (int y = 0; y < size.y; y++)
	{
		gotoxy(lefttop.x - 2, lefttop.y + y);
		cout << y % 10 << '.'; // in truc tung
		for (int x = 0; x < size.x; x++)
			if (0 == x || size.x - 1 == x || 0 == y || size.y - 1 == y)
				cout << '\4';
			else
				cout << ' ';
	}
}

void newFood(Coordinates &food, Coordinates size, const vector<Coordinates> snake, const Coordinates lefttop)
{
	SetColor(13);
	gotoxy(food.x + lefttop.x, food.y + lefttop.y);
	cout << '*';  // Hinh than con ran
	SetColor(14); // Mau vang
newFoodLabel:
	food.x = rand() % (size.x - 2) + 1; // Tao vi tri thuc an ngau nhien
	food.y = rand() % (size.y - 2) + 1;
	for (int i = 0; i < snake.size(); i++)
		if (snake[i].x == food.x && snake[i].y == food.y) // Neu dau ran dung thuc an => tao thuc an vi tri moi
			goto newFoodLabel;
	gotoxy(food.x + lefttop.x, food.y + lefttop.y);
	cout << '0'; // Hinh dang thuc an
}

void getKey(vector<Coordinates> &snake, const Coordinates lefttop, const Coordinates food)
{
	SetColor(13); // Mau hong
	// xoa duoi con ran:
	if (!((food.x == snake[snake.size() - 1].x) && (food.y == snake[snake.size() - 1].y)))
	{
		gotoxy(snake[snake.size() - 1].x + lefttop.x, snake[snake.size() - 1].y + lefttop.y);
		cout << ' '; // Sua * thanh ky tu trong
	}
	static char moveDirection(RIGHT);
	static char lastMove = RIGHT;
	// Nhan lenh tu ban phim
	if (_kbhit())
	{
		_getch();
		moveDirection = _getch();
	}
	// di chuyen than
	for (int i = snake.size() - 1; i > 0; i--)
		snake[i] = snake[i - 1]; // Di chuyen len vi tri +1
	// xet phim nhap vao co nguoc chieu voi chuyen dong khong?
	if (!((0 == moveDirection - lastMove) || 3 == abs(moveDirection - lastMove) || 5 == abs(moveDirection - lastMove)))
		moveDirection = lastMove;
	// di chuyen dau
	switch (moveDirection)
	{
	case UP:
		snake[0].y--;
		break;
	case DOWN:
		snake[0].y++;
		break;
	case LEFT:
		snake[0].x--;
		break;
	case RIGHT:
		snake[0].x++;
		break;
	}
	lastMove = moveDirection;

	// in dau con ran
	gotoxy(snake[0].x + lefttop.x, snake[0].y + lefttop.y);
	cout << '*';
}

int liveStatus(vector<Coordinates> &snake, const Coordinates lefttop, Coordinates size, Coordinates &food)
{
	// Dieu kiem cham Wall(tuong)
	if (0 == snake[0].x || size.x - 1 == snake[0].x || 0 == snake[0].y || size.y - 1 == snake[0].y)
		return 1;
	// Dieu kien Cham Food (thuc an)
	else if (snake[0].x == food.x && snake[0].y == food.y)
	{
		Coordinates newSnakeBody;
		newSnakeBody.x = 2 * snake[snake.size() - 1].x - snake[snake.size() - 2].x;
		newSnakeBody.y = 2 * snake[snake.size() - 1].y - snake[snake.size() - 2].y;
		snake.push_back(newSnakeBody);
		newFood(food, size, snake, lefttop);
		return 0;
	}
	// Dieu kien cham chinh minh
	else
		for (int i = 1; i < snake.size(); i++)
			if ((snake[0].x == snake[i].x) && (snake[0].y == snake[i].y))
				return 2;
	return 0;
}

int fastFoodStatus(const Coordinates size, const Coordinates lefttop, const vector<Coordinates> snake, int &loopCount)
{

	static Coordinates fastFood;

	if (loopCount == FAST_FOOD_EXIST)
	{
	newFoodLabel:
		fastFood.x = rand() % (size.x - 2) + 1;
		fastFood.y = rand() % (size.y - 2) + 1;
		for (int i = 0; i < snake.size(); i++)
			if (snake[i].x == fastFood.x && snake[i].y == fastFood.y)
				goto newFoodLabel;
		gotoxy(lefttop.x + fastFood.x, lefttop.y + fastFood.y);
		SetColor(12); // Mau do
		cout << '\3';
		gotoxy(lefttop.x + size.x + 5, lefttop.y + 7); // prinft time left
		for (int i = 0; i < FAST_FOOD_LIVE_TIME; i++)
			if (i % 2)
				cout << '#';
	}
	else if (loopCount == FAST_FOOD_EXIST + FAST_FOOD_LIVE_TIME + 1)
	{
		gotoxy(fastFood.x + lefttop.x, fastFood.y + lefttop.y); // delete food
		if (fastFood.x != 0 && fastFood.y != 0)					// de phong sau khi da an dc thuc an, c�i nay se xoa mat diem (0;0)
			cout << ' ';
		fastFood.x = fastFood.y = 0; // delete fast food value
		loopCount = 1;
		return 1;
	}
	else if (snake[0].x == fastFood.x && snake[0].y == fastFood.y)
	{
		gotoxy(lefttop.x + size.x + 5, lefttop.y + 7); // delete time left
		for (int i = 0; i < FAST_FOOD_LIVE_TIME; i++)
			if (i % 2)
				cout << ' ';
		fastFood.x = fastFood.y = 0; // delete fast food value
		return 1;					 // lay duoc fast food
	}
	else
	{
		gotoxy(lefttop.x + size.x + 5 + (FAST_FOOD_LIVE_TIME + FAST_FOOD_EXIST - loopCount) / 2, lefttop.y + 7); // prinft time left
		cout << ' ';
	}

	return 0; // khon lay dc fast food
}

void gameOver(const vector<Coordinates> snake)
{
	Sleep(800);
	system("cls");
	cout << "\n\n\n\t\tGAME OVER!\n\n";
	cout << "\t\tYour score: " << (snake.size() - 4) * 50;
	cout << "\n\n\n\t\tGoodbye! See you again!";
}
