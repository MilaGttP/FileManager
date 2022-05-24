
#include "Manager.h"
#include "Includes.h"
#include <boost/filesystem.hpp>
using namespace std;
using namespace boost;
namespace fs = boost::filesystem;

//------------* MAIN FUNC *----------------------

    //1------------* Common *--------------------

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
    catch (fs::filesystem_error const& e)
    {
        cout << e.what() << endl;
        std::system("pause");
    }
}

void FileManager::SortByName()
{

}

void FileManager::SortBySize()
{

}

void FileManager::SortByType()
{

}

void FileManager::Delete()
{
    string name, path;
    uint32_t tmp;
    cout << "What item will you delete?" << endl;
    cout << "\t1 - Directory" << endl;
    cout << "\t2 - File" << endl;
    cout << "\tYour choice: ";
    cin >> tmp;
    try
    {
        switch (tmp)
        {
        case 1:
        {
            cin.ignore();
            path = EnterPath();
            DeleteDir(path);
            break;
        }
        case 2:
        {
            cin.ignore();
            path = EnterPath();
            name = EnterName();
            DeletingFile(path, name);
            break;
        }
        }
    }
    catch (fs::filesystem_error const& e)
    {
        cout << e.what() << endl;
        std::system("pause");
    }
}

    //2-----------* For Directories *------------------

void FileManager::ShowDir()
{
    string buff = EnterPath();
    fs::directory_iterator begin(buff);
    fs::directory_iterator end;
    fs::path tmp;
    cout << "\t" << left << setfill(' ') << setw(42) << "* FileName *"
        << "* Size *" << right << setfill(' ') << setw(28) << "* Type *" << endl << endl;
    for (; begin != end; ++begin)
    {
        fs::file_status fs = fs::status(*begin);
        tmp = *begin;
        cout << left << setw(50) << tmp.filename().string();
        switch (fs.type())
        {
        case fs::regular_file:
            cout << HumanReadable { file_size(*begin) } << right << setw(30) << "FILE" << endl;
            break;
        case fs::symlink_file:
            cout << HumanReadable { SizeOf(*begin) } << right << setw(30) << "SYMLINK" << endl;
            break;
        case fs::directory_file:
            cout << HumanReadable { SizeOf(*begin) } << right << setw(30) << "DIRECTORY" << endl;
            break;
        default:
            cout << HumanReadable { SizeOf(*begin) } << right << setw(30) << "OTHER" << endl;
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
    fs::create_directories(dir.GetPath() + '/' + dir.GetName(), error);
    assert(!error);
}

void FileManager::CopyDir()
{
    string source = EnterPath();
    string destination = EnterPath();
    try
    {
        if (!fs::exists(source) ||
            !fs::is_directory(source))
        {
            cerr << "Source directory " << source
                << " does not exist or is not a directory." << '\n';
        }

        if (fs::exists(destination))
        {
            cerr << "Destination directory " << destination << " already exists." << '\n';
        }

        if (!fs::create_directory(destination))
        {
            cerr << "Unable to create destination directory"
                << destination << '\n';
        }
    }
    catch (fs::filesystem_error const& e)
    {
        cerr << e.what() << '\n';
    }

    CopyingDir(source, destination);
}

void FileManager::MoveDir()
{
    string source = EnterPath();
    string destination = EnterPath();
    try
    {
        if (!fs::exists(source) ||
            !fs::is_directory(source))
        {
            cerr << "Source directory " << source
                << " does not exist or is not a directory." << '\n';
        }

        if (fs::exists(destination))
        {
            cerr << "Destination directory " << destination << " already exists." << '\n';
        }

        if (!fs::create_directory(destination))
        {
            cerr << "Unable to create destination directory"
                << destination << '\n';
        }
    }
    catch (fs::filesystem_error const& e)
    {
        cerr << e.what() << '\n';
    }

    CopyingDir(source, destination);
    DeleteDir(source);
}

    //3-----------* For Files *------------------


void FileManager::CreatingFile()
{
    string name = EnterName();
    fstream stream;
    stream.open(name, ios::out);
    if (stream.is_open())
    {
        stream.close();
        cout << "Created" << endl;
    }
}

void FileManager::CopyingFile()
{
    string source = EnterPath();
    string destination = EnterPath();
    string name = EnterName();
    try
    {
        if (!fs::exists(source) || !fs::is_regular_file(name))
        {
            cerr << "Source file " << source
                << " does not exist or is not a file." << '\n';
        }
        if (!fs::exists(destination))
        {
            cerr << "Destination directory " << destination << " haven`t already exists." << '\n';
        }
        /*else
        {
            fs::copy_file()
        }*/
    }
    catch (fs::filesystem_error const& e)
    {
        cerr << e.what() << '\n';
    }
}

void FileManager::MovingFile()
{

}



//------------* Auxiliary Func *----------------------

uint32_t FileManager::SizeOf(fs::path path)
{
    size_t size = 0;
    for (fs::recursive_directory_iterator it(path);
        it != fs::recursive_directory_iterator(); ++it)
    {
        if (!fs::is_directory(*it))
            size += fs::file_size(*it);
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

void FileManager::CopyingDir(fs::path const& source, fs::path const& destination)
{
    for (fs::directory_iterator file(source); file != fs::directory_iterator(); ++file)
    {
        try
        {
            fs::path current(file->path());
            if (fs::is_directory(current))
                fs::copy_directory(current, destination / current.filename());
            else
                fs::copy_file(current, destination / current.filename());
        }
        catch (fs::filesystem_error const& e)
        {
            cerr << e.what() << '\n';
        }
    }
}

void FileManager::RenameDir(string path, string oldName, string newName)
{
    dir.SetPath(path);
    if (fs::exists(dir.GetPath() + '/' + oldName))
        fs::rename(dir.GetPath() + '/' + oldName, dir.GetPath() + '/' + newName);
}

void FileManager::RenameFile(string path, string oldName, string newName)
{
    file.SetPath(path);
    if (fs::exists(file.GetPath() + '/' + oldName))
        fs::rename(file.GetPath() + '/' + oldName, file.GetPath() + '/' + newName);
}

void FileManager::DeleteDir(string path)
{
    dir.SetPath(path);
    if (fs::exists(dir.GetPath()))
        fs::remove_all(dir.GetPath());
}

void FileManager::DeletingFile(string path, string name)
{
    file.SetPath(path);
    file.SetName(name);
    if (fs::exists(file.GetPath() + '/' + file.GetName()))
        fs::remove_all(file.GetPath() + '/' + file.GetName());
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
