
#pragma once
#include "File.h"

class TextEditor
{
protected:
	File file;
public:
	void ShowFile();
	void AppendFile();
	void CopyValue();
	void Rewrite();
};