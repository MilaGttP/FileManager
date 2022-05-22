
#include "Manager.h"
#include "Includes.h"
using namespace std;
using namespace boost;


//------------* Main Func *----------------------

void FileManager::ShowDir()
{
    string buff = EnterPath();
    boost::filesystem::directory_iterator begin(buff);
    boost::filesystem::directory_iterator end;
    boost::filesystem::path path;
    cout << "\t" << left << setfill(' ') << setw(45) << "Filename"
        << "Size" << right << setfill(' ') << setw(45) << "Type" << endl;
    for (; begin != end; ++begin)
    {
        boost::filesystem::file_status fs = boost::filesystem::status(*begin);
        path = *begin;
        cout << left << setw(50) << path.filename().string();
        switch (fs.type())
        {
        case boost::filesystem::regular_file:
            cout << HumanReadable { file_size(*begin) } << right << setw(45) << "FILE" << endl;
            break;
        case boost::filesystem::symlink_file:
            cout << HumanReadable { SizeOf(*begin) } << right << setw(45) << "SYMLINK" << endl;
            break;
        case boost::filesystem::directory_file:
            cout << HumanReadable { SizeOf(*begin) } << right << setw(45) << "DIRECTORY" << endl;
            break;
        default:
            cout << HumanReadable { SizeOf(*begin) } << right << setw(45) << "OTHER" << endl;
            break;
        }
    }
}

void FileManager::CreateDir()
{
    string path = EnterPath();
    dir.SetPath(path);
    string name = EnterName();
    dir.SetName(name);
    boost::system::error_code error;
    boost::filesystem::create_directories(dir.GetPath() + '/' + dir.GetName(), error);
    assert(!error);
}

void FileManager::CreatingFile()
{

}

void FileManager::Rename()
{
    string oldName, newName, path;
    uint32_t tmp;
    cout << "What item will you rename?" << endl;
    cout << "\t1 - Directory" << endl;
    cout << "\t2 - File" << endl;
    cout << "\tYour choice: "; cin >> tmp;
    cin.ignore();
    path = EnterPath();
    cout << "Enter old name: ";
    getline(cin, oldName);
    cout << "Enter new name: ";
    getline(cin, newName);
    try
    {
        switch (tmp)
        {
        case 1:
        {
            RenameDir(path, oldName, newName);
            break;
        }
        case 2:
        {
            RenameFile(path, oldName, newName);
            break;
        }
        }
    }
    catch (boost::filesystem::filesystem_error const& e)
    {
        cout << e.what() << endl;
        std::system("pause");
    }
}

void FileManager::Delete()
{
    string name, path;
    uint32_t tmp;
    cout << "What item will you delete?" << endl;
    cout << "\t1 - Directory" << endl;
    cout << "\t2 - File" << endl;
    cout << "\tYour choice: "; cin >> tmp;
    cin.ignore();
    path = EnterPath();
    name = EnterName();
    try
    {
        switch (tmp)
        {
        case 1:
        {
            DeleteDir(path, name);
            break;
        }
        case 2:
        {
            DeletingFile(path, name);
            break;
        }
        }
    }
    catch (boost::filesystem::filesystem_error const& e)
    {
        cout << e.what() << endl;
        std::system("pause");
    }
}


//------------* Auxiliary Func *----------------------

uint32_t FileManager::SizeOf(boost::filesystem::path path)
{
    size_t size = 0;
    for (boost::filesystem::recursive_directory_iterator it(path);
        it != boost::filesystem::recursive_directory_iterator();
        ++it)
    {
        if (!boost::filesystem::is_directory(*it))
            size += boost::filesystem::file_size(*it);
    }
    return size;
}

string FileManager::EnterPath()
{
    string path;
    cout << "Enter path: ";
    getline(cin, path);
    return path;
}

string FileManager::EnterName()
{
    string name;
    cout << "Enter name: ";
    getline(cin, name);
    return name;
}

void FileManager::RenameDir(string path, string oldName, string newName)
{
    dir.SetPath(path);
    if (boost::filesystem::exists(dir.GetPath() + '/' + oldName))
        boost::filesystem::rename(dir.GetPath() + '/' + oldName, dir.GetPath() + '/' + newName);
}

void FileManager::RenameFile(string path, string oldName, string newName)
{
    file.SetPath(path);
    if (boost::filesystem::exists(file.GetPath() + '/' + oldName))
        boost::filesystem::rename(file.GetPath() + '/' + oldName, file.GetPath() + '/' + newName);
}

void FileManager::DeleteDir(string path, string name)
{
    dir.SetPath(path);
    dir.SetName(name);
    if (boost::filesystem::exists(dir.GetPath() + '/' + dir.GetName()))
        boost::filesystem::remove_all(dir.GetPath() + '/' + dir.GetName());
}

void FileManager::DeletingFile(string path, string name)
{
    file.SetPath(path);
    file.SetName(name);
    if (boost::filesystem::exists(file.GetPath() + '/' + file.GetName()))
        boost::filesystem::remove_all(file.GetPath() + '/' + file.GetName());
}



//-------------* For FileManager *-------------------

ostream& operator << (ostream& os, HumanReadable hr)
{
    int i{};
    double mantissa = hr.size;
    for (; mantissa >= 1024.; mantissa /= 1024., ++i) {}
    mantissa = ceil(mantissa * 10.) / 10.;
    os << mantissa << " " << "BKMGTPE"[i];
    return i == 0 ? os : os << "B ";
}

ostream& operator << (ostream& os, uint32_t size)
{
    int i{};
    double mantissa = size;
    for (; mantissa >= 1024.; mantissa /= 1024., ++i) {}
    mantissa = std::ceil(mantissa * 10.) / 10.;
    os << mantissa << " " << "BKMGTPE"[i];
    return i == 0 ? os : os << "B ";
}
