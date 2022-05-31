
#pragma once
#include <boost/filesystem/operations.hpp>
using std::string;

class FileManager
{
protected:
	string path;
	string name;
	string source;
	string destination;
public:

	//------------* MAIN FUNC *---------
	
	//1------------* Common *------------

	void SearchByName();
	void Rename();
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
	void ShowingDir(boost::filesystem::path source);
	void CopyingDir(boost::filesystem::path const& source, boost::filesystem::path const& destination);
	void CopingFile(string source, string name, string destination);
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