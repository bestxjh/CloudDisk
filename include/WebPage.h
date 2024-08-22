#ifndef __WEBPAGE_H__
#define __WEBPAGE_H__

#include <iostream>
#include <vector>

using std::string;


class WebPage
{
public:
    WebPage(string title,string url,string content);
    size_t getDocld();
    string getTitle();
    string getUrl();
private:
    size_t _docld;
    string _docTitle;
    string _docUrl;
    string _docContent;
};

#endif
