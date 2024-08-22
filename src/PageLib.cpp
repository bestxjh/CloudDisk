#include "../include/PageLib.h"

PageLib::PageLib(DirScanner& dirScanner)
    :_dirScanner(dirScanner)
{
    _files = dirScanner.getFiles();    
}

PageLib::~PageLib(){

}

void PageLib::create()
{
    string path = Configuration::getInstance().getValue("dat","ripepage");
    
    std::fstream ofs(path,std::ios::binary | std::ios::in | std::ios::out | std::ios::ate | std::ios::trunc);
    int pid = 0;
    for(size_t i =0;i<_files.size();++i)
    {
        cout<<_files[i]<<"\n";
    }
    
    for(size_t idx = 0; idx<_files.size(); ++idx)
    {
        //std::fstream ofs(_files[pid],std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
        XMLDocument doc;
        doc.LoadFile(_files[idx].c_str());
        if(doc.ErrorID()) {
            std::cerr << "Error loading file: " << _files[idx] << " - " << doc.ErrorStr() << "\n";
            continue;
        }
        if(doc.LoadFile(_files[idx].c_str()) != XML_SUCCESS)
        {
            std::cerr<<"LoadFile fail"<<_files[idx]<<"\n";
            continue ;
        }

        std::cout<<_files[idx]<<" is reading\n";
        XMLElement *itenNode = doc.RootElement();
        if(!itenNode)
        {
            std::cerr<<"Invalid XML";
            return ;
        }
        std::cout<<_files[idx]<<" is reading\n";
        for(XMLElement* item = itenNode->FirstChildElement("channel")->FirstChildElement("item");item;item = item->NextSiblingElement("item"))
        {
            const string title = item->FirstChildElement("title")?item->FirstChildElement("title")->GetText():"";

            string url = item->FirstChildElement("link")? item->FirstChildElement("link")->GetText():"";

             string content = item->FirstChildElement("description")?item->FirstChildElement("description")->GetText():"";

            std::regex reg("<[^>]+>");
            content = regex_replace(content,reg,"");

             WebPage web(
               url,
               title,
               content
               );

               int start = ofs.tellp();
               string word =  "<doc>\n\t<docid>"+std::to_string(pid)
               +"</docid>\n\t<title>"+title
               +"</title>\n\t<link>"+url
               +"</link>\n\t<content>"+content+"</content>\n</doc>\n";
               //int end = word.size();
               ofs<<word;
               ofs.flush();
               int end = ofs.tellp(); 
               _offsetLib[pid] = std::make_pair(start,end);
               pid++;           
        }

        cout<<_files[idx]<< "have finish\n";

    }

    store();
}


void PageLib::store()//存储网页库和文件偏移
{
    string path = Configuration::getInstance().getValue("dat","offset");
    std::ofstream ofs(path,std::ios::trunc);
    for(map<int,pair<int,int>>::iterator it = _offsetLib.begin();it!=_offsetLib.end();++it)
    {
        ofs<<it->first<<" "<<it->second.first<<" "<<it->second.second<<"\n";
    }
}
