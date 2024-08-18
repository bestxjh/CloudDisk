#include "../include/DicProducer.h"

void pushCnYuLiao(const string dir,vector<string> &_files)
{
    DIR* path = opendir(dir.c_str());
  
    struct dirent* entry;
    while((entry=readdir(path))!=nullptr)
    {
        string fileName = entry->d_name;
        if(fileName == "." || fileName == "..")
        {
            continue;
        }

        string lastPath = dir + "/" + fileName;
        
        struct stat file_stat;
        if(stat(lastPath.c_str(),&file_stat) == 0 &&S_ISREG(file_stat.st_mode))
        {
            _files.emplace_back(lastPath);
        }
    }
}

void getStopCn(const string path,map<string,bool> &_stopCn)
{
    std::ifstream ifs(path);
    string line;
    while(getline(ifs,line))
    {
        std::istringstream iss(line);
        string word;
        while(iss>>word)
        {
            _stopCn[word] = true;
        }
    }
    ifs.close();
    // for(map<string,bool>::iterator it = _stopCn.begin();it!=_stopCn.end();++it)
    // {
    //     std::cout<<it->first<<" "<<it->second<<"\n";
    // }
}

void getStopEng(const string path,map<string,bool> & _stopEng)
{
    std::ifstream ifs(path);
    string line;
    while(getline(ifs,line))
    {
        std::istringstream iss(line);
        string word;
        while(iss>>word)
            _stopEng[word] = true;
    }
    ifs.close();
    // for(map<string,bool>::iterator it = _stopEng.begin();it!=_stopEng.end();++it)
    // {
    //     std::cout<<it->first<<" "<<it->second<<"\n";
    // }
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

DicProducer::DicProducer(const string dir,SplitTool* tool):
    _cuttor(tool)
{
    pushCnYuLiao(dir,_files);
    getStopCn("../data/stop_words_zh.txt",_stopCn);
    getStopEng("../data/stop_words_eng.txt",_stopEng);
}

DicProducer::~DicProducer() 
{
}

void DicProducer::buildEnDict()
{
    //英文词典
    std::ifstream offile("../data/The_Holy_Bible.txt");
    map<string,int> _map;
    string line;
    while(getline(offile,line)){
        size_t low = 0;
        size_t fast = 0;
        size_t lineSize= line.size();
        while(fast<lineSize)
        {
            if(isalpha(line[fast])&&isupper(line[fast]))
            {
                line[fast] = tolower(line[fast]);
            }

            if(!isalpha(line[fast]))
            {
                if(fast>low)
                {
                    string word(line,low,fast-low);
                    if(!_stopEng.count(word))
                    {
                        _map[word]++;
                    }
                }
                low = fast+1;
            }
            fast++;
        }

        //std::cout<<"106\n";
        if(fast>low)
        {
            string word(line,low,fast-low);
            _map[word]++;
        }
    }
    
    for(map<string,int>::iterator it = _map.begin();it!=_map.end();++it)
    {
        _dictEnd.emplace_back(it->first,it->second);
    }
    offile.close();
}

void DicProducer::buildCnDict()
{
    //中文词典
    map<string,int> frquery;
    for(int i = 0;i<_files.size();++i)
    {
        std::ifstream ifs(_files[i]);
        string line;
        while(getline(ifs,line))
        {
            vector<string> words = _cuttor->cut(line);
            for(int j = 0;j<words.size();++j)
            {
                size_t wordsLen = words[j].size();
                string chinese;
                for(size_t index = 0;index<wordsLen;)
                {
                    int temp = getUtf8ByteType(words[j][index]);
                    if(temp>2)
                    {
                        chinese+=words[j].substr(index,temp);
                    }
                    index += temp;
                }
                if(_stopCn.count(chinese))
                {
                    continue;
                }
                    
                frquery[words[j]]++;  
            }
        }
        ifs.close();
    }

    for(map<string,int>::iterator it = frquery.begin(); it!=frquery.end();++it)
    {
        _dictCn.emplace_back(it->first,it->second);
    }
}

void DicProducer::createIndex()
{
    //英文
    int num = _dictEnd.size();
    for(int index = 0;index<num;index++)
    {
        string word = _dictEnd[index].first;
        size_t wordLen = word.size();
        for(size_t low = 1;low<=wordLen;++low)
        {
            string input = word.substr(0,low);
            _indexEnd[input].insert(index);
        }
    }
    
//中文

    int dictCnLen = _dictCn.size();
    for(size_t index = 0;index<dictCnLen;index++)
    {
        string word = _dictCn[index].first;
        size_t len = word.size();
        int temp;
        for (size_t start = 0; start < len; ) {
            temp = getUtf8ByteType(word[0]);
            string chinese = word.substr(start,temp);
            start += temp;
            _indexCn[chinese].insert(index);
        }
    }

}

void DicProducer::store()
{

    buildEnDict();
    buildCnDict();
    createIndex();
    //英文词典

    std::ofstream dictEng("../data/dict_eng.txt");

    for(vector<pair<string,int>>::iterator it = _dictEnd.begin(); it!=_dictEnd.end();++it)
    {
        dictEng<<it->first<<" "<<it->second<<"\n";
    }

    dictEng.close();

    //英文索引

    std::ofstream indexWordsEng("../data/index_words_eng.txt");
    for(map<string,set<int>>::iterator it = _indexEnd.begin();it!= _indexEnd.end();++it)
    {
        indexWordsEng<<it->first<<" ";
        for(int num:it->second)
        {
            indexWordsEng<<num<<" ";
        }
        indexWordsEng<<"\n";
    }
    indexWordsEng.close();
    


    //中文词典

    std::ofstream dict_cn("../data/dict_cn.txt");
    for(vector<pair<string,int>>::iterator it = _dictCn.begin(); it!=_dictCn.end();++it)
    {
        dict_cn<<it->first<<" "<<it->second<<"\n";
    }
    dict_cn.close();

    //中文索引
    std::ofstream indexWordsCn("../data/index_words_cn.txt");
    for(map<string,set<int>>::iterator it = _indexCn.begin();it!= _indexCn.end();++it)
    {
        indexWordsCn<<it->first<<" ";
        for(int num:it->second)
        {
            indexWordsCn<<num<<" ";
        }
        indexWordsCn<<"\n";
    }
    indexWordsCn.close();
}

