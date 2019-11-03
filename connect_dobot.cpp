#include "DobotDll_x64/DobotDll.h"
#include <iostream>
#include <string.h>

int split(char **dst, char* str, const char* spl)
{
    int n = 0;
    char* result = NULL;
    result = strtok(str, spl);

    while(result != NULL)
    {
        strcpy(dst[n++], result);
        result = strtok(NULL, spl);
    }

    return n;
}

int main()
{
    int result;
    int maxDevCount = 100;
    int maxDevLen = 20;

    char* devsChr = new char[maxDevCount * maxDevLen]();
    char **devsList = new char*[maxDevCount]();
    for(int i = 0 ; i < maxDevCount ; i++)
        devsList[i] = new char[maxDevLen]();

    SearchDobot(devsChr, 1024);
    split(devsList, devsChr, "");
    std::cout << "Device's Port is " << devsList[0] << std::endl;

    result = ConnectDobot(devsList[0], 115200, NULL, NULL, NULL);
    if(result == DobotConnect_NoError)
        std::cout << "Connect Success!!" << std::endl;
    else if(result == DobotConnect_NotFound)
        std::cout << "Dobot interface was not found!!" << std::endl;
    else if(result == DobotConnect_Occupied)
        std::cout << "Dobot interface is occupied or unavailable" << std::endl;

    DisconnectDobot();
    delete [] devsChr;
    for(int i = 0; i < maxDevCount ; i++)
        delete[] devsList[i];
    delete[] devsList;
}