#pragma once
#ifndef __SPLITTOOLCPPJIEBA_H__
#define __SPLITTOOLCPPJIEBA_H__

#include <string>
#include <vector>
#include <fstream>
#include "SplitTool.h"

using std::string;
using std::vector;

class SplitToolCppJieba:public SplitTool
{
public:
    SplitToolCppJieba();
    ~SplitToolCppJieba();
    vector<string> cut(const string& sentence) override;
private:
    
};

#endif
