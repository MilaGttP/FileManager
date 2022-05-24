
#include "Includes.h";
#include "Entering.h"
#include "Manager.h"
#include "Editor.h"
#include "Run.h"
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 
COORD CursorPosition;
FileManager fileManager;

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void OutFunc()
{
	gotoXY(20, 7);  cout << "Exit";
	gotoXY(20, 8);  cout << "Show directory";
	gotoXY(20, 9);  cout << "Create directory";
	gotoXY(20, 10); cout << "Copy directory";
	gotoXY(20, 11); cout << "Move directory";
	gotoXY(20, 12); cout << "Create file";
	gotoXY(20, 13); cout << "Copy file";
	gotoXY(20, 14); cout << "Move file";
	gotoXY(20, 15); cout << "Rename";
	gotoXY(20, 16); cout << "Delete";
	gotoXY(20, 17); cout << "Sort by name";
	gotoXY(20, 18); cout << "Sort by type";
	gotoXY(20, 19); cout << "Sort by size";
}

void Run()
{
	int menu_item = 0, run, x = 7;
	bool running = true;

	gotoXY(18, 5); cout << " --- MENU --- ";
	gotoXY(18, 7); cout << "->";

	while (running)
	{
		OutFunc();
		system("pause>nul");

		if (GetAsyncKeyState(VK_DOWN) && x != 19)
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
		if (GetAsyncKeyState(VK_RETURN)) 
		{ 
			switch (menu_item) 
			{
			case 0: 
			{
				gotoXY(20, 22);
				running = false;
				break;
			}
			case 1: 
			{
				gotoXY(20, 22);
				fileManager.ShowDir();
				break;
			}
			case 2: 
			{
				gotoXY(20, 22);
				fileManager.CreateDir();
				break;
			}
			case 3: 
			{
				gotoXY(20, 22);
				fileManager.CopyDir();
				break;
			}
			case 4: 
			{
				gotoXY(20, 22);
				fileManager.MoveDir();
				break;
			}
			case 5:
			{
				gotoXY(20, 22);
				fileManager.CreatingFile();
				break;
			}
			case 6:
			{
				gotoXY(20, 22);
				fileManager.CopyingFile();
				break;
			}
			case 7:
			{
				gotoXY(20, 22);
				fileManager.MovingFile();
				break;
			}
			case 8:
			{
				gotoXY(20, 22);
				fileManager.Rename();
				break;
			}
			case 9:
			{
				gotoXY(20, 22);
				fileManager.Delete();
				break;
			}
			case 10:
			{
				gotoXY(20, 22);
				fileManager.SortByName();
				break;
			}
			case 11:
			{
				gotoXY(20, 22);
				fileManager.SortByType();
				break;
			}
			case 12:
			{
				gotoXY(20, 22);
				fileManager.SortBySize();
				break;
			}

			}
		}
	}

	gotoXY(20, 21);
}