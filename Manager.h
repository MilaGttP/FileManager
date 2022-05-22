
#pragma once
#include <boost/filesystem/operations.hpp>
#include "File.h"
#include "Directory.h"

class FileManager
{
protected:
	File file;
	Dir dir;
public:

	//------------* MAIN FUNC *---------

	
	//1------------* Common *------------

	void Rename();
	void SortByName();
	void SortBySize();
	void Delete();

	//2-----------* For Directories *--------

	void ShowDir();
	void CreateDir();
	void CopyDir();
	void MoveDir();


	//3-----------* For Files *--------------

  	void CreatingFile();
	void CopyingFile();
	void MovingFile();
	


	//------------* AUXILIARY FUNC *----------

	uint32_t SizeOf(boost::filesystem::path path);
	string EnterPath();
	string EnterName();
	void RenameDir(string path, string oldName, string newName);
	void RenameFile(string path, string oldName, string newName);
	void DeleteDir(string path, string name);
	void DeletingFile(string path, string name);
};



//--------* FOR FILEMANAGER *---------

struct HumanReadable
{
private:
	friend std::ostream& operator << (std::ostream& os, HumanReadable hr);
	friend std::ostream& operator << (std::ostream& os, uint32_t size);
public:
	uintmax_t size{};
};

