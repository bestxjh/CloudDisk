#include "../include/KeyRecommander.h"
#include "../include/nlohmann/json.hpp"
using nlohmann::json;


size_t nBytesCode(const char ch)
{
    if(ch & (1 << 7))
    {
        int nBytes = 1;
        for(int idx = 0; idx != 6; ++idx)
        {
            if(ch & (1 << (6 - idx)))
            {
                ++nBytes;
            }
            else
                break;
        }
        return nBytes;
    }
    return 1;
}

int getUtf8ByteType(unsigned char c)
{
     if ((c & 0xE0) == 0xC0) {  
        return 2; 
    }else if((c&0xF0)==0xE0)
    {
        return 3;
    }else if((c&0xF8)==0xF0)
    {
        return 4;
    }else{
        return 1;
    }
}

std::size_t length(const std::string &str)
{
    std::size_t ilen = 0;
    for(std::size_t idx = 0; idx != str.size(); ++idx)
    {
        int nBytes = nBytesCode(str[idx]);
        idx += (nBytes - 1);
        ++ilen;
    }
    return ilen;
}

int triple_min(const int &a, const int &b, const int &c)
{
    return a < b ? (a < c ? a : c) : (b < c ? b : c);
}

int KeyRecommander::distance(const std::string &rhs)
{
    const string &lhs = _queryWord;
    //计算最小编辑距离-包括处理中英文
    size_t lhs_len = length(lhs);
    size_t rhs_len = length(rhs);
    int editDist[lhs_len + 1][rhs_len + 1];
    for(size_t idx = 0; idx <= lhs_len; ++idx)
    {
        editDist[idx][0] = idx;
    }
    for(size_t idx = 0; idx <= rhs_len; ++idx)
    {
        editDist[0][idx] = idx;
    }
    std::string sublhs, subrhs;
    for(std::size_t dist_i = 1, lhs_idx = 0; dist_i <= lhs_len; ++dist_i,
        ++lhs_idx)
    {
        size_t nBytes = nBytesCode(lhs[lhs_idx]);
        sublhs = lhs.substr(lhs_idx, nBytes);
        lhs_idx += (nBytes - 1);
        for(std::size_t dist_j = 1, rhs_idx = 0;
            dist_j <= rhs_len; ++dist_j, ++rhs_idx)
        {
            nBytes = nBytesCode(rhs[rhs_idx]);
            subrhs = rhs.substr(rhs_idx, nBytes);
            rhs_idx += (nBytes - 1);
            if(sublhs == subrhs)
            {
                editDist[dist_i][dist_j] = editDist[dist_i - 1][dist_j -
                    1];
            }
            else
            {
                editDist[dist_i][dist_j] =
                    triple_min(editDist[dist_i][dist_j - 1] + 1,
                               editDist[dist_i - 1][dist_j] + 1,
                               editDist[dist_i - 1][dist_j - 1] + 1);
            }
        }
    }
    return editDist[lhs_len][rhs_len];
}

KeyRecommander::KeyRecommander(const string& query,const TcpConnectionPtr& conn):
    _queryWord(query),
    _conn(conn)
{

}

void KeyRecommander::doQuery()
{
    queryIndexTable();
    response();
}

void KeyRecommander::queryIndexTable()
{
    if(_queryWord.size()==0)
    {
        std::cout<<"messgae not send\n";
    }
    Dictionary* diction = Dictionary::createInstance();
    map<string,set<int>> & indexTable = diction->getIndexTable();
    vector<pair<string,int>> & dict = diction->getDict();
    size_t wordLen = _queryWord.size();
    for(size_t idx = 0;idx < wordLen;)
    {
        int len = getUtf8ByteType(_queryWord[idx]);
        string word = _queryWord.substr(idx,len);
        CandidateResult can;
        set<int> wordFreq = indexTable[word];
        int maxIdx = statistic(wordFreq);
        can._word = dict[maxIdx].first;
        can._dist = distance(can._word);
        can._freq = wordFreq.size();
        _resultQue.push(can);
        idx += len;
    }
}

int KeyRecommander::statistic(set<int> &iset)
{
    Dictionary* diction = Dictionary::createInstance();
    vector<pair<string,int>> &dict = diction->getDict();
    int max = -1;
    int idx;
    for(set<int>::iterator it = iset.begin();it != iset.end();++it)
    {
        int dist = distance(dict[*it].first);
        if(dist>max)
        {
            idx = *it;
            max = dist;
        }
    }
    return idx;
}

void KeyRecommander::response()
{
    json msg;
    int count = 0;
    if(_resultQue.empty())
    {
        std::cout<<"resultQue is empty\n";
    }
    while(!_resultQue.empty() && count<5)
    {
        msg.push_back(_resultQue.top()._word);
        _resultQue.pop();
        ++count;
    }
    std::cout << "msg = " << msg.dump() << "\n";        // TODO rm
    std::cout << "msgsize = " << msg.dump().size() << "\n";
    _conn->send(msg.dump());
}