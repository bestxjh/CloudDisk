#include "../include/PageLib.h"
#include "../include/DirScanner.h"
#include "../include/Configuration.h"

int main()
{
//    Configuration& con = Configuration::getInstance();
    DirScanner dir;
    PageLib lib(dir);
    lib.create();
    return 0;
}
