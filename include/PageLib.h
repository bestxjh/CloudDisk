#pragma once
#ifndef __PAGELIB_H__
#define __PAGELIB_H__
#include<map>
#include <vector>
#include <iostream>
#include <string>
#include <utility>
#include <fstream>

#include "DirScanner.h"
#include "Configuration.h"
#include "DirScanner.h"
#include "FileProcessor.h"
#include "tinyxml2.h"
#include "WebPage.h"
#include <regex>
using std::ifstream;
using namespace tinyxml2;
using std::cout;
using std::vector;
using std::map;
using std::string;
using std::pair;

/* struct RSSIteam */
/* { */
/*     int docid; */
/*     string url; */
/*     string title; */
/*     string content; */
/* }; */

class PageLib
{
public:
    PageLib(DirScanner& dirScanner);
    ~PageLib();

    void create();
    void store();
private:
    DirScanner _dirScanner;
    vector<string> _files;
    map<int,pair<int,int>> _offsetLib;
};

#endif 
