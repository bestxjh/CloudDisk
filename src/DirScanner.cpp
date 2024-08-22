#include "../include/DirScanner.h"
#include "../include/Configuration.h"

DirScanner::DirScanner()
{
    
}

DirScanner::~DirScanner()
{

}

void DirScanner::traverse(const string &dirname)
{
    std::cout<<"DirScanner16\n";
    DIR* path = opendir(dirname.c_str());
    struct dirent* entry;
    while((entry = readdir(path))!=nullptr)
    {
        string filename = entry->d_name;

        if(filename =="."||filename =="..")
            continue;
        string lastPath = dirname + "/"+filename;
        struct stat file_stat;
        if(stat(lastPath.c_str(),&file_stat) == 0 && S_ISREG(file_stat.st_mode) && lastPath.substr(lastPath.size()-3)=="xml")
        {
            _files.emplace_back(lastPath);
        }
    }
    closedir(path);
}

vector<string> DirScanner::getFiles()
{
    std::cout<<"Dirscanner 37\n";
    Configuration& mycon = Configuration::getInstance();
    string path = mycon.getValue("DIR","yuliao");
    traverse(path);
    return _files;
}
