#pragma once
#ifndef __DICPRODUCER_H__
#define __DICPRODUCER_H__

#include <vector>
#include <string>
#include <utility>
#include <set>
#include <map>
#include "SplitTool.h"
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>

using std::map;
using std::pair;
using std::set;
using std::string;

class DicProducer
{
public:
    DicProducer(const string dir,SplitTool* tool) ;
    ~DicProducer() ;

    void buildEnDict();
    void buildCnDict();
    void createIndex();
    void store();

private:
    vector<string> _files;
    vector<pair<string,int>> _dictEnd;
    map<string,set<int>> _indexEnd;
    
    vector<pair<string,int>> _dictCn;
    map<string,set<int>> _indexCn;
    SplitTool* _cuttor;
};

#endif
