#include "../include/SplitTool.h"

cppjieba::Jieba* SplitTool::jieba = nullptr;

SplitTool::~SplitTool()
{
    delete jieba;    
}

