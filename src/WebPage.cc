#include "../include/WebPage.h"


WebPage::WebPage(string title,string url,string content):
    _docTitle(title),
    _docUrl(url),
    _docContent(content)
{

}


size_t WebPage::getDocld()
{
    return _docld;
}

string WebPage::getTitle()
{
    return _docTitle;
}

string WebPage::getUrl()
{
    return _docUrl;
}
