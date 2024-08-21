#include "DirScanner.h"
#include "Configuration.h"

DirScanner::DirScanner()
{

}

DirScanner::~DirScanner()
{

}

void DirScanner::(const string &dirname)
{
    DIR * path = readdir64(dirname);

    struct dirent* entry;
    while((entry = path)!=nullptr)
    {
        string filename = entry->d_name;
    }
}

vector<string> DirScanner::getFiles()
{
    Configuration* conPtr = Configuration::getInstance();
    map<string,map<string,string>>& filePath = conPtr->getConfigFile();

}