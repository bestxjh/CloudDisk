#pragma once
#ifndef __PAGELIBPREPROCESSOR_H__
#define __PAGELIBPREPROCESSOR_H__

#include "SplitTool.h"
#include "Configuration.h"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <utility>

using std::vector;
using std::unordered_map;
using std::pair;

class PageLibPreprocessor
{
public:
    PageLibPreprocessor(Configuration& conf);
    void doProcess();
    void readInfoFromFile();
    void cutRedundantPage();
    void buildInvertIndexMap();
    void storeOnDisk();
    ~PageLibPreprocessor();

private:
    vector<WebPage> _pageList;
    unordered_map _offsetLib;
    unordered_map<string,vector<pair<int,double>>> _invertIndexLib;
    SplitTool* _wordCutter;
};

#endif