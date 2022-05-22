
#include "Includes.h";
#include "Entering.h"
#include "Manager.h"
#include "Editor.h"
#include "Run.h"
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // used for goto
COORD CursorPosition; // used for goto
FileManager fileManager;

void gotoXY(int, int); // function defined below if this is new to you.

void Run()
{
	int menu_item = 0, run, x = 7;
	bool running = true;

	gotoXY(18, 5); cout << "Main Menu";
	gotoXY(18, 7); cout << "->";

	while (running)
	{
		gotoXY(20, 7);  cout << "Create dir";
		gotoXY(20, 8);  cout << "Rename";
		gotoXY(20, 9);  cout << "Show dir";
		gotoXY(20, 10); cout << "Delete";
		gotoXY(20, 11); cout << "Exit";

		system("pause>nul"); // the >nul bit causes it the print no message

		if (GetAsyncKeyState(VK_DOWN) && x != 11) //down button pressed
		{
			gotoXY(18, x); cout << "  ";
			x++;
			gotoXY(18, x); cout << "->";
			menu_item++;
			continue;

		}

		if (GetAsyncKeyState(VK_UP) && x != 7) //up button pressed
		{
			gotoXY(18, x); cout << "  ";
			x--;
			gotoXY(18, x); cout << "->";
			menu_item--;
			continue;
		}

		if (GetAsyncKeyState(VK_RETURN)) { // Enter key pressed

			switch (menu_item) {

			case 0: {

				gotoXY(20, 16);
				fileManager.CreateDir();
				break;
			}


			case 1: {
				gotoXY(20, 16);
				fileManager.Rename();
				break;
			}

			case 2: {
				gotoXY(20, 16);
				fileManager.ShowDir();
				break;
			}

			case 3: {
				gotoXY(20, 16);
				fileManager.Delete();
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