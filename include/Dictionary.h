#ifndef __Dictionary_H__
#define __Dictionary_H__

#include <vector>
#include <map>
#include <set>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::string;
using std::pair;
using std::map;
using std::set;
using std::vector;

class Dictionary{
public:
    static Dictionary* createInstance();
    void init(const string& dictpath);
    vector<pair<string,int>> & getDict();
    map<string,set<int>> &getIndexTable();
private:
    vector<pair<string,int>> _dict;
    map<string,set<int>> _indexTable;
    static Dictionary* dicPtr;
};

int getUtf8ByteType(unsigned char c);
#endif
