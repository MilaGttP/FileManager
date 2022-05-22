
#include "Directory.h"
#include <iostream>

Dir::Dir()
{
	this->path = "";
	this->name = "";
	this->size = 0;
}

Dir::Dir(string path, string name, uint32_t size)
{
	this->path = path;
	this->name = name;
	this->size = size;
}

void Dir::SetPath(string path)
{
	this->path = path;
}

void Dir::SetName(string name)
{
	this->name = name;
}

void Dir::SetSize(uint32_t size)
{
	this->size = size;
}

string Dir::GetPath()
{
	return this->path;
}

string Dir::GetName()
{
	return this->name;
}

uint32_t Dir::GetSize()
{
	return this->size;
}

Dir::~Dir()
{
	this->path.clear();
	this->name.clear();
	this->size = 0;
}
