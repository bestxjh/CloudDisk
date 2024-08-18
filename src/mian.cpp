#include "../include/SplitTool.h"
#include "../include/SplitToolCppJieba.h"
#include "../include/DicProducer.h"

int main()
{
    SplitTool* tool = new SplitToolCppJieba();
    //tool->getInstance();
    DicProducer dirc("../data/art",tool);
    dirc.store();
    return 0;
}
