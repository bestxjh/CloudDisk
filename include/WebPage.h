#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__

#include <iostream>
#include <vector>
#include <map>
#include "Configuration.h"
#include "SplitTool.h"

using std::vector;
using std::map;
using std::string;


class WebPage
{
public:
    WebPage(string &doc,Configuration& config,SplitTool& jieba);
    int getDocld();
    string getDoc();
    map<string,int> &getWordMap();
    void processDoc(const string& doc,Configuration & config,SplitTool & jieba);
    void calcTopK(vector<string>& wordsVec,int k,set<string> & stopWordList);
    friend bool operator==(const WebPage &lhs,const WebPage & rhs);
    friend bool operator<(const WebPage &lhs,const WebPage & rhs);
private:
    const static int TOPK_NUMBER = 20;
    string _doc;
    int _docld;
    string _docTitle;
    string _docUrl;
    string _docContent;
    string _docSummary;
    vector<string> _topWords;
    map<string,int> _wordsMap;
};

bool operator==(const WebPage &lhs,const WebPage & rhs);
bool operator<(const WebPage &lhs,const WebPage & rhs);
#endif