#include <iostream>
#include "hvhmi.h"

using namespace std;

int main()
{
    hvHMI * pclHMI = new hvHMI;

    pclHMI->create();
    pclHMI->init();
    pclHMI->run();

    delete pclHMI;
    pclHMI = NULL;
    return 0;
}
