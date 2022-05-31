
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
		else if (GetAsyncKeyState(VK_DOWN) && x != 17)
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
				system("cls");
				gotoXY(4, 2);				
				fileManager.CreateDir();
				system("cls");
				break;
			}
			case 3: 
			{
				system("cls");
				gotoXY(4, 2);
				fileManager.CopyDir();
				system("cls");
				break;
			}
			case 4: 
			{
				system("cls");
				gotoXY(4, 2);
				fileManager.MoveDir();
				system("cls");
				break;
			}
			case 5:
			{
				system("cls");
				gotoXY(4, 2);
				fileManager.CreatingFile();
				system("cls");
				break;
			}
			case 6:
			{
				system("cls");
				gotoXY(4, 2);
				fileManager.CopyingFile();
				system("cls");
				break;
			}
			case 7:
			{
				system("cls");
				gotoXY(4, 2);
				fileManager.MovingFile();
				system("cls");
				break;
			}
			case 8:
			{
				system("cls");
				gotoXY(4, 2);
				fileManager.SearchByName();
				system("pause");
				system("cls");
				break;
			}
			case 9:
			{
				system("cls");
				gotoXY(4, 2);
				fileManager.Rename();
				system("cls");
				break;
			}
			case 10:
			{
				system("cls");
				gotoXY(4, 2);
				fileManager.Delete();
				system("cls");
				break;
			}
			case 11:
			{
				system("cls");
				gotoXY(4, 2);
				textEditor.ShowFile();
				system("pause");
				system("cls");
				break;
			}
			case 12:
			{
				system("cls");
				gotoXY(4, 2);
				textEditor.Append();
				system("cls");
				break;
			}
			case 13:
			{
				system("cls");
				gotoXY(4, 2);
				textEditor.Rewrite();
				system("cls");
				break;
			}
			}
		}
	}

	gotoXY(20, 21);
}