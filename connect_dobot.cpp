#include "DobotDll_x64/DobotDll.h"
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <thread>

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

void go()
{
    IODO io;
    io.address = 16;
    bool hop_hey = true;

    int j = 0;
    do {
        j++;
        io.level = hop_hey;

        for(int i = 0; !SetIODO(&io, 0, NULL); i++ )
        {
            if(i > 100)
                break;
        }
        std::cout << 9 << std::endl;
        if(j > 10)
            break;
    }   
    while(1);
}

int main()
{
    //DisconnectDobot();
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


    uint64_t queuedCmdIndex = 0;
    PTPCmd cmd;
    cmd.ptpMode = 0;
    cmd.x = 200;
    cmd.y = 0;
    cmd.z = 0;
    cmd.r = 0;


    result = ConnectDobot(devsList[0], 115200, NULL, NULL, NULL);
    if(result == DobotConnect_NoError)
        std::cout << "Connect Success!!" << std::endl;
    else if(result == DobotConnect_NotFound)
        std::cout << "Dobot interface was not found!!" << std::endl;
    else if(result == DobotConnect_Occupied)
        std::cout << "Dobot interface is occupied or unavailable" << std::endl;

   // SetQueuedCmdForceStopExec();

    EMotorS mt;
    mt.isEnabled = 1;
    mt.distance = 100000;
    mt.speed = 1000;
    mt.index = 0;

   //SetPTPCmd(&cmd, 0, &queuedCmdIndex);
    IODI io;
    io.address = 4;
    io.level = 0;

    // while(1)
    // {
    //     int res = GetIODI(&io);

    //     std::cout << res << " " << (int)io.level << std::endl;
    // }

   // while(1)
    //{

           SetCmdTimeout(3000);
    SetQueuedCmdClear();
    SetQueuedCmdStartExec();
    
        GetQueuedCmdCurrentIndex(&queuedCmdIndex);
       // queuedCmdIndex--;
       SetEMotorS(&mt, 1, &queuedCmdIndex);
         //  mt.speed = 0;

    sleep(3);
    SetQueuedCmdForceStopExec();
         //  SetEMotorS(&mt, 0, &queuedCmdIndex);

        //break;
   // }

 
//works POMP
    // std::thread vacuum(go);

    // vacuum.detach();

    // int i = 0;
    // sleep(5);

    // for(int i = 0; i < 2; i++)
    // {
    //     SetPTPCmd(&cmd, 0, &queuedCmdIndex);

    //     sleep(3);

    //     IODO io;
    //     io.address = 11;
    //     io.level = 1;

    //     while(1)
    //     {
    //         SetIODO(&io, 0, &queuedCmdIndex); 
    //         sleep(2);
    //         break;
    //     }

    //     io.level = 0;

    //     while(1)
    //     {
    //         SetIODO(&io, 0, &queuedCmdIndex); 
    //         sleep(2);
    //         break;
    //     } 
    // }

    // IODO io;
    // io.address = 16;
    // bool hop_hey = false;

    // io.level = hop_hey;

    // for(int i = 0; !SetIODO(&io, 0, NULL); i++ )
    // {
    //     if(i > 100)
    //         break;
    // }



    DisconnectDobot();
    delete [] devsChr;
    for(int i = 0; i < maxDevCount ; i++)
        delete[] devsList[i];
    delete[] devsList;
}