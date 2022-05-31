
#include "Manager.h"
#include "Editor.h"
#include "Includes.h"
using namespace std;
namespace fs = boost::filesystem;


//------------------* MAIN FUNC *----------------------

    //1---------------* Common *--------------------

void FileManager::SearchByName()
{
    cout << "Enter path of directory, in which you search item: ";
    getline(cin, source);
    cout << "\tEnter item`s name: ";
    getline(cin, name);
    try
    {
        if (!fs::exists(source) || !fs::is_directory(source))
            cerr << "Source directory " << source << " does not exist or is not a directory." << '\n';
        else if (!fs::exists(source + '/' + name))
            cerr << "Item " << name << " doesn`t exists.";
        if (fs::is_directory(source + '/' + name))
            ShowingDir(source + '/' + name);
        else if (fs::is_regular_file(source + '/' + name))
        {
            TextEditor tx;
            tx.ShowingFile(source + '/' + name);
        }
    }
    catch (fs::filesystem_error const& e)
    {
        cerr << e.what() << '\n';
    }
}

void FileManager::Rename()
{
     cout << "What item will you delete?" << endl;
     cout << "\t1 - Directory" << endl;
     cout << "\t2 - File" << endl;
     cout << "\tYour choice: ";
    cin.ignore(); cin.ignore();
    cout << "Enter path for renaming: ";
    getline(cin, path);
    string oldName, newName;
    uint32_t tmp;
    cout << "\tEnter old name: ";
    getline(cin, oldName);
    cout << "\tEnter new name: ";
    getline(cin, newName);
    try
    {
        if (!fs::exists(path) || !fs::is_directory(path))
            cerr << "Path " << path << " does not exist or is not a directory." << '\n';
        else if (fs::exists(path + '/' + oldName))
            fs::rename(path + '/' + oldName, path + '/' + newName);
    }
    catch (fs::filesystem_error const& e)
    {
        cout << e.what() << endl;
        std::system("pause");
    }
}

void FileManager::Delete()
{
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
            cout << "\tEnter path for delete: ";
            getline(cin, path);
            if (fs::exists(path))
                fs::remove_all(path);
            break;
        }
        case 2:
        {
            cin.ignore();
            cout << "\tEnter path for delete: ";
            getline(cin, path);
            cout << "\tEnter file name for delete: ";
            getline(cin, name);
            if (fs::exists(path + '/' + name))
                fs::remove_all(path + '/' + name);
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

    //2-------------* For Directories *------------------

void FileManager::ShowDir()
{
    cout << "Enter path of directory, what you want to show: ";
    getline(cin, source);
    ShowingDir(source);
}

void FileManager::CreateDir()
{
    cout << "Enter path for creating directory: ";
    getline(cin, path);
    cout << "\tEnter directory name: ";
    getline(cin, name);
    fs::create_directories(path + '/' + name);
}

void FileManager::CopyDir()
{
    cout << "Enter source path: ";
    getline(cin, source);
    cout << "\tEnter destination path: ";
    getline(cin, destination);
    CopyingDir(source, destination);
}

void FileManager::MoveDir()
{
    cout << "Enter source path: ";
    getline(cin, source);
    cout << "\tEnter destination path: ";
    getline(cin, destination);
    CopyingDir(source, destination);
    fs::remove_all(source);
}

    //3-------------* For Files *------------------

void FileManager::CreatingFile()
{
    cout << "Enter name of new file: ";
    getline(cin, name);
    fstream stream;
    stream.open(name, ios::out);
    if (stream.is_open())
        stream.close();
}

void FileManager::CopyingFile()
{
    cout << "Enter source path: ";
    getline(cin, source);
    cout << "\tEnter name of file: ";
    getline(cin, name);
    cout << "\tEnter destination path: ";
    getline(cin, destination);
    CopingFile(source, name, destination);
}

void FileManager::MovingFile()
{
    cout << "Enter source path: ";
    getline(cin, source);
    cout << "\tEnter name of file: ";
    getline(cin, name);
    cout << "\tEnter destination path: ";
    getline(cin, destination);
    CopingFile(source, name, destination);
    fs::remove_all(source + '/' + name);
}



//-------------------* AUXILIARY FUNC *---------------------

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

void FileManager::ShowingDir(fs::path source)
{
    fs::directory_iterator begin(source);
    fs::directory_iterator end;
    cout << "\t" << left << setfill(' ') << setw(42) << "* FileName *"
        << "* Size *" << right << setfill(' ') << setw(28) << "* Type *" << endl << endl;
    for (; begin != end; ++begin)
    {
        fs::file_status fs = fs::status(*begin);
        fs::path tmp = *begin;
        cout << left << setw(50) << tmp.filename().string();
        switch (fs.type())
        {
        case fs::regular_file:
            cout << HumanReadable{ file_size(*begin) } << right << setw(30) << "FILE" << endl;
            break;
        case fs::symlink_file:
            cout << HumanReadable{ SizeOf(*begin) } << right << setw(30) << "SYMLINK" << endl;
            break;
        case fs::directory_file:
            cout << HumanReadable{ SizeOf(*begin) } << right << setw(30) << "DIRECTORY" << endl;
            break;
        default:
            cout << HumanReadable{ SizeOf(*begin) } << right << setw(30) << "OTHER" << endl;
            break;
        }
    }
}

void FileManager::CopyingDir(fs::path const& source, fs::path const& destination)
{
    try
    {
        if (!fs::exists(source) || !fs::is_directory(source))
            cerr << "Source directory " << source << " does not exist or is not a directory." << '\n';

        else if (fs::exists(destination))
            cerr << "Destination directory " << destination << " already exists." << '\n';

        else if (!fs::create_directory(destination))
            cerr << "Unable to create destination directory " << destination << '\n';
    }
    catch (fs::filesystem_error const& e)
    {
        cerr << e.what() << '\n';
    }
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

void FileManager::CopingFile(string source, string name, string destination)
{
    try
    {
        if (!fs::exists(source))
            cerr << "Source directory " << source << " does not exist or is not a directory." << '\n';
        else if (!fs::exists(source + '/' + name) || !fs::is_regular_file(source + '/' + name))
            cerr << "Source file " << source + '/' + name << " does not exist or is not a file." << '\n';
        else if (!fs::exists(destination))
        {
            string buff;
            cout << "You haven`t such a directory! Enter wanted path and name to create it: ";
            getline(cin, buff);
            if(fs::create_directories(buff))
                fs::copy_file(source + '/' + name, destination + '/' + name);
        }
        else
            fs::copy_file(source + '/' + name, destination + '/' + name);
    }
    catch (fs::filesystem_error const& e)
    {
        cerr << e.what() << '\n';
    }
}



//----------------* FOR FILEMANAGER *------------------

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