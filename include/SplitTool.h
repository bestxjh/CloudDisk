#pragma once
#ifndef __SPLITHTOOL_H__
#define __SPLITTOOL_H__
#include <string>
#include <vector>
#include "cppjieba/Jieba.hpp"

using std::string;
using std::vector;

const char* const DICT_PATH = "./dict/jieba.dict.utf8";
const char* const HMM_PATH = "./dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "./dict/user.dict.utf8";
const char* const IDF_PATH = "./dict/idf.utf8";
const char* const STOP_WORD_PATH = "./dict/stop_words.utf8";

class SplitTool
{
public:
    static cppjieba::Jieba& getInstance()
    {
        if(!jieba){
            jieba = new cppjieba::Jieba(
                                        DICT_PATH,
                                        HMM_PATH,
                                        USER_DICT_PATH,
                                        IDF_PATH,
                                        STOP_WORD_PATH
                                       );
        }
        return *jieba;
    }
    ~SplitTool() ;
    
    SplitTool(SplitTool& other) = delete;
    void operator=(const SplitTool&) =delete;
    virtual vector<string> cut(const string& sentence) = 0;
private:
    SplitTool() {}
    static cppjieba::Jieba* jieba;
};
#endif
