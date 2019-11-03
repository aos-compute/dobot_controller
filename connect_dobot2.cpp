#include "DobotDll_x64/DobotDll.h"
#include <iostream>

int main()
{
    int result = ConnectDobot(NULL, 115200, NULL, NULL, NULL);

    if(result == DobotConnect_NoError)
        std::cout << "Connect Success!!" << std::endl;
    else if(result == DobotConnect_NotFound)
        std::cout << "Dobot interface was not found!!" << std::endl;
    else if(result == DobotConnect_Occupied)
        std::cout << "Dobot interface is occupied or unavailable" << std::endl;

    DisconnectDobot();
    
    return 0;
}