#pragma once
#ifndef __DIRSCANNER_H__
#define __DIRSCANNER_H__

#include <vector>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>


using std::vector;
using std::string;

class DirScanner
{
public:
    DirScanner();
    vector<string> getFiles();
    void traverse(const string &dirname);
    ~DirScanner();
private:
    vector<string> _files;
};
#endif
