//Dev. BlockDMask
//Blog. https://blockdmask.tistory.com/
#include<iostream>
#include<Windows.h>
#include<conio.h>
using namespace std;
#define INIT_POS 1
void GotoXY(int x, int y)
{
	COORD pos;
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetConsoleView()
{
	system("mode con:cols=65 lines=10");
	system("title Card Matching Game. by BlockDmask.");
}

int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

const int originMap[4][4] = { {1, 6, 1, 8},
								{6, 2, 5, 4},
								{7, 2, 5, 4},
								{8, 3, 3, 7} };

struct Pos
{
	int x;
	int y;
};

enum KEYBOARD
{
	IS_ARROW = 224,
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80,
	SPACE = 32,
};


enum COLOR
{
	GREEN = 10,
	MINT,
	RED,
	PINK,
	YELLOW,
	WHITE,
};


class GameManager
{
private:
	char questionMap[4][4];	
	Pos player;				
	Pos flipPos[2];			
	int flipCount;		
	int spaceCount;		
	int matchedCardCount;	
public:
	void StartGame()
	{
		Init();		
		DrawBack();	

		
		int key = 0;
		while (true)
		{
			key = GetKeyDown();	
			if (key == KEYBOARD::IS_ARROW)
			{
			
				MovePos();
			}
			if (key == KEYBOARD::SPACE)
			{
			
				FlipCard();
			}
			//draw
			DrawMain();
			Sleep(100);
			CheckCard();
		}
	}

	void Init()
	{
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 4; ++x)
			{
				questionMap[y][x] = '?';	
			}
		}
		player.x = 0;
		player.y = 0;
		flipCount = 0;
		spaceCount = 0;
		matchedCardCount = 0;
	}

	void FlipCard()
	{
		if (questionMap[player.y][player.x] != '?') return;
		if (flipCount > 2) return;
		flipPos[flipCount].x = player.x;
		flipPos[flipCount].y = player.y;
		questionMap[player.y][player.x] = originMap[player.y][player.x] + '0';
		++flipCount;
	}


	void MovePos()
	{
		GotoXY(INIT_POS + (player.x * 3), INIT_POS + (player.y * 2) + 1);
		printf("  ");

		
		switch (_getch())
		{
		case KEYBOARD::LEFT:
			--player.x;
			if (player.x <= 0)
			{
				player.x = 0;
			}
			break;
		case KEYBOARD::RIGHT:
			++player.x;
			if (player.x >= 3)
			{
				player.x = 3;
			}
			break;
		case KEYBOARD::UP:
			--player.y;
			if (player.y <= 0)
			{
				player.y = 0;
			}
			break;
		case KEYBOARD::DOWN:
			++player.y;
			if (player.y >= 3)
			{
				player.y = 3;
			}
			break;
		}
	}

	void DrawMain()
	{
		//map draw
		SetTextColor(WHITE);
		char c = '\0';
		for (int y = 0; y < 4; ++y)
		{
			GotoXY(INIT_POS, INIT_POS + (2 * y));
			for (int x = 0; x < 4; ++x)
			{
				c = questionMap[y][x];
				if (c != '?')
				{
					SetTextColor(GREEN);
				}
				printf("[%c]   ", c);
				SetTextColor(WHITE);
			}
		}

		//player draw
		GotoXY(INIT_POS + (player.x * 3), INIT_POS + (player.y * 2) + 1);
		printf(" ^");

		GotoXY(14, 1);
		printf("Count : %d", spaceCount);
	}

	void CheckCard()
	{
		if (flipCount == 2)
		{
			char c = '?';
			if (originMap[flipPos[0].y][flipPos[0].x] == originMap[flipPos[1].y][flipPos[1].x])
			{
				c = originMap[flipPos[0].y][flipPos[0].x] + '0';
				++matchedCardCount;
			}
			else
			{
				Sleep(500);
			}
			questionMap[flipPos[0].y][flipPos[0].x] = c;
			questionMap[flipPos[1].y][flipPos[1].x] = c;
			flipCount = 0;
			++spaceCount;

			if (matchedCardCount >= 8)
			{
				DrawGameClear();
				Sleep(2000);
				system("cls");
				Init();
				DrawBack();
			}
		}
	}

	void DrawBack()
	{
		SetTextColor(WHITE);
		GotoXY(14, 6);
		cout << "https://blockdmask.tistory.com/";
		GotoXY(14, 7);
		cout << "_by. ";
		SetTextColor(PINK);
		cout << "BlockDMask";
		SetTextColor(WHITE);
	}

	void DrawGameClear()
	{
		SetTextColor(YELLOW);
		GotoXY(10, 3);
		cout << "=========================";
		GotoXY(10, 4);
		cout << "======= C L E A R =======";
		GotoXY(10, 5);
		cout << "=========================";
		SetTextColor(WHITE);
	}

	void SetTextColor(int color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}
};

int main(void)
{
	SetConsoleView();
	GameManager* pGameMgr = new GameManager();
	pGameMgr->StartGame();
	delete(pGameMgr);
	return 0;
}
