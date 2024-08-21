#pragma once
#ifndef __PAGELIB_H__
#define __PAGELIB_H__
#include<map>
#include <vector>
#include <iostream>
#include <string>
#include <utility>

#include "DirScanner.h"
#include "Configuration.h"
#include "DirScanner.h"
#include "FileProcessor.h"

using std::cout;
using std::vector;
using std::map;
using std::string;
using std::pair;

class PageLib
{
public:
    PageLib(Configuration& conf,
            DirScanner& dirScanner,
            FileProcessor& fileProcessor);
    ~PageLib();

    void create();
    void store();
private:
    DirScanner _dirScanner;
    vector<string> _files;
    map<int,pair<int,int>> _offsetLib;
};

#endif 