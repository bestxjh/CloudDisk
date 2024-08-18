#include "../include/DicProducer.h"


DicProducer::DicProducer(const string dir,SplitTool* tool):
    _cuttor(tool)
{
    std::cout<<"hello\n";
    DIR* path = opendir(dir.c_str());
    struct dirent* entry;
    while((entry=readdir(path))!=nullptr)
    {
        string fileName = entry->d_name;
        if(fileName == "." || fileName == "..")
        {
            continue;
        }

        string lastPath = fileName + "/" + fileName;
        
        struct stat file_stat;
        if(stat(lastPath.c_str(),&file_stat) == 0 &&S_ISREG(file_stat.st_mode))
        {
            _files.emplace_back(lastPath);
        }
    }
}

DicProducer::~DicProducer() 
{
}

void DicProducer::buildEnDict()
{
    std::cout<<"34\n";
    //英文词典
    std::ifstream offile("../data/The_Holy_Bible.txt");
    map<string,int> _map;
    string line;
    while(getline(offile,line)){
        size_t low = 0;
        size_t fast = 0;
        while(fast<line.size())
        {
            if(isupper(line[fast]))
            {
                line[fast] = tolower(line[fast]);
            }

            if(!isalpha(line[fast]) && line[fast]!='\r' && line[fast]!='\n')
            {
                if(fast>low)
                {
                    string word(line,low,fast-low);
                    _map[word]++;
                }
                low = fast+1;
            }
            fast++;
        }

        if(fast>low)
        {
            string word(line,low,fast-low);
            _map[word]++;
        }
    }

    std::ofstream ofs("../data/index_words_end.txt");
    
    for(map<string,int>::iterator it = _map.begin();it!=_map.end();++it)
    {
        _dictEnd.emplace_back(it->first,it->second);
        ofs<<it->first<<"\n";
    }
    
}

void DicProducer::buildCnDict()
{
    //中文词典
}

void DicProducer::createIndex()
{
   
}

void DicProducer::store()
{

}

