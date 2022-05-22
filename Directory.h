
#pragma once
#include <string>
using std::string;

class Dir
{
protected:
	string path;
	string name;
	uint32_t size;
public:
	Dir();
	Dir(string path, string name, uint32_t size);
	void SetPath(string path);
	void SetName(string name);
	void SetSize(uint32_t size);
	string GetPath();
	string GetName();
	uint32_t GetSize();
	~Dir();
};