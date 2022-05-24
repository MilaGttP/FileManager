
#include "Includes.h";
#include "Entering.h"
#include "Manager.h"
#include "Editor.h"
#include "Run.h"
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 
COORD CursorPosition;
FileManager fileManager;

void gotoXY(int, int);

void Run()
{
	int menu_item = 0, run, x = 7;
	bool running = true;

	gotoXY(18, 5); cout << "Main Menu";
	gotoXY(18, 7); cout << "->";

	while (running)
	{
		gotoXY(20, 7);  cout << "Create dir";
		gotoXY(20, 8);  cout << "Show dir";
		gotoXY(20, 9);  cout << "Move dir";
		gotoXY(20, 10); cout << "Copy dir";
		gotoXY(20, 11); cout << "Exit";

		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && x != 11)
		{
			gotoXY(18, x); cout << "  ";
			x++;
			gotoXY(18, x); cout << "->";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 7) 
		{
			gotoXY(18, x); cout << "  ";
			x--;
			gotoXY(18, x); cout << "->";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { 

			switch (menu_item) {

			case 0: {

				gotoXY(20, 16);
				fileManager.CreateDir();
				break;
			}


			case 1: {
				gotoXY(20, 16);
				fileManager.ShowDir();
				break;
			}

			case 2: {
				gotoXY(20, 16);
				fileManager.MoveDir();
				break;
			}

			case 3: {
				gotoXY(20, 16);
				fileManager.CopyDir();
				break;
			}

			case 4: {
				gotoXY(20, 16);
				cout << "Exit";
				running = false;
			}

			}

		}

	}

	gotoXY(20, 21);
}

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}