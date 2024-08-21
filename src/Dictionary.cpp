#include "../include/Dictionary.h"

const string dictCn = "../data/dict_cn.txt";
const string dictEn = "../data/dict_eng.txt";

Dictionary* Dictionary::dicPtr = nullptr;

// int getUtf8ByteType(unsigned char c)
// {
//      if ((c & 0xE0) == 0xC0) {  
//         return 2; 
//     }else if((c&0xF0)==0xE0)
//     {
//         return 3;
//     }else if((c&0xF8)==0xF0)
//     {
//         return 4;
//     }else{
//         return 1;
//     }
// }

Dictionary* Dictionary::createInstance()
{
    if(dicPtr == nullptr)
    {
        dicPtr = new Dictionary();
        dicPtr->init(dictCn);
        dicPtr->init(dictEn);
    }
    return dicPtr;
}


void Dictionary::init(const string &dictpath)
{
    ifstream dictIfs(dictpath);
    string line;
    while(dictIfs>>line)
    {
        string key;
        int value;
        std::istringstream iss(line);
        iss>>key;
        iss>>value;
        _dict.emplace_back(make_pair(key,value));
    }

    size_t dictLen = _dict.size();
    for(size_t idx = 0; idx<dictLen; ++idx)
    {
        string word = _dict[idx].first;
        size_t wordLen = word.length();
        for(size_t i = 0;i<wordLen;)
        {
            int temp = getUtf8ByteType(word[i]);
            string ch = word.substr(i,temp);
            _indexTable[ch].insert(idx);
            i += temp;
        }
    }
}

vector<pair<string,int>>& Dictionary::getDict()
{
    return _dict;
}

map<string,set<int>>& Dictionary::getIndexTable()
{
    return _indexTable;
}


