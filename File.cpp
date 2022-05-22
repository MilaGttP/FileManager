
#include "File.h"
#include <iostream>

File::File()
{
	this->path = "";
	this->name = "";
	this->size = 0;
}

File::File(string path, string name, uint32_t size)
{
	this->path = path;
	this->name = name;
	this->size = size;
}

void File::SetPath(string path)
{
	this->path = path;
}

void File::SetName(string name)
{
	this->name = name;
}

void File::SetSize(uint32_t size)
{
	this->size = size;
}

string File::GetPath()
{
	return this->path;
}

string File::GetName()
{
	return this->name;
}

uint32_t File::GetSize()
{
	return this->size;
}

File::~File()
{
	this->path.clear();
	this->name.clear();
	this->size = 0;
}
