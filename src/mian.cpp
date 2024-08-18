#include "../include/SplitTool.h"
#include "../include/SplitToolCppJieba.h"
#include "../include/DicProducer.h"

int main()
{
    SplitTool* tool;
    DicProducer dirc("../data/art",tool);
    dirc.buildEnDict();
    return 0;
}
