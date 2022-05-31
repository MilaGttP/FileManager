
#pragma once
#include <iostream>
using std::string;

class TextEditor
{
protected:
	uint32_t count = 1;
	string name;
	string buff;
	string tmp;
public:

	//------------* MAIN FUNC *---------

	void ShowFile();
	void Append();
	void Rewrite();

	//------------* AUXILIARY FUNC *----------

	void ShowingFile(string name);
};