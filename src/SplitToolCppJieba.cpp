#include "SplitToolCppJieba.h"

SplitToolCppJieba::SplitToolCppJieba(){

}
SplitToolCppJieba::~SplitToolCppJieba(){

}

vector<string> SplitToolCppJieba::cut(const string& sentence){
    vector<string> words;
    cppjieba::Jieba* jiebaptr = SplitTool::getInstance();
    jiebaptr->Cut(sentence,words);
    return words;
}
