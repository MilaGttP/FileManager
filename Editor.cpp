
#include "Editor.h"
#include "Includes.h"
#include <boost/filesystem/operations.hpp>
using namespace std;
using namespace boost;
namespace fs = boost::filesystem;

//------------* MAIN FUNC *---------

void TextEditor::ShowFile()
{
	cout << "Enter file name: ";
	getline(cin, name);
	cout << "File " << name << " contents: " << endl;
	ShowingFile(name);
}

void TextEditor::Append()
{
	fstream stream;
	cout << "Enter file name for appending (hint: hit TAB to finish): ";
	getline(cin, name);
	cout << endl;
	try
	{
		stream.open(name, ios::out | ios::app);
		if (stream.is_open())
		{
			while (true)
			{
				cout << right << setfill(' ') << setw(8) << count << "| ";
				getline(cin, buff);
				if (GetAsyncKeyState(VK_TAB))
				{
					_getch();
					cout << "Done!" << endl;
					break;
				}
				else
				{
					stream << buff << endl;
					count++;
				}
			}
			stream.close();
		}
	}
	catch (fs::filesystem_error const& e)
	{
		cout << e.what() << endl;
		std::system("pause");
	}
}

void TextEditor::Rewrite()
{
	fstream stream; 
	cout << "Enter file name for rewriting (hint: hit TAB to finish): ";
	getline(cin, name);
	stream.open(name, ios::in);
	try
	{
		if (stream.is_open())
		{
			cout << "\nPrevious text is: \n";
			while (getline(stream, tmp))
				cout << tmp << endl;
			stream.close();
		}
		cout << endl;
		stream.open(name, ios::out | ios::app);
		if (stream.is_open())
		{
			while (true)
			{
				cout << right << setfill(' ') << setw(8) << count << "| ";
				getline(cin, buff);
				if (GetAsyncKeyState(VK_TAB))
				{
					_getch();
					cout << "Done!" << endl;
					break;
				}
				else
				{
					stream << buff << endl;
					count++;
				}
			}
			stream.close();
		}
	}
	catch (fs::filesystem_error const& e)
	{
		cout << e.what() << endl;
		std::system("pause");
	}
}

//------------* AUXILIARY FUNC *----------

void TextEditor::ShowingFile(string name)
{
	fstream stream;
	stream.open(name, ios::in);
	try
	{
		if (stream.is_open())
		{
			while (getline(stream, buff))
				cout << buff << endl;
			stream.close();
		}
	}
	catch (fs::filesystem_error const& e)
	{
		cout << e.what() << endl;
		std::system("pause");
	}
}
	