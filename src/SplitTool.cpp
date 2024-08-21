#include "SplitTool.h"

cppjieba::Jieba* SplitTool::jieba = nullptr;

SplitTool::~SplitTool()
{
    if(jieba != nullptr){
        delete jieba;    
        jieba=nullptr;
    }
}

