#include "../include/CandidateResult.h"

CandidateResult::CandidateResult()
{

}


CandidateResult::CandidateResult(string word,int dreq,int dist):
    _word(word),
    _freq(dreq),
    _dist(dist)

{

}

