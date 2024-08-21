#ifndef __KeyRecommander_h__
#define __KeyRecommander_h__

#include <string>
#include <set>
#include <queue>
#include <vector>
#include <iostream>
#include "TcpServer.h"
#include "TcpConnection.h"
#include "Dictionary.h"
#include "CandidateResult.h"

using std::set;
using std::string;
using std::priority_queue;
using std::vector;

class KeyRecommander{
public:
    KeyRecommander(const string& query,const TcpConnectionPtr& conn);
    void doQuery();
    void queryIndexTable();
    int statistic(set<int> &iset);
    int distance(const string &rhs);
    void response();
private:
    string _queryWord;
    TcpConnectionPtr _conn;
    priority_queue<CandidateResult,vector<CandidateResult>,Compare> _resultQue;
};

size_t nBytesCode(const char ch);
int getUtf8ByteType(unsigned char c);
std::size_t length(const std::string &str);
int triple_min(const int &a, const int &b, const int &c);

#endif
