
#include "Includes.h";
#include "Manager.h"
#include "Editor.h"
#include "Run.h"
using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); 
COORD CursorPosition;

FileManager fileManager;
TextEditor textEditor;

void gotoXY(int x, int y)
{
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void OutFunc()
{
	gotoXY(15, 4);  cout << "Exit";
	gotoXY(15, 5);  cout << "Show directory";
	gotoXY(15, 6);  cout << "Create directory";
	gotoXY(15, 7);  cout << "Copy directory";
	gotoXY(15, 8);  cout << "Move directory";
	gotoXY(15, 9);  cout << "Create file";
	gotoXY(15, 10); cout << "Copy file";
	gotoXY(15, 11); cout << "Move file";
	gotoXY(15, 12); cout << "Search by name";
	gotoXY(15, 13); cout << "Rename";
	gotoXY(15, 14); cout << "Delete";
	gotoXY(15, 15); cout << "Show file";
	gotoXY(15, 16); cout << "Append file";
	gotoXY(15, 17); cout << "Rewrite file";
	gotoXY(15, 18); cout << "Sort by name";
	gotoXY(15, 19); cout << "Sort by type";
	gotoXY(15, 20); cout << "Sort by size";
}

void Run()
{
	int menu_item = 0, run, x = 4;
	bool running = true;
	gotoXY(12, 4); cout << "->";
	while (running)
	{
		gotoXY(12, 2); cout << " --- MENU --- ";
		OutFunc();
		system("pause>nul");

		if (GetAsyncKeyState(VK_UP) && x != 4)
		{
		    gotoXY(12, x); cout << "  ";
		    x--;
		    gotoXY(12, x); cout << "->";
		    menu_item--;
		    continue;
		}
		else if (GetAsyncKeyState(VK_DOWN) && x != 20)
		{
			gotoXY(12, x); cout << "  ";
			x++;
			gotoXY(12, x); cout << "->";
			menu_item++;
			continue;
		}
		else if (GetAsyncKeyState(VK_RETURN)) 
		{ 
			switch (menu_item) 
			{
			case 0: 
			{
				system("cls");
				cout << "\n\tExit." << endl;
				running = false;
				break;
			}
			case 1: 
			{
				system("cls");
				gotoXY(4, 2);
				fileManager.ShowDir();
				system("pause");
				system("cls");
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
				fileManager.SearchByName();
				break;
			}
			case 9:
			{
				gotoXY(20, 22);
				fileManager.Rename();
				break;
			}
			case 10:
			{
				gotoXY(20, 22);
				fileManager.Delete();
				break;
			}
			case 11:
			{
				gotoXY(20, 22);
				textEditor.ShowFile();
				break;
			}
			case 12:
			{
				gotoXY(20, 22);
				textEditor.Append();
				break;
			}
			case 13:
			{
				gotoXY(20, 22);
				textEditor.Rewrite();
				break;
			}
			case 14:
			{
				gotoXY(20, 22);
				fileManager.SortByName();
				break;
			}
			case 15:
			{
				gotoXY(20, 22);
				fileManager.SortByType();
				break;
			}
			case 16:
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