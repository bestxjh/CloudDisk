#ifndef __CandidateResult_H__
#define __CandidateResult_H__

#include <string>
using std::string;

class CandidateResult{
public:
    CandidateResult();
    CandidateResult(string word,int dreq,int dist);
    friend struct Compare;
    string _word;
    int _freq;
    int _dist;
};

struct Compare{
    bool operator()(const CandidateResult& c1,const CandidateResult& c2)
    {
        if(c1._dist == c2._dist)
        {
            if(c1._freq == c2._freq)
            {
                return c1._word>c2._word;
            }
            return c1._freq > c2._freq;
        }
        return c1._dist>c2._dist;
    }
};

#endif
